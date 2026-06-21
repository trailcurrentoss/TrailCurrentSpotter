#include "app_mqtt.h"
#include "mqtt_client.h" /* ESP-IDF esp_mqtt library */
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "pendant_config.h"

/* Defined in main/spoor_alarms.c. Forward-declared here so this component
 * doesn't have to REQUIRES-import the main archive (which ESP-IDF doesn't
 * allow). The symbol resolves at link time. */
extern void spoor_alarms_handle_inputs(int addr, uint8_t inputs);
extern void device_alarms_handle_state(int channel, int state);

/* MQTT variable setters (vars.c) */
extern void set_var_battery_soc_percentage(int32_t value);
extern void set_var_battery_voltage(float value);
extern void set_var_solar_wattage(int32_t value);
extern void set_var_solar_status(const char *value);
extern void set_var_current_power_consumption_in_watts(const char *value);
extern void set_var_current_latitude(float value);
extern void set_var_current_longitude(float value);
extern void set_var_current_altitude_value(float value);
extern void set_var_current_speed_value(int32_t value);
extern void set_var_current_course_over_ground(float value);
extern void set_var_gnss_mode(const char *value);
extern void set_var_current_humidity_value(float value);
extern void set_var_current_temperature_value(float value);
extern void set_var_number_of_satellites(int32_t value);
extern void set_var_current_date_time(const char *value);
extern void set_var_wifi_connected(bool value);
extern void set_var_power_time_to_go_measurement(float value);

static const char *TAG = "MQTT";

#define NVS_NAMESPACE "sd_config"

/* Connection settings loaded from NVS */
static char s_host[128] = {0};
static uint16_t s_port = 8883;
static char s_username[64] = {0};
static char s_password[128] = {0};
static char *s_ca_cert_pem = NULL;

static esp_mqtt_client_handle_t s_client = NULL;
static volatile bool s_connected = false;
static mqtt_client_state_cb_t s_state_cb = NULL;

void mqtt_client_set_state_callback(mqtt_client_state_cb_t cb)
{
    s_state_cb = cb;
}

/* Queue for passing received messages from MQTT task to main loop */
typedef struct {
    char topic[128];
    char payload[512];
    int payload_len;
} mqtt_message_t;

static QueueHandle_t s_incoming_queue = NULL;

/* Forward declarations */
static void process_message(const char *topic, const char *payload, int length);
static void process_gnss_mode(int mode);

