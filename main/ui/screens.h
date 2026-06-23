#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *page_drive;
    lv_obj_t *page_lights;
    lv_obj_t *page_alarms;
    lv_obj_t *page_setup;
    lv_obj_t *page_wifi_setup;
    lv_obj_t *page_wifi_connecting;
    lv_obj_t *page_mqtt_setup;
    lv_obj_t *page_mqtt_connecting;
    lv_obj_t *page_rename_sensor;
    lv_obj_t *page_clock_mode;
    lv_obj_t *drive_status_bar;
    lv_obj_t *drive_status_bar__root;
    lv_obj_t *drive_status_bar__status_brand_icon;
    lv_obj_t *drive_status_bar__status_brand_text;
    lv_obj_t *drive_status_bar__status_div_1;
    lv_obj_t *drive_status_bar__status_link_dot;
    lv_obj_t *drive_status_bar__status_link_label;
    lv_obj_t *drive_status_bar__status_wifi_icon;
    lv_obj_t *drive_status_bar__status_signal_left;
    lv_obj_t *drive_status_bar__status_signal_right;
    lv_obj_t *drive_status_bar__status_div_2;
    lv_obj_t *drive_status_bar__status_speed_value;
    lv_obj_t *drive_status_bar__status_speed_unit;
    lv_obj_t *drive_status_bar__status_time;
    lv_obj_t *drive_status_bar__status_theme_toggle;
    lv_obj_t *drive_status_bar__status_theme_icon;
    lv_obj_t *drive_status_bar__status_battery_icon;
    lv_obj_t *drive_status_bar__status_battery_value;
    lv_obj_t *drive_body;
    lv_obj_t *drive_cab;
    lv_obj_t *drive_windshield;
    lv_obj_t *drive_mirror_l;
    lv_obj_t *drive_mirror_r;
    lv_obj_t *drive_hitch_aframe;
    lv_obj_t *drive_hitch_dot;
    lv_obj_t *drive_breakaway;
    lv_obj_t *drive_trailer_body;
    lv_obj_t *drive_ac;
    lv_obj_t *drive_axle1_bar;
    lv_obj_t *drive_tire_l1;
    lv_obj_t *drive_tire_r1;
    lv_obj_t *drive_tire_l1_psi;
    lv_obj_t *drive_tire_r1_psi;
    lv_obj_t *drive_axle2_bar;
    lv_obj_t *drive_tire_l2;
    lv_obj_t *drive_tire_r2;
    lv_obj_t *drive_tire_l2_psi;
    lv_obj_t *drive_tire_r2_psi;
    lv_obj_t *drive_axle3_bar;
    lv_obj_t *drive_tire_l3;
    lv_obj_t *drive_tire_r3;
    lv_obj_t *drive_tire_l3_psi;
    lv_obj_t *drive_tire_r3_psi;
    lv_obj_t *drive_chip_run;
    lv_obj_t *drive_chip_run_icon;
    lv_obj_t *drive_chip_run_lbl;
    lv_obj_t *drive_chip_left;
    lv_obj_t *drive_chip_left_icon;
    lv_obj_t *drive_chip_left_lbl;
    lv_obj_t *drive_chip_brake;
    lv_obj_t *drive_chip_brake_icon;
    lv_obj_t *drive_chip_brake_lbl;
    lv_obj_t *drive_chip_right;
    lv_obj_t *drive_chip_right_icon;
    lv_obj_t *drive_chip_right_lbl;
    lv_obj_t *drive_chip_rev;
    lv_obj_t *drive_chip_rev_icon;
    lv_obj_t *drive_chip_rev_lbl;
    lv_obj_t *drive_bat_arc;
    lv_obj_t *drive_bat_dial;
    lv_obj_t *drive_bat_icon;
    lv_obj_t *drive_bat_value;
    lv_obj_t *drive_bat_volts;
    lv_obj_t *drive_bat_remain;
    lv_obj_t *drive_solar_arc;
    lv_obj_t *drive_solar_dial;
    lv_obj_t *drive_solar_icon;
    lv_obj_t *drive_solar_value;
    lv_obj_t *drive_solar_unit;
    lv_obj_t *drive_solar_pct;
    lv_obj_t *drive_bsm_l_a1;
    lv_obj_t *drive_bsm_l_a2;
    lv_obj_t *drive_bsm_l_a3;
    lv_obj_t *drive_bsm_r_a1;
    lv_obj_t *drive_bsm_r_a2;
    lv_obj_t *drive_bsm_r_a3;
    lv_obj_t *drive_bsm_l_car;
    lv_obj_t *drive_bsm_r_car;
    lv_obj_t *drive_bsm_warning;
    lv_obj_t *drive_bsm_warn_text;
    lv_obj_t *drive_solar_w;
    lv_obj_t *drive_sol_icon;
    lv_obj_t *obj0;
    lv_obj_t *drive_dock;
    lv_obj_t *drive_dock__root;
    lv_obj_t *drive_dock__dock_btn_drive;
    lv_obj_t *drive_dock__dock_btn_drive_icon;
    lv_obj_t *drive_dock__dock_btn_drive_label;
    lv_obj_t *drive_dock__dock_btn_lights;
    lv_obj_t *drive_dock__dock_btn_lights_icon;
    lv_obj_t *drive_dock__dock_btn_lights_label;
    lv_obj_t *drive_dock__dock_btn_alarms;
    lv_obj_t *drive_dock__dock_btn_alarms_icon;
    lv_obj_t *drive_dock__dock_btn_alarms_label;
    lv_obj_t *drive_dock__dock_btn_setup;
    lv_obj_t *drive_dock__dock_btn_setup_icon;
    lv_obj_t *drive_dock__dock_btn_setup_label;
    lv_obj_t *lights_status_bar;
    lv_obj_t *lights_status_bar__root;
    lv_obj_t *lights_status_bar__status_brand_icon;
    lv_obj_t *lights_status_bar__status_brand_text;
    lv_obj_t *lights_status_bar__status_div_1;
    lv_obj_t *lights_status_bar__status_link_dot;
    lv_obj_t *lights_status_bar__status_link_label;
    lv_obj_t *lights_status_bar__status_wifi_icon;
    lv_obj_t *lights_status_bar__status_signal_left;
    lv_obj_t *lights_status_bar__status_signal_right;
    lv_obj_t *lights_status_bar__status_div_2;
    lv_obj_t *lights_status_bar__status_speed_value;
    lv_obj_t *lights_status_bar__status_speed_unit;
    lv_obj_t *lights_status_bar__status_time;
    lv_obj_t *lights_status_bar__status_theme_toggle;
    lv_obj_t *lights_status_bar__status_theme_icon;
    lv_obj_t *lights_status_bar__status_battery_icon;
    lv_obj_t *lights_status_bar__status_battery_value;
    lv_obj_t *lights_header;
    lv_obj_t *lights_prev_btn;
    lv_obj_t *lights_prev_icon;
    lv_obj_t *lights_next_btn;
    lv_obj_t *lights_next_icon;
    lv_obj_t *lights_zone_title;
    lv_obj_t *lights_zone_sub;
    lv_obj_t *lights_body;
    lv_obj_t *lights_body_placeholder;
    lv_obj_t *lights_footer;
    lv_obj_t *lights_all_on_btn;
    lv_obj_t *lights_all_on_lbl;
    lv_obj_t *lights_all_off_btn;
    lv_obj_t *lights_all_off_lbl;
    lv_obj_t *lights_zone_dots;
    lv_obj_t *lights_zone_dot_0;
    lv_obj_t *lights_zone_dot_1;
    lv_obj_t *lights_zone_dot_2;
    lv_obj_t *lights_zone_dot_3;
    lv_obj_t *lights_zone_dot_4;
    lv_obj_t *lights_zone_dot_5;
    lv_obj_t *lights_off_all_btn;
    lv_obj_t *lights_off_all_lbl;
    lv_obj_t *lights_dock;
    lv_obj_t *lights_dock__root;
    lv_obj_t *lights_dock__dock_btn_drive;
    lv_obj_t *lights_dock__dock_btn_drive_icon;
    lv_obj_t *lights_dock__dock_btn_drive_label;
    lv_obj_t *lights_dock__dock_btn_lights;
    lv_obj_t *lights_dock__dock_btn_lights_icon;
    lv_obj_t *lights_dock__dock_btn_lights_label;
    lv_obj_t *lights_dock__dock_btn_alarms;
    lv_obj_t *lights_dock__dock_btn_alarms_icon;
    lv_obj_t *lights_dock__dock_btn_alarms_label;
    lv_obj_t *lights_dock__dock_btn_setup;
    lv_obj_t *lights_dock__dock_btn_setup_icon;
    lv_obj_t *lights_dock__dock_btn_setup_label;
    lv_obj_t *alarms_status_bar;
    lv_obj_t *alarms_status_bar__root;
    lv_obj_t *alarms_status_bar__status_brand_icon;
    lv_obj_t *alarms_status_bar__status_brand_text;
    lv_obj_t *alarms_status_bar__status_div_1;
    lv_obj_t *alarms_status_bar__status_link_dot;
    lv_obj_t *alarms_status_bar__status_link_label;
    lv_obj_t *alarms_status_bar__status_wifi_icon;
    lv_obj_t *alarms_status_bar__status_signal_left;
    lv_obj_t *alarms_status_bar__status_signal_right;
    lv_obj_t *alarms_status_bar__status_div_2;
    lv_obj_t *alarms_status_bar__status_speed_value;
    lv_obj_t *alarms_status_bar__status_speed_unit;
    lv_obj_t *alarms_status_bar__status_time;
    lv_obj_t *alarms_status_bar__status_theme_toggle;
    lv_obj_t *alarms_status_bar__status_theme_icon;
    lv_obj_t *alarms_status_bar__status_battery_icon;
    lv_obj_t *alarms_status_bar__status_battery_value;
    lv_obj_t *alarms_body;
    lv_obj_t *alarms_header;
    lv_obj_t *alarms_title;
    lv_obj_t *alarms_subtitle;
    lv_obj_t *alarms_armed_icon;
    lv_obj_t *alarms_armed_count;
    lv_obj_t *alarms_list;
    lv_obj_t *alarm_spoor0_grp_lbl;
    lv_obj_t *alarm_spoor0_grp_desc;
    lv_obj_t *alarm_spoor0_s1_row;
    lv_obj_t *alarm_spoor0_s1_name;
    lv_obj_t *alarm_spoor0_s1_pencil_btn;
    lv_obj_t *alarm_spoor0_s1_pencil_icon;
    lv_obj_t *alarm_spoor0_s1_sw;
    lv_obj_t *alarm_spoor0_s2_row;
    lv_obj_t *alarm_spoor0_s2_name;
    lv_obj_t *alarm_spoor0_s2_pencil_btn;
    lv_obj_t *alarm_spoor0_s2_pencil_icon;
    lv_obj_t *alarm_spoor0_s2_sw;
    lv_obj_t *alarm_spoor0_s3_row;
    lv_obj_t *alarm_spoor0_s3_name;
    lv_obj_t *alarm_spoor0_s3_pencil_btn;
    lv_obj_t *alarm_spoor0_s3_pencil_icon;
    lv_obj_t *alarm_spoor0_s3_sw;
    lv_obj_t *alarm_spoor0_s4_row;
    lv_obj_t *alarm_spoor0_s4_name;
    lv_obj_t *alarm_spoor0_s4_pencil_btn;
    lv_obj_t *alarm_spoor0_s4_pencil_icon;
    lv_obj_t *alarm_spoor0_s4_sw;
    lv_obj_t *alarm_spoor0_s5_row;
    lv_obj_t *alarm_spoor0_s5_name;
    lv_obj_t *alarm_spoor0_s5_pencil_btn;
    lv_obj_t *alarm_spoor0_s5_pencil_icon;
    lv_obj_t *alarm_spoor0_s5_sw;
    lv_obj_t *alarm_spoor0_s6_row;
    lv_obj_t *alarm_spoor0_s6_name;
    lv_obj_t *alarm_spoor0_s6_pencil_btn;
    lv_obj_t *alarm_spoor0_s6_pencil_icon;
    lv_obj_t *alarm_spoor0_s6_sw;
    lv_obj_t *alarm_spoor0_s7_row;
    lv_obj_t *alarm_spoor0_s7_name;
    lv_obj_t *alarm_spoor0_s7_pencil_btn;
    lv_obj_t *alarm_spoor0_s7_pencil_icon;
    lv_obj_t *alarm_spoor0_s7_sw;
    lv_obj_t *alarm_spoor0_s8_row;
    lv_obj_t *alarm_spoor0_s8_name;
    lv_obj_t *alarm_spoor0_s8_pencil_btn;
    lv_obj_t *alarm_spoor0_s8_pencil_icon;
    lv_obj_t *alarm_spoor0_s8_sw;
    lv_obj_t *alarm_spoor0_d1_row;
    lv_obj_t *alarm_spoor0_d1_name;
    lv_obj_t *alarm_spoor0_d1_pencil_btn;
    lv_obj_t *alarm_spoor0_d1_pencil_icon;
    lv_obj_t *alarm_spoor0_d1_sw;
    lv_obj_t *alarm_spoor0_d1_inv_sw;
    lv_obj_t *alarm_spoor0_d2_row;
    lv_obj_t *alarm_spoor0_d2_name;
    lv_obj_t *alarm_spoor0_d2_pencil_btn;
    lv_obj_t *alarm_spoor0_d2_pencil_icon;
    lv_obj_t *alarm_spoor0_d2_sw;
    lv_obj_t *alarm_spoor0_d2_inv_sw;
    lv_obj_t *alarm_spoor0_d3_row;
    lv_obj_t *alarm_spoor0_d3_name;
    lv_obj_t *alarm_spoor0_d3_pencil_btn;
    lv_obj_t *alarm_spoor0_d3_pencil_icon;
    lv_obj_t *alarm_spoor0_d3_sw;
    lv_obj_t *alarm_spoor0_d3_inv_sw;
    lv_obj_t *alarm_spoor0_d4_row;
    lv_obj_t *alarm_spoor0_d4_name;
    lv_obj_t *alarm_spoor0_d4_pencil_btn;
    lv_obj_t *alarm_spoor0_d4_pencil_icon;
    lv_obj_t *alarm_spoor0_d4_sw;
    lv_obj_t *alarm_spoor0_d4_inv_sw;
    lv_obj_t *alarm_spoor0_d5_row;
    lv_obj_t *alarm_spoor0_d5_name;
    lv_obj_t *alarm_spoor0_d5_pencil_btn;
    lv_obj_t *alarm_spoor0_d5_pencil_icon;
    lv_obj_t *alarm_spoor0_d5_sw;
    lv_obj_t *alarm_spoor0_d5_inv_sw;
    lv_obj_t *alarm_spoor0_d6_row;
    lv_obj_t *alarm_spoor0_d6_name;
    lv_obj_t *alarm_spoor0_d6_pencil_btn;
    lv_obj_t *alarm_spoor0_d6_pencil_icon;
    lv_obj_t *alarm_spoor0_d6_sw;
    lv_obj_t *alarm_spoor0_d6_inv_sw;
    lv_obj_t *alarm_spoor0_d7_row;
    lv_obj_t *alarm_spoor0_d7_name;
    lv_obj_t *alarm_spoor0_d7_pencil_btn;
    lv_obj_t *alarm_spoor0_d7_pencil_icon;
    lv_obj_t *alarm_spoor0_d7_sw;
    lv_obj_t *alarm_spoor0_d7_inv_sw;
    lv_obj_t *alarm_spoor0_d8_row;
    lv_obj_t *alarm_spoor0_d8_name;
    lv_obj_t *alarm_spoor0_d8_pencil_btn;
    lv_obj_t *alarm_spoor0_d8_pencil_icon;
    lv_obj_t *alarm_spoor0_d8_sw;
    lv_obj_t *alarm_spoor0_d8_inv_sw;
    lv_obj_t *alarm_spoor1_grp_lbl;
    lv_obj_t *alarm_spoor1_grp_desc;
    lv_obj_t *alarm_spoor1_s1_row;
    lv_obj_t *alarm_spoor1_s1_name;
    lv_obj_t *alarm_spoor1_s1_pencil_btn;
    lv_obj_t *alarm_spoor1_s1_pencil_icon;
    lv_obj_t *alarm_spoor1_s1_sw;
    lv_obj_t *alarm_spoor1_s2_row;
    lv_obj_t *alarm_spoor1_s2_name;
    lv_obj_t *alarm_spoor1_s2_pencil_btn;
    lv_obj_t *alarm_spoor1_s2_pencil_icon;
    lv_obj_t *alarm_spoor1_s2_sw;
    lv_obj_t *alarm_spoor1_s3_row;
    lv_obj_t *alarm_spoor1_s3_name;
    lv_obj_t *alarm_spoor1_s3_pencil_btn;
    lv_obj_t *alarm_spoor1_s3_pencil_icon;
    lv_obj_t *alarm_spoor1_s3_sw;
    lv_obj_t *alarm_spoor1_s4_row;
    lv_obj_t *alarm_spoor1_s4_name;
    lv_obj_t *alarm_spoor1_s4_pencil_btn;
    lv_obj_t *alarm_spoor1_s4_pencil_icon;
    lv_obj_t *alarm_spoor1_s4_sw;
    lv_obj_t *alarm_spoor1_s5_row;
    lv_obj_t *alarm_spoor1_s5_name;
    lv_obj_t *alarm_spoor1_s5_pencil_btn;
    lv_obj_t *alarm_spoor1_s5_pencil_icon;
    lv_obj_t *alarm_spoor1_s5_sw;
    lv_obj_t *alarm_spoor1_s6_row;
    lv_obj_t *alarm_spoor1_s6_name;
    lv_obj_t *alarm_spoor1_s6_pencil_btn;
    lv_obj_t *alarm_spoor1_s6_pencil_icon;
    lv_obj_t *alarm_spoor1_s6_sw;
    lv_obj_t *alarm_spoor1_s7_row;
    lv_obj_t *alarm_spoor1_s7_name;
    lv_obj_t *alarm_spoor1_s7_pencil_btn;
    lv_obj_t *alarm_spoor1_s7_pencil_icon;
    lv_obj_t *alarm_spoor1_s7_sw;
    lv_obj_t *alarm_spoor1_s8_row;
    lv_obj_t *alarm_spoor1_s8_name;
    lv_obj_t *alarm_spoor1_s8_pencil_btn;
    lv_obj_t *alarm_spoor1_s8_pencil_icon;
    lv_obj_t *alarm_spoor1_s8_sw;
    lv_obj_t *alarm_spoor1_d1_row;
    lv_obj_t *alarm_spoor1_d1_name;
    lv_obj_t *alarm_spoor1_d1_pencil_btn;
    lv_obj_t *alarm_spoor1_d1_pencil_icon;
    lv_obj_t *alarm_spoor1_d1_sw;
    lv_obj_t *alarm_spoor1_d1_inv_sw;
    lv_obj_t *alarm_spoor1_d2_row;
    lv_obj_t *alarm_spoor1_d2_name;
    lv_obj_t *alarm_spoor1_d2_pencil_btn;
    lv_obj_t *alarm_spoor1_d2_pencil_icon;
    lv_obj_t *alarm_spoor1_d2_sw;
    lv_obj_t *alarm_spoor1_d2_inv_sw;
    lv_obj_t *alarm_spoor1_d3_row;
    lv_obj_t *alarm_spoor1_d3_name;
    lv_obj_t *alarm_spoor1_d3_pencil_btn;
    lv_obj_t *alarm_spoor1_d3_pencil_icon;
    lv_obj_t *alarm_spoor1_d3_sw;
    lv_obj_t *alarm_spoor1_d3_inv_sw;
    lv_obj_t *alarm_spoor1_d4_row;
    lv_obj_t *alarm_spoor1_d4_name;
    lv_obj_t *alarm_spoor1_d4_pencil_btn;
    lv_obj_t *alarm_spoor1_d4_pencil_icon;
    lv_obj_t *alarm_spoor1_d4_sw;
    lv_obj_t *alarm_spoor1_d4_inv_sw;
    lv_obj_t *alarm_spoor1_d5_row;
    lv_obj_t *alarm_spoor1_d5_name;
    lv_obj_t *alarm_spoor1_d5_pencil_btn;
    lv_obj_t *alarm_spoor1_d5_pencil_icon;
    lv_obj_t *alarm_spoor1_d5_sw;
    lv_obj_t *alarm_spoor1_d5_inv_sw;
    lv_obj_t *alarm_spoor1_d6_row;
    lv_obj_t *alarm_spoor1_d6_name;
    lv_obj_t *alarm_spoor1_d6_pencil_btn;
    lv_obj_t *alarm_spoor1_d6_pencil_icon;
    lv_obj_t *alarm_spoor1_d6_sw;
    lv_obj_t *alarm_spoor1_d6_inv_sw;
    lv_obj_t *alarm_spoor1_d7_row;
    lv_obj_t *alarm_spoor1_d7_name;
    lv_obj_t *alarm_spoor1_d7_pencil_btn;
    lv_obj_t *alarm_spoor1_d7_pencil_icon;
    lv_obj_t *alarm_spoor1_d7_sw;
    lv_obj_t *alarm_spoor1_d7_inv_sw;
    lv_obj_t *alarm_spoor1_d8_row;
    lv_obj_t *alarm_spoor1_d8_name;
    lv_obj_t *alarm_spoor1_d8_pencil_btn;
    lv_obj_t *alarm_spoor1_d8_pencil_icon;
    lv_obj_t *alarm_spoor1_d8_sw;
    lv_obj_t *alarm_spoor1_d8_inv_sw;
    lv_obj_t *alarm_spoor2_grp_lbl;
    lv_obj_t *alarm_spoor2_grp_desc;
    lv_obj_t *alarm_spoor2_s1_row;
    lv_obj_t *alarm_spoor2_s1_name;
    lv_obj_t *alarm_spoor2_s1_pencil_btn;
    lv_obj_t *alarm_spoor2_s1_pencil_icon;
    lv_obj_t *alarm_spoor2_s1_sw;
    lv_obj_t *alarm_spoor2_s2_row;
    lv_obj_t *alarm_spoor2_s2_name;
    lv_obj_t *alarm_spoor2_s2_pencil_btn;
    lv_obj_t *alarm_spoor2_s2_pencil_icon;
    lv_obj_t *alarm_spoor2_s2_sw;
    lv_obj_t *alarm_spoor2_s3_row;
    lv_obj_t *alarm_spoor2_s3_name;
    lv_obj_t *alarm_spoor2_s3_pencil_btn;
    lv_obj_t *alarm_spoor2_s3_pencil_icon;
    lv_obj_t *alarm_spoor2_s3_sw;
    lv_obj_t *alarm_spoor2_s4_row;
    lv_obj_t *alarm_spoor2_s4_name;
    lv_obj_t *alarm_spoor2_s4_pencil_btn;
    lv_obj_t *alarm_spoor2_s4_pencil_icon;
    lv_obj_t *alarm_spoor2_s4_sw;
    lv_obj_t *alarm_spoor2_s5_row;
    lv_obj_t *alarm_spoor2_s5_name;
    lv_obj_t *alarm_spoor2_s5_pencil_btn;
    lv_obj_t *alarm_spoor2_s5_pencil_icon;
    lv_obj_t *alarm_spoor2_s5_sw;
    lv_obj_t *alarm_spoor2_s6_row;
    lv_obj_t *alarm_spoor2_s6_name;
    lv_obj_t *alarm_spoor2_s6_pencil_btn;
    lv_obj_t *alarm_spoor2_s6_pencil_icon;
    lv_obj_t *alarm_spoor2_s6_sw;
    lv_obj_t *alarm_spoor2_s7_row;
    lv_obj_t *alarm_spoor2_s7_name;
    lv_obj_t *alarm_spoor2_s7_pencil_btn;
    lv_obj_t *alarm_spoor2_s7_pencil_icon;
    lv_obj_t *alarm_spoor2_s7_sw;
    lv_obj_t *alarm_spoor2_s8_row;
    lv_obj_t *alarm_spoor2_s8_name;
    lv_obj_t *alarm_spoor2_s8_pencil_btn;
    lv_obj_t *alarm_spoor2_s8_pencil_icon;
    lv_obj_t *alarm_spoor2_s8_sw;
    lv_obj_t *alarm_spoor2_d1_row;
    lv_obj_t *alarm_spoor2_d1_name;
    lv_obj_t *alarm_spoor2_d1_pencil_btn;
    lv_obj_t *alarm_spoor2_d1_pencil_icon;
    lv_obj_t *alarm_spoor2_d1_sw;
    lv_obj_t *alarm_spoor2_d1_inv_sw;
    lv_obj_t *alarm_spoor2_d2_row;
    lv_obj_t *alarm_spoor2_d2_name;
    lv_obj_t *alarm_spoor2_d2_pencil_btn;
    lv_obj_t *alarm_spoor2_d2_pencil_icon;
    lv_obj_t *alarm_spoor2_d2_sw;
    lv_obj_t *alarm_spoor2_d2_inv_sw;
    lv_obj_t *alarm_spoor2_d3_row;
    lv_obj_t *alarm_spoor2_d3_name;
    lv_obj_t *alarm_spoor2_d3_pencil_btn;
    lv_obj_t *alarm_spoor2_d3_pencil_icon;
    lv_obj_t *alarm_spoor2_d3_sw;
    lv_obj_t *alarm_spoor2_d3_inv_sw;
    lv_obj_t *alarm_spoor2_d4_row;
    lv_obj_t *alarm_spoor2_d4_name;
    lv_obj_t *alarm_spoor2_d4_pencil_btn;
    lv_obj_t *alarm_spoor2_d4_pencil_icon;
    lv_obj_t *alarm_spoor2_d4_sw;
    lv_obj_t *alarm_spoor2_d4_inv_sw;
    lv_obj_t *alarm_spoor2_d5_row;
    lv_obj_t *alarm_spoor2_d5_name;
    lv_obj_t *alarm_spoor2_d5_pencil_btn;
    lv_obj_t *alarm_spoor2_d5_pencil_icon;
    lv_obj_t *alarm_spoor2_d5_sw;
    lv_obj_t *alarm_spoor2_d5_inv_sw;
    lv_obj_t *alarm_spoor2_d6_row;
    lv_obj_t *alarm_spoor2_d6_name;
    lv_obj_t *alarm_spoor2_d6_pencil_btn;
    lv_obj_t *alarm_spoor2_d6_pencil_icon;
    lv_obj_t *alarm_spoor2_d6_sw;
    lv_obj_t *alarm_spoor2_d6_inv_sw;
    lv_obj_t *alarm_spoor2_d7_row;
    lv_obj_t *alarm_spoor2_d7_name;
    lv_obj_t *alarm_spoor2_d7_pencil_btn;
    lv_obj_t *alarm_spoor2_d7_pencil_icon;
    lv_obj_t *alarm_spoor2_d7_sw;
    lv_obj_t *alarm_spoor2_d7_inv_sw;
    lv_obj_t *alarm_spoor2_d8_row;
    lv_obj_t *alarm_spoor2_d8_name;
    lv_obj_t *alarm_spoor2_d8_pencil_btn;
    lv_obj_t *alarm_spoor2_d8_pencil_icon;
    lv_obj_t *alarm_spoor2_d8_sw;
    lv_obj_t *alarm_spoor2_d8_inv_sw;
    lv_obj_t *alarms_dock;
    lv_obj_t *alarms_dock__root;
    lv_obj_t *alarms_dock__dock_btn_drive;
    lv_obj_t *alarms_dock__dock_btn_drive_icon;
    lv_obj_t *alarms_dock__dock_btn_drive_label;
    lv_obj_t *alarms_dock__dock_btn_lights;
    lv_obj_t *alarms_dock__dock_btn_lights_icon;
    lv_obj_t *alarms_dock__dock_btn_lights_label;
    lv_obj_t *alarms_dock__dock_btn_alarms;
    lv_obj_t *alarms_dock__dock_btn_alarms_icon;
    lv_obj_t *alarms_dock__dock_btn_alarms_label;
    lv_obj_t *alarms_dock__dock_btn_setup;
    lv_obj_t *alarms_dock__dock_btn_setup_icon;
    lv_obj_t *alarms_dock__dock_btn_setup_label;
    lv_obj_t *setup_status_bar;
    lv_obj_t *setup_status_bar__root;
    lv_obj_t *setup_status_bar__status_brand_icon;
    lv_obj_t *setup_status_bar__status_brand_text;
    lv_obj_t *setup_status_bar__status_div_1;
    lv_obj_t *setup_status_bar__status_link_dot;
    lv_obj_t *setup_status_bar__status_link_label;
    lv_obj_t *setup_status_bar__status_wifi_icon;
    lv_obj_t *setup_status_bar__status_signal_left;
    lv_obj_t *setup_status_bar__status_signal_right;
    lv_obj_t *setup_status_bar__status_div_2;
    lv_obj_t *setup_status_bar__status_speed_value;
    lv_obj_t *setup_status_bar__status_speed_unit;
    lv_obj_t *setup_status_bar__status_time;
    lv_obj_t *setup_status_bar__status_theme_toggle;
    lv_obj_t *setup_status_bar__status_theme_icon;
    lv_obj_t *setup_status_bar__status_battery_icon;
    lv_obj_t *setup_status_bar__status_battery_value;
    lv_obj_t *setup_body;
    lv_obj_t *setup_axle_title;
    lv_obj_t *setup_axle_single;
    lv_obj_t *setup_axle_single_lbl;
    lv_obj_t *setup_axle_single_sub;
    lv_obj_t *setup_axle_tandem;
    lv_obj_t *setup_axle_tandem_lbl;
    lv_obj_t *setup_axle_tandem_sub;
    lv_obj_t *setup_axle_triple;
    lv_obj_t *setup_axle_triple_lbl;
    lv_obj_t *setup_axle_triple_sub;
    lv_obj_t *setup_brake_title;
    lv_obj_t *setup_brakes_row;
    lv_obj_t *setup_brakes_icon;
    lv_obj_t *setup_brakes_name;
    lv_obj_t *setup_brakes_desc;
    lv_obj_t *setup_brakes_sw;
    lv_obj_t *setup_breakaway_row;
    lv_obj_t *setup_breakaway_icon;
    lv_obj_t *setup_breakaway_name;
    lv_obj_t *setup_breakaway_desc;
    lv_obj_t *setup_breakaway_sw;
    lv_obj_t *setup_theme_title;
    lv_obj_t *setup_theme_light;
    lv_obj_t *setup_theme_light_icon;
    lv_obj_t *setup_theme_light_lbl;
    lv_obj_t *setup_theme_dark;
    lv_obj_t *setup_theme_dark_icon;
    lv_obj_t *setup_theme_dark_lbl;
    lv_obj_t *setup_info_banner;
    lv_obj_t *setup_info_icon;
    lv_obj_t *setup_info_text;
    lv_obj_t *setup_battery_meter_row;
    lv_obj_t *setup_battery_meter_icon;
    lv_obj_t *setup_battery_meter_name;
    lv_obj_t *setup_battery_meter_desc;
    lv_obj_t *setup_battery_meter_sw;
    lv_obj_t *setup_reset_conn_title;
    lv_obj_t *setup_reset_conn_btn;
    lv_obj_t *setup_reset_conn_btn_lbl;
    lv_obj_t *setup_alarm_timing_title;
    lv_obj_t *setup_alarm_snooze_row;
    lv_obj_t *setup_alarm_snooze_name;
    lv_obj_t *setup_alarm_snooze_value;
    lv_obj_t *setup_alarm_snooze_slider;
    lv_obj_t *setup_audio_title;
    lv_obj_t *setup_volume_row;
    lv_obj_t *setup_volume_name;
    lv_obj_t *setup_volume_value;
    lv_obj_t *setup_volume_slider;
    lv_obj_t *setup_brightness_row;
    lv_obj_t *setup_brightness_name;
    lv_obj_t *setup_brightness_value;
    lv_obj_t *setup_brightness_slider;
    lv_obj_t *setup_timezone_title;
    lv_obj_t *setup_timezone_dropdown;
    lv_obj_t *setup_date_row;
    lv_obj_t *setup_date_icon;
    lv_obj_t *setup_date_name;
    lv_obj_t *setup_date_value;
    lv_obj_t *setup_time_row;
    lv_obj_t *setup_time_icon;
    lv_obj_t *setup_time_name;
    lv_obj_t *setup_time_value;
    lv_obj_t *setup_clock_format_row;
    lv_obj_t *setup_clock_format_icon;
    lv_obj_t *setup_clock_format_name;
    lv_obj_t *setup_clock_format_desc;
    lv_obj_t *setup_clock_format_sw;
    lv_obj_t *setup_dock;
    lv_obj_t *setup_dock__root;
    lv_obj_t *setup_dock__dock_btn_drive;
    lv_obj_t *setup_dock__dock_btn_drive_icon;
    lv_obj_t *setup_dock__dock_btn_drive_label;
    lv_obj_t *setup_dock__dock_btn_lights;
    lv_obj_t *setup_dock__dock_btn_lights_icon;
    lv_obj_t *setup_dock__dock_btn_lights_label;
    lv_obj_t *setup_dock__dock_btn_alarms;
    lv_obj_t *setup_dock__dock_btn_alarms_icon;
    lv_obj_t *setup_dock__dock_btn_alarms_label;
    lv_obj_t *setup_dock__dock_btn_setup;
    lv_obj_t *setup_dock__dock_btn_setup_icon;
    lv_obj_t *setup_dock__dock_btn_setup_label;
    lv_obj_t *wifi_header;
    lv_obj_t *wifi_brand;
    lv_obj_t *wifi_brand_sub;
    lv_obj_t *wifi_title;
    lv_obj_t *wifi_sub;
    lv_obj_t *wifi_scan_spinner;
    lv_obj_t *wifi_scan_status;
    lv_obj_t *wifi_scan_list;
    lv_obj_t *wifi_net_0;
    lv_obj_t *wifi_net_icon_0;
    lv_obj_t *wifi_net_ssid_0;
    lv_obj_t *wifi_net_signal_0;
    lv_obj_t *wifi_net_bar1_0;
    lv_obj_t *wifi_net_bar2_0;
    lv_obj_t *wifi_net_bar3_0;
    lv_obj_t *wifi_net_lock_0;
    lv_obj_t *wifi_net_act_0;
    lv_obj_t *wifi_net_1;
    lv_obj_t *wifi_net_icon_1;
    lv_obj_t *wifi_net_ssid_1;
    lv_obj_t *wifi_net_signal_1;
    lv_obj_t *wifi_net_bar1_1;
    lv_obj_t *wifi_net_bar2_1;
    lv_obj_t *wifi_net_bar3_1;
    lv_obj_t *wifi_net_lock_1;
    lv_obj_t *wifi_net_act_1;
    lv_obj_t *wifi_net_2;
    lv_obj_t *wifi_net_icon_2;
    lv_obj_t *wifi_net_ssid_2;
    lv_obj_t *wifi_net_signal_2;
    lv_obj_t *wifi_net_bar1_2;
    lv_obj_t *wifi_net_bar2_2;
    lv_obj_t *wifi_net_bar3_2;
    lv_obj_t *wifi_net_lock_2;
    lv_obj_t *wifi_net_act_2;
    lv_obj_t *wifi_net_3;
    lv_obj_t *wifi_net_icon_3;
    lv_obj_t *wifi_net_ssid_3;
    lv_obj_t *wifi_net_signal_3;
    lv_obj_t *wifi_net_bar1_3;
    lv_obj_t *wifi_net_bar2_3;
    lv_obj_t *wifi_net_bar3_3;
    lv_obj_t *wifi_net_lock_3;
    lv_obj_t *wifi_net_act_3;
    lv_obj_t *wifi_net_4;
    lv_obj_t *wifi_net_icon_4;
    lv_obj_t *wifi_net_ssid_4;
    lv_obj_t *wifi_net_signal_4;
    lv_obj_t *wifi_net_bar1_4;
    lv_obj_t *wifi_net_bar2_4;
    lv_obj_t *wifi_net_bar3_4;
    lv_obj_t *wifi_net_lock_4;
    lv_obj_t *wifi_net_act_4;
    lv_obj_t *wifi_net_5;
    lv_obj_t *wifi_net_icon_5;
    lv_obj_t *wifi_net_ssid_5;
    lv_obj_t *wifi_net_signal_5;
    lv_obj_t *wifi_net_bar1_5;
    lv_obj_t *wifi_net_bar2_5;
    lv_obj_t *wifi_net_bar3_5;
    lv_obj_t *wifi_net_lock_5;
    lv_obj_t *wifi_net_act_5;
    lv_obj_t *wifi_net_6;
    lv_obj_t *wifi_net_icon_6;
    lv_obj_t *wifi_net_ssid_6;
    lv_obj_t *wifi_net_signal_6;
    lv_obj_t *wifi_net_bar1_6;
    lv_obj_t *wifi_net_bar2_6;
    lv_obj_t *wifi_net_bar3_6;
    lv_obj_t *wifi_net_lock_6;
    lv_obj_t *wifi_net_act_6;
    lv_obj_t *wifi_net_7;
    lv_obj_t *wifi_net_icon_7;
    lv_obj_t *wifi_net_ssid_7;
    lv_obj_t *wifi_net_signal_7;
    lv_obj_t *wifi_net_bar1_7;
    lv_obj_t *wifi_net_bar2_7;
    lv_obj_t *wifi_net_bar3_7;
    lv_obj_t *wifi_net_lock_7;
    lv_obj_t *wifi_net_act_7;
    lv_obj_t *wifi_footer;
    lv_obj_t *wifi_btn_refresh;
    lv_obj_t *wifi_btn_refresh_icon;
    lv_obj_t *wifi_btn_refresh_lbl;
    lv_obj_t *wifi_btn_skip;
    lv_obj_t *wifi_btn_skip_lbl;
    lv_obj_t *wifi_password_panel;
    lv_obj_t *wifi_pwd_caption;
    lv_obj_t *wifi_pwd_ssid;
    lv_obj_t *wifi_pwd_input;
    lv_obj_t *wifi_pwd_reveal;
    lv_obj_t *wifi_pwd_reveal_icon;
    lv_obj_t *wifi_pwd_keyboard;
    lv_obj_t *wifi_pwd_cancel;
    lv_obj_t *wifi_pwd_cancel_lbl;
    lv_obj_t *wifi_pwd_connect;
    lv_obj_t *wifi_pwd_connect_lbl;
    lv_obj_t *wifi_connecting_panel;
    lv_obj_t *wifi_conn_brand;
    lv_obj_t *wifi_conn_brand_sub;
    lv_obj_t *wifi_connecting_spinner;
    lv_obj_t *wifi_connecting_caption;
    lv_obj_t *wifi_connecting_ssid;
    lv_obj_t *wifi_connecting_hint;
    lv_obj_t *mqtt_brand;
    lv_obj_t *mqtt_brand_text;
    lv_obj_t *mqtt_caption;
    lv_obj_t *mqtt_step;
    lv_obj_t *mqtt_input;
    lv_obj_t *mqtt_keyboard;
    lv_obj_t *mqtt_footer;
    lv_obj_t *mqtt_back;
    lv_obj_t *mqtt_back_lbl;
    lv_obj_t *mqtt_next;
    lv_obj_t *mqtt_next_lbl;
    lv_obj_t *mqtt_connecting_panel;
    lv_obj_t *mqtt_conn_brand;
    lv_obj_t *mqtt_conn_brand_sub;
    lv_obj_t *mqtt_connecting_spinner;
    lv_obj_t *mqtt_connecting_caption;
    lv_obj_t *mqtt_connecting_host;
    lv_obj_t *mqtt_connecting_hint;
    lv_obj_t *rename_title;
    lv_obj_t *rename_subtitle;
    lv_obj_t *sensor_rename_input;
    lv_obj_t *sensor_rename_kb;
    lv_obj_t *rename_footer;
    lv_obj_t *rename_cancel_btn;
    lv_obj_t *rename_cancel_lbl;
    lv_obj_t *rename_save_btn;
    lv_obj_t *rename_save_lbl;
    lv_obj_t *header_bar;
    lv_obj_t *clock_brand_icon;
    lv_obj_t *clock_brand_text;
    lv_obj_t *clock_brand_divider;
    lv_obj_t *clock_brand_subtitle;
    lv_obj_t *clock_warning_pill;
    lv_obj_t *clock_warning_dot;
    lv_obj_t *clock_warning_text;
    lv_obj_t *clock_theme_btn;
    lv_obj_t *clock_theme_icon;
    lv_obj_t *clock_dow;
    lv_obj_t *digit_hh;
    lv_obj_t *clock_colon;
    lv_obj_t *digit_mm;
    lv_obj_t *clock_ampm;
    lv_obj_t *clock_seconds;
    lv_obj_t *clock_date_label;
    lv_obj_t *clock_last_header;
    lv_obj_t *clock_ago_icon;
    lv_obj_t *clock_ago_label;
    lv_obj_t *clock_bat_card;
    lv_obj_t *clock_bat_icon;
    lv_obj_t *clock_bat_title;
    lv_obj_t *clock_bat_dot;
    lv_obj_t *clock_bat_value;
    lv_obj_t *clock_bat_unit;
    lv_obj_t *clock_bat_sub;
    lv_obj_t *clock_sol_card;
    lv_obj_t *clock_sol_icon;
    lv_obj_t *clock_sol_title;
    lv_obj_t *clock_sol_dot;
    lv_obj_t *clock_sol_value;
    lv_obj_t *clock_sol_unit;
    lv_obj_t *clock_sol_sub;
    lv_obj_t *clock_fresh_card;
    lv_obj_t *clock_fresh_icon;
    lv_obj_t *clock_fresh_title;
    lv_obj_t *clock_fresh_dot;
    lv_obj_t *clock_fresh_value;
    lv_obj_t *clock_fresh_unit;
    lv_obj_t *clock_fresh_sub;
    lv_obj_t *footer_bar;
    lv_obj_t *clock_retry_btn;
    lv_obj_t *clock_retry_icon;
    lv_obj_t *clock_retry_label;
    lv_obj_t *clock_settings_btn;
    lv_obj_t *clock_settings_icon;
    lv_obj_t *clock_settings_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_PAGE_DRIVE = 1,
    SCREEN_ID_PAGE_LIGHTS = 2,
    SCREEN_ID_PAGE_ALARMS = 3,
    SCREEN_ID_PAGE_SETUP = 4,
    SCREEN_ID_PAGE_WIFI_SETUP = 5,
    SCREEN_ID_PAGE_WIFI_CONNECTING = 6,
    SCREEN_ID_PAGE_MQTT_SETUP = 7,
    SCREEN_ID_PAGE_MQTT_CONNECTING = 8,
    SCREEN_ID_PAGE_RENAME_SENSOR = 9,
    SCREEN_ID_PAGE_CLOCK_MODE = 10,
};

