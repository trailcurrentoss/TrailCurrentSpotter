#include "connectivity_alarm.h"

#include "esp_log.h"
#include "lvgl.h"

#include "app_state.h"
#include "spotter_alarm.h"

/* Defined in actions.c — wipes every MQTT-fed widget back to its placeholder
 * ("--", "-- V", "-- left", "No data"). Called here on any down-transition so
 * stale values aren't mistaken for live ones while the link is broken. */
extern void spotter_paint_placeholders(void);

static const char *TAG = "conn_alarm";

typedef enum {
    ALARM_KIND_NONE = 0,
    ALARM_KIND_WIFI,
    ALARM_KIND_MQTT,
} alarm_kind_t;

static bool          s_wifi_ok   = false;
static bool          s_mqtt_ok   = false;
static bool          s_raised    = false;        /* our overlay is currently showing */
static alarm_kind_t  s_kind      = ALARM_KIND_NONE;
static lv_timer_t   *s_debounce  = NULL;

/* ----- internal --------------------------------------------------------- */

static alarm_kind_t desired_alarm(void)
{
    if (!s_wifi_ok) return ALARM_KIND_WIFI;
    if (!s_mqtt_ok) return ALARM_KIND_MQTT;
    return ALARM_KIND_NONE;
}

static void raise_for(alarm_kind_t kind)
{
    if (kind == ALARM_KIND_WIFI) {
        spotter_alarm_raise(
            "Lost WiFi Connection",
            "Network unreachable.\nAlarms cannot be received until connection is restored.",
            0 /* no auto-dismiss — sticks until user ack or reconnect */);
        ESP_LOGW(TAG, "Raised: Lost WiFi Connection");
    } else if (kind == ALARM_KIND_MQTT) {
        spotter_alarm_raise(
            "Lost TrailCurrent Connection",
            "Broker unreachable.\nAlarms cannot be received until connection is restored.",
            0);
        ESP_LOGW(TAG, "Raised: Lost TrailCurrent Connection");
    }
    s_kind   = kind;
    s_raised = (kind != ALARM_KIND_NONE);
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
    /* Only fire if we've reached the main dashboard. During setup the device
     * is intentionally not yet connected, so an alarm there would be noise. */
    if (app_state_get() != APP_STATE_READY) return;
    alarm_kind_t want = desired_alarm();
    if (want == ALARM_KIND_NONE) return;          /* recovered during debounce */
    if (s_raised && s_kind == want) return;       /* already showing the right one */
    raise_for(want);
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
    alarm_kind_t want = desired_alarm();

    if (want == ALARM_KIND_NONE) {
        /* All good. Cancel any pending debounce and tear down our overlay. */
        cancel_debounce();
        if (s_raised) {
            spotter_alarm_force_dismiss();
            s_raised = false;
            s_kind   = ALARM_KIND_NONE;
            ESP_LOGI(TAG, "Connectivity restored — alarm dismissed");
        }
        return;
    }

    if (s_raised) {
        /* We're already showing an alarm. If the situation escalated
         * (MQTT-only → WiFi-also-down), swap to the higher-priority message
         * immediately — no second debounce window. */
        if (s_kind != want) {
            raise_for(want);
        }
        return;
    }

    /* Not raised yet — start (or leave running) the debounce timer. */
    schedule_debounce();
}

/* ----- public ----------------------------------------------------------- */

void connectivity_alarm_init(void)
{
    s_wifi_ok  = false;
    s_mqtt_ok  = false;
    s_raised   = false;
    s_kind     = ALARM_KIND_NONE;
    s_debounce = NULL;
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
