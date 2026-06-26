#include "telemetry.h"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"

#include "app_mqtt.h"
#include "wifi_setup.h"

static const char *TAG = "telemetry";

#define TELEM_HEARTBEAT_INTERVAL_MS  10000
#define TELEM_EVENT_QUEUE_DEPTH      32
#define TELEM_TOPIC_MAX              96
#define TELEM_PAYLOAD_MAX            384

/* ----- queued-while-offline events -------------------------------------- */
typedef enum {
    EVT_WIFI_DOWN = 0,
    EVT_WIFI_UP,
    EVT_MQTT_DOWN,
    EVT_MQTT_UP,
} telem_kind_t;

typedef struct {
    int64_t  uptime_us;
    uint8_t  kind;
    int      d1;   /* raw_reason | err_type */
    int      d2;   /* rssi_at_drop | sock_errno */
} telem_event_t;

static telem_event_t s_ring[TELEM_EVENT_QUEUE_DEPTH];
static size_t        s_ring_head = 0;
static size_t        s_ring_count = 0;

/* ----- running counters / last-known fields ----------------------------- */
static uint32_t s_wifi_drops          = 0;
static uint32_t s_mqtt_drops          = 0;
static int      s_last_wifi_reason    = 0;
static int      s_last_mqtt_err_type  = 0;
static int      s_last_mqtt_sock_err  = 0;
static int      s_last_mqtt_tls_esp   = 0;
static int      s_last_mqtt_tls_stack = 0;
static int      s_last_mqtt_conn_rc   = 0;
/* Last RSSI we sampled in a heartbeat — used to annotate "wifi_down" events
 * with the signal level the device saw right before it lost the AP. */
static int8_t   s_last_rssi           = 0;
static bool     s_rssi_valid          = false;

static bool     s_mqtt_up             = false;
static char     s_topic_telem[TELEM_TOPIC_MAX];
static char     s_topic_events[TELEM_TOPIC_MAX];

/* ----- forward decls ---------------------------------------------------- */
static void publish_event(const telem_event_t *ev);
static void flush_queue(void);
static void enqueue(telem_kind_t k, int d1, int d2);
static void on_wifi_link_event(int kind, int raw_reason);

/* ----- helpers ---------------------------------------------------------- */

static uint32_t uptime_s(void) {
    return (uint32_t)(esp_timer_get_time() / 1000000);
}

static const char *wifi_state_str(void) {
    switch (wifi_setup_get_state()) {
    case WIFI_SETUP_STATE_IDLE:        return "idle";
    case WIFI_SETUP_STATE_SCANNING:    return "scanning";
    case WIFI_SETUP_STATE_CONNECTING:  return "connecting";
    case WIFI_SETUP_STATE_CONNECTED:   return "connected";
    case WIFI_SETUP_STATE_FAILED:      return "failed";
    }
    return "?";
}

/* ----- ring buffer ------------------------------------------------------ */

static void enqueue(telem_kind_t k, int d1, int d2) {
    telem_event_t *slot;
    if (s_ring_count < TELEM_EVENT_QUEUE_DEPTH) {
        slot = &s_ring[(s_ring_head + s_ring_count) % TELEM_EVENT_QUEUE_DEPTH];
        s_ring_count++;
    } else {
        /* Drop oldest so the most recent events near the reconnect window
         * survive — that's the bit that's most useful for diagnosis. */
        slot = &s_ring[s_ring_head];
        s_ring_head = (s_ring_head + 1) % TELEM_EVENT_QUEUE_DEPTH;
    }
    slot->uptime_us = esp_timer_get_time();
    slot->kind = (uint8_t)k;
    slot->d1 = d1;
    slot->d2 = d2;
}

static void flush_queue(void) {
    while (s_ring_count > 0 && mqtt_client_is_connected()) {
        telem_event_t ev = s_ring[s_ring_head];
        s_ring_head = (s_ring_head + 1) % TELEM_EVENT_QUEUE_DEPTH;
        s_ring_count--;
        publish_event(&ev);
    }
}

/* ----- publish ---------------------------------------------------------- */

