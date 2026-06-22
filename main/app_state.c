#include "app_state.h"

#include <string.h>
#include "esp_log.h"
#include "lvgl.h"
#include "ui/screens.h"
#include "wifi_setup.h"
#include "pendant_config.h"
#include "app_mqtt.h"
#include "connectivity_alarm.h"

static const char *TAG = "app_state";
static app_state_t s_state = APP_STATE_BOOT;

extern void spotter_set_active_tab(int index);
extern void spotter_set_mqtt_connected(bool connected);
extern void spotter_mqtt_setup_enter(void);

/* ============================================================================
 * Per-row scan-list helpers. PageWifiSetup has 8 fixed rows (wifi_net_0..7),
 * each with a SSID label, a lock icon, a 3-bar signal indicator and an
 * invisible "tap target" button (wifi_net_act_0..7). The C code populates the
 * row text + visibility from the latest wifi_setup scan results.
 * ============================================================================ */
static void row_set_visible(int idx, bool visible)
{
    lv_obj_t *rows[8] = {
        objects.wifi_net_0, objects.wifi_net_1, objects.wifi_net_2, objects.wifi_net_3,
        objects.wifi_net_4, objects.wifi_net_5, objects.wifi_net_6, objects.wifi_net_7,
    };
    if (idx < 0 || idx >= 8 || !rows[idx]) return;
    if (visible) lv_obj_clear_flag(rows[idx], LV_OBJ_FLAG_HIDDEN);
    else         lv_obj_add_flag(rows[idx], LV_OBJ_FLAG_HIDDEN);
}

static void row_set_ssid(int idx, const char *ssid)
{
    lv_obj_t *labels[8] = {
        objects.wifi_net_ssid_0, objects.wifi_net_ssid_1, objects.wifi_net_ssid_2, objects.wifi_net_ssid_3,
        objects.wifi_net_ssid_4, objects.wifi_net_ssid_5, objects.wifi_net_ssid_6, objects.wifi_net_ssid_7,
    };
    if (idx < 0 || idx >= 8 || !labels[idx]) return;
    lv_label_set_text(labels[idx], ssid);
}

static void row_set_locked(int idx, bool locked)
{
    lv_obj_t *locks[8] = {
        objects.wifi_net_lock_0, objects.wifi_net_lock_1, objects.wifi_net_lock_2, objects.wifi_net_lock_3,
        objects.wifi_net_lock_4, objects.wifi_net_lock_5, objects.wifi_net_lock_6, objects.wifi_net_lock_7,
    };
    if (idx < 0 || idx >= 8 || !locks[idx]) return;
    if (locked) lv_obj_clear_flag(locks[idx], LV_OBJ_FLAG_HIDDEN);
    else        lv_obj_add_flag(locks[idx], LV_OBJ_FLAG_HIDDEN);
}

static void row_set_bars(int idx, uint8_t bars)
{
    lv_obj_t *b1[8] = {
        objects.wifi_net_bar1_0, objects.wifi_net_bar1_1, objects.wifi_net_bar1_2, objects.wifi_net_bar1_3,
        objects.wifi_net_bar1_4, objects.wifi_net_bar1_5, objects.wifi_net_bar1_6, objects.wifi_net_bar1_7,
    };
    lv_obj_t *b2[8] = {
        objects.wifi_net_bar2_0, objects.wifi_net_bar2_1, objects.wifi_net_bar2_2, objects.wifi_net_bar2_3,
        objects.wifi_net_bar2_4, objects.wifi_net_bar2_5, objects.wifi_net_bar2_6, objects.wifi_net_bar2_7,
    };
    lv_obj_t *b3[8] = {
        objects.wifi_net_bar3_0, objects.wifi_net_bar3_1, objects.wifi_net_bar3_2, objects.wifi_net_bar3_3,
        objects.wifi_net_bar3_4, objects.wifi_net_bar3_5, objects.wifi_net_bar3_6, objects.wifi_net_bar3_7,
    };
    if (idx < 0 || idx >= 8) return;
    /* bar visible = CHECKED state on a panel; clear means dim. */
    lv_obj_t *bars_arr[3] = { b1[idx], b2[idx], b3[idx] };
    for (int i = 0; i < 3; i++) {
        if (!bars_arr[i]) continue;
        if (i < bars) lv_obj_add_state(bars_arr[i], LV_STATE_CHECKED);
        else          lv_obj_clear_state(bars_arr[i], LV_STATE_CHECKED);
    }
}

