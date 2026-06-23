#include "connectivity_alarm.h"

#include "esp_log.h"
#include "lvgl.h"

#include "app_state.h"
#include "ui/screens.h"

/* Defined in actions.c — wipes every MQTT-fed widget back to its placeholder
 * ("--", "-- V", "-- left", "No data"). Called here on any down-transition so
 * stale values aren't mistaken for live ones while the link is broken. */
extern void spotter_paint_placeholders(void);

/* Defined in main.c — paints the full-screen clock widgets (clock_value,
 * clock_ampm, clock_date). Called immediately on entering clock mode so the
 * screen is up-to-date before the next 2 Hz tick fires. */
extern void spotter_clock_paint_mode(bool force);

/* Defined in main.c — paints the three frozen-data stat cards on
 * PageClockMode (battery / solar / fresh) plus the "X min ago" label. */
extern void spotter_clock_paint_stats(void);

static const char *TAG = "conn_alarm";

/* The connectivity "alarm" no longer raises a red pulsing overlay with a
 * chime — that was noisy in the powered-on-but-not-towing case (the user is
 * driving without the trailer attached, WiFi is intentionally out of range,
 * and the device should just sit quietly and be useful as a clock).
 *
 * Behaviour now: when WiFi or MQTT goes down past the debounce window we
 * swap the active screen to PageClockMode, which carries a non-pulsing
 * warning strip ("No TrailCurrent Connection") and a large monospaced clock
 * fed from the RTC. The screen the user was on before is restored on
 * reconnect. No chime, no pulse, no acknowledge-required modal.
 *
 * Real alarms — switchback sensor trips, device-relay state changes — still
 * raise the full alarm overlay (with chime) via spotter_alarm_raise(). Only
 * connectivity loss is routed through PageClockMode. */

static bool         s_wifi_ok           = false;
static bool         s_mqtt_ok           = false;
static bool         s_in_clock_mode     = false;  /* PageClockMode is loaded by us */
static lv_obj_t    *s_prev_screen       = NULL;   /* screen to restore on reconnect */
static lv_timer_t  *s_debounce          = NULL;

/* ----- internal --------------------------------------------------------- */

static bool desired_clock_mode(void) { return !s_wifi_ok || !s_mqtt_ok; }

static void enter_clock_mode(void)
{
    if (s_in_clock_mode) return;
    if (!objects.page_clock_mode) {
        ESP_LOGW(TAG, "PageClockMode not exported yet — staying on current screen");
        return;
    }
    lv_obj_t *cur = lv_scr_act();
    if (cur != objects.page_clock_mode) {
        s_prev_screen = cur;
        lv_scr_load(objects.page_clock_mode);
    }
    s_in_clock_mode = true;
    spotter_clock_paint_mode(true);
    spotter_clock_paint_stats();
    ESP_LOGI(TAG, "Connectivity lost — switched to PageClockMode");
}

static void exit_clock_mode(void)
{
    if (!s_in_clock_mode) {
        s_prev_screen = NULL;
        return;
    }
    s_in_clock_mode = false;
    if (objects.page_clock_mode && lv_scr_act() == objects.page_clock_mode) {
        lv_obj_t *target = s_prev_screen ? s_prev_screen : objects.page_drive;
        if (target) lv_scr_load(target);
    }
    s_prev_screen = NULL;
    ESP_LOGI(TAG, "Connectivity restored — clock mode dismissed");
}

static void cancel_debounce(void)
{
    if (s_debounce) {
        lv_timer_del(s_debounce);
        s_debounce = NULL;
    }
}

static void debounce_fire_cb(lv_timer_t *t)
{
    (void)t;
    s_debounce = NULL;
    /* Only enter clock mode once the device is past setup — during WiFi /
     * MQTT setup the user is intentionally not yet connected, and bouncing
     * them off the setup screen mid-typing would be hostile. */
    if (app_state_get() != APP_STATE_READY) return;
    if (!desired_clock_mode()) return;          /* recovered during debounce */
    enter_clock_mode();
}

static void schedule_debounce(void)
{
    if (s_debounce) return;
    s_debounce = lv_timer_create(debounce_fire_cb,
                                 CONNECTIVITY_ALARM_DEBOUNCE_MS, NULL);
    if (s_debounce) lv_timer_set_repeat_count(s_debounce, 1);
}

static void reevaluate(void)
{
    if (!desired_clock_mode()) {
        /* All links up. Cancel pending debounce, restore previous screen. */
        cancel_debounce();
        exit_clock_mode();
        return;
    }
    /* Not yet in clock mode — start (or leave running) the debounce timer. */
    if (!s_in_clock_mode) schedule_debounce();
}

/* ----- public ----------------------------------------------------------- */

void connectivity_alarm_init(void)
{
    s_wifi_ok       = false;
    s_mqtt_ok       = false;
    s_in_clock_mode = false;
    s_prev_screen   = NULL;
    s_debounce      = NULL;
}

void connectivity_alarm_set_wifi(bool connected)
{
    if (s_wifi_ok == connected) return;
    s_wifi_ok = connected;
    ESP_LOGI(TAG, "wifi=%d mqtt=%d", (int)s_wifi_ok, (int)s_mqtt_ok);
    if (!connected) spotter_paint_placeholders();
    reevaluate();
}

void connectivity_alarm_set_mqtt(bool connected)
{
    if (s_mqtt_ok == connected) return;
    s_mqtt_ok = connected;
    ESP_LOGI(TAG, "wifi=%d mqtt=%d", (int)s_wifi_ok, (int)s_mqtt_ok);
    if (!connected) spotter_paint_placeholders();
    reevaluate();
}

void connectivity_alarm_evaluate(void)
{
    reevaluate();
}

/* Called from actions.c when the user taps the gear icon on PageClockMode
 * to access settings. We clear our internal "we put them here" flag so the
 * auto-restore-on-reconnect doesn't bounce them off PageSetup. */
void connectivity_clock_user_left(void)
{
    s_in_clock_mode = false;
    s_prev_screen   = NULL;
}
