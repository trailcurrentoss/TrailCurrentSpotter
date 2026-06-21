#include "spoor_alarms.h"

#include <string.h>
#include <stdio.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "ui/vars.h"

#include "spotter_alarm.h"

static const char *TAG = "spoor";
#define NVS_NS "spoor"

/* ============================================================================
 * State
 * ============================================================================ */
static uint8_t  s_armed[SPOOR_ADDR_COUNT];                       /* arm bitmasks */
static char     s_custom[SPOOR_SENSOR_COUNT][SPOOR_LABEL_MAX + 1];
static uint8_t  s_last_inputs[SPOOR_ADDR_COUNT];
static int64_t  s_last_alarm_us[SPOOR_SENSOR_COUNT];             /* snooze tracking */
static int      s_show_secs   = SPOOR_SHOW_SECS_DEFAULT;
static int      s_snooze_secs = SPOOR_SNOOZE_SECS_DEFAULT;
static int      s_rename_target = -1;                            /* sensor being renamed */

/* Default label scratch buffer for spoor_alarms_display_label(). */
static char     s_label_scratch[64];

/* ============================================================================
 * EEZ object lookup tables — populated lazily on first use. The widgets only
 * exist after the user does EEZ Studio Build (Ctrl+B); referencing the
 * `objects.*` fields before that fails at link time. Keep this strictly to
 * names introduced by the spoor patch so the rest of the firmware compiles.
 * ============================================================================ */
static lv_obj_t *sw_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_s1_sw;
    case  1: return objects.alarm_spoor0_s2_sw;
    case  2: return objects.alarm_spoor0_s3_sw;
    case  3: return objects.alarm_spoor0_s4_sw;
    case  4: return objects.alarm_spoor0_s5_sw;
    case  5: return objects.alarm_spoor0_s6_sw;
    case  6: return objects.alarm_spoor0_s7_sw;
    case  7: return objects.alarm_spoor0_s8_sw;
    case  8: return objects.alarm_spoor1_s1_sw;
    case  9: return objects.alarm_spoor1_s2_sw;
    case 10: return objects.alarm_spoor1_s3_sw;
    case 11: return objects.alarm_spoor1_s4_sw;
    case 12: return objects.alarm_spoor1_s5_sw;
    case 13: return objects.alarm_spoor1_s6_sw;
    case 14: return objects.alarm_spoor1_s7_sw;
    case 15: return objects.alarm_spoor1_s8_sw;
    case 16: return objects.alarm_spoor2_s1_sw;
    case 17: return objects.alarm_spoor2_s2_sw;
    case 18: return objects.alarm_spoor2_s3_sw;
    case 19: return objects.alarm_spoor2_s4_sw;
    case 20: return objects.alarm_spoor2_s5_sw;
    case 21: return objects.alarm_spoor2_s6_sw;
    case 22: return objects.alarm_spoor2_s7_sw;
    case 23: return objects.alarm_spoor2_s8_sw;
    }
    return NULL;
}

static lv_obj_t *name_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_s1_name;
    case  1: return objects.alarm_spoor0_s2_name;
    case  2: return objects.alarm_spoor0_s3_name;
    case  3: return objects.alarm_spoor0_s4_name;
    case  4: return objects.alarm_spoor0_s5_name;
    case  5: return objects.alarm_spoor0_s6_name;
    case  6: return objects.alarm_spoor0_s7_name;
    case  7: return objects.alarm_spoor0_s8_name;
    case  8: return objects.alarm_spoor1_s1_name;
    case  9: return objects.alarm_spoor1_s2_name;
    case 10: return objects.alarm_spoor1_s3_name;
    case 11: return objects.alarm_spoor1_s4_name;
    case 12: return objects.alarm_spoor1_s5_name;
    case 13: return objects.alarm_spoor1_s6_name;
    case 14: return objects.alarm_spoor1_s7_name;
    case 15: return objects.alarm_spoor1_s8_name;
    case 16: return objects.alarm_spoor2_s1_name;
    case 17: return objects.alarm_spoor2_s2_name;
    case 18: return objects.alarm_spoor2_s3_name;
    case 19: return objects.alarm_spoor2_s4_name;
    case 20: return objects.alarm_spoor2_s5_name;
    case 21: return objects.alarm_spoor2_s6_name;
    case 22: return objects.alarm_spoor2_s7_name;
    case 23: return objects.alarm_spoor2_s8_name;
    }
    return NULL;
}

