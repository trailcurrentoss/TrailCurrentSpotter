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
    lv_obj_t *drive_status_bar;
    lv_obj_t *drive_status_bar__root;
    lv_obj_t *drive_status_bar__status_brand_icon;
    lv_obj_t *drive_status_bar__status_brand_text;
    lv_obj_t *drive_status_bar__status_link_dot;
    lv_obj_t *drive_status_bar__status_link_label;
    lv_obj_t *drive_status_bar__status_signal_left;
    lv_obj_t *drive_status_bar__status_signal_right;
    lv_obj_t *drive_status_bar__status_speed_value;
    lv_obj_t *drive_status_bar__status_speed_unit;
    lv_obj_t *drive_status_bar__status_time;
    lv_obj_t *drive_body;
    lv_obj_t *drive_card_bat;
    lv_obj_t *drive_bat_title;
    lv_obj_t *drive_bat_arc;
    lv_obj_t *drive_bat_value;
    lv_obj_t *drive_bat_pct_sym;
    lv_obj_t *drive_bat_volts;
    lv_obj_t *drive_bat_remain;
    lv_obj_t *drive_card_tires;
    lv_obj_t *drive_tire_title;
    lv_obj_t *drive_tire_sub;
    lv_obj_t *drive_tire_l1;
    lv_obj_t *drive_tire_l1_psi;
    lv_obj_t *drive_tire_l1_lbl;
    lv_obj_t *drive_tire_r1;
    lv_obj_t *drive_tire_r1_psi;
    lv_obj_t *drive_tire_r1_lbl;
    lv_obj_t *drive_tire_l2;
    lv_obj_t *drive_tire_l2_psi;
    lv_obj_t *drive_tire_l2_lbl;
    lv_obj_t *drive_tire_r2;
    lv_obj_t *drive_tire_r2_psi;
    lv_obj_t *drive_tire_r2_lbl;
    lv_obj_t *drive_bsm_warning;
    lv_obj_t *drive_bsm_warn_icon;
    lv_obj_t *drive_bsm_warn_text;
    lv_obj_t *drive_card_solar;
    lv_obj_t *drive_solar_title;
    lv_obj_t *drive_solar_arc;
    lv_obj_t *drive_solar_icon;
    lv_obj_t *drive_solar_value;
    lv_obj_t *drive_solar_unit_sym;
    lv_obj_t *drive_solar_units_label;
    lv_obj_t *drive_solar_pct;
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
    lv_obj_t *lights_status_bar__status_link_dot;
    lv_obj_t *lights_status_bar__status_link_label;
    lv_obj_t *lights_status_bar__status_signal_left;
    lv_obj_t *lights_status_bar__status_signal_right;
    lv_obj_t *lights_status_bar__status_speed_value;
    lv_obj_t *lights_status_bar__status_speed_unit;
    lv_obj_t *lights_status_bar__status_time;
    lv_obj_t *lights_body;
    lv_obj_t *lights_header;
    lv_obj_t *lights_prev_zone;
    lv_obj_t *lights_prev_icon;
    lv_obj_t *lights_zone_icon;
    lv_obj_t *lights_zone_name;
    lv_obj_t *lights_zone_meta;
    lv_obj_t *lights_next_zone;
    lv_obj_t *lights_next_icon;
    lv_obj_t *lights_grid;
    lv_obj_t *lights_btn_1;
    lv_obj_t *lights_btn_1_icon;
    lv_obj_t *lights_btn_1_name;
    lv_obj_t *lights_btn_1_state;
    lv_obj_t *lights_btn_2;
    lv_obj_t *lights_btn_2_icon;
    lv_obj_t *lights_btn_2_name;
    lv_obj_t *lights_btn_2_state;
    lv_obj_t *lights_btn_3;
    lv_obj_t *lights_btn_3_icon;
    lv_obj_t *lights_btn_3_name;
    lv_obj_t *lights_btn_3_state;
    lv_obj_t *lights_btn_4;
    lv_obj_t *lights_btn_4_icon;
    lv_obj_t *lights_btn_4_name;
    lv_obj_t *lights_btn_4_state;
    lv_obj_t *lights_btn_5;
    lv_obj_t *lights_btn_5_icon;
    lv_obj_t *lights_btn_5_name;
    lv_obj_t *lights_btn_5_state;
    lv_obj_t *lights_btn_6;
    lv_obj_t *lights_btn_6_icon;
    lv_obj_t *lights_btn_6_name;
    lv_obj_t *lights_btn_6_state;
    lv_obj_t *lights_footer;
    lv_obj_t *lights_all_on;
    lv_obj_t *lights_all_on_lbl;
    lv_obj_t *lights_all_off;
    lv_obj_t *lights_all_off_lbl;
    lv_obj_t *lights_dot_0;
    lv_obj_t *lights_dot_1;
    lv_obj_t *lights_dot_2;
    lv_obj_t *lights_dot_3;
    lv_obj_t *lights_dot_4;
    lv_obj_t *lights_dot_5;
    lv_obj_t *lights_off_all_devices;
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
    lv_obj_t *alarms_status_bar__status_link_dot;
    lv_obj_t *alarms_status_bar__status_link_label;
    lv_obj_t *alarms_status_bar__status_signal_left;
    lv_obj_t *alarms_status_bar__status_signal_right;
    lv_obj_t *alarms_status_bar__status_speed_value;
    lv_obj_t *alarms_status_bar__status_speed_unit;
    lv_obj_t *alarms_status_bar__status_time;
    lv_obj_t *alarms_body;
    lv_obj_t *alarms_header;
    lv_obj_t *alarms_title;
    lv_obj_t *alarms_subtitle;
    lv_obj_t *alarms_armed_icon;
    lv_obj_t *alarms_armed_count;
    lv_obj_t *alarms_list;
    lv_obj_t *alarms_grp_lbl_0;
    lv_obj_t *alarms_grp_desc_0;
    lv_obj_t *alarm_galley_cab_row;
    lv_obj_t *alarm_galley_cab_name;
    lv_obj_t *alarm_galley_cab;
    lv_obj_t *alarm_pantry_row;
    lv_obj_t *alarm_pantry_name;
    lv_obj_t *alarm_pantry;
    lv_obj_t *alarm_wardrobe_row;
    lv_obj_t *alarm_wardrobe_name;
    lv_obj_t *alarm_wardrobe;
    lv_obj_t *alarm_bath_door_row;
    lv_obj_t *alarm_bath_door_name;
    lv_obj_t *alarm_bath_door;
    lv_obj_t *alarm_entry_row;
    lv_obj_t *alarm_entry_name;
    lv_obj_t *alarm_entry;
    lv_obj_t *alarm_pass_thru_row;
    lv_obj_t *alarm_pass_thru_name;
    lv_obj_t *alarm_pass_thru;
    lv_obj_t *alarms_grp_lbl_6;
    lv_obj_t *alarms_grp_desc_6;
    lv_obj_t *alarm_bath_light_row;
    lv_obj_t *alarm_bath_light_name;
    lv_obj_t *alarm_bath_light;
    lv_obj_t *alarm_porch_light_row;
    lv_obj_t *alarm_porch_light_name;
    lv_obj_t *alarm_porch_light;
    lv_obj_t *alarm_galley_light_row;
    lv_obj_t *alarm_galley_light_name;
    lv_obj_t *alarm_galley_light;
    lv_obj_t *alarms_grp_lbl_9;
    lv_obj_t *alarms_grp_desc_9;
    lv_obj_t *alarm_fridge_row;
    lv_obj_t *alarm_fridge_name;
    lv_obj_t *alarm_fridge;
    lv_obj_t *alarm_pump_row;
    lv_obj_t *alarm_pump_name;
    lv_obj_t *alarm_pump;
    lv_obj_t *alarm_heater_row;
    lv_obj_t *alarm_heater_name;
    lv_obj_t *alarm_heater;
    lv_obj_t *alarm_inverter_row;
    lv_obj_t *alarm_inverter_name;
    lv_obj_t *alarm_inverter;
    lv_obj_t *alarms_grp_lbl_13;
    lv_obj_t *alarms_grp_desc_13;
    lv_obj_t *alarm_co2_row;
    lv_obj_t *alarm_co2_name;
    lv_obj_t *alarm_co2;
    lv_obj_t *alarm_smoke_row;
    lv_obj_t *alarm_smoke_name;
    lv_obj_t *alarm_smoke;
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
    lv_obj_t *setup_status_bar__status_link_dot;
    lv_obj_t *setup_status_bar__status_link_label;
    lv_obj_t *setup_status_bar__status_signal_left;
    lv_obj_t *setup_status_bar__status_signal_right;
    lv_obj_t *setup_status_bar__status_speed_value;
    lv_obj_t *setup_status_bar__status_speed_unit;
    lv_obj_t *setup_status_bar__status_time;
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
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_PAGE_DRIVE = 1,
    SCREEN_ID_PAGE_LIGHTS = 2,
    SCREEN_ID_PAGE_ALARMS = 3,
    SCREEN_ID_PAGE_SETUP = 4,
};

void create_screen_page_drive();
void tick_screen_page_drive();

void create_screen_page_lights();
void tick_screen_page_lights();

void create_screen_page_alarms();
void tick_screen_page_alarms();

void create_screen_page_setup();
void tick_screen_page_setup();

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
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][12];
extern uint32_t active_theme_index;

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/