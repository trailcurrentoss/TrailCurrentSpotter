#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lvgl.h"
#include "ui/screens.h"
#include "ui/vars.h"
#include "ui/styles.h"

static char date_time_utc[100] = {0};
static char date_time_local[100] = {0};

/* Portable timegm() replacement */
static time_t my_timegm(struct tm *tm)
{
    char *old_tz = getenv("TZ");
    char *saved_tz = NULL;

    if (old_tz) {
        saved_tz = strdup(old_tz);
    }
    setenv("TZ", "UTC0", 1);
    tzset();
    tm->tm_isdst = 0;

    time_t t = mktime(tm);

    setenv("TZ", get_var_current_time_zone_string(), 1);
    tzset();

    if (saved_tz) {
        free(saved_tz);
    }
    return t;
}

/* --- Solar --- */

static int32_t solar_wattage;
int32_t get_var_solar_wattage(void) { return solar_wattage; }
void set_var_solar_wattage(int32_t value) { solar_wattage = value; }

static char solar_status[100] = {0};
const char *get_var_solar_status(void) { return solar_status; }
void set_var_solar_status(const char *value) {
    strncpy(solar_status, value, sizeof(solar_status) - 1);
    solar_status[sizeof(solar_status) - 1] = '\0';
}

/* --- Shore power --- */

static char shore_power_connection_status[100] = {0};
const char *get_var_shore_power_connection_status(void) { return shore_power_connection_status; }
void set_var_shore_power_connection_status(const char *value) {
    strncpy(shore_power_connection_status, value, sizeof(shore_power_connection_status) - 1);
    shore_power_connection_status[sizeof(shore_power_connection_status) - 1] = '\0';
}

/* --- PDM device status (8 devices) --- */