/* ============================================================================
 * NVS load / save
 * ============================================================================ */
static void nvs_load_state(void)
{
    nvs_handle_t h;
    esp_err_t r = nvs_open(NVS_NS, NVS_READONLY, &h);
    if (r == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(TAG, "no saved state — using defaults");
        return;
    }
    if (r != ESP_OK) {
        ESP_LOGW(TAG, "nvs_open: %s", esp_err_to_name(r));
        return;
    }

    /* Armed bitmask blob (3 bytes). Missing = all-zero (no sensors armed). */
    size_t blen = sizeof(s_armed);
    if (nvs_get_blob(h, "armed", s_armed, &blen) != ESP_OK || blen != sizeof(s_armed)) {
        memset(s_armed, 0, sizeof(s_armed));
    }

    /* Custom labels. Stored only when set, key "lbl_<00..23>". */
    for (int i = 0; i < SPOOR_SENSOR_COUNT; i++) {
        char key[12];
        snprintf(key, sizeof(key), "lbl_%02d", i);
        size_t slen = sizeof(s_custom[i]);
        if (nvs_get_str(h, key, s_custom[i], &slen) != ESP_OK) {
            s_custom[i][0] = '\0';
        }
    }

    /* Timing. Single-byte u8 to keep the keys tiny. Clamp on load to defend
     * against a corrupt/hand-edited entry. */
    uint8_t v = 0;
    if (nvs_get_u8(h, "show_s", &v) == ESP_OK) {
        if (v < SPOOR_SHOW_SECS_MIN)      v = SPOOR_SHOW_SECS_MIN;
        if (v > SPOOR_SHOW_SECS_MAX)      v = SPOOR_SHOW_SECS_MAX;
        s_show_secs = v;
    }
    if (nvs_get_u8(h, "snooze_s", &v) == ESP_OK) {
        if (v < SPOOR_SNOOZE_SECS_MIN)    v = SPOOR_SNOOZE_SECS_MIN;
        /* snooze max is 180 which fits in u8. */
        if (v > SPOOR_SNOOZE_SECS_MAX)    v = SPOOR_SNOOZE_SECS_MAX;
        s_snooze_secs = v;
    }
    nvs_close(h);
}

static void nvs_save_armed(void)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_blob(h, "armed", s_armed, sizeof(s_armed));
    nvs_commit(h);
    nvs_close(h);
}

static void nvs_save_label(int idx)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    char key[12];
    snprintf(key, sizeof(key), "lbl_%02d", idx);
    if (s_custom[idx][0] == '\0') {
        nvs_erase_key(h, key);
    } else {
        nvs_set_str(h, key, s_custom[idx]);
    }
    nvs_commit(h);
    nvs_close(h);
}

static void nvs_save_show(void)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_u8(h, "show_s", (uint8_t)s_show_secs);
    nvs_commit(h);
    nvs_close(h);
}

static void nvs_save_snooze(void)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_u8(h, "snooze_s", (uint8_t)s_snooze_secs);
    nvs_commit(h);
    nvs_close(h);
}

/* ============================================================================
 * Helpers
 * ============================================================================ */
static inline bool armed(int idx)
{
    return (s_armed[idx / SPOOR_SENSORS_PER_ADDR] >> (idx % SPOOR_SENSORS_PER_ADDR)) & 1;
}

static inline void set_armed(int idx, bool on)
{
    uint8_t mask = 1u << (idx % SPOOR_SENSORS_PER_ADDR);
    if (on) s_armed[idx / SPOOR_SENSORS_PER_ADDR] |=  mask;
    else    s_armed[idx / SPOOR_SENSORS_PER_ADDR] &= ~mask;
}

static void default_label(int idx, char *out, size_t out_sz)
{
    int addr   = idx / SPOOR_SENSORS_PER_ADDR;
    int sensor = (idx % SPOOR_SENSORS_PER_ADDR) + 1;
    snprintf(out, out_sz, "Sensor %d", sensor);
    (void)addr;  /* addr context is on the group header label */
}

static void compose_row_text(int idx, char *out, size_t out_sz)
{
    char def[24];
    default_label(idx, def, sizeof(def));
    if (s_custom[idx][0] != '\0') {
        snprintf(out, out_sz, "%s (%s)", def, s_custom[idx]);
    } else {
        snprintf(out, out_sz, "%s", def);
    }
}