static void publish_event(const telem_event_t *ev) {
    char payload[TELEM_PAYLOAD_MAX];
    uint32_t up = (uint32_t)(ev->uptime_us / 1000000);
    int n;
    switch ((telem_kind_t)ev->kind) {
    case EVT_WIFI_DOWN:
        n = snprintf(payload, sizeof(payload),
                     "{\"uptime_s\":%lu,\"kind\":\"wifi_down\","
                     "\"raw_reason\":%d,\"rssi_at_drop\":%d}",
                     (unsigned long)up, ev->d1, ev->d2);
        break;
    case EVT_WIFI_UP:
        n = snprintf(payload, sizeof(payload),
                     "{\"uptime_s\":%lu,\"kind\":\"wifi_up\"}",
                     (unsigned long)up);
        break;
    case EVT_MQTT_DOWN:
        n = snprintf(payload, sizeof(payload),
                     "{\"uptime_s\":%lu,\"kind\":\"mqtt_down\","
                     "\"err_type\":%d,\"sock_errno\":%d}",
                     (unsigned long)up, ev->d1, ev->d2);
        break;
    case EVT_MQTT_UP:
        n = snprintf(payload, sizeof(payload),
                     "{\"uptime_s\":%lu,\"kind\":\"mqtt_up\"}",
                     (unsigned long)up);
        break;
    default:
        return;
    }
    if (n <= 0) return;
    mqtt_client_publish(s_topic_events, payload, n);
}