void create_screen_page_drive();
void tick_screen_page_drive();

void create_screen_page_lights();
void tick_screen_page_lights();

void create_screen_page_alarms();
void tick_screen_page_alarms();

void create_screen_page_setup();
void tick_screen_page_setup();

void create_screen_page_wifi_setup();
void tick_screen_page_wifi_setup();

void create_screen_page_wifi_connecting();
void tick_screen_page_wifi_connecting();

void create_screen_page_mqtt_setup();
void tick_screen_page_mqtt_setup();

void create_screen_page_mqtt_connecting();
void tick_screen_page_mqtt_connecting();

void create_screen_page_rename_sensor();
void tick_screen_page_rename_sensor();

void create_screen_page_clock_mode();
void tick_screen_page_clock_mode();

void create_user_widget_top_status_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_top_status_bar(int startWidgetIndex);

void create_user_widget_bottom_tab_bar(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_bottom_tab_bar(int startWidgetIndex);

enum Themes {
    THEME_ID_DEFAULT,
    THEME_ID_DARK,
};
enum Colors {
    COLOR_ID_ACCENT_COLOR,
    COLOR_ID_BACKGROUND_BLACK,
    COLOR_ID_BACKGROUND_CONTENT,
    COLOR_ID_BACKGROUND_NOT_SELECTED,
    COLOR_ID_BACKGROUND_PANEL,
    COLOR_ID_BACKGROUND_SELECTED,
    COLOR_ID_COOL,
    COLOR_ID_FOREGROUND_WHITE,
    COLOR_ID_HOT,
    COLOR_ID_PRIMARY_TEXT_COLOR,
    COLOR_ID_SECONDARY_TEXT_COLOR,
    COLOR_ID_SUCCESS,
    COLOR_ID_WARNING,
    COLOR_ID_CLOCK_SCREEN_BG,
    COLOR_ID_CLOCK_CHROME_BG,
    COLOR_ID_CLOCK_BAR_BORDER,
    COLOR_ID_CLOCK_DIVIDER_COLOR,
    COLOR_ID_CLOCK_TEXT_PRIMARY,
    COLOR_ID_CLOCK_TEXT_SECONDARY,
    COLOR_ID_CLOCK_TEXT_MUTED,
    COLOR_ID_CLOCK_ACCENT,
    COLOR_ID_CLOCK_ACCENT_SOFT,
    COLOR_ID_CLOCK_CARD_BG,
    COLOR_ID_CLOCK_CARD_BORDER,
    COLOR_ID_CLOCK_VALUE_MUTED,
    COLOR_ID_CLOCK_UNIT_COLOR,
    COLOR_ID_CLOCK_SUB_COLOR,
    COLOR_ID_CLOCK_PILL_BG,
    COLOR_ID_CLOCK_PILL_BORDER,
    COLOR_ID_CLOCK_PILL_TEXT,
    COLOR_ID_CLOCK_PILL_DOT,
    COLOR_ID_CLOCK_STALE_DOT,
    COLOR_ID_CLOCK_RETRY_TEXT,
    COLOR_ID_CHROME_BORDER,
    COLOR_ID_PANEL_BORDER,
    COLOR_ID_SURFACE_SUNK,
    COLOR_ID_MUTED_TEXT_COLOR,
    COLOR_ID_TRACK_COLOR,
    COLOR_ID_GAUGE_INNER_TOP,
    COLOR_ID_GAUGE_INNER_BOT,
    COLOR_ID_OK_DIM,
    COLOR_ID_GREEN_TILE_BG,
    COLOR_ID_GREEN_TILE_BD,
    COLOR_ID_GREEN_LABEL,
    COLOR_ID_RED_TILE_BG,
    COLOR_ID_RED_TILE_BD,
    COLOR_ID_RED_LABEL,
    COLOR_ID_METAL_TOP,
    COLOR_ID_METAL_BOT,
    COLOR_ID_METAL_BD,
    COLOR_ID_TIRE_MID,
    COLOR_ID_TIRE_EDGE,
    COLOR_ID_TIRE_OK_BD,
    COLOR_ID_TIRE_OK_TEXT,
    COLOR_ID_WINDSHIELD,
    COLOR_ID_WINDSHIELD_BD,
    COLOR_ID_AMBER_TEXT,
    COLOR_ID_ALARM_BG_TOP,
    COLOR_ID_ALARM_BG_BOT,
    COLOR_ID_ALARM_BTN_TEXT,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][60];
extern uint32_t active_theme_index;

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/