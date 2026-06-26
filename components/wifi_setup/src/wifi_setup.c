#include "wifi_setup.h"

#include <string.h>

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

static const char *TAG = "wifi_setup";

#define WIFI_CONNECT_TIMEOUT_MS 12000
#define WIFI_MAX_RETRIES        3

static wifi_setup_state_t        s_state       = WIFI_SETUP_STATE_IDLE;
static wifi_setup_state_cb_t     s_state_cb    = NULL;
static wifi_setup_link_event_cb_t s_link_cb    = NULL;
static void                     *s_user_ctx    = NULL;
static esp_netif_t              *s_sta_netif   = NULL;
static uint32_t                  s_ip          = 0;
static uint8_t                   s_retries     = 0;
static bool                      s_initialized = false;
static wifi_setup_fail_reason_t  s_fail_reason = WIFI_SETUP_FAIL_NONE;
/* Latched true the first time we get an IP. From then on, any disconnect is
 * treated as a transient drop that must keep retrying — the device is a fixed
 * in-trailer monitor, not a hand-held that legitimately wanders out of range,
 * so giving up on the AP would leave the user with a dead alarm panel and no
 * UI affordance to recover short of a power cycle. */
static bool                      s_was_ever_connected = false;
/* Set by wifi_setup_connect_persistent() for the boot-time auto-connect with
 * saved credentials. While true, the disconnect handler retries forever
 * instead of giving up after WIFI_MAX_RETRIES — so a power cycle with the
 * router off doesn't dump the user into the setup screen. Cleared by
 * wifi_setup_connect() (user-initiated, must keep its fail/retry feedback)
 * and wifi_setup_disconnect(). */
static bool                      s_persistent_retry = false;

static wifi_setup_network_t s_scan[WIFI_SETUP_MAX_SCAN_RESULTS];
static size_t                s_scan_count = 0;

static void set_state(wifi_setup_state_t st)
{
    if (s_state == st) return;
    s_state = st;
    if (s_state_cb) s_state_cb(st, s_user_ctx);
}

/* Map ESP-IDF's wifi_err_reason_t code into the bucketed reason exposed by
 * this component. Keep the mapping narrow — only call out the ones we can
 * give actionable UI advice for. Everything else lands in UNKNOWN. */
static wifi_setup_fail_reason_t bucket_disconnect_reason(int reason)
{
    switch (reason) {
    case WIFI_REASON_AUTH_FAIL:
    case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
    case WIFI_REASON_HANDSHAKE_TIMEOUT:
    case WIFI_REASON_MIC_FAILURE:
    case WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT:
    case WIFI_REASON_IE_IN_4WAY_DIFFERS:
    case WIFI_REASON_PAIRWISE_CIPHER_INVALID:
    case WIFI_REASON_GROUP_CIPHER_INVALID:
    case WIFI_REASON_AKMP_INVALID:
    case WIFI_REASON_802_1X_AUTH_FAILED:
        return WIFI_SETUP_FAIL_BAD_PASSWORD;
    case WIFI_REASON_NO_AP_FOUND:
    case WIFI_REASON_BEACON_TIMEOUT:
        return WIFI_SETUP_FAIL_AP_NOT_FOUND;
    case WIFI_REASON_ASSOC_EXPIRE:
    case WIFI_REASON_AUTH_EXPIRE:
    case WIFI_REASON_ASSOC_TOOMANY:
    case WIFI_REASON_CONNECTION_FAIL:
        return WIFI_SETUP_FAIL_TIMEOUT;
    default:
        return WIFI_SETUP_FAIL_UNKNOWN;
    }
}

static uint8_t rssi_to_bars(int8_t rssi)
{
    if (rssi >= -55) return 3;
    if (rssi >= -70) return 2;
    if (rssi >= -85) return 1;
    return 0;
}

static int rssi_desc(const void *a, const void *b)
{
    const wifi_setup_network_t *na = a, *nb = b;
    return nb->rssi - na->rssi;
}