static void paint_row(int idx)
{
    lv_obj_t *sw = sw_for(idx);
    if (sw) {
        if (armed(idx)) lv_obj_add_state(sw, LV_STATE_CHECKED);
        else            lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_t *nm = name_for(idx);
    if (nm) {
        char buf[64];
        compose_row_text(idx, buf, sizeof(buf));
        lv_label_set_text(nm, buf);
    }
}

static void paint_timing(void)
{
    if (objects.setup_alarm_show_slider) {
        lv_slider_set_value(objects.setup_alarm_show_slider, s_show_secs, LV_ANIM_OFF);
    }
    if (objects.setup_alarm_show_value) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d sec", s_show_secs);
        lv_label_set_text(objects.setup_alarm_show_value, buf);
    }
    if (objects.setup_alarm_snooze_slider) {
        lv_slider_set_value(objects.setup_alarm_snooze_slider, s_snooze_secs, LV_ANIM_OFF);
    }
    if (objects.setup_alarm_snooze_value) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d sec", s_snooze_secs);
        lv_label_set_text(objects.setup_alarm_snooze_value, buf);
    }
}

/* ============================================================================
 * Public API
 * ============================================================================ */
void spoor_alarms_init(void)
{
    memset(s_armed,        0, sizeof(s_armed));
    memset(s_custom,       0, sizeof(s_custom));
    memset(s_last_inputs,  0, sizeof(s_last_inputs));
    memset(s_last_alarm_us, 0, sizeof(s_last_alarm_us));
    nvs_load_state();
    for (int i = 0; i < SPOOR_SENSOR_COUNT; i++) paint_row(i);
    paint_timing();
    ESP_LOGI(TAG, "init: armed=[0x%02x 0x%02x 0x%02x] show=%ds snooze=%ds",
             s_armed[0], s_armed[1], s_armed[2], s_show_secs, s_snooze_secs);
}

bool spoor_alarms_is_armed(int idx)
{
    if (idx < 0 || idx >= SPOOR_SENSOR_COUNT) return false;
    return armed(idx);
}

int spoor_alarms_show_secs(void)   { return s_show_secs; }
int spoor_alarms_snooze_secs(void) { return s_snooze_secs; }

const char *spoor_alarms_display_label(int idx)
{
    if (idx < 0 || idx >= SPOOR_SENSOR_COUNT) {
        snprintf(s_label_scratch, sizeof(s_label_scratch), "Unknown");
        return s_label_scratch;
    }
    char def[24];
    default_label(idx, def, sizeof(def));
    if (s_custom[idx][0] != '\0') {
        snprintf(s_label_scratch, sizeof(s_label_scratch), "%s (%s)", def, s_custom[idx]);
    } else {
        snprintf(s_label_scratch, sizeof(s_label_scratch), "%s", def);
    }
    return s_label_scratch;
}

void spoor_alarms_toggle_arm(int idx)
{
    if (idx < 0 || idx >= SPOOR_SENSOR_COUNT) return;
    bool now;
    lv_obj_t *sw = sw_for(idx);
    if (sw) {
        /* Trust the LVGL state the user just produced — it's authoritative. */
        now = lv_obj_has_state(sw, LV_STATE_CHECKED);
    } else {
        now = !armed(idx);
    }
    set_armed(idx, now);
    nvs_save_armed();
    ESP_LOGI(TAG, "arm[%d] = %d", idx, now);
}

/* ----- Rename flow ------------------------------------------------------- */
void spoor_alarms_open_rename(int idx)
{
    if (idx < 0 || idx >= SPOOR_SENSOR_COUNT) return;
    s_rename_target = idx;

    /* Subtitle: which sensor this rename targets ("Switchback Addr 0 — Sensor 3"). */
    if (objects.rename_subtitle) {
        char sub[64];
        int addr   = idx / SPOOR_SENSORS_PER_ADDR;
        int sensor = (idx % SPOOR_SENSORS_PER_ADDR) + 1;
        snprintf(sub, sizeof(sub), "Switchback Addr %d - Sensor %d", addr, sensor);
        lv_label_set_text(objects.rename_subtitle, sub);
    }

    /* Pre-fill textarea with the current custom label so editing it is in-place
     * rather than a blank-slate retype. Empty if no custom label yet. */
    if (objects.sensor_rename_input) {
        lv_textarea_set_text(objects.sensor_rename_input, s_custom[idx]);
        /* Bind the keyboard once per open — the textarea may have been
         * recreated by a screen reload. */
        if (objects.sensor_rename_kb) {
            lv_keyboard_set_textarea(objects.sensor_rename_kb, objects.sensor_rename_input);
        }
    }

    if (objects.page_rename_sensor) {
        lv_scr_load(objects.page_rename_sensor);
    }
}

