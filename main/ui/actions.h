#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_change_screen(lv_event_t * e);
extern void action_settings_selection_change(lv_event_t * e);
extern void action_change_theme(lv_event_t * e);
extern void action_timeout_changed(lv_event_t * e);
extern void action_keep_on_while_driving_changed(lv_event_t * e);
extern void action_timezone_change(lv_event_t * e);
extern void action_wifi_scan(lv_event_t * e);
extern void action_wifi_connect(lv_event_t * e);
extern void action_save_server_url(lv_event_t * e);
extern void action_save_api_key(lv_event_t * e);
extern void action_save_server_config(lv_event_t * e);
extern void action_navigate_to_wifi_setup(lv_event_t * e);
extern void action_set_axle_count(lv_event_t * e);
extern void action_toggle_brakes(lv_event_t * e);
extern void action_toggle_breakaway(lv_event_t * e);
extern void action_acknowledge_alarm(lv_event_t * e);
extern void action_go_alarms(lv_event_t * e);
extern void action_wifi_select_network(lv_event_t * e);
extern void action_wifi_password_submit(lv_event_t * e);
extern void action_wifi_toggle_password_reveal(lv_event_t * e);
extern void action_wifi_back(lv_event_t * e);
extern void action_wifi_skip_to_serial(lv_event_t * e);
extern void action_mqtt_back(lv_event_t * e);
extern void action_mqtt_next(lv_event_t * e);
extern void action_test_alarms(lv_event_t * e);
extern void action_clear_connection(lv_event_t * e);
extern void action_toggle_spoor_sensor(lv_event_t * e);
extern void action_open_rename_sensor(lv_event_t * e);
extern void action_save_sensor_rename(lv_event_t * e);
extern void action_cancel_sensor_rename(lv_event_t * e);
extern void action_alarm_snooze_duration_changed(lv_event_t * e);
extern void action_toggle_device_alarm(lv_event_t * e);
extern void action_toggle_device_invert(lv_event_t * e);
extern void action_open_rename_device(lv_event_t * e);
extern void action_volume_changed(lv_event_t * e);
extern void action_brightness_changed(lv_event_t * e);
extern void action_go_setup_from_clock(lv_event_t * e);
extern void action_toggle_clock_format(lv_event_t * e);
extern void action_retry_connection(lv_event_t * e);
extern void action_toggle_theme(lv_event_t * e);
extern void action_toggle_battery_meter(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/