static void on_scan_done(void)
{
    uint16_t count = WIFI_SETUP_MAX_SCAN_RESULTS;
    wifi_ap_record_t records[WIFI_SETUP_MAX_SCAN_RESULTS] = {0};

    esp_err_t err = esp_wifi_scan_get_ap_records(&count, records);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "scan_get_ap_records: %s", esp_err_to_name(err));
        set_state(WIFI_SETUP_STATE_IDLE);
        return;
    }

    /* Dedup by SSID, keep strongest RSSI. */
    s_scan_count = 0;
    for (uint16_t i = 0; i < count && s_scan_count < WIFI_SETUP_MAX_SCAN_RESULTS; i++) {
        const wifi_ap_record_t *r = &records[i];
        if (r->ssid[0] == '\0') continue;

        bool dup = false;
        for (size_t j = 0; j < s_scan_count; j++) {
            if (strncmp(s_scan[j].ssid, (const char *)r->ssid, WIFI_SETUP_SSID_MAX) == 0) {
                if (r->rssi > s_scan[j].rssi) {
                    s_scan[j].rssi  = r->rssi;
                    s_scan[j].bars  = rssi_to_bars(r->rssi);
                    memcpy(s_scan[j].bssid, r->bssid, WIFI_SETUP_BSSID_LEN);
                }
                dup = true;
                break;
            }
        }
        if (dup) continue;

        wifi_setup_network_t *n = &s_scan[s_scan_count++];
        strlcpy(n->ssid, (const char *)r->ssid, WIFI_SETUP_SSID_MAX);
        memcpy(n->bssid, r->bssid, WIFI_SETUP_BSSID_LEN);
        n->rssi   = r->rssi;
        n->bars   = rssi_to_bars(r->rssi);
        n->locked = r->authmode != WIFI_AUTH_OPEN;
    }
    qsort(s_scan, s_scan_count, sizeof(s_scan[0]), rssi_desc);

    ESP_LOGI(TAG, "scan complete — %u unique networks", (unsigned)s_scan_count);
    set_state(WIFI_SETUP_STATE_IDLE);
}

static void wifi_event_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT) {
        switch (id) {
        case WIFI_EVENT_STA_START:
            ESP_LOGI(TAG, "STA started");
            break;
        case WIFI_EVENT_SCAN_DONE:
            on_scan_done();
            break;
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGI(TAG, "STA connected — waiting for IP");
            break;
        case WIFI_EVENT_STA_DISCONNECTED: {
            wifi_event_sta_disconnected_t *e = data;
            int raw_reason = e ? e->reason : -1;
            ESP_LOGW(TAG, "STA disconnected, reason=%d (state=%d retries=%u ever_connected=%d persistent=%d)",
                     raw_reason, (int)s_state, (unsigned)s_retries, (int)s_was_ever_connected, (int)s_persistent_retry);
            if (s_link_cb) s_link_cb(0 /* wifi_down */, raw_reason);
            s_ip = 0;
            if (s_was_ever_connected || s_persistent_retry) {
                /* Post-IP drop. The state machine flips to CONNECTING so the
                 * UI's connectivity indicator (and the connectivity-alarm
                 * monitor) sees that we've lost the link. Reconnect attempts
                 * continue forever — esp_wifi_connect() rate-limits itself
                 * internally per attempt, so this is not a tight loop. */
                s_retries = 0;
                if (s_state != WIFI_SETUP_STATE_CONNECTING) {
                    set_state(WIFI_SETUP_STATE_CONNECTING);
                }
                esp_wifi_connect();
            } else if (s_state == WIFI_SETUP_STATE_CONNECTING && s_retries < WIFI_MAX_RETRIES) {
                s_retries++;
                ESP_LOGI(TAG, "reconnect attempt %u/%u", s_retries, WIFI_MAX_RETRIES);
                esp_wifi_connect();
            } else if (s_state == WIFI_SETUP_STATE_CONNECTED
                    || s_state == WIFI_SETUP_STATE_CONNECTING) {
                s_fail_reason = bucket_disconnect_reason(raw_reason);
                set_state(WIFI_SETUP_STATE_FAILED);
            }
            break;
        }
        default:
            break;
        }
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *e = data;
        s_ip = e->ip_info.ip.addr;
        s_retries = 0;
        s_fail_reason = WIFI_SETUP_FAIL_NONE;
        s_was_ever_connected = true;
        ESP_LOGI(TAG, "got IP " IPSTR, IP2STR(&e->ip_info.ip));
        if (s_link_cb) s_link_cb(1 /* wifi_up */, 0);
        set_state(WIFI_SETUP_STATE_CONNECTED);
    }
}

void wifi_setup_set_link_event_callback(wifi_setup_link_event_cb_t cb)
{
    s_link_cb = cb;
}

esp_err_t wifi_setup_get_link_info(int8_t *rssi, uint8_t bssid[6], uint8_t *channel)
{
    if (s_state != WIFI_SETUP_STATE_CONNECTED) return ESP_ERR_INVALID_STATE;
    wifi_ap_record_t info = {0};
    esp_err_t err = esp_wifi_sta_get_ap_info(&info);
    if (err != ESP_OK) return err;
    if (rssi)    *rssi    = info.rssi;
    if (channel) *channel = info.primary;
    if (bssid)   memcpy(bssid, info.bssid, 6);
    return ESP_OK;
}

wifi_setup_fail_reason_t wifi_setup_get_last_failure_reason(void)
{
    return s_fail_reason;
}