void app_state_refresh_wifi_list(void)
{
    wifi_setup_network_t nets[WIFI_SETUP_MAX_SCAN_RESULTS];
    size_t n = wifi_setup_get_scan_results(nets, WIFI_SETUP_MAX_SCAN_RESULTS);
    for (int i = 0; i < 8; i++) {
        if (i < (int)n) {
            row_set_visible(i, true);
            row_set_ssid(i, nets[i].ssid);
            row_set_locked(i, nets[i].locked);
            row_set_bars(i, nets[i].bars);
        } else {
            row_set_visible(i, false);
        }
    }
    if (objects.wifi_scan_spinner) lv_obj_add_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    if (objects.wifi_scan_status) {
        char buf[48];
        snprintf(buf, sizeof(buf), n == 0 ? "No networks found" : "%u network%s found",
                 (unsigned)n, n == 1 ? "" : "s");
        lv_label_set_text(objects.wifi_scan_status, buf);
    }
}

void app_state_wifi_show_scanning(void)
{
    if (objects.wifi_scan_spinner) lv_obj_clear_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    if (objects.wifi_scan_status)  lv_label_set_text(objects.wifi_scan_status, "Scanning...");
}

void app_state_wifi_show_idle_message(const char *msg)
{
    if (objects.wifi_scan_spinner) lv_obj_add_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    if (objects.wifi_scan_status)  lv_label_set_text(objects.wifi_scan_status, msg);
}

/* Set the status_wifi_icon color across all 3 TopStatusBar instances. The
 * icon exists per-page (drive/alarms/setup_status_bar__status_wifi_icon)
 * because each page has its own user-widget instance. Color uses the project's
 * theme tables so the icon flips correctly with light/dark theme. */
