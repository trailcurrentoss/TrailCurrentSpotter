#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lvgl.h"
#include "ui/screens.h"
#include "ui/vars.h"
#include "ui/styles.h"

/* Defined in main.c — seeds the system clock from a Bearing UTC string and
 * triggers the top-toolbar clock to repaint. */
extern void spotter_clock_set_from_iso_utc(const char *iso_utc);

/* --- Solar --- */

static int32_t solar_wattage;
int32_t get_var_solar_wattage(void) { return solar_wattage; }
void set_var_solar_wattage(int32_t value) {
    solar_wattage = value;
    if (objects.drive_solar_value) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", (int)value);
        lv_label_set_text(objects.drive_solar_value, buf);
    }
    /* Drive arc: scale to a 600 W "capacity" reference so the ring fills as
     * the array approaches full output. If the actual array is smaller/larger
     * the arc still gives a useful visual without needing the user to enter
     * an array-spec. */
    if (objects.drive_solar_arc) {
        int pct = value < 0 ? 0 : (value > 600 ? 100 : (value * 100) / 600);
        lv_arc_set_value(objects.drive_solar_arc, (int16_t)pct);
    }
}

static char solar_status[100] = {0};
const char *get_var_solar_status(void) { return solar_status; }
void set_var_solar_status(const char *value) {
    strncpy(solar_status, value, sizeof(solar_status) - 1);
    solar_status[sizeof(solar_status) - 1] = '\0';
    /* Map raw status strings to UI-friendly text shown under the solar arc. */
    if (objects.drive_solar_pct) {
        const char *display;
        if      (strcmp(value, "solar") == 0)         display = "Solar charging";
        else if (strcmp(value, "shore") == 0)         display = "Shore power";
        else if (strcmp(value, "not_charging") == 0)  display = "Not charging";
        else if (strcmp(value, "float") == 0)         display = "Float charge";
        else if (strcmp(value, "absorption") == 0)    display = "Absorption";
        else if (strcmp(value, "bulk") == 0)          display = "Bulk charge";
        else                                          display = value;
        lv_label_set_text(objects.drive_solar_pct, display);
    }
}

/* --- Shore power --- */

static char shore_power_connection_status[100] = {0};
const char *get_var_shore_power_connection_status(void) { return shore_power_connection_status; }
void set_var_shore_power_connection_status(const char *value) {
    strncpy(shore_power_connection_status, value, sizeof(shore_power_connection_status) - 1);
    shore_power_connection_status[sizeof(shore_power_connection_status) - 1] = '\0';
}

/* --- Battery --- */

static float battery_voltage;
float get_var_battery_voltage(void) { return battery_voltage; }
void set_var_battery_voltage(float value) {
    battery_voltage = value;
    if (objects.drive_bat_volts) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%.1f", value);
        lv_label_set_text(objects.drive_bat_volts, buf);
    }
}

static int32_t battery_soc_percentage;
int32_t get_var_battery_soc_percentage(void) { return battery_soc_percentage; }
void set_var_battery_soc_percentage(int32_t value) {
    battery_soc_percentage = value;
    if (objects.drive_bat_value) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", (int)value);
        lv_label_set_text(objects.drive_bat_value, buf);
    }
    if (objects.drive_bat_arc) {
        lv_arc_set_value(objects.drive_bat_arc, (int16_t)value);
    }
}

/* --- Power consumption --- */

static char current_power_consumption_in_watts[100] = {0};
const char *get_var_current_power_consumption_in_watts(void) { return current_power_consumption_in_watts; }
void set_var_current_power_consumption_in_watts(const char *value) {
    strncpy(current_power_consumption_in_watts, value, sizeof(current_power_consumption_in_watts) - 1);
    current_power_consumption_in_watts[sizeof(current_power_consumption_in_watts) - 1] = '\0';
    /* widget removed in new GUI */
}

/* --- Speed --- */

static int32_t current_speed_value;
int32_t get_var_current_speed_value(void) { return current_speed_value; }
void set_var_current_speed_value(int32_t value) {
    current_speed_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    /* TopStatusBar is instanced on all 3 pages — push to every per-instance copy */
    lv_obj_t *speed_widgets[] = {
        objects.drive_status_bar__status_speed_value,
        objects.alarms_status_bar__status_speed_value,
        objects.setup_status_bar__status_speed_value,
    };
    for (size_t i = 0; i < sizeof(speed_widgets)/sizeof(*speed_widgets); i++) {
        if (speed_widgets[i]) lv_label_set_text(speed_widgets[i], buf);
    }
}

/* --- MAC address --- */

static char mcu_mac_address[100] = {0};
const char *get_var_mcu_mac_address(void) { return mcu_mac_address; }
void set_var_mcu_mac_address(const char *value) {
    strncpy(mcu_mac_address, value, sizeof(mcu_mac_address) - 1);
    mcu_mac_address[sizeof(mcu_mac_address) - 1] = '\0';
    /* widget removed in new GUI */
}

/* --- GPS --- */

static int32_t number_of_satellites;
int32_t get_var_number_of_satellites(void) { return number_of_satellites; }
void set_var_number_of_satellites(int32_t value) {
    number_of_satellites = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    /* widget removed in new GUI */
}

static float current_course_over_ground;
float get_var_current_course_over_ground(void) { return current_course_over_ground; }
void set_var_current_course_over_ground(float value) { current_course_over_ground = value; }

