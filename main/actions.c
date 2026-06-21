#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "ui/ui.h"
#include "ui/actions.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "ui/vars.h"
#include "ui/fonts.h"
#include "audio.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_mqtt.h"
#include "app_state.h"
#include "wifi_setup.h"
#include "pendant_config.h"
#include "spoor_alarms.h"
#include "device_alarms.h"

static const char *TAG = "ACTIONS";

/* ============================================================================
 * Screen navigation — 4-tab dock (Drive / Lights / Alarms / Setup)
 * Tab indices wired in the .eez-project as ChangeScreen userData = 0..3.
 *
 * Each page has its own BottomTabBar instance, so the dock buttons are
 * per-instance objects (drive_dock__dock_btn_drive, lights_dock__dock_btn_drive,
 * etc.). After loading the target screen we need to set LV_STATE_CHECKED on
 * the active tab of THAT screen's dock and clear it on the other three so the
 * highlight reflects the current page.
 * ============================================================================ */
typedef struct {
    lv_obj_t *page;
    lv_obj_t *btn_drive;
    lv_obj_t *btn_lights;
    lv_obj_t *btn_alarms;
    lv_obj_t *btn_setup;
} dock_set_t;

/* Expose externally so main.c can paint the initial tab state after ui_init. */
void spotter_set_active_tab(int index);
static void _do_set_tab_checked(int index);
void spotter_set_active_tab(int index) { _do_set_tab_checked(index); }

static void _do_set_tab_checked(int index)
{
    dock_set_t docks[4] = {
        { objects.page_drive,
          objects.drive_dock__dock_btn_drive,
          objects.drive_dock__dock_btn_lights,
          objects.drive_dock__dock_btn_alarms,
          objects.drive_dock__dock_btn_setup },
        { objects.page_lights,
          objects.lights_dock__dock_btn_drive,
          objects.lights_dock__dock_btn_lights,
          objects.lights_dock__dock_btn_alarms,
          objects.lights_dock__dock_btn_setup },
        { objects.page_alarms,
          objects.alarms_dock__dock_btn_drive,
          objects.alarms_dock__dock_btn_lights,
          objects.alarms_dock__dock_btn_alarms,
          objects.alarms_dock__dock_btn_setup },
        { objects.page_setup,
          objects.setup_dock__dock_btn_drive,
          objects.setup_dock__dock_btn_lights,
          objects.setup_dock__dock_btn_alarms,
          objects.setup_dock__dock_btn_setup },
    };
    if (index < 0 || index > 3) return;
    const dock_set_t *d = &docks[index];
    lv_obj_t *btns[4] = { d->btn_drive, d->btn_lights, d->btn_alarms, d->btn_setup };
    for (int i = 0; i < 4; i++) {
        if (!btns[i]) continue;
        if (i == index) lv_obj_add_state(btns[i], LV_STATE_CHECKED);
        else            lv_obj_clear_state(btns[i], LV_STATE_CHECKED);
    }
}

void action_change_screen(lv_event_t *e)
{
    int screen_index = (int)(intptr_t)lv_event_get_user_data(e);
    lv_obj_t *target = NULL;
    switch (screen_index) {
    case 0: target = objects.page_drive;  break;
    case 1: target = objects.page_lights; break;
    case 2: target = objects.page_alarms; break;
    case 3: target = objects.page_setup;  break;
    default:
        ESP_LOGW(TAG, "ChangeScreen: unknown index %d", screen_index);
        return;
    }
    lv_scr_load(target);
    _do_set_tab_checked(screen_index);
}

/* ============================================================================
 * Theme switcher — Light = 0, Dark = 1 (wired from setup_theme_light/dark)
 * ============================================================================ */
void action_change_theme(lv_event_t *e)
{
    int theme_index = (int)(intptr_t)lv_event_get_user_data(e);
    set_var_selected_theme(theme_index);
    set_var_user_settings_changed(true);
    ESP_LOGI(TAG, "Theme changed to %d", theme_index);

    /* Mutually exclusive: light(0) / dark(1). */
    if (objects.setup_theme_light) {
        if (theme_index == 0) lv_obj_add_state(objects.setup_theme_light, LV_STATE_CHECKED);
        else                  lv_obj_clear_state(objects.setup_theme_light, LV_STATE_CHECKED);
    }
    if (objects.setup_theme_dark) {
        if (theme_index == 1) lv_obj_add_state(objects.setup_theme_dark, LV_STATE_CHECKED);
        else                  lv_obj_clear_state(objects.setup_theme_dark, LV_STATE_CHECKED);
    }
}

/* ============================================================================
 * User-settings actions — these still exist on the old Settings flow but the
 * new design doesn't expose them yet. Keep the variable-update side; drop the
 * direct objects.* references (those widgets are gone).
 * ============================================================================ */
void action_settings_selection_change(lv_event_t *e)
{
    /* Old multi-panel Settings was removed. No-op until the new Setup page
     * exposes equivalent sub-panels. */
    (void)e;
}

void action_timeout_changed(lv_event_t *e)
{
    int direction = (int)(intptr_t)lv_event_get_user_data(e);
    int32_t cur = get_var_screen_timeout_value();
    cur += (direction == 0) ? -1 : 1;
    if (cur < 0) cur = 0;
    set_var_screen_timeout_value(cur);
    set_var_user_settings_changed(true);
}

void action_keep_on_while_driving_changed(lv_event_t *e)
{
    /* Widget that drove this on the old Settings page is gone; no-op until
     * a checkbox is re-added to the new Setup screen. */
    (void)e;
}

void action_timezone_change(lv_event_t *e)
{
    /* Dropdown widget is gone; no-op until re-added to the new Setup screen. */
    (void)e;
}