esp_err_t wifi_setup_init(wifi_setup_state_cb_t state_cb, void *user_ctx)
{
    s_state_cb = state_cb;
    s_user_ctx = user_ctx;

    if (s_initialized) return ESP_OK;

    ESP_ERROR_CHECK(esp_netif_init());
    esp_err_t err = esp_event_loop_create_default();
    if (err == ESP_ERR_INVALID_STATE) err = ESP_OK;  /* Already created by app */
    ESP_ERROR_CHECK(err);

    s_sta_netif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL, NULL));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    s_initialized = true;
    ESP_LOGI(TAG, "initialized (STA started)");
    return ESP_OK;
}

esp_err_t wifi_setup_set_hostname(const char *hostname)
{
    if (!hostname || !hostname[0]) return ESP_ERR_INVALID_ARG;
    if (!s_sta_netif) return ESP_ERR_INVALID_STATE;
    esp_err_t r = esp_netif_set_hostname(s_sta_netif, hostname);
    if (r == ESP_OK) {
        ESP_LOGI(TAG, "hostname set to '%s'", hostname);
    } else {
        ESP_LOGW(TAG, "esp_netif_set_hostname failed: %s", esp_err_to_name(r));
    }
    return r;
}

esp_err_t wifi_setup_scan_start(void)
{
    if (!s_initialized) return ESP_ERR_INVALID_STATE;
    if (s_state == WIFI_SETUP_STATE_SCANNING) return ESP_OK;

    set_state(WIFI_SETUP_STATE_SCANNING);
    wifi_scan_config_t scan = {
        .ssid = NULL, .bssid = NULL, .channel = 0,
        .show_hidden = false, .scan_type = WIFI_SCAN_TYPE_ACTIVE,
        .scan_time.active = { .min = 100, .max = 200 },
    };
    return esp_wifi_scan_start(&scan, false /* async */);
}

size_t wifi_setup_get_scan_results(wifi_setup_network_t *out, size_t out_cap)
{
    if (!out || out_cap == 0) return 0;
    size_t n = s_scan_count < out_cap ? s_scan_count : out_cap;
    memcpy(out, s_scan, n * sizeof(s_scan[0]));
    return n;
}

static esp_err_t connect_internal(const char *ssid, const char *password, bool persistent)
{
    if (!ssid || ssid[0] == '\0') return ESP_ERR_INVALID_ARG;
    if (!s_initialized) return ESP_ERR_INVALID_STATE;

    wifi_config_t cfg = {0};
    strlcpy((char *)cfg.sta.ssid,     ssid,     sizeof(cfg.sta.ssid));
    if (password) strlcpy((char *)cfg.sta.password, password, sizeof(cfg.sta.password));
    cfg.sta.threshold.authmode = password && password[0] ? WIFI_AUTH_WPA2_PSK : WIFI_AUTH_OPEN;
    cfg.sta.pmf_cfg.capable    = true;
    cfg.sta.pmf_cfg.required   = false;

    s_retries = 0;
    s_fail_reason = WIFI_SETUP_FAIL_NONE;
    /* New connection attempt — until the new SSID actually gives us an IP,
     * treat this as a fresh initial setup so the bad-password / AP-not-found
     * paths can surface FAILED instead of looping forever. Persistent mode
     * overrides that and keeps retrying. */
    s_was_ever_connected = false;
    s_persistent_retry   = persistent;
    set_state(WIFI_SETUP_STATE_CONNECTING);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &cfg));
    return esp_wifi_connect();
}

esp_err_t wifi_setup_connect(const char *ssid, const char *password)
{
    return connect_internal(ssid, password, false);
}

esp_err_t wifi_setup_connect_persistent(const char *ssid, const char *password)
{
    return connect_internal(ssid, password, true);
}

esp_err_t wifi_setup_disconnect(void)
{
    if (!s_initialized) return ESP_OK;
    s_ip = 0;
    s_was_ever_connected = false;
    s_persistent_retry   = false;
    set_state(WIFI_SETUP_STATE_IDLE);
    return esp_wifi_disconnect();
}

wifi_setup_state_t wifi_setup_get_state(void) { return s_state; }
uint32_t            wifi_setup_get_ip(void)    { return s_ip; }

void wifi_setup_format_ip(char *buf, size_t buf_sz)
{
    if (!buf || buf_sz == 0) return;
    if (s_ip == 0) {
        /* Plain hyphen — Montserrat's built-in glyph subset has no em-dash. */
        strlcpy(buf, "-", buf_sz);
        return;
    }
    snprintf(buf, buf_sz, "%lu.%lu.%lu.%lu",
             (unsigned long)( s_ip        & 0xff),
             (unsigned long)((s_ip >>  8) & 0xff),
             (unsigned long)((s_ip >> 16) & 0xff),
             (unsigned long)((s_ip >> 24) & 0xff));
}