static int32_t pdm01_device01_status;
int32_t get_var_pdm01_device01_status(void) { return pdm01_device01_status; }
void set_var_pdm01_device01_status(int32_t value) {
    pdm01_device01_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device01_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device01, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device01_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device01, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device01_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device01_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device02_status;
int32_t get_var_pdm01_device02_status(void) { return pdm01_device02_status; }
void set_var_pdm01_device02_status(int32_t value) {
    pdm01_device02_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device02_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device02, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device02_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device02, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device02_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device02_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device03_status;
int32_t get_var_pdm01_device03_status(void) { return pdm01_device03_status; }
void set_var_pdm01_device03_status(int32_t value) {
    pdm01_device03_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device03_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device03, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device03_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device03, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device03_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device03_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device04_status;
int32_t get_var_pdm01_device04_status(void) { return pdm01_device04_status; }
void set_var_pdm01_device04_status(int32_t value) {
    pdm01_device04_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device04_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device04, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device04_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device04, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device04_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device04_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device05_status;
int32_t get_var_pdm01_device05_status(void) { return pdm01_device05_status; }
void set_var_pdm01_device05_status(int32_t value) {
    pdm01_device05_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device05_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device05, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device05_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device05, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device05_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device05_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device06_status;
int32_t get_var_pdm01_device06_status(void) { return pdm01_device06_status; }
void set_var_pdm01_device06_status(int32_t value) {
    pdm01_device06_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device06_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device06, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device06_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device06, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device06_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device06_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device07_status;
int32_t get_var_pdm01_device07_status(void) { return pdm01_device07_status; }
void set_var_pdm01_device07_status(int32_t value) {
    pdm01_device07_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device07_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device07, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device07_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device07, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device07_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device07_label, LV_STATE_CHECKED);
    }
}

static int32_t pdm01_device08_status;
int32_t get_var_pdm01_device08_status(void) { return pdm01_device08_status; }
void set_var_pdm01_device08_status(int32_t value) {
    pdm01_device08_status = value;
    if (value > 0) {
        lv_obj_add_state(objects.lbl_device08_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device08, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device08_label, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.btn_device08, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device08_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device08_label, LV_STATE_CHECKED);
    }
}

/* --- Battery --- */

static float battery_voltage;
float get_var_battery_voltage(void) { return battery_voltage; }
void set_var_battery_voltage(float value) { battery_voltage = value; }

static int32_t battery_soc_percentage;
int32_t get_var_battery_soc_percentage(void) { return battery_soc_percentage; }
void set_var_battery_soc_percentage(int32_t value) { battery_soc_percentage = value; }

/* --- Power consumption --- */

static char current_power_consumption_in_watts[100] = {0};
const char *get_var_current_power_consumption_in_watts(void) { return current_power_consumption_in_watts; }
void set_var_current_power_consumption_in_watts(const char *value) {
    strncpy(current_power_consumption_in_watts, value, sizeof(current_power_consumption_in_watts) - 1);
    current_power_consumption_in_watts[sizeof(current_power_consumption_in_watts) - 1] = '\0';
    lv_label_set_text(objects.label_remaining_cacpity_1, current_power_consumption_in_watts);
}

/* --- Speed --- */

static int32_t current_speed_value;
int32_t get_var_current_speed_value(void) { return current_speed_value; }
void set_var_current_speed_value(int32_t value) {
    current_speed_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    lv_label_set_text(objects.label_current_speed_value, buf);
}

/* --- MAC address --- */

static char mcu_mac_address[100] = {0};
const char *get_var_mcu_mac_address(void) { return mcu_mac_address; }
void set_var_mcu_mac_address(const char *value) {
    strncpy(mcu_mac_address, value, sizeof(mcu_mac_address) - 1);
    mcu_mac_address[sizeof(mcu_mac_address) - 1] = '\0';
    lv_label_set_text(objects.mcu_mac_address_value, value);
}

/* --- GPS --- */

static int32_t number_of_satellites;
int32_t get_var_number_of_satellites(void) { return number_of_satellites; }
void set_var_number_of_satellites(int32_t value) {
    number_of_satellites = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    lv_label_set_text(objects.label_number_of_satellite_value, buf);
}

static float current_course_over_ground;
float get_var_current_course_over_ground(void) { return current_course_over_ground; }
void set_var_current_course_over_ground(float value) { current_course_over_ground = value; }

static char gnss_mode[100] = {0};
const char *get_var_gnss_mode(void) { return gnss_mode; }
void set_var_gnss_mode(const char *value) {
    strncpy(gnss_mode, value, sizeof(gnss_mode) - 1);
    gnss_mode[sizeof(gnss_mode) - 1] = '\0';
    lv_label_set_text(objects.gnss_mode_value, value);
}

static float current_altitude_value;
float get_var_current_altitude_value(void) { return current_altitude_value; }
void set_var_current_altitude_value(float value) {
    current_altitude_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    lv_label_set_text(objects.label_altitude_in_feet_value, buf);
}

static float current_latitude;
float get_var_current_latitude(void) { return current_latitude; }
void set_var_current_latitude(float value) {
    current_latitude = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%10.6f", value);
    lv_label_set_text(objects.label_current_lat_value, buf);
}

static float current_longitude;
float get_var_current_longitude(void) { return current_longitude; }
void set_var_current_longitude(float value) {
    current_longitude = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%11.6f", value);
    lv_label_set_text(objects.label_current_long_value, buf);
}

/* --- Date/Time --- */

static char current_date_time[100] = {0};
const char *get_var_current_date_time(void) { return current_date_time; }
void set_var_current_date_time(const char *value) {
    strncpy(date_time_utc, value, sizeof(date_time_utc) - 1);
    date_time_utc[sizeof(date_time_utc) - 1] = '\0';

    struct tm tm_utc = {0};
    if (strptime(date_time_utc, "%Y-%m-%d %H:%M:%S", &tm_utc) != NULL) {
        time_t t_utc = my_timegm(&tm_utc);
        struct tm *tm_local = localtime(&t_utc);
        strftime(date_time_local, sizeof(date_time_local),
                 "%m/%d/%Y %I:%M %p", tm_local);
    } else {
        date_time_local[0] = '\0';
    }
}

/* --- Temperature & Humidity --- */

static float current_temperature_value;
float get_var_current_temperature_value(void) { return current_temperature_value; }
void set_var_current_temperature_value(float value) {
    current_temperature_value = value;
    lv_bar_set_value(objects.bar_interior_temperature, (int32_t)value, LV_ANIM_ON);
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    lv_label_set_text(objects.label_interior_temp_value, buf);
}

static float current_humidity_value;
float get_var_current_humidity_value(void) { return current_humidity_value; }
void set_var_current_humidity_value(float value) {
    current_humidity_value = value;
    lv_arc_set_value(objects.arc_relative_humidity, (int16_t)value);
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    lv_label_set_text(objects.label_humidty_level, buf);
}

/* --- User settings --- */

static bool user_settings_changed;
bool get_var_user_settings_changed(void) { return user_settings_changed; }
void set_var_user_settings_changed(bool value) { user_settings_changed = value; }

static int32_t selected_theme;
int32_t get_var_selected_theme(void) { return selected_theme; }
void set_var_selected_theme(int32_t value) {
    selected_theme = value;
    lv_obj_clear_state(objects.btn_theme_dark, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.btn_theme_light, LV_STATE_CHECKED);
    if (selected_theme == 0) {
        change_color_theme(THEME_ID_DEFAULT);
        lv_obj_add_state(objects.btn_theme_light, LV_STATE_CHECKED);
    } else if (selected_theme == 1) {
        change_color_theme(THEME_ID_DARK);
        lv_obj_add_state(objects.btn_theme_dark, LV_STATE_CHECKED);
    }
}

static int32_t screen_timeout_value;
int32_t get_var_screen_timeout_value(void) { return screen_timeout_value; }
void set_var_screen_timeout_value(int32_t value) {
    screen_timeout_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    lv_label_set_text(objects.label_screen_timeout_value, buf);
}

static bool keep_screen_on_while_driving;
bool get_var_keep_screen_on_while_driving(void) { return keep_screen_on_while_driving; }
void set_var_keep_screen_on_while_driving(bool value) {
    keep_screen_on_while_driving = value;
    if (value) {
        lv_obj_add_state(objects.check_box_keep_screen_on_while_in_motion, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.check_box_keep_screen_on_while_in_motion, LV_STATE_CHECKED);
    }
}

/* --- WiFi / Connection state --- */

static bool wifi_connected;
bool get_var_wifi_connected(void) { return wifi_connected; }
void set_var_wifi_connected(bool value) { wifi_connected = value; }

static bool websocket_connected;
bool get_var_websocket_connected(void) { return websocket_connected; }
void set_var_websocket_connected(bool value) { websocket_connected = value; }

static char wifi_ssid[64] = {0};
const char *get_var_wifi_ssid(void) { return wifi_ssid; }
void set_var_wifi_ssid(const char *value) {
    strncpy(wifi_ssid, value, sizeof(wifi_ssid) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
}

static char server_url_var[256] = {0};
const char *get_var_server_url(void) { return server_url_var; }
void set_var_server_url(const char *value) {
    strncpy(server_url_var, value, sizeof(server_url_var) - 1);
    server_url_var[sizeof(server_url_var) - 1] = '\0';
}

static bool api_key_configured;
bool get_var_api_key_configured(void) { return api_key_configured; }
void set_var_api_key_configured(bool value) { api_key_configured = value; }

static char connection_status_text[100] = {0};
const char *get_var_connection_status_text(void) { return connection_status_text; }
void set_var_connection_status_text(const char *value) {
    strncpy(connection_status_text, value, sizeof(connection_status_text) - 1);
    connection_status_text[sizeof(connection_status_text) - 1] = '\0';
}

static char current_time_zone_string[100] = {0};
const char *get_var_current_time_zone_string(void) { return current_time_zone_string; }
void set_var_current_time_zone_string(const char *value) {
    strncpy(current_time_zone_string, value, sizeof(current_time_zone_string) - 1);
    current_time_zone_string[sizeof(current_time_zone_string) - 1] = '\0';
}

/* --- Variables declared in vars.h but not yet used --- */

static float power_time_to_go_measurement;
float get_var_power_time_to_go_measurement(void) { return power_time_to_go_measurement; }
void set_var_power_time_to_go_measurement(float value) { power_time_to_go_measurement = value; }

static char power_time_to_go_measurement_type[100] = {0};
const char *get_var_power_time_to_go_measurement_type(void) { return power_time_to_go_measurement_type; }
void set_var_power_time_to_go_measurement_type(const char *value) {
    strncpy(power_time_to_go_measurement_type, value, sizeof(power_time_to_go_measurement_type) - 1);
    power_time_to_go_measurement_type[sizeof(power_time_to_go_measurement_type) - 1] = '\0';
}