/* ============================================================================
 * WiFi / server config — stubs (no widgets in the new design yet)
 * ============================================================================ */
/* action_wifi_scan and friends are defined below in the WiFi setup section.
 * These legacy stubs remain for actions the new wifi_setup module doesn't own: */
void action_wifi_connect(lv_event_t *e)           { (void)e; }
void action_save_server_url(lv_event_t *e)        { (void)e; }
void action_save_api_key(lv_event_t *e)           { (void)e; }
void action_save_server_config(lv_event_t *e)     { (void)e; }
void action_navigate_to_wifi_setup(lv_event_t *e) { (void)e; }

/* ============================================================================
 * Light control — toggle via MQTT publish
 * ============================================================================ */
void action_toggle_light(lv_event_t *e)
{
    int light_id = (int)(intptr_t)lv_event_get_user_data(e);
    ESP_LOGI(TAG, "Toggling light ID: %d", light_id);

    int current = 0;
    switch (light_id) {
    case 1: current = get_var_pdm01_device01_status(); break;
    case 2: current = get_var_pdm01_device02_status(); break;
    case 3: current = get_var_pdm01_device03_status(); break;
    case 4: current = get_var_pdm01_device04_status(); break;
    case 5: current = get_var_pdm01_device05_status(); break;
    case 6: current = get_var_pdm01_device06_status(); break;
    case 7: current = get_var_pdm01_device07_status(); break;
    case 8: current = get_var_pdm01_device08_status(); break;
    default: return;
    }
    int new_state = (current > 0) ? 0 : 1;

    char topic[64], payload[32];
    snprintf(topic, sizeof(topic), "local/lights/%d/command", light_id);
    snprintf(payload, sizeof(payload), "{\"state\":%d}", new_state);
    mqtt_client_publish(topic, payload, 0);
}

/* Wire the 6 light grid buttons on PageLights to action_toggle_light with
 * stable IDs 1..6. Called once from app_main after ui_init(). */
void setup_light_buttons(void)
{
    lv_obj_t *btns[6] = {
        objects.lights_btn_1, objects.lights_btn_2, objects.lights_btn_3,
        objects.lights_btn_4, objects.lights_btn_5, objects.lights_btn_6,
    };
    for (int i = 0; i < 6; i++) {
        if (btns[i]) {
            lv_obj_add_event_cb(btns[i], action_toggle_light,
                                LV_EVENT_CLICKED, (void *)(intptr_t)(i + 1));
        }
    }
}

/* ============================================================================
 * New actions declared by the v4 .eez-project — stubs for now. Wire to real
 * MQTT/state logic as those features are implemented.
 * ============================================================================ */
void action_prev_zone(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "PrevZone");
}

void action_next_zone(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "NextZone");
}

void action_zone_all_on(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "ZoneAllOn");
}

void action_zone_all_off(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "ZoneAllOff");
}

void action_all_lights_off(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "AllLightsOff");
    /* Broadcast turn-off for every known light ID. */
    for (int id = 1; id <= 8; id++) {
        char topic[64];
        snprintf(topic, sizeof(topic), "local/lights/%d/command", id);
        mqtt_client_publish(topic, "{\"state\":0}", 0);
    }
}

/* Top-toolbar text = "<AXLE> | <Connected|Offline>". Both pieces are user-
 * controlled and they fan out across all 4 page instances of TopStatusBar
 * (drive/lights/alarms/setup_status_bar__status_link_label).
 *
 * Axle comes from the Setup-page choice (default single on boot, persistable
 * later). Status reflects the MQTT broker connection — NOT WiFi. The wifi
 * icon to the right of the toolbar shows WiFi state independently. */
static int  s_axle_count     = 1;     /* Default: single axle */
static bool s_mqtt_connected = false;