/* --- MQTT event handler (runs in MQTT task context) --- */

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                                int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "Connected to broker");
        s_connected = true;
        if (s_state_cb) s_state_cb(true);

        /* Subscribe to all data topics */
        esp_mqtt_client_subscribe(s_client, "local/energy/status", 0);
        esp_mqtt_client_subscribe(s_client, "local/airquality/temphumid", 0);
        esp_mqtt_client_subscribe(s_client, "local/airquality/status", 0);
        esp_mqtt_client_subscribe(s_client, "local/gps/latlon", 0);
        esp_mqtt_client_subscribe(s_client, "local/gps/alt", 0);
        esp_mqtt_client_subscribe(s_client, "local/gps/details", 0);
        esp_mqtt_client_subscribe(s_client, "local/gps/time", 0);
        /* Switchback digital-input broadcasts, one per Switchback address
         * (0..2). The Headwaters can-bridge republishes CAN 0x12/0x13/0x14
         * to local/spoor/<addr>/inputs as {"inputs": <0..255>}. */
        esp_mqtt_client_subscribe(s_client, "local/spoor/+/inputs", 0);
        /* Switchback relay-output broadcasts, one per relay channel
         * (1..24). Headwaters publishes {"state": 0|1} per channel.
         * Feeds the device-alarm module (relay-state-driven alarms). */
        esp_mqtt_client_subscribe(s_client, "local/relays/+/status", 0);
        ESP_LOGI(TAG, "Subscribed to all topics");
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGW(TAG, "Disconnected from broker (was_connected=%d)", (int)s_connected);
        s_connected = false;
        if (s_state_cb) s_state_cb(false);
        break;

    case MQTT_EVENT_BEFORE_CONNECT:
        ESP_LOGI(TAG, "BEFORE_CONNECT — opening socket to broker");
        break;

    case MQTT_EVENT_DATA: {
        /* Skip fragmented messages */
        if (event->current_data_offset != 0 ||
            event->data_len != event->total_data_len) {
            ESP_LOGW(TAG, "Skipping fragmented message");
            break;
        }

        mqtt_message_t msg = {0};
        int topic_len = (event->topic_len < (int)sizeof(msg.topic) - 1)
                            ? event->topic_len
                            : (int)sizeof(msg.topic) - 1;
        int data_len = (event->data_len < (int)sizeof(msg.payload) - 1)
                           ? event->data_len
                           : (int)sizeof(msg.payload) - 1;

        memcpy(msg.topic, event->topic, topic_len);
        msg.topic[topic_len] = '\0';
        memcpy(msg.payload, event->data, data_len);
        msg.payload[data_len] = '\0';
        msg.payload_len = data_len;

        ESP_LOGD(TAG, "RX: %s (%d bytes)", msg.topic, msg.payload_len);

        if (s_incoming_queue) {
            xQueueSend(s_incoming_queue, &msg, 0);
        }
        break;
    }

    case MQTT_EVENT_ERROR:
        if (event->error_handle) {
            esp_mqtt_error_codes_t *err = event->error_handle;
            const char *etype = "?";
            switch (err->error_type) {
            case MQTT_ERROR_TYPE_NONE:                 etype = "NONE"; break;
            case MQTT_ERROR_TYPE_TCP_TRANSPORT:        etype = "TCP_TRANSPORT"; break;
            case MQTT_ERROR_TYPE_CONNECTION_REFUSED:   etype = "CONNECTION_REFUSED"; break;
            case MQTT_ERROR_TYPE_SUBSCRIBE_FAILED:     etype = "SUBSCRIBE_FAILED"; break;
            }
            ESP_LOGE(TAG, "MQTT ERROR: type=%d(%s) tls_last_esp_err=0x%x "
                          "tls_stack_err=0x%x tls_cert_flags=0x%x "
                          "transport_sock_errno=%d(%s) connect_return_code=%d",
                     err->error_type, etype,
                     err->esp_tls_last_esp_err, err->esp_tls_stack_err,
                     err->esp_tls_cert_verify_flags,
                     err->esp_transport_sock_errno,
                     err->esp_transport_sock_errno
                         ? strerror(err->esp_transport_sock_errno) : "ok",
                     err->connect_return_code);
            ESP_LOGE(TAG, "free heap: total=%u internal=%u largest_internal=%u",
                     (unsigned)esp_get_free_heap_size(),
                     (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
                     (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
        }
        break;

    default:
        break;
    }
}

/* --- Public API --- */

bool mqtt_client_load_settings(void) {
    /* Source of truth: pendant_config (touchscreen-entered, NVS namespace
     * "spotter"). Fall back to the legacy "sd_config" namespace for setups
     * that pre-date the in-UI MQTT setup screen. */
    const pendant_config_t *pc = pendant_config_get();
    if (pc && pc->mqtt_host[0]) {
        strlcpy(s_host,     pc->mqtt_host, sizeof(s_host));
        strlcpy(s_username, pc->mqtt_user, sizeof(s_username));
        strlcpy(s_password, pc->mqtt_pass, sizeof(s_password));
        s_port = pc->mqtt_port ? pc->mqtt_port : 8883;
        ESP_LOGI(TAG, "Loaded from pendant_config: %s:%u user=%s",
                 s_host, (unsigned)s_port, s_username);
        return strlen(s_host) > 0 && strlen(s_username) > 0;
    }

    /* Legacy path — sd_config NVS namespace */
    nvs_handle_t nvs;
    esp_err_t ret = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs);
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "No MQTT config in pendant_config or sd_config NVS");
        return false;
    }

    size_t len = sizeof(s_host);
    nvs_get_str(nvs, "mqttHost", s_host, &len);
    if (nvs_get_u16(nvs, "mqttPort", &s_port) != ESP_OK) s_port = 8883;
    len = sizeof(s_username);  nvs_get_str(nvs, "mqttUser", s_username, &len);
    len = sizeof(s_password);  nvs_get_str(nvs, "mqttPass", s_password, &len);

    /* CA cert support kept for compat — but we don't need it: insecure TLS
     * flags in sdkconfig.defaults make mbedtls accept any cert. */
    len = 0;
    if (nvs_get_str(nvs, "mqttCaCert", NULL, &len) == ESP_OK && len > 0) {
        if (s_ca_cert_pem) free(s_ca_cert_pem);
        s_ca_cert_pem = malloc(len);
        if (s_ca_cert_pem) {
            nvs_get_str(nvs, "mqttCaCert", s_ca_cert_pem, &len);
            ESP_LOGI(TAG, "CA cert loaded from legacy NVS (%d bytes)", (int)len);
        }
    }
    nvs_close(nvs);

    bool has_config = strlen(s_host) > 0 && strlen(s_username) > 0;
    if (has_config) {
        ESP_LOGI(TAG, "Loaded from legacy sd_config NVS: %s:%u user=%s",
                 s_host, (unsigned)s_port, s_username);
    }
    return has_config;
}