void app_state_refresh_connection_display(void)
{
    bool connected = (wifi_setup_get_state() == WIFI_SETUP_STATE_CONNECTED);
    /* Pull theme colors from the EEZ-exported tables. COLOR_ID_SUCCESS is
     * the bright "on" green; COLOR_ID_WARNING is amber so a dropped link is
     * obvious at a glance instead of fading into muted chrome. */
    uint32_t c = connected
        ? theme_colors[active_theme_index][COLOR_ID_SUCCESS]
        : theme_colors[active_theme_index][COLOR_ID_WARNING];
    lv_color_t lc = lv_color_hex(c);

    lv_obj_t *icons[] = {
        objects.drive_status_bar__status_wifi_icon,
        objects.alarms_status_bar__status_wifi_icon,
        objects.setup_status_bar__status_wifi_icon,
    };
    for (size_t i = 0; i < sizeof(icons)/sizeof(*icons); i++) {
        if (icons[i]) {
            lv_obj_set_style_text_color(icons[i], lc, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

/* ============================================================================
 * wifi_setup state callback. Runs on the WiFi event task — bounce LVGL work
 * via lv_async_call so we don't touch the UI from a non-LVGL context.
 * ============================================================================ */
static void on_wifi_state(wifi_setup_state_t st, void *user_ctx);

static void async_refresh_list(void *arg)   { (void)arg; app_state_refresh_wifi_list(); }
static void async_show_scanning(void *arg)  { (void)arg; app_state_wifi_show_scanning(); }
static void async_state_ready(void *arg)    { (void)arg; app_state_set(APP_STATE_READY); }
static void async_state_setup(void *arg)    { (void)arg; app_state_set(APP_STATE_WIFI_SETUP); }
static void async_refresh_conn(void *arg)   { (void)arg; app_state_refresh_connection_display(); }
static void async_show_fail(void *arg)
{
    const char *msg = "Connection failed. Pick a network and try again.";
    switch (wifi_setup_get_last_failure_reason()) {
    case WIFI_SETUP_FAIL_BAD_PASSWORD:
        msg = "Incorrect password. Try again."; break;
    case WIFI_SETUP_FAIL_AP_NOT_FOUND:
        msg = "Network not in range. Rescan."; break;
    case WIFI_SETUP_FAIL_TIMEOUT:
        msg = "Timed out joining. Check signal."; break;
    default: break;
    }
    app_state_wifi_show_idle_message(msg);
}

static void async_state_mqtt_setup(void *arg)      { (void)arg; app_state_set(APP_STATE_MQTT_SETUP); }
static void async_state_mqtt_connecting(void *arg) { (void)arg; app_state_set(APP_STATE_MQTT_CONNECTING); }

/* Bounce the connectivity-alarm notifications onto the LVGL thread. The arg
 * encodes a bool: non-NULL = connected, NULL = disconnected. */
static void async_notify_conn_wifi(void *arg) { connectivity_alarm_set_wifi(arg != NULL); }
static void async_notify_conn_mqtt(void *arg) { connectivity_alarm_set_mqtt(arg != NULL); }

/* Decide what to do once WiFi is up. Three cases by current state:
 *   - APP_STATE_READY: boot-to-dashboard path. Start the MQTT client silently
 *     in the background (once); don't change UI state. The connectivity alarm
 *     dismisses itself when MQTT actually connects.
 *   - APP_STATE_WIFI_CONNECTING: user-initiated setup flow. Drive the normal
 *     progression to MQTT setup or MQTT connecting.
 *   - APP_STATE_MQTT_SETUP / anything else: don't disturb (user is finishing
 *     setup; WiFi just associated in the background).
 * Runs on LVGL thread (async_call target). */
static void async_wifi_up_next(void *arg)
{
    (void)arg;
    static bool s_mqtt_kicked = false;

    if (s_state == APP_STATE_READY) {
        if (!s_mqtt_kicked && pendant_config_has_mqtt()) {
            ESP_LOGI(TAG, "WiFi up on dashboard — starting MQTT client in background");
            if (mqtt_client_load_settings()) {
                mqtt_client_connect();
                s_mqtt_kicked = true;
            }
        }
        return;
    }
    if (s_state != APP_STATE_WIFI_CONNECTING) {
        return;
    }
    if (pendant_config_has_mqtt()) {
        app_state_set(APP_STATE_MQTT_CONNECTING);
        if (mqtt_client_load_settings()) {
            mqtt_client_connect();
            s_mqtt_kicked = true;
        }
    } else {
        app_state_set(APP_STATE_MQTT_SETUP);
    }
}

static void on_wifi_state(wifi_setup_state_t st, void *user_ctx)
{
    (void)user_ctx;
    ESP_LOGI(TAG, "wifi_setup state = %d", (int)st);
    /* Always refresh the wifi indicator on any state change so the icon
     * flips in real time. Bounce onto LVGL thread. */
    lv_async_call(async_refresh_conn, NULL);
    /* Tell the connectivity-alarm monitor. CONNECTED is the only state where
     * we actually have a working link; anything else (idle/scanning/
     * connecting/failed) counts as "no link". */
    lv_async_call(async_notify_conn_wifi,
                  (st == WIFI_SETUP_STATE_CONNECTED) ? (void *)1 : NULL);
    switch (st) {
    case WIFI_SETUP_STATE_IDLE:
        if (s_state == APP_STATE_WIFI_SETUP) {
            lv_async_call(async_refresh_list, NULL);
        }
        break;
    case WIFI_SETUP_STATE_SCANNING:
        if (s_state == APP_STATE_WIFI_SETUP) {
            lv_async_call(async_show_scanning, NULL);
        }
        break;
    case WIFI_SETUP_STATE_CONNECTED:
        /* WiFi just came up. Fire async_wifi_up_next regardless of current
         * state — it decides what to do based on s_state (boot-to-dashboard
         * vs. user-driven setup flow) and is a no-op for subsequent
         * reconnects once MQTT is already running. */
        lv_async_call(async_wifi_up_next, NULL);
        break;
    case WIFI_SETUP_STATE_FAILED:
        if (s_state == APP_STATE_WIFI_CONNECTING) {
            lv_async_call(async_show_fail, NULL);
            lv_async_call(async_state_setup, NULL);
        }
        break;
    default: break;
    }
}

/* MQTT state callback — bridges to spotter_set_mqtt_connected for the
 * top-toolbar label/dot, and advances the state machine to READY on first
 * successful connection. Runs on the MQTT task — bounce onto LVGL thread
 * with lv_async_call. */
static void async_apply_mqtt_connected(void *arg)
{
    spotter_set_mqtt_connected(arg != NULL);
}

/* Tap-anywhere-to-skip on the MQTT connecting spinner. Without this an
 * unreachable broker (server down, wrong config) traps the device on the
 * spinner with no escape. Once we install the handler it stays installed —
 * subsequent visits to this screen reuse it. The handler only fires while
 * we're still in MQTT_CONNECTING, so re-entering CONNECTING after a manual
 * skip still gives the user the same escape. */
static void mqtt_connecting_skip_cb(lv_event_t *e)
{
    (void)e;
    if (s_state == APP_STATE_MQTT_CONNECTING) {
        ESP_LOGI(TAG, "MQTT-connecting skipped by user — advancing to READY");
        app_state_set(APP_STATE_READY);
    }
}
static void mqtt_connecting_wire_skip(void)
{
    static bool wired = false;
    if (wired || !objects.page_mqtt_connecting) return;
    lv_obj_add_flag(objects.page_mqtt_connecting, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(objects.page_mqtt_connecting, mqtt_connecting_skip_cb,
                        LV_EVENT_CLICKED, NULL);
    wired = true;
}
static void async_state_ready_from_mqtt(void *arg) { (void)arg;
    if (s_state == APP_STATE_MQTT_CONNECTING) app_state_set(APP_STATE_READY);
}

static void on_mqtt_state(bool connected)
{
    ESP_LOGI(TAG, "mqtt connected = %d", (int)connected);
    /* Pass non-NULL for connected, NULL for disconnected. */
    lv_async_call(async_apply_mqtt_connected, connected ? (void *)1 : NULL);
    lv_async_call(async_notify_conn_mqtt,    connected ? (void *)1 : NULL);
    /* Advance to READY on the first MQTT result either way. If the broker is
     * unreachable we still want the dashboard usable; the MQTT client keeps
     * retrying in the background and the top-bar dot turns green when it
     * eventually connects. */
    lv_async_call(async_state_ready_from_mqtt, NULL);
}

/* ============================================================================
 * State transitions
 * ============================================================================ */
static void load_screen(lv_obj_t *target) { if (target) lv_scr_load(target); }

/* Disable LVGL's screen-level scrolling on the setup screens. Without this,
 * any drag on a child (the password textarea, the keyboard) is interpreted
 * as a screen scroll — the textarea slides off-screen on touch. The setup
 * screens don't actually need to scroll. */
static void make_unscrollable(lv_obj_t *screen)
{
    if (!screen) return;
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
}

void app_state_set(app_state_t next)
{
    /* Safety belt: never display the MQTT setup screen when MQTT creds are
     * already saved. If anything tries to route us there, redirect to the
     * connecting state instead — matches the WiFi pattern where saved creds
     * mean the setup screen is only reachable via Settings → Clear data. */
    if (next == APP_STATE_MQTT_SETUP && pendant_config_has_mqtt()) {
        ESP_LOGW(TAG, "MQTT_SETUP requested but MQTT creds saved — redirecting to MQTT_CONNECTING");
        next = APP_STATE_MQTT_CONNECTING;
        if (mqtt_client_load_settings()) {
            mqtt_client_connect();
        }
    }

    if (s_state == next) return;
    ESP_LOGI(TAG, "state %d -> %d", (int)s_state, (int)next);
    s_state = next;

    switch (next) {
    case APP_STATE_WIFI_SETUP:
        make_unscrollable(objects.page_wifi_setup);
        if (objects.wifi_password_panel)
            make_unscrollable(objects.wifi_password_panel);
        load_screen(objects.page_wifi_setup);
        app_state_wifi_show_scanning();
        wifi_setup_scan_start();
        break;
    case APP_STATE_WIFI_CONNECTING:
        load_screen(objects.page_wifi_connecting);
        break;
    case APP_STATE_MQTT_SETUP:
        if (objects.page_mqtt_setup) {
            make_unscrollable(objects.page_mqtt_setup);
            load_screen(objects.page_mqtt_setup);
            spotter_mqtt_setup_enter();  /* reset wizard to step 0 */
        } else {
            ESP_LOGW(TAG, "page_mqtt_setup not exported yet — skipping to READY");
            app_state_set(APP_STATE_READY);
        }
        break;
    case APP_STATE_MQTT_CONNECTING:
        if (objects.page_mqtt_connecting) {
            load_screen(objects.page_mqtt_connecting);
            mqtt_connecting_wire_skip();
        }
        break;
    case APP_STATE_READY:
        load_screen(objects.page_drive);
        spotter_set_active_tab(0);
        break;
    default:
        break;
    }
}

app_state_t app_state_get(void) { return s_state; }

esp_err_t app_state_init(void)
{
    ESP_ERROR_CHECK(wifi_setup_init(on_wifi_state, NULL));
    /* Advertise the device as "Spotter" via DHCP so it's easy to spot in the
     * router's connected-clients list (and discoverable via mDNS as
     * "Spotter.local" if mDNS is enabled later). */
    wifi_setup_set_hostname("Spotter");
    mqtt_client_set_state_callback(on_mqtt_state);

    /* Boot-time policy: a setup screen (WiFi or MQTT) is shown ONLY if the
     * corresponding credentials are missing. Anything else — including being
     * unable to associate with the AP or reach the broker at power-on — lands
     * on the dashboard, where the existing connectivity alarm already
     * communicates the loss. The setup screens are only reachable again via
     * Settings → Clear data.
     *
     * Runtime drops (connectivity lost after we were once up) are unaffected
     * — the connectivity_alarm continues to fire normally. */

    if (!pendant_config_has_wifi()) {
        ESP_LOGI(TAG, "no saved WiFi — entering WiFi setup");
        app_state_set(APP_STATE_WIFI_SETUP);
        return ESP_OK;
    }

    /* WiFi creds saved — start the auto-connect in the background regardless
     * of which screen we land on. Uses persistent retry so it keeps trying
     * forever rather than ever transitioning to STATE_FAILED. */
    const pendant_config_t *cfg = pendant_config_get();
    ESP_LOGI(TAG, "auto-connecting to saved SSID: %s", cfg->wifi_ssid);
    wifi_setup_connect_persistent(cfg->wifi_ssid, cfg->wifi_pass);

    if (!pendant_config_has_mqtt()) {
        ESP_LOGI(TAG, "no saved MQTT — entering MQTT setup (WiFi connects in background)");
        app_state_set(APP_STATE_MQTT_SETUP);
        return ESP_OK;
    }

    /* Both sets of creds saved — go straight to the dashboard. The MQTT
     * client is kicked off by on_wifi_state(CONNECTED) once WiFi associates;
     * the connectivity alarm raises on its own if either link is still down
     * when the debounce window elapses. */
    ESP_LOGI(TAG, "both creds saved — going directly to dashboard");
    app_state_set(APP_STATE_READY);
    return ESP_OK;
}

void app_state_set_mqtt_connected(bool connected)
{
    spotter_set_mqtt_connected(connected);
}