static void refresh_top_label(void)
{
    const char *axle =
        (s_axle_count == 2) ? "TANDEM" :
        (s_axle_count == 3) ? "TRIPLE" : "SINGLE";
    const char *status = s_mqtt_connected ? "Connected" : "Offline";
    char buf[40];
    snprintf(buf, sizeof(buf), "%s | %s", axle, status);

    lv_obj_t *labels[] = {
        objects.drive_status_bar__status_link_label,
        objects.lights_status_bar__status_link_label,
        objects.alarms_status_bar__status_link_label,
        objects.setup_status_bar__status_link_label,
    };
    for (size_t i = 0; i < sizeof(labels)/sizeof(*labels); i++) {
        if (labels[i]) lv_label_set_text(labels[i], buf);
    }

    /* The "link" dot to the left of the label tracks MQTT too — green when
     * connected, dim when not. */
    lv_obj_t *dots[] = {
        objects.drive_status_bar__status_link_dot,
        objects.lights_status_bar__status_link_dot,
        objects.alarms_status_bar__status_link_dot,
        objects.setup_status_bar__status_link_dot,
    };
    uint32_t c = s_mqtt_connected
        ? theme_colors[active_theme_index][COLOR_ID_SUCCESS]
        : theme_colors[active_theme_index][COLOR_ID_SECONDARY_TEXT_COLOR];
    lv_color_t lc = lv_color_hex(c);
    for (size_t i = 0; i < sizeof(dots)/sizeof(*dots); i++) {
        if (dots[i]) lv_obj_set_style_bg_color(dots[i], lc,
                                               LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

/* Called from app_state when the MQTT client's state callback fires. */
void spotter_set_mqtt_connected(bool connected);
void spotter_set_mqtt_connected(bool connected)
{
    if (s_mqtt_connected == connected) return;
    s_mqtt_connected = connected;
    refresh_top_label();
}

/* spotter_apply_axle_count — applies the user's axle choice everywhere:
 *   1. Setup-page button checked state (mutually exclusive)
 *   2. Top status-bar label (with current MQTT status — see refresh_top_label)
 *   3. Tire card subtitle ("Single | Target 65 PSI")
 *   4. Tire grid cell visibility (L2/R2/L3/R3 hide when not needed)
 *
 * Exposed externally so main.c can apply the default at boot. */
/* spotter_paint_placeholders — called once after ui_init to set every
 * widget that's supposed to display data from TrailCurrent to a clear
 * placeholder, so the user can tell at a glance that nothing's arrived
 * yet. Once an MQTT message lands, the corresponding set_var_*()
 * setter overwrites the placeholder with the real value. */
void spotter_paint_placeholders(void);
void spotter_paint_placeholders(void)
{
    /* Battery card */
    if (objects.drive_bat_value)  lv_label_set_text(objects.drive_bat_value, "--");
    if (objects.drive_bat_volts)  lv_label_set_text(objects.drive_bat_volts, "-- V");
    /* Same idiom as Headwaters web UI when the shunt hasn't reported yet. */
    if (objects.drive_bat_remain) lv_label_set_text(objects.drive_bat_remain, "Calculating...");
    if (objects.drive_bat_arc)    lv_arc_set_value(objects.drive_bat_arc, 0);

    /* Solar card */
    if (objects.drive_solar_value) lv_label_set_text(objects.drive_solar_value, "--");
    if (objects.drive_solar_pct)   lv_label_set_text(objects.drive_solar_pct, "Waiting for data...");
    if (objects.drive_solar_arc)   lv_arc_set_value(objects.drive_solar_arc, 0);

    /* Tire pressure cells — six cells, all placeholder until TPMS reports. */
    lv_obj_t *tire_psi[] = {
        objects.drive_tire_l1_psi, objects.drive_tire_r1_psi,
        objects.drive_tire_l2_psi, objects.drive_tire_r2_psi,
        objects.drive_tire_l3_psi, objects.drive_tire_r3_psi,
    };
    for (size_t i = 0; i < sizeof(tire_psi)/sizeof(*tire_psi); i++) {
        if (tire_psi[i]) lv_label_set_text(tire_psi[i], "--");
    }

    /* Top status bar speed — fan out to all 4 page instances. */
    lv_obj_t *speeds[] = {
        objects.drive_status_bar__status_speed_value,
        objects.lights_status_bar__status_speed_value,
        objects.alarms_status_bar__status_speed_value,
        objects.setup_status_bar__status_speed_value,
    };
    for (size_t i = 0; i < sizeof(speeds)/sizeof(*speeds); i++) {
        if (speeds[i]) lv_label_set_text(speeds[i], "--");
    }
}

void spotter_apply_axle_count(int axles);
void spotter_apply_axle_count(int axles)
{
    if (axles < 1 || axles > 3) return;
    s_axle_count = axles;

    /* 1. Setup-page axle buttons — mutually exclusive CHECKED state. */
    lv_obj_t *axle_btns[3] = {
        objects.setup_axle_single,
        objects.setup_axle_tandem,
        objects.setup_axle_triple,
    };
    for (int i = 0; i < 3; i++) {
        if (!axle_btns[i]) continue;
        if ((i + 1) == axles) lv_obj_add_state(axle_btns[i], LV_STATE_CHECKED);
        else                  lv_obj_clear_state(axle_btns[i], LV_STATE_CHECKED);
    }

    /* 2. Top status-bar label — fans out across all 4 page-instances. */
    refresh_top_label();

    /* 3. Tire card subtitle. */
    if (objects.drive_tire_sub) {
        const char *sub =
            (axles == 1) ? "Single | Target 65 PSI" :
            (axles == 2) ? "Tandem | Target 65 PSI" : "Triple | Target 65 PSI";
        lv_label_set_text(objects.drive_tire_sub, sub);
    }

    /* 4. Show/hide tire cells.
     *    axles=1 (single):  L1,R1 visible; L2,R2,L3,R3 hidden
     *    axles=2 (tandem):  L1,R1,L2,R2 visible; L3,R3 hidden
     *    axles=3 (triple):  all 6 visible
     */
    struct { lv_obj_t *cell; int min_axles; } tires[] = {
        { objects.drive_tire_l1, 1 }, { objects.drive_tire_r1, 1 },
        { objects.drive_tire_l2, 2 }, { objects.drive_tire_r2, 2 },
        { objects.drive_tire_l3, 3 }, { objects.drive_tire_r3, 3 },
    };
    for (size_t i = 0; i < sizeof(tires)/sizeof(*tires); i++) {
        if (!tires[i].cell) continue;
        if (axles >= tires[i].min_axles)
            lv_obj_clear_flag(tires[i].cell, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(tires[i].cell, LV_OBJ_FLAG_HIDDEN);
    }
}

void action_set_axle_count(lv_event_t *e)
{
    int axles = (int)(intptr_t)lv_event_get_user_data(e);
    ESP_LOGI(TAG, "SetAxleCount %d", axles);
    spotter_apply_axle_count(axles);
    set_var_user_settings_changed(true);
}

void action_toggle_brakes(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "ToggleBrakes");
    set_var_user_settings_changed(true);
}

void action_toggle_breakaway(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "ToggleBreakaway");
    set_var_user_settings_changed(true);
}

/* ============================================================================
 * Alarm overlay — full-screen modal on lv_layer_top(), used by Test Alarms and
 * eventually by any real alarm trigger. Visual is built in C (not in EEZ) so it
 * always sits above the active page regardless of which screen is loaded.
 *
 * Acknowledge closes the overlay and stops the chime. The chime is a stubbed
 * tick timer for now (Stage 1) — Stage 2 swaps it for ES8311 audio.
 * ============================================================================ */
static lv_obj_t *s_alarm_overlay = NULL;
static lv_obj_t *s_alarm_pulse_panel = NULL;
static lv_timer_t *s_alarm_pulse_timer = NULL;
static lv_timer_t *s_alarm_chime_timer = NULL;
static bool s_alarm_pulse_high = false;
/* When >= 0, the current overlay was raised by device_alarms for this device
 * index and gets a green "Resolve" button beside Acknowledge that publishes
 * a CAN relay-toggle command. Cleared by alarm_dismiss(). */
static int  s_alarm_device_idx = -1;
static lv_obj_t *s_alarm_resolve_btn = NULL;

static void alarm_pulse_cb(lv_timer_t *t)
{
    (void)t;
    if (!s_alarm_pulse_panel) return;
    s_alarm_pulse_high = !s_alarm_pulse_high;
    uint32_t hot = theme_colors[active_theme_index][COLOR_ID_HOT];
    lv_obj_set_style_bg_color(s_alarm_pulse_panel, lv_color_hex(hot),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(s_alarm_pulse_panel,
                            s_alarm_pulse_high ? 230 : 110,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void alarm_chime_cb(lv_timer_t *t)
{
    (void)t;
    spotter_audio_chime_tick();
}

static void alarm_dismiss(void)
{
    if (s_alarm_pulse_timer) { lv_timer_del(s_alarm_pulse_timer); s_alarm_pulse_timer = NULL; }
    if (s_alarm_chime_timer) { lv_timer_del(s_alarm_chime_timer); s_alarm_chime_timer = NULL; }
    if (s_alarm_overlay)     { lv_obj_del(s_alarm_overlay);       s_alarm_overlay = NULL; }
    s_alarm_pulse_panel = NULL;
    s_alarm_resolve_btn = NULL;
    s_alarm_device_idx  = -1;
    spotter_audio_chime_stop();
}

static void alarm_ack_event_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Alarm acknowledged");
    /* At most one of these has an active alarm; each function is a no-op
     * unless it owns the currently-showing overlay. */
    spoor_alarms_acknowledged();
    device_alarms_acknowledged();
    alarm_dismiss();
    /* Surface any other still-active armed alarm. bypass_snooze=false so
     * the alarm we just acknowledged stays silent for its snooze window
     * (its s_last_alarm_us was just bumped to "now" by acknowledged()). */
    if (!spoor_alarms_try_raise_next(false)) {
        device_alarms_try_raise_next(false);
    }
}

/* Resolve button — publish a relay-toggle CAN command for the device whose
 * alarm is currently showing, then disable the button so a stuck-finger
 * double-tap doesn't toggle the relay twice. The overlay STAYS until the
 * relay's status MQTT message comes back and device_alarms dismisses on
 * condition clear — gives the user feedback that the toggle landed. */
static void alarm_resolve_event_cb(lv_event_t *e)
{
    (void)e;
    if (s_alarm_device_idx < 0) {
        ESP_LOGW(TAG, "Resolve tapped but no device_idx — ignored");
        return;
    }
    ESP_LOGI(TAG, "Resolve tapped for device %d", s_alarm_device_idx);
    device_alarms_send_toggle(s_alarm_device_idx);
    if (s_alarm_resolve_btn) {
        lv_obj_clear_flag(s_alarm_resolve_btn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(s_alarm_resolve_btn, 120,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

static void spotter_show_alarm_overlay(const char *title, const char *body)
{
    if (s_alarm_overlay) alarm_dismiss();

    lv_obj_t *top = lv_layer_top();
    lv_obj_clear_flag(top, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_clear_flag(top, LV_OBJ_FLAG_SCROLLABLE);

    /* Full-screen pulsing red wash. */
    lv_obj_t *bg = lv_obj_create(top);
    s_alarm_overlay = bg;
    lv_obj_remove_style_all(bg);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_set_pos(bg, 0, 0);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);
    uint32_t hot = theme_colors[active_theme_index][COLOR_ID_HOT];
    lv_obj_set_style_bg_color(bg, lv_color_hex(hot),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(bg, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
    s_alarm_pulse_panel = bg;
    s_alarm_pulse_high = true;

    /* Center card. */
    lv_obj_t *card = lv_obj_create(bg);
    lv_obj_remove_style_all(card);
    lv_obj_set_size(card, 560, 320);
    lv_obj_align(card, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    uint32_t card_bg = theme_colors[active_theme_index][COLOR_ID_BACKGROUND_PANEL];
    lv_obj_set_style_bg_color(card, lv_color_hex(card_bg),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(card, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(card, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(card, lv_color_hex(hot),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(card, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(card, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Warning icon (fa-exclamation-circle 0xf06a). */
    lv_obj_t *icon = lv_label_create(card);
    lv_obj_set_style_text_font(icon, &ui_font_fa32,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(icon, lv_color_hex(hot),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(icon, "\xEF\x81\xAA");          /* U+F06A */
    lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 32);

    /* Title. */
    lv_obj_t *t = lv_label_create(card);
    uint32_t fg = theme_colors[active_theme_index][COLOR_ID_PRIMARY_TEXT_COLOR];
    lv_obj_set_style_text_color(t, lv_color_hex(fg),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(t, &lv_font_montserrat_32,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(t, title ? title : "ALARM");
    lv_obj_align(t, LV_ALIGN_TOP_MID, 0, 96);

    /* Body. */
    lv_obj_t *b = lv_label_create(card);
    uint32_t fg2 = theme_colors[active_theme_index][COLOR_ID_SECONDARY_TEXT_COLOR];
    lv_obj_set_style_text_color(b, lv_color_hex(fg2),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(b, &lv_font_montserrat_18,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(b, 480);
    lv_label_set_long_mode(b, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(b, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(b, body ? body
                              : "Test alarm — chime active. Press Acknowledge to silence.");
    lv_obj_align(b, LV_ALIGN_TOP_MID, 0, 150);

    /* Button row. Sensor / connectivity alarms get a single centered
     * Acknowledge. Device alarms get Acknowledge on the left + a green
     * Resolve on the right (taps publish a relay-toggle CAN command). */
    bool has_resolve = (s_alarm_device_idx >= 0);
    uint32_t fg_w = theme_colors[active_theme_index][COLOR_ID_FOREGROUND_WHITE];

    lv_obj_t *btn = lv_btn_create(card);
    if (has_resolve) {
        /* Two-button layout: 220 + 20 gap + 220 = 460 centered in 560 card. */
        lv_obj_set_size(btn, 220, 64);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 50, -28);
    } else {
        lv_obj_set_size(btn, 260, 64);
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -28);
    }
    lv_obj_set_style_bg_color(btn, lv_color_hex(hot),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(btn, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(btn, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn, alarm_ack_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btnlbl = lv_label_create(btn);
    lv_obj_set_style_text_color(btnlbl, lv_color_hex(fg_w),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(btnlbl, &lv_font_montserrat_22,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(btnlbl, "Acknowledge");
    lv_obj_center(btnlbl);

    if (has_resolve) {
        uint32_t success = theme_colors[active_theme_index][COLOR_ID_SUCCESS];
        lv_obj_t *resolve = lv_btn_create(card);
        s_alarm_resolve_btn = resolve;
        lv_obj_set_size(resolve, 220, 64);
        lv_obj_align(resolve, LV_ALIGN_BOTTOM_RIGHT, -50, -28);
        lv_obj_set_style_bg_color(resolve, lv_color_hex(success),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(resolve, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(resolve, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_event_cb(resolve, alarm_resolve_event_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t *rlbl = lv_label_create(resolve);
        lv_obj_set_style_text_color(rlbl, lv_color_hex(fg_w),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(rlbl, &lv_font_montserrat_22,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(rlbl, "Resolve");
        lv_obj_center(rlbl);
    }

    /* Start the pulse + chime timers. spotter_audio_chime_start enables the
     * PA and opens the codec; ticks fire a tone burst each cycle until
     * Acknowledge stops both timers and closes the codec. */
    spotter_audio_chime_start();
    s_alarm_pulse_timer = lv_timer_create(alarm_pulse_cb, 350, NULL);
    s_alarm_chime_timer = lv_timer_create(alarm_chime_cb, 900, NULL);

    ESP_LOGI(TAG, "Alarm overlay raised: %s", title ? title : "(no title)");
}

/* AcknowledgeAlarm action — wired to the alarm list rows in EEZ and also
 * reachable via the overlay's button (which uses its own event_cb above so it
 * works whether or not the action handler is bound). */
void action_acknowledge_alarm(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "AcknowledgeAlarm");
    spoor_alarms_acknowledged();
    device_alarms_acknowledged();
    if (s_alarm_overlay) alarm_dismiss();
    if (!spoor_alarms_try_raise_next(false)) {
        device_alarms_try_raise_next(false);
    }
}

void action_test_alarms(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "TestAlarms — raising overlay");
    spotter_show_alarm_overlay("TEST ALARM",
        "Diagnostic chime active.\nPress Acknowledge to silence.");
}

/* ============================================================================
 * Switchback ("spoor") sensor actions — declared in the EEZ project, wired
 * by userData encoding addr*8 + sensor_index (0..23). Slider value-changed
 * events drop into the spoor module so timing config persists immediately.
 * Logic lives in spoor_alarms.c.
 * ============================================================================ */
void action_toggle_spoor_sensor(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    spoor_alarms_toggle_arm(idx);
}

void action_open_rename_sensor(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    spoor_alarms_open_rename(idx);
}

void action_save_sensor_rename(lv_event_t *e)
{
    (void)e;
    /* The same rename page is reused by spoor_alarms (sensors) and
     * device_alarms (devices). Only one of these has an active rename
     * target; the other is a no-op. */
    spoor_alarms_save_rename();
    device_alarms_save_rename();
}

void action_cancel_sensor_rename(lv_event_t *e)
{
    (void)e;
    spoor_alarms_cancel_rename();
    device_alarms_cancel_rename();
}

void action_alarm_snooze_duration_changed(lv_event_t *e)
{
    lv_obj_t *t = (lv_obj_t *)lv_event_get_target(e);
    if (!t) return;
    spoor_alarms_set_snooze_secs((int)lv_slider_get_value(t));
}

/* ============================================================================
 * Switchback relay-output ("device") actions — userData = 0..23 maps to
 * MQTT channel 1..24 (i.e. device idx 0 = local/relays/1/status).
 * Logic lives in device_alarms.c.
 * ============================================================================ */
void action_toggle_device_alarm(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    device_alarms_toggle_arm(idx);
}

void action_toggle_device_invert(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    device_alarms_toggle_invert(idx);
}

void action_open_rename_device(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    device_alarms_open_rename(idx);
}

/* ============================================================================
 * Public alarm façade (spotter_alarm.h) — lets other modules raise the overlay
 * with an optional auto-dismiss timer. The user-configurable "show duration"
 * is owned by spoor_alarms; this layer just runs whatever timer it's given.
 * ============================================================================ */
static lv_timer_t *s_alarm_auto_dismiss_timer = NULL;

static void alarm_auto_dismiss_cb(lv_timer_t *t)
{
    (void)t;
    s_alarm_auto_dismiss_timer = NULL;
    if (s_alarm_overlay) {
        ESP_LOGI(TAG, "Alarm auto-dismiss fired");
        alarm_dismiss();
    }
}

void spotter_alarm_raise(const char *title, const char *body, int auto_dismiss_secs)
{
    /* Cancel any pending auto-dismiss from a previous raise. alarm_dismiss
     * doesn't touch our timer, so we have to clear it here. */
    if (s_alarm_auto_dismiss_timer) {
        lv_timer_del(s_alarm_auto_dismiss_timer);
        s_alarm_auto_dismiss_timer = NULL;
    }
    /* Non-device path — clear any leftover device idx so the new overlay
     * doesn't accidentally render a Resolve button bound to the previous
     * alarm's device. */
    s_alarm_device_idx = -1;
    spotter_show_alarm_overlay(title, body);
    if (auto_dismiss_secs > 0) {
        s_alarm_auto_dismiss_timer = lv_timer_create(
            alarm_auto_dismiss_cb, (uint32_t)auto_dismiss_secs * 1000U, NULL);
        lv_timer_set_repeat_count(s_alarm_auto_dismiss_timer, 1);
    }
}

void spotter_alarm_raise_device(const char *title, const char *body, int device_idx)
{
    if (s_alarm_auto_dismiss_timer) {
        lv_timer_del(s_alarm_auto_dismiss_timer);
        s_alarm_auto_dismiss_timer = NULL;
    }
    s_alarm_device_idx = device_idx;        /* enables the Resolve button */
    spotter_show_alarm_overlay(title, body);
    /* Always sticky — overlay clears on Acknowledge tap, Resolve-triggered
     * relay status flip, or the alarm condition resolving on its own. No
     * auto-dismiss timer. */
}

void spotter_alarm_force_dismiss(void)
{
    if (s_alarm_auto_dismiss_timer) {
        lv_timer_del(s_alarm_auto_dismiss_timer);
        s_alarm_auto_dismiss_timer = NULL;
    }
    if (s_alarm_overlay) alarm_dismiss();
}

/* ============================================================================
 * Reset Connection — clears saved WiFi + MQTT credentials and reboots so the
 * state machine re-enters first-time setup (WiFi scan → MQTT wizard → ready).
 * Two-step confirm to avoid a stray tap nuking the configuration.
 * ============================================================================ */
static lv_obj_t *s_reset_confirm = NULL;

static void reset_confirm_dismiss(void)
{
    if (s_reset_confirm) { lv_obj_del(s_reset_confirm); s_reset_confirm = NULL; }
}

static void reset_confirm_cancel_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "Reset cancelled");
    reset_confirm_dismiss();
}

static void reset_confirm_ok_cb(lv_event_t *e)
{
    (void)e;
    ESP_LOGW(TAG, "Reset confirmed — clearing pendant_config and rebooting");
    pendant_config_clear_wifi();
    pendant_config_clear_mqtt();
    /* Give NVS commit + the log line a moment before the hard restart. */
    vTaskDelay(pdMS_TO_TICKS(250));
    esp_restart();
}

void action_clear_connection(lv_event_t *e)
{
    (void)e;
    if (s_reset_confirm) return;
    ESP_LOGI(TAG, "ClearConnection — showing confirmation modal");

    lv_obj_t *top = lv_layer_top();
    lv_obj_clear_flag(top, LV_OBJ_FLAG_IGNORE_LAYOUT);

    lv_obj_t *bg = lv_obj_create(top);
    s_reset_confirm = bg;
    lv_obj_remove_style_all(bg);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_set_pos(bg, 0, 0);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(bg, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(bg, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *card = lv_obj_create(bg);
    lv_obj_remove_style_all(card);
    lv_obj_set_size(card, 520, 300);
    lv_obj_align(card, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    uint32_t card_bg = theme_colors[active_theme_index][COLOR_ID_BACKGROUND_PANEL];
    uint32_t hot     = theme_colors[active_theme_index][COLOR_ID_HOT];
    lv_obj_set_style_bg_color(card, lv_color_hex(card_bg), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(card, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(card, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(card, lv_color_hex(hot), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(card, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(card, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *t = lv_label_create(card);
    uint32_t fg = theme_colors[active_theme_index][COLOR_ID_PRIMARY_TEXT_COLOR];
    lv_obj_set_style_text_color(t, lv_color_hex(fg), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(t, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(t, "Reset Connection?");
    lv_obj_align(t, LV_ALIGN_TOP_MID, 0, 32);

    lv_obj_t *b = lv_label_create(card);
    uint32_t fg2 = theme_colors[active_theme_index][COLOR_ID_SECONDARY_TEXT_COLOR];
    lv_obj_set_style_text_color(b, lv_color_hex(fg2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(b, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(b, 460);
    lv_label_set_long_mode(b, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(b, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(b, "This clears saved WiFi and MQTT credentials, then reboots into setup.");
    lv_obj_align(b, LV_ALIGN_TOP_MID, 0, 96);

    /* Cancel (neutral) on the left, Reset (danger) on the right. */
    lv_obj_t *cancel = lv_btn_create(card);
    lv_obj_set_size(cancel, 200, 64);
    lv_obj_align(cancel, LV_ALIGN_BOTTOM_LEFT, 30, -28);
    uint32_t notsel = theme_colors[active_theme_index][COLOR_ID_BACKGROUND_NOT_SELECTED];
    lv_obj_set_style_bg_color(cancel, lv_color_hex(notsel), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cancel, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cancel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(cancel, reset_confirm_cancel_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *cl = lv_label_create(cancel);
    lv_obj_set_style_text_color(cl, lv_color_hex(fg), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cl, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(cl, "Cancel");
    lv_obj_center(cl);

    lv_obj_t *ok = lv_btn_create(card);
    lv_obj_set_size(ok, 200, 64);
    lv_obj_align(ok, LV_ALIGN_BOTTOM_RIGHT, -30, -28);
    lv_obj_set_style_bg_color(ok, lv_color_hex(hot), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ok, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ok, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ok, reset_confirm_ok_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *ol = lv_label_create(ok);
    uint32_t fg_w = theme_colors[active_theme_index][COLOR_ID_FOREGROUND_WHITE];
    lv_obj_set_style_text_color(ol, lv_color_hex(fg_w), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ol, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ol, "Reset");
    lv_obj_center(ol);
}

void action_go_lights(lv_event_t *e)
{
    (void)e;
    lv_scr_load(objects.page_lights);
}

void action_go_alarms(lv_event_t *e)
{
    (void)e;
    lv_scr_load(objects.page_alarms);
}

/* ============================================================================
 * MQTT setup wizard — single textarea + keyboard, 3 steps:
 *   step 0: TrailCurrent server hostname
 *   step 1: MQTT username
 *   step 2: MQTT password
 * "Next" advances; "Back" returns one step (or exits to PageDrive on step 0).
 * After step 2 we persist via pendant_config_set_mqtt and kick off the
 * connection through app_state (which loads PageMqttConnecting).
 * ============================================================================ */
static int  s_mqtt_step = 0;
static char s_mqtt_host[65]  = {0};
static char s_mqtt_user[65]  = {0};
static char s_mqtt_pass[129] = {0};

extern void app_state_show_mqtt_connecting(const char *host);

static void mqtt_setup_show_step(int step)
{
    s_mqtt_step = step;
    const char *caption, *placeholder;
    bool password = false;
    const char *cur = "";
    switch (step) {
    case 0:
        caption = "TrailCurrent server";
        placeholder = "hostname or IP";
        cur = s_mqtt_host;
        break;
    case 1:
        caption = "MQTT username";
        placeholder = "username";
        cur = s_mqtt_user;
        break;
    case 2:
        caption = "MQTT password";
        placeholder = "password";
        cur = s_mqtt_pass;
        password = true;
        break;
    default: return;
    }
    char step_buf[24];
    snprintf(step_buf, sizeof(step_buf), "Step %d of 3", step + 1);
    if (objects.mqtt_caption) lv_label_set_text(objects.mqtt_caption, caption);
    if (objects.mqtt_step)    lv_label_set_text(objects.mqtt_step, step_buf);
    if (objects.mqtt_input) {
        lv_textarea_set_password_mode(objects.mqtt_input, password);
        lv_textarea_set_placeholder_text(objects.mqtt_input, placeholder);
        lv_textarea_set_text(objects.mqtt_input, cur);
    }
    if (objects.mqtt_input && objects.mqtt_keyboard) {
        lv_keyboard_set_textarea(objects.mqtt_keyboard, objects.mqtt_input);
    }
    /* Final step's "Next" button reads "Save" to set expectation. */
    if (objects.mqtt_next_lbl) {
        lv_label_set_text(objects.mqtt_next_lbl, step == 2 ? "Save" : "Next");
    }
    /* Step 0's "Back" reads "Skip" — pressing it exits to the dashboard
     * without saving MQTT config. */
    if (objects.mqtt_back_lbl) {
        lv_label_set_text(objects.mqtt_back_lbl, step == 0 ? "Skip" : "Back");
    }
}

/* Called externally when state machine enters APP_STATE_MQTT_SETUP. */
void spotter_mqtt_setup_enter(void);
void spotter_mqtt_setup_enter(void)
{
    /* Pre-populate accumulators from any previously saved values so the user
     * can edit instead of starting from scratch. */
    const pendant_config_t *pc = pendant_config_get();
    if (pc) {
        strlcpy(s_mqtt_host, pc->mqtt_host, sizeof(s_mqtt_host));
        strlcpy(s_mqtt_user, pc->mqtt_user, sizeof(s_mqtt_user));
        strlcpy(s_mqtt_pass, pc->mqtt_pass, sizeof(s_mqtt_pass));
    }
    mqtt_setup_show_step(0);
}

void action_mqtt_next(lv_event_t *e)
{
    (void)e;
    const char *txt = objects.mqtt_input
        ? lv_textarea_get_text(objects.mqtt_input) : "";
    switch (s_mqtt_step) {
    case 0:
        strlcpy(s_mqtt_host, txt, sizeof(s_mqtt_host));
        mqtt_setup_show_step(1);
        break;
    case 1:
        strlcpy(s_mqtt_user, txt, sizeof(s_mqtt_user));
        mqtt_setup_show_step(2);
        break;
    case 2:
        strlcpy(s_mqtt_pass, txt, sizeof(s_mqtt_pass));
        /* Persist + advance to PageMqttConnecting. mqtt port stays at 8883
         * (default in pendant_config_set_mqtt when port=0). */
        pendant_config_set_mqtt(s_mqtt_host, s_mqtt_user, s_mqtt_pass, 0);
        ESP_LOGI(TAG, "MqttSave host=%s user=%s", s_mqtt_host, s_mqtt_user);
        app_state_set(APP_STATE_MQTT_CONNECTING);
        if (objects.mqtt_connecting_host) {
            lv_label_set_text(objects.mqtt_connecting_host, s_mqtt_host);
        }
        if (mqtt_client_load_settings()) {
            mqtt_client_connect();
        }
        break;
    default: break;
    }
}

void action_mqtt_back(lv_event_t *e)
{
    (void)e;
    /* Save what's currently in the textarea so going Back doesn't erase it. */
    const char *txt = objects.mqtt_input
        ? lv_textarea_get_text(objects.mqtt_input) : "";
    switch (s_mqtt_step) {
    case 0:
        /* "Back" on step 0 = Skip MQTT entirely. Land on the dashboard
         * without saving. The user can re-enter setup via Settings later
         * (TODO: add Settings → MQTT entry). */
        ESP_LOGI(TAG, "MqttSkip — proceeding to READY without MQTT");
        app_state_set(APP_STATE_READY);
        break;
    case 1:
        strlcpy(s_mqtt_user, txt, sizeof(s_mqtt_user));
        mqtt_setup_show_step(0);
        break;
    case 2:
        strlcpy(s_mqtt_pass, txt, sizeof(s_mqtt_pass));
        mqtt_setup_show_step(1);
        break;
    default: break;
    }
}

/* ============================================================================
 * WiFi setup actions — drive PageWifiSetup + PageWifiConnecting
 * ============================================================================ */
static char s_selected_ssid[33] = {0};
static bool s_selected_locked = false;
static bool s_password_revealed = false;

void action_wifi_scan(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "WifiScan");
    app_state_wifi_show_scanning();
    wifi_setup_scan_start();
}

static void show_password_panel(bool show)
{
    if (!objects.wifi_password_panel) return;
    if (show) {
        lv_obj_clear_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
        /* Move focus into the textarea so keystrokes go there. */
        if (objects.wifi_pwd_input && objects.wifi_pwd_keyboard) {
            lv_keyboard_set_textarea(objects.wifi_pwd_keyboard, objects.wifi_pwd_input);
        }
        if (objects.wifi_pwd_input) {
            lv_textarea_set_text(objects.wifi_pwd_input, "");
        }
        s_password_revealed = false;
        if (objects.wifi_pwd_input) {
            lv_textarea_set_password_mode(objects.wifi_pwd_input, true);
        }
    } else {
        lv_obj_add_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
    }
}

void action_wifi_select_network(lv_event_t *e)
{
    int idx = (int)(intptr_t)lv_event_get_user_data(e);
    wifi_setup_network_t nets[WIFI_SETUP_MAX_SCAN_RESULTS];
    size_t n = wifi_setup_get_scan_results(nets, WIFI_SETUP_MAX_SCAN_RESULTS);
    if (idx < 0 || (size_t)idx >= n) {
        ESP_LOGW(TAG, "WifiSelectNetwork: row %d out of range (n=%zu)", idx, n);
        return;
    }
    strlcpy(s_selected_ssid, nets[idx].ssid, sizeof(s_selected_ssid));
    s_selected_locked = nets[idx].locked;
    ESP_LOGI(TAG, "WifiSelectNetwork %d: %s (%s)",
             idx, s_selected_ssid, s_selected_locked ? "locked" : "open");

    if (!s_selected_locked) {
        /* Open network — connect directly, skip password panel. */
        if (objects.wifi_connecting_ssid) {
            lv_label_set_text(objects.wifi_connecting_ssid, s_selected_ssid);
        }
        app_state_set(APP_STATE_WIFI_CONNECTING);
        wifi_setup_connect(s_selected_ssid, "");
        return;
    }

    /* Locked — show password panel with the SSID echoed. */
    if (objects.wifi_pwd_ssid) {
        lv_label_set_text(objects.wifi_pwd_ssid, s_selected_ssid);
    }
    show_password_panel(true);
}

void action_wifi_password_submit(lv_event_t *e)
{
    (void)e;
    const char *pwd = objects.wifi_pwd_input
        ? lv_textarea_get_text(objects.wifi_pwd_input) : "";
    if (!s_selected_ssid[0]) {
        ESP_LOGW(TAG, "WifiPasswordSubmit with no selected SSID");
        return;
    }
    ESP_LOGI(TAG, "WifiPasswordSubmit ssid=%s pwd_len=%d",
             s_selected_ssid, (int)strlen(pwd));

    /* Persist creds BEFORE attempting connect so a power-cycle mid-attempt
     * still ends up with them saved. wifi_setup_connect handles the retries. */
    pendant_config_set_wifi(s_selected_ssid, pwd);

    show_password_panel(false);
    if (objects.wifi_connecting_ssid) {
        lv_label_set_text(objects.wifi_connecting_ssid, s_selected_ssid);
    }
    app_state_set(APP_STATE_WIFI_CONNECTING);
    wifi_setup_connect(s_selected_ssid, pwd);
}

void action_wifi_toggle_password_reveal(lv_event_t *e)
{
    (void)e;
    if (!objects.wifi_pwd_input) return;
    s_password_revealed = !s_password_revealed;
    lv_textarea_set_password_mode(objects.wifi_pwd_input, !s_password_revealed);
    if (objects.wifi_pwd_reveal_icon) {
        /* fa-eye / fa-eye-slash — both in fa16 ranges per project audit. */
        lv_label_set_text(objects.wifi_pwd_reveal_icon,
                          s_password_revealed ? "\xEF\x81\xB0" /* eye-slash uf070 */
                                              : "\xEF\x81\xAE" /* eye uf06e */);
    }
}

void action_wifi_back(lv_event_t *e)
{
    (void)e;
    show_password_panel(false);
    s_selected_ssid[0] = '\0';
}

void action_wifi_skip_to_serial(lv_event_t *e)
{
    (void)e;
    /* No serial-only mode in Spotter today — just jump to the dashboard so the
     * user can use the device without WiFi. Settings page can re-trigger
     * provisioning later. */
    ESP_LOGI(TAG, "WifiSkipToSerial");
    app_state_set(APP_STATE_READY);
}