void mqtt_client_connect(void) {
    if (strlen(s_host) == 0 || strlen(s_username) == 0 ||
        strlen(s_password) == 0) {
        ESP_LOGW(TAG, "Cannot connect - missing MQTT configuration");
        return;
    }

    /* Insecure TLS — accept any cert (incl. self-signed). The TLS layer skips
     * verification because CONFIG_ESP_TLS_INSECURE=y and
     * CONFIG_ESP_TLS_SKIP_SERVER_CERT_VERIFY=y are set in sdkconfig.defaults.
     * No CA cert needs to live on the device. */

    /* Create incoming message queue */
    if (!s_incoming_queue) {
        s_incoming_queue = xQueueCreate(16, sizeof(mqtt_message_t));
    }

    /* Build URI */
    char uri[192];
    snprintf(uri, sizeof(uri), "mqtts://%s:%d", s_host, s_port);

    /* Generate client ID from MAC */
    uint8_t mac[6] = {0};
    esp_wifi_get_mac(WIFI_IF_STA, mac);
    char client_id[32];
    snprintf(client_id, sizeof(client_id), "tc-remote-%02x%02x", mac[4], mac[5]);

    ESP_LOGI(TAG, "Connecting to %s as %s (client_id=%s)", uri, s_username, client_id);
    ESP_LOGI(TAG, "  heap before connect: free=%u largest=%u",
             (unsigned)esp_get_free_heap_size(),
             (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));

    /* Destroy previous client if reconnecting. Important: without this, repeated
     * mqtt_client_connect() calls would leak the previous esp_mqtt_client and its
     * TLS socket, which the broker would see as a parade of zombie sessions. */
    if (s_client) {
        ESP_LOGW(TAG, "  destroying previous esp_mqtt_client first (was non-NULL)");
        esp_mqtt_client_stop(s_client);
        esp_mqtt_client_destroy(s_client);
        s_client = NULL;
    }

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = uri,
        /* Accept any TLS cert (incl. self-signed). The actual cert-chain
         * verification is bypassed by CONFIG_ESP_TLS_INSECURE +
         * CONFIG_ESP_TLS_SKIP_SERVER_CERT_VERIFY in sdkconfig.defaults; this
         * flag covers the CN match check inside esp-mqtt itself. */
        .broker.verification.skip_cert_common_name_check = true,
        .credentials.client_id = client_id,
        .credentials.username = s_username,
        .credentials.authentication.password = s_password,
        .network.timeout_ms = 10000,
        .session.keepalive = 30,
        .buffer.size = 1024,
    };
    /* Intentionally NOT setting .broker.verification.certificate — leaving it
     * NULL combined with the kconfig insecure flags above makes mbedtls accept
     * whatever the broker presents. If a CA cert ever IS provided via NVS, it
     * will get wired in here; otherwise we run insecure. */
    if (s_ca_cert_pem) {
        mqtt_cfg.broker.verification.certificate = s_ca_cert_pem;
        ESP_LOGI(TAG, "Using saved CA cert from NVS");
    } else {
        ESP_LOGI(TAG, "No CA cert — running with insecure TLS (cert verification skipped)");
    }

    s_client = esp_mqtt_client_init(&mqtt_cfg);
    if (!s_client) {
        ESP_LOGE(TAG, "Failed to init MQTT client");
        return;
    }

    esp_mqtt_client_register_event(s_client, ESP_EVENT_ANY_ID,
                                   mqtt_event_handler, NULL);

    esp_err_t err = esp_mqtt_client_start(s_client);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start MQTT client: %s", esp_err_to_name(err));
    }
}