static void publish_heartbeat(void) {
    int8_t   rssi    = 0;
    uint8_t  bssid[6] = {0};
    uint8_t  ch      = 0;
    bool     link_ok = (wifi_setup_get_link_info(&rssi, bssid, &ch) == ESP_OK);
    if (link_ok) {
        s_last_rssi  = rssi;
        s_rssi_valid = true;
    }

    char ipbuf[20];
    wifi_setup_format_ip(ipbuf, sizeof(ipbuf));

    char payload[TELEM_PAYLOAD_MAX];
    int n;
    if (link_ok) {
        n = snprintf(payload, sizeof(payload),
            "{\"uptime_s\":%lu,\"wifi\":\"%s\","
            "\"rssi\":%d,\"bssid\":\"%02x:%02x:%02x:%02x:%02x:%02x\",\"ch\":%u,"
            "\"ip\":\"%s\",\"mqtt\":\"%s\","
            "\"wifi_drops\":%lu,\"mqtt_drops\":%lu,"
            "\"last_wifi_rsn\":%d,\"last_mqtt_etyp\":%d,\"last_mqtt_err\":%d,"
            "\"heap\":%u}",
            (unsigned long)uptime_s(), wifi_state_str(),
            (int)rssi, bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5],
            (unsigned)ch, ipbuf,
            s_mqtt_up ? "up" : "down",
            (unsigned long)s_wifi_drops, (unsigned long)s_mqtt_drops,
            s_last_wifi_reason, s_last_mqtt_err_type, s_last_mqtt_sock_err,
            (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    } else {
        n = snprintf(payload, sizeof(payload),
            "{\"uptime_s\":%lu,\"wifi\":\"%s\","
            "\"ip\":\"%s\",\"mqtt\":\"%s\","
            "\"wifi_drops\":%lu,\"mqtt_drops\":%lu,"
            "\"last_wifi_rsn\":%d,\"last_mqtt_etyp\":%d,\"last_mqtt_err\":%d,"
            "\"heap\":%u}",
            (unsigned long)uptime_s(), wifi_state_str(),
            ipbuf, s_mqtt_up ? "up" : "down",
            (unsigned long)s_wifi_drops, (unsigned long)s_mqtt_drops,
            s_last_wifi_reason, s_last_mqtt_err_type, s_last_mqtt_sock_err,
            (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    }
    if (n > 0) mqtt_client_publish(s_topic_telem, payload, n);
}

/* ----- callbacks -------------------------------------------------------- */

static void on_wifi_link_event(int kind, int raw_reason) {
    /* Runs on the WiFi event task. mqtt_client_publish is safe to call from
     * any task — esp-mqtt queues to its own task. */
    if (kind == 0 /* wifi_down */) {
        s_wifi_drops++;
        s_last_wifi_reason = raw_reason;
        int rssi_drop = s_rssi_valid ? (int)s_last_rssi : 0;
        /* Mark RSSI stale: we just lost the link, so the cached value no
         * longer represents a current signal — the next "rssi_at_drop" would
         * be a lie until heartbeat re-samples after reconnect. */
        s_rssi_valid = false;
        ESP_LOGW(TAG, "EVENT wifi_down raw=%d rssi_at_drop=%d", raw_reason, rssi_drop);
        if (mqtt_client_is_connected()) {
            telem_event_t ev = {
                .uptime_us = esp_timer_get_time(),
                .kind = EVT_WIFI_DOWN, .d1 = raw_reason, .d2 = rssi_drop,
            };
            publish_event(&ev);
        } else {
            enqueue(EVT_WIFI_DOWN, raw_reason, rssi_drop);
        }
    } else {
        ESP_LOGI(TAG, "EVENT wifi_up");
        if (mqtt_client_is_connected()) {
            telem_event_t ev = {
                .uptime_us = esp_timer_get_time(),
                .kind = EVT_WIFI_UP, .d1 = 0, .d2 = 0,
            };
            publish_event(&ev);
        } else {
            enqueue(EVT_WIFI_UP, 0, 0);
        }
    }
}

void telemetry_on_mqtt_state(bool connected) {
    if (connected) {
        s_mqtt_up = true;
        ESP_LOGI(TAG, "EVENT mqtt_up — flushing %u queued events",
                 (unsigned)s_ring_count);
        /* Publish the mqtt_up edge itself first, then drain anything that
         * happened while we were offline. Order in the queue is preserved
         * because it's a FIFO. */
        telem_event_t ev = {
            .uptime_us = esp_timer_get_time(),
            .kind = EVT_MQTT_UP, .d1 = 0, .d2 = 0,
        };
        publish_event(&ev);
        flush_queue();
    } else {
        if (s_mqtt_up) s_mqtt_drops++;
        s_mqtt_up = false;
        ESP_LOGW(TAG, "EVENT mqtt_down etype=%d sock_errno=%d",
                 s_last_mqtt_err_type, s_last_mqtt_sock_err);
        /* MQTT is by definition down right now — queue for later. */
        enqueue(EVT_MQTT_DOWN, s_last_mqtt_err_type, s_last_mqtt_sock_err);
    }
}

void telemetry_on_mqtt_error(int error_type, int sock_errno,
                             int tls_last_esp_err, int tls_stack_err,
                             int connect_return_code) {
    s_last_mqtt_err_type  = error_type;
    s_last_mqtt_sock_err  = sock_errno;
    s_last_mqtt_tls_esp   = tls_last_esp_err;
    s_last_mqtt_tls_stack = tls_stack_err;
    s_last_mqtt_conn_rc   = connect_return_code;
    ESP_LOGW(TAG, "mqtt_err captured: etype=%d sock=%d tls_esp=0x%x tls_stack=0x%x conn_rc=%d",
             error_type, sock_errno, tls_last_esp_err, tls_stack_err,
             connect_return_code);
}

/* ----- init / tick ------------------------------------------------------ */

void telemetry_init(void) {
    char host[16];
    mqtt_client_hostname(host, sizeof(host));
    snprintf(s_topic_telem,  sizeof(s_topic_telem),  "local/spotter/%s/telemetry", host);
    snprintf(s_topic_events, sizeof(s_topic_events), "local/spotter/%s/events",    host);
    wifi_setup_set_link_event_callback(on_wifi_link_event);
    ESP_LOGI(TAG, "telemetry topics: %s , %s", s_topic_telem, s_topic_events);
}

void telemetry_tick(void) {
    static int64_t s_last_heartbeat_us = 0;
    int64_t now = esp_timer_get_time();
    if ((now - s_last_heartbeat_us) < ((int64_t)TELEM_HEARTBEAT_INTERVAL_MS * 1000)) {
        return;
    }
    s_last_heartbeat_us = now;
    if (!mqtt_client_is_connected()) return;
    publish_heartbeat();
    /* Opportunistic drain in case events were queued during a brief MQTT
     * blip but the state callback fired before we got here. */
    if (s_ring_count > 0) flush_queue();
}
