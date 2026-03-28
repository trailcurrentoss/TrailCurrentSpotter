#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "ui/ui.h"
#include "ui/actions.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "ui/vars.h"
#include "app_mqtt.h"

static const char *TAG = "ACTIONS";

void action_settings_selection_change(lv_event_t *e)
{
    int menuSelection = (int)(intptr_t)lv_event_get_user_data(e);
    lv_obj_add_flag(objects.container_display_settings, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.container_connectivity_options, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.container_demo_settings, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.container_about_settings, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.container_date_time_settings, LV_OBJ_FLAG_HIDDEN);
    if (menuSelection == 0) {
        lv_obj_clear_flag(objects.container_display_settings, LV_OBJ_FLAG_HIDDEN);
    } else if (menuSelection == 1) {
        lv_obj_clear_flag(objects.container_connectivity_options, LV_OBJ_FLAG_HIDDEN);
    } else if (menuSelection == 2) {
        lv_obj_clear_flag(objects.container_demo_settings, LV_OBJ_FLAG_HIDDEN);
    } else if (menuSelection == 3) {
        lv_obj_clear_flag(objects.container_about_settings, LV_OBJ_FLAG_HIDDEN);
    } else if (menuSelection == 4) {
        lv_obj_clear_flag(objects.container_date_time_settings, LV_OBJ_FLAG_HIDDEN);
    }
}

void action_change_theme(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    int themeIndex = (int)(intptr_t)lv_event_get_user_data(e);
    set_var_selected_theme(themeIndex);
}

void action_change_screen(lv_event_t *e)
{
    int screenData = (int)(intptr_t)lv_event_get_user_data(e);

    /* Clear all toolbar button checked states for all home buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all trailer buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all power buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all solar buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all settings buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);

    if (screenData == 0) {
        lv_scr_load(objects.home);
        lv_obj_add_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    } else if (screenData == 1) {
        lv_scr_load(objects.trailer);
        lv_obj_add_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    } else if (screenData == 2) {
        lv_scr_load(objects.power);
        lv_obj_add_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    } else if (screenData == 3) {
        lv_scr_load(objects.solar);
        lv_obj_add_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    } else if (screenData == 4) {
        lv_scr_load(objects.air);
        lv_obj_add_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_fridge, LV_STATE_CHECKED);
    } else if (screenData == 5) {
        lv_scr_load(objects.settings);
        lv_obj_add_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    }
}

void action_timeout_changed(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    int32_t currentTimeoutValue = get_var_screen_timeout_value();
    int eventValue = (int)(intptr_t)lv_event_get_user_data(e);
    if (eventValue == 0) {
        currentTimeoutValue--;
    } else {
        currentTimeoutValue++;
    }
    set_var_screen_timeout_value(currentTimeoutValue);
}

void action_keep_on_while_driving_changed(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    bool keep_on = lv_obj_has_state(objects.check_box_keep_screen_on_while_in_motion, LV_STATE_CHECKED);
    set_var_keep_screen_on_while_driving(keep_on);
}

static const char *timezone_items[] = {
    "ASKT9AKDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "CST6CDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "HST11HDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "EST5EDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
    "MST7"
};

void action_timezone_change(lv_event_t *e)
{
    (void)e;
    uint16_t idx = lv_dropdown_get_selected(objects.drop_down_selected_time_zone);
    if (idx < 7) {
        set_var_user_settings_changed(true);
        set_var_current_time_zone_string(timezone_items[idx]);
    }
}

/* --- WiFi / Server config stubs (EEZ actions.h still declares these) --- */

void action_wifi_scan(lv_event_t *e) { (void)e; }
void action_wifi_connect(lv_event_t *e) { (void)e; }
void action_save_server_url(lv_event_t *e) { (void)e; }
void action_save_api_key(lv_event_t *e) { (void)e; }
void action_save_server_config(lv_event_t *e) { (void)e; }
void action_navigate_to_wifi_setup(lv_event_t *e) { (void)e; }

/* --- Light control --- */

void action_toggle_light(lv_event_t *e)
{
    int lightId = (int)(intptr_t)lv_event_get_user_data(e);
    ESP_LOGI(TAG, "Toggling light ID: %d", lightId);

    int currentState = 0;
    switch (lightId) {
    case 1: currentState = get_var_pdm01_device01_status(); break;
    case 2: currentState = get_var_pdm01_device02_status(); break;
    case 3: currentState = get_var_pdm01_device03_status(); break;
    case 4: currentState = get_var_pdm01_device04_status(); break;
    case 5: currentState = get_var_pdm01_device05_status(); break;
    case 6: currentState = get_var_pdm01_device06_status(); break;
    case 7: currentState = get_var_pdm01_device07_status(); break;
    case 8: currentState = get_var_pdm01_device08_status(); break;
    }

    int newState = (currentState > 0) ? 0 : 1;

    char topic[64];
    snprintf(topic, sizeof(topic), "local/lights/%d/command", lightId);
    char payload[32];
    snprintf(payload, sizeof(payload), "{\"state\":%d}", newState);
    mqtt_client_publish(topic, payload, 0);
}

/* --- Wire light buttons --- */

void setup_light_buttons(void)
{
    lv_obj_add_event_cb(objects.btn_device01, action_toggle_light, LV_EVENT_CLICKED, (void *)1);
    lv_obj_add_event_cb(objects.btn_device02, action_toggle_light, LV_EVENT_CLICKED, (void *)2);
    lv_obj_add_event_cb(objects.btn_device03, action_toggle_light, LV_EVENT_CLICKED, (void *)3);
    lv_obj_add_event_cb(objects.btn_device04, action_toggle_light, LV_EVENT_CLICKED, (void *)4);
    lv_obj_add_event_cb(objects.btn_device05, action_toggle_light, LV_EVENT_CLICKED, (void *)5);
    lv_obj_add_event_cb(objects.btn_device06, action_toggle_light, LV_EVENT_CLICKED, (void *)6);
    lv_obj_add_event_cb(objects.btn_device07, action_toggle_light, LV_EVENT_CLICKED, (void *)7);
    lv_obj_add_event_cb(objects.btn_device08, action_toggle_light, LV_EVENT_CLICKED, (void *)8);
}