void mqtt_client_process_messages(void) {
    if (!s_incoming_queue) {
        vTaskDelay(pdMS_TO_TICKS(10));
        return;
    }

    mqtt_message_t msg;
    if (xQueueReceive(s_incoming_queue, &msg, pdMS_TO_TICKS(10)) == pdTRUE) {
        process_message(msg.topic, msg.payload, msg.payload_len);
        while (xQueueReceive(s_incoming_queue, &msg, 0) == pdTRUE) {
            process_message(msg.topic, msg.payload, msg.payload_len);
        }
    }
}

bool mqtt_client_is_connected(void) {
    return s_connected;
}

int mqtt_client_publish(const char *topic, const char *payload, int payload_len) {
    if (!s_connected || !s_client) {
        ESP_LOGW(TAG, "Not connected, cannot publish to %s", topic);
        return -1;
    }
    int msg_id = esp_mqtt_client_publish(s_client, topic, payload, payload_len, 0, 0);
    ESP_LOGI(TAG, "Published to %s (msg_id=%d)", topic, msg_id);
    return msg_id;
}

/* --- GNSS mode helper --- */

static void process_gnss_mode(int mode) {
    switch (mode) {
    case 1: set_var_gnss_mode("GPS"); break;
    case 2: set_var_gnss_mode("Beidou"); break;
    case 3: set_var_gnss_mode("GPS + Beidou"); break;
    case 4: set_var_gnss_mode("GLONASS"); break;
    case 5: set_var_gnss_mode("GPS + GLONASS"); break;
    case 6: set_var_gnss_mode("Beidou + GLONASS"); break;
    case 7: set_var_gnss_mode("GPS + Beidou + GLONASS"); break;
    default: set_var_gnss_mode("Unknown"); break;
    }
}

/* --- Process incoming MQTT message --- */