static char gnss_mode[100] = {0};
const char *get_var_gnss_mode(void) { return gnss_mode; }
void set_var_gnss_mode(const char *value) {
    strncpy(gnss_mode, value, sizeof(gnss_mode) - 1);
    gnss_mode[sizeof(gnss_mode) - 1] = '\0';
    /* widget removed in new GUI */
}

static float current_altitude_value;
float get_var_current_altitude_value(void) { return current_altitude_value; }
void set_var_current_altitude_value(float value) {
    current_altitude_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    /* widget removed in new GUI */
}

static float current_latitude;
float get_var_current_latitude(void) { return current_latitude; }
void set_var_current_latitude(float value) {
    current_latitude = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%10.6f", value);
    /* widget removed in new GUI */
}

static float current_longitude;
float get_var_current_longitude(void) { return current_longitude; }
void set_var_current_longitude(float value) {
    current_longitude = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%11.6f", value);
    /* widget removed in new GUI */
}

/* --- Date/Time ---
 * Value arrives as a UTC ISO string ("YYYY-MM-DD HH:MM:SS") from Bearing
 * via MQTT topic local/gps/time. The clock module in main.c owns the
 * system time and the user-selected POSIX timezone; we just relay. */

static char current_date_time[100] = {0};
const char *get_var_current_date_time(void) { return current_date_time; }
void set_var_current_date_time(const char *value) {
    if (!value) return;
    strncpy(current_date_time, value, sizeof(current_date_time) - 1);
    current_date_time[sizeof(current_date_time) - 1] = '\0';
    spotter_clock_set_from_iso_utc(current_date_time);
}

/* --- Temperature & Humidity --- */

static float current_temperature_value;
float get_var_current_temperature_value(void) { return current_temperature_value; }
void set_var_current_temperature_value(float value) {
    current_temperature_value = value;
    /* widget removed in new GUI */
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    /* widget removed in new GUI */
}

static float current_humidity_value;
float get_var_current_humidity_value(void) { return current_humidity_value; }
void set_var_current_humidity_value(float value) {
    current_humidity_value = value;
    /* widget removed in new GUI */
    char buf[16];
    snprintf(buf, sizeof(buf), "%.0f", value);
    /* widget removed in new GUI */
}

/* --- User settings --- */

static bool user_settings_changed;
bool get_var_user_settings_changed(void) { return user_settings_changed; }
void set_var_user_settings_changed(bool value) { user_settings_changed = value; }

static int32_t selected_theme;
int32_t get_var_selected_theme(void) { return selected_theme; }
void set_var_selected_theme(int32_t value) {
    selected_theme = value;
    lv_obj_clear_state(objects.setup_theme_dark, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setup_theme_light, LV_STATE_CHECKED);
    if (selected_theme == 0) {
        change_color_theme(THEME_ID_DEFAULT);
        lv_obj_add_state(objects.setup_theme_light, LV_STATE_CHECKED);
    } else if (selected_theme == 1) {
        change_color_theme(THEME_ID_DARK);
        lv_obj_add_state(objects.setup_theme_dark, LV_STATE_CHECKED);
    }
}

static int32_t screen_timeout_value;
int32_t get_var_screen_timeout_value(void) { return screen_timeout_value; }
void set_var_screen_timeout_value(int32_t value) {
    screen_timeout_value = value;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", (int)value);
    /* widget removed in new GUI */
}

static bool keep_screen_on_while_driving;
bool get_var_keep_screen_on_while_driving(void) { return keep_screen_on_while_driving; }
void set_var_keep_screen_on_while_driving(bool value) {
    keep_screen_on_while_driving = value;
    /* check_box_keep_screen_on_while_in_motion removed in new GUI */
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
static void refresh_battery_remaining_label(void);  /* fwd */
void set_var_power_time_to_go_measurement(float value) {
    power_time_to_go_measurement = value;
    refresh_battery_remaining_label();
}

static char power_time_to_go_measurement_type[100] = {0};
const char *get_var_power_time_to_go_measurement_type(void) { return power_time_to_go_measurement_type; }
void set_var_power_time_to_go_measurement_type(const char *value) {
    strncpy(power_time_to_go_measurement_type, value, sizeof(power_time_to_go_measurement_type) - 1);
    power_time_to_go_measurement_type[sizeof(power_time_to_go_measurement_type) - 1] = '\0';
    refresh_battery_remaining_label();
}

/* drive_bat_remain text — auto-picks the friendliest unit format based on
 * magnitude. Matches Headwaters' web UI:
 *   >= 24 h:   "1d 7h"
 *   >= 1 h:    "13h 40m"
 *   < 1 h:     "45m"
 * Input is in HOURS (mqtt_client converts time_remaining_minutes → hours). */
static void refresh_battery_remaining_label(void)
{
    if (!objects.drive_bat_remain) return;
    if (power_time_to_go_measurement <= 0.0f) {
        lv_label_set_text(objects.drive_bat_remain, "-- left");
        return;
    }
    char buf[32];
    int total_min = (int)(power_time_to_go_measurement * 60.0f + 0.5f);
    int days  = total_min / (24 * 60);
    int hours = (total_min % (24 * 60)) / 60;
    int mins  = total_min % 60;
    if (days > 0) {
        snprintf(buf, sizeof(buf), "%dd %dh left", days, hours);
    } else if (hours > 0) {
        snprintf(buf, sizeof(buf), "%dh %02dm left", hours, mins);
    } else {
        snprintf(buf, sizeof(buf), "%dm left", mins);
    }
    lv_label_set_text(objects.drive_bat_remain, buf);
}