static void rename_return_to_alarms(void)
{
    s_rename_target = -1;
    if (objects.page_alarms) lv_scr_load(objects.page_alarms);
}

void spoor_alarms_save_rename(void)
{
    if (s_rename_target < 0 || s_rename_target >= SPOOR_SENSOR_COUNT) {
        rename_return_to_alarms();
        return;
    }
    const char *txt = objects.sensor_rename_input
                          ? lv_textarea_get_text(objects.sensor_rename_input)
                          : "";
    /* Trim trailing whitespace — light touch. */
    char tmp[SPOOR_LABEL_MAX + 1];
    strncpy(tmp, txt ? txt : "", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    for (int n = (int)strlen(tmp) - 1; n >= 0 && (tmp[n] == ' ' || tmp[n] == '\t'); n--) {
        tmp[n] = '\0';
    }

    int idx = s_rename_target;
    strncpy(s_custom[idx], tmp, sizeof(s_custom[idx]) - 1);
    s_custom[idx][sizeof(s_custom[idx]) - 1] = '\0';
    nvs_save_label(idx);
    paint_row(idx);
    ESP_LOGI(TAG, "label[%d] = %s", idx, s_custom[idx][0] ? s_custom[idx] : "(cleared)");
    rename_return_to_alarms();
}

void spoor_alarms_cancel_rename(void)
{
    rename_return_to_alarms();
}

/* ----- Timing sliders --------------------------------------------------- */
void spoor_alarms_set_show_secs(int s)
{
    if (s < SPOOR_SHOW_SECS_MIN) s = SPOOR_SHOW_SECS_MIN;
    if (s > SPOOR_SHOW_SECS_MAX) s = SPOOR_SHOW_SECS_MAX;
    if (s == s_show_secs) {
        paint_timing();
        return;
    }
    s_show_secs = s;
    nvs_save_show();
    paint_timing();
    ESP_LOGI(TAG, "show_secs = %d", s_show_secs);
}

void spoor_alarms_set_snooze_secs(int s)
{
    if (s < SPOOR_SNOOZE_SECS_MIN) s = SPOOR_SNOOZE_SECS_MIN;
    if (s > SPOOR_SNOOZE_SECS_MAX) s = SPOOR_SNOOZE_SECS_MAX;
    if (s == s_snooze_secs) {
        paint_timing();
        return;
    }
    s_snooze_secs = s;
    nvs_save_snooze();
    paint_timing();
    ESP_LOGI(TAG, "snooze_secs = %d", s_snooze_secs);
}

/* ----- MQTT input handler ----------------------------------------------- */
void spoor_alarms_handle_inputs(int addr, uint8_t inputs)
{
    if (addr < 0 || addr >= SPOOR_ADDR_COUNT) return;
    uint8_t prev = s_last_inputs[addr];
    uint8_t rising = inputs & ~prev;     /* newly active bits */
    s_last_inputs[addr] = inputs;
    if (rising == 0) return;

    int64_t now = esp_timer_get_time();
    for (int bit = 0; bit < SPOOR_SENSORS_PER_ADDR; bit++) {
        if (!(rising & (1u << bit))) continue;
        int idx = addr * SPOOR_SENSORS_PER_ADDR + bit;
        if (!armed(idx)) continue;

        int64_t snooze_us = (int64_t)s_snooze_secs * 1000000LL;
        if (s_last_alarm_us[idx] != 0 &&
            (now - s_last_alarm_us[idx]) < snooze_us) {
            ESP_LOGD(TAG, "sensor %d active but in snooze window", idx);
            continue;
        }
        s_last_alarm_us[idx] = now;

        /* display_label may be up to ~63 chars (custom label format
         * "Sensor N (<24-char custom>)"); suffix is ~50 chars; pad. */
        char body[128];
        snprintf(body, sizeof(body),
                 "%s active.\nTap Acknowledge or toggle off in Alarms.",
                 spoor_alarms_display_label(idx));
        spotter_alarm_raise(spoor_alarms_display_label(idx), body, s_show_secs);
    }
}