static void process_message(const char *topic, const char *payload, int length) {
    cJSON *doc = cJSON_ParseWithLength(payload, length);
    if (!doc) {
        ESP_LOGW(TAG, "JSON parse error for topic: %s", topic);
        return;
    }

    /* local/energy/status — emitted by TrailCurrentHeadwaters can-bridge.
     * Fields per containers/backend/src/services/can-bridge.js:
     *   battery_percent, battery_voltage, solar_watts, charge_type,
     *   consumption_watts, time_remaining_minutes (from shunt) */
    if (strcmp(topic, "local/energy/status") == 0) {
        cJSON *bp = cJSON_GetObjectItem(doc, "battery_percent");
        cJSON *bv = cJSON_GetObjectItem(doc, "battery_voltage");
        cJSON *sw = cJSON_GetObjectItem(doc, "solar_watts");
        cJSON *ct = cJSON_GetObjectItem(doc, "charge_type");
        cJSON *cw = cJSON_GetObjectItem(doc, "consumption_watts");
        cJSON *trm = cJSON_GetObjectItem(doc, "time_remaining_minutes");

        if (bp) set_var_battery_soc_percentage((int32_t)bp->valuedouble);
        if (bv) set_var_battery_voltage((float)bv->valuedouble);
        if (sw) set_var_solar_wattage((int32_t)sw->valuedouble);
        if (ct && ct->valuestring) set_var_solar_status(ct->valuestring);
        if (cw) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%d W", (int)cw->valuedouble);
            set_var_current_power_consumption_in_watts(buf);
        }
        /* Shunt time-to-go arrives in MINUTES; vars.c formatter expects hours
         * by default. Convert here so the rest of the chain stays simple. */
        if (trm) {
            set_var_power_time_to_go_measurement((float)(trm->valuedouble / 60.0));
        }
    }
    /* local/airquality/temphumid */
    else if (strcmp(topic, "local/airquality/temphumid") == 0) {
        cJSON *temp_f = cJSON_GetObjectItem(doc, "tempInF");
        cJSON *humid = cJSON_GetObjectItem(doc, "humidity");

        if (temp_f) set_var_current_temperature_value((float)temp_f->valuedouble);
        if (humid) set_var_current_humidity_value((float)humid->valuedouble);
    }
    /* local/gps/latlon */
    else if (strcmp(topic, "local/gps/latlon") == 0) {
        cJSON *lat = cJSON_GetObjectItem(doc, "latitude");
        cJSON *lon = cJSON_GetObjectItem(doc, "longitude");
        if (lat) set_var_current_latitude((float)lat->valuedouble);
        if (lon) set_var_current_longitude((float)lon->valuedouble);
    }
    /* local/gps/alt */
    else if (strcmp(topic, "local/gps/alt") == 0) {
        cJSON *alt = cJSON_GetObjectItem(doc, "altitudeFeet");
        if (alt) set_var_current_altitude_value((float)alt->valuedouble);
    }
    /* local/gps/details */
    else if (strcmp(topic, "local/gps/details") == 0) {
        cJSON *sats = cJSON_GetObjectItem(doc, "numberOfSatellites");
        cJSON *spd = cJSON_GetObjectItem(doc, "speedOverGround");
        cJSON *crs = cJSON_GetObjectItem(doc, "courseOverGround");
        cJSON *gnss = cJSON_GetObjectItem(doc, "gnssMode");

        if (sats) set_var_number_of_satellites(sats->valueint);
        /* Bearing publishes via CAN as (knots × 100); Headwaters' can-bridge
         * forwards the raw scaled value to local/gps/details. Convert to MPH
         * (knots × 1.15078) here so the toolbar speed widget shows MPH
         * directly. Headwaters' web UI uses the same constant 0.0115078. */
        if (spd) set_var_current_speed_value(
                    (int32_t)(spd->valuedouble * 0.0115078 + 0.5));
        if (crs) set_var_current_course_over_ground((float)crs->valuedouble);
        if (gnss) process_gnss_mode(gnss->valueint);
    }
    /* local/gps/time */
    else if (strcmp(topic, "local/gps/time") == 0) {
        cJSON *yr = cJSON_GetObjectItem(doc, "year");
        cJSON *mo = cJSON_GetObjectItem(doc, "month");
        cJSON *dy = cJSON_GetObjectItem(doc, "day");
        cJSON *hr = cJSON_GetObjectItem(doc, "hour");
        cJSON *mn = cJSON_GetObjectItem(doc, "minute");
        cJSON *sc = cJSON_GetObjectItem(doc, "second");

        if (yr && mo && dy && hr && mn && sc) {
            char datetime_str[32];
            snprintf(datetime_str, sizeof(datetime_str),
                     "%04d-%02d-%02d %02d:%02d:%02d",
                     yr->valueint, mo->valueint, dy->valueint,
                     hr->valueint, mn->valueint, sc->valueint);
            set_var_current_date_time(datetime_str);
        }
    }
    /* local/spoor/<addr>/inputs — Switchback DI bitmask, addr 0..2 */
    else if (strncmp(topic, "local/spoor/", 12) == 0) {
        int addr = atoi(topic + 12);
        cJSON *inputs_j = cJSON_GetObjectItem(doc, "inputs");
        if (inputs_j) {
            int bits = inputs_j->valueint & 0xFF;
            ESP_LOGD(TAG, "spoor rx: addr=%d bits=0x%02x", addr, bits);
            spoor_alarms_handle_inputs(addr, (uint8_t)bits);
        } else {
            ESP_LOGW(TAG, "spoor rx: topic=%s missing 'inputs' field", topic);
        }
    }
    /* local/relays/<channel>/status — Switchback relay state, channel 1..24 */
    else if (strncmp(topic, "local/relays/", 13) == 0) {
        int channel = atoi(topic + 13);
        cJSON *state_j = cJSON_GetObjectItem(doc, "state");
        if (state_j) {
            int state = state_j->valueint ? 1 : 0;
            ESP_LOGD(TAG, "relay rx: ch=%d state=%d", channel, state);
            device_alarms_handle_state(channel, state);
        } else {
            ESP_LOGW(TAG, "relay rx: topic=%s missing 'state' field", topic);
        }
    }
    else {
        ESP_LOGD(TAG, "Unhandled topic: %s", topic);
    }

    cJSON_Delete(doc);
}
