#include "device_alarms.h"

#include <string.h>
#include <stdio.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/screens.h"

#include "spoor_alarms.h"     /* for SPOOR_SNOOZE_SECS_DEFAULT — shared default */
#include "spotter_alarm.h"
#include "app_mqtt.h"          /* mqtt_client_publish for can/outbound */

static const char *TAG = "device";
#define NVS_NS "device"

/* ============================================================================
 * State
 * ============================================================================ */
static uint8_t  s_armed[DEVICE_BOARD_COUNT];                     /* arm bitmasks */
static uint8_t  s_inverted[DEVICE_BOARD_COUNT];                  /* invert bitmasks */
static char     s_custom[DEVICE_COUNT][DEVICE_LABEL_MAX + 1];
static uint8_t  s_last_state[DEVICE_BOARD_COUNT];                /* last seen relay byte per board */
static int64_t  s_last_alarm_us[DEVICE_COUNT];                   /* snooze tracking */
static int      s_rename_target = -1;
static int      s_active_alarm_idx = -1;

static char     s_label_scratch[64];

/* ============================================================================
 * EEZ object lookup tables — populated lazily on first use, exactly mirroring
 * the spoor_alarms pattern. Per-device widgets are alarm_spoor<board>_d<n>_*.
 * ============================================================================ */
static lv_obj_t *sw_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_d1_sw;
    case  1: return objects.alarm_spoor0_d2_sw;
    case  2: return objects.alarm_spoor0_d3_sw;
    case  3: return objects.alarm_spoor0_d4_sw;
    case  4: return objects.alarm_spoor0_d5_sw;
    case  5: return objects.alarm_spoor0_d6_sw;
    case  6: return objects.alarm_spoor0_d7_sw;
    case  7: return objects.alarm_spoor0_d8_sw;
    case  8: return objects.alarm_spoor1_d1_sw;
    case  9: return objects.alarm_spoor1_d2_sw;
    case 10: return objects.alarm_spoor1_d3_sw;
    case 11: return objects.alarm_spoor1_d4_sw;
    case 12: return objects.alarm_spoor1_d5_sw;
    case 13: return objects.alarm_spoor1_d6_sw;
    case 14: return objects.alarm_spoor1_d7_sw;
    case 15: return objects.alarm_spoor1_d8_sw;
    case 16: return objects.alarm_spoor2_d1_sw;
    case 17: return objects.alarm_spoor2_d2_sw;
    case 18: return objects.alarm_spoor2_d3_sw;
    case 19: return objects.alarm_spoor2_d4_sw;
    case 20: return objects.alarm_spoor2_d5_sw;
    case 21: return objects.alarm_spoor2_d6_sw;
    case 22: return objects.alarm_spoor2_d7_sw;
    case 23: return objects.alarm_spoor2_d8_sw;
    }
    return NULL;
}

static lv_obj_t *inv_sw_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_d1_inv_sw;
    case  1: return objects.alarm_spoor0_d2_inv_sw;
    case  2: return objects.alarm_spoor0_d3_inv_sw;
    case  3: return objects.alarm_spoor0_d4_inv_sw;
    case  4: return objects.alarm_spoor0_d5_inv_sw;
    case  5: return objects.alarm_spoor0_d6_inv_sw;
    case  6: return objects.alarm_spoor0_d7_inv_sw;
    case  7: return objects.alarm_spoor0_d8_inv_sw;
    case  8: return objects.alarm_spoor1_d1_inv_sw;
    case  9: return objects.alarm_spoor1_d2_inv_sw;
    case 10: return objects.alarm_spoor1_d3_inv_sw;
    case 11: return objects.alarm_spoor1_d4_inv_sw;
    case 12: return objects.alarm_spoor1_d5_inv_sw;
    case 13: return objects.alarm_spoor1_d6_inv_sw;
    case 14: return objects.alarm_spoor1_d7_inv_sw;
    case 15: return objects.alarm_spoor1_d8_inv_sw;
    case 16: return objects.alarm_spoor2_d1_inv_sw;
    case 17: return objects.alarm_spoor2_d2_inv_sw;
    case 18: return objects.alarm_spoor2_d3_inv_sw;
    case 19: return objects.alarm_spoor2_d4_inv_sw;
    case 20: return objects.alarm_spoor2_d5_inv_sw;
    case 21: return objects.alarm_spoor2_d6_inv_sw;
    case 22: return objects.alarm_spoor2_d7_inv_sw;
    case 23: return objects.alarm_spoor2_d8_inv_sw;
    }
    return NULL;
}

static lv_obj_t *name_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_d1_name;
    case  1: return objects.alarm_spoor0_d2_name;
    case  2: return objects.alarm_spoor0_d3_name;
    case  3: return objects.alarm_spoor0_d4_name;
    case  4: return objects.alarm_spoor0_d5_name;
    case  5: return objects.alarm_spoor0_d6_name;
    case  6: return objects.alarm_spoor0_d7_name;
    case  7: return objects.alarm_spoor0_d8_name;
    case  8: return objects.alarm_spoor1_d1_name;
    case  9: return objects.alarm_spoor1_d2_name;
    case 10: return objects.alarm_spoor1_d3_name;
    case 11: return objects.alarm_spoor1_d4_name;
    case 12: return objects.alarm_spoor1_d5_name;
    case 13: return objects.alarm_spoor1_d6_name;
    case 14: return objects.alarm_spoor1_d7_name;
    case 15: return objects.alarm_spoor1_d8_name;
    case 16: return objects.alarm_spoor2_d1_name;
    case 17: return objects.alarm_spoor2_d2_name;
    case 18: return objects.alarm_spoor2_d3_name;
    case 19: return objects.alarm_spoor2_d4_name;
    case 20: return objects.alarm_spoor2_d5_name;
    case 21: return objects.alarm_spoor2_d6_name;
    case 22: return objects.alarm_spoor2_d7_name;
    case 23: return objects.alarm_spoor2_d8_name;
    }
    return NULL;
}

static lv_obj_t *pencil_btn_for(int idx)
{
    switch (idx) {
    case  0: return objects.alarm_spoor0_d1_pencil_btn;
    case  1: return objects.alarm_spoor0_d2_pencil_btn;
    case  2: return objects.alarm_spoor0_d3_pencil_btn;
    case  3: return objects.alarm_spoor0_d4_pencil_btn;
    case  4: return objects.alarm_spoor0_d5_pencil_btn;
    case  5: return objects.alarm_spoor0_d6_pencil_btn;
    case  6: return objects.alarm_spoor0_d7_pencil_btn;
    case  7: return objects.alarm_spoor0_d8_pencil_btn;
    case  8: return objects.alarm_spoor1_d1_pencil_btn;
    case  9: return objects.alarm_spoor1_d2_pencil_btn;
    case 10: return objects.alarm_spoor1_d3_pencil_btn;
    case 11: return objects.alarm_spoor1_d4_pencil_btn;
    case 12: return objects.alarm_spoor1_d5_pencil_btn;
    case 13: return objects.alarm_spoor1_d6_pencil_btn;
    case 14: return objects.alarm_spoor1_d7_pencil_btn;
    case 15: return objects.alarm_spoor1_d8_pencil_btn;
    case 16: return objects.alarm_spoor2_d1_pencil_btn;
    case 17: return objects.alarm_spoor2_d2_pencil_btn;
    case 18: return objects.alarm_spoor2_d3_pencil_btn;
    case 19: return objects.alarm_spoor2_d4_pencil_btn;
    case 20: return objects.alarm_spoor2_d5_pencil_btn;
    case 21: return objects.alarm_spoor2_d6_pencil_btn;
    case 22: return objects.alarm_spoor2_d7_pencil_btn;
    case 23: return objects.alarm_spoor2_d8_pencil_btn;
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

    size_t blen = sizeof(s_armed);
    if (nvs_get_blob(h, "armed", s_armed, &blen) != ESP_OK || blen != sizeof(s_armed)) {
        memset(s_armed, 0, sizeof(s_armed));
    }
    blen = sizeof(s_inverted);
    if (nvs_get_blob(h, "inverted", s_inverted, &blen) != ESP_OK || blen != sizeof(s_inverted)) {
        memset(s_inverted, 0, sizeof(s_inverted));
    }

    for (int i = 0; i < DEVICE_COUNT; i++) {
        char key[12];
        snprintf(key, sizeof(key), "lbl_%02d", i);
        size_t slen = sizeof(s_custom[i]);
        if (nvs_get_str(h, key, s_custom[i], &slen) != ESP_OK) {
            s_custom[i][0] = '\0';
        }
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

static void nvs_save_inverted(void)
{
    nvs_handle_t h;
    if (nvs_open(NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_blob(h, "inverted", s_inverted, sizeof(s_inverted));
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

/* ============================================================================
 * Helpers
 * ============================================================================ */
static inline bool armed(int idx)
{
    return (s_armed[idx / DEVICES_PER_BOARD] >> (idx % DEVICES_PER_BOARD)) & 1;
}

static inline bool inverted(int idx)
{
    return (s_inverted[idx / DEVICES_PER_BOARD] >> (idx % DEVICES_PER_BOARD)) & 1;
}

static inline void set_armed_bit(int idx, bool on)
{
    uint8_t mask = 1u << (idx % DEVICES_PER_BOARD);
    if (on) s_armed[idx / DEVICES_PER_BOARD] |=  mask;
    else    s_armed[idx / DEVICES_PER_BOARD] &= ~mask;
}

static inline void set_inverted_bit(int idx, bool on)
{
    uint8_t mask = 1u << (idx % DEVICES_PER_BOARD);
    if (on) s_inverted[idx / DEVICES_PER_BOARD] |=  mask;
    else    s_inverted[idx / DEVICES_PER_BOARD] &= ~mask;
}

static void default_label(int idx, char *out, size_t out_sz)
{
    int device = (idx % DEVICES_PER_BOARD) + 1;
    snprintf(out, out_sz, "Device %d", device);
}

static void compose_row_text(int idx, char *out, size_t out_sz)
{
    if (s_custom[idx][0] != '\0') {
        snprintf(out, out_sz, "%s", s_custom[idx]);
    } else {
        default_label(idx, out, out_sz);
    }
}

static void paint_row(int idx)
{
    lv_obj_t *sw = sw_for(idx);
    if (sw) {
        if (armed(idx)) lv_obj_add_state(sw, LV_STATE_CHECKED);
        else            lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_t *isw = inv_sw_for(idx);
    if (isw) {
        if (inverted(idx)) lv_obj_add_state(isw, LV_STATE_CHECKED);
        else               lv_obj_clear_state(isw, LV_STATE_CHECKED);
    }
    lv_obj_t *nm = name_for(idx);
    if (nm) {
        char buf[64];
        compose_row_text(idx, buf, sizeof(buf));
        lv_label_set_text(nm, buf);
    }
}

/* See spoor_alarms.c — same reasoning for ext_click_area. */
static void expand_hit_area(lv_obj_t *obj, int pad)
{
    if (obj) lv_obj_set_ext_click_area(obj, pad);
}

/* ============================================================================
 * Public API
 * ============================================================================ */
void device_alarms_init(void)
{
    memset(s_armed,         0, sizeof(s_armed));
    memset(s_inverted,      0, sizeof(s_inverted));
    memset(s_custom,        0, sizeof(s_custom));
    memset(s_last_state,    0, sizeof(s_last_state));
    memset(s_last_alarm_us, 0, sizeof(s_last_alarm_us));
    s_active_alarm_idx = -1;
    s_rename_target    = -1;
    nvs_load_state();
    for (int i = 0; i < DEVICE_COUNT; i++) {
        paint_row(i);
        expand_hit_area(sw_for(i),         15);
        expand_hit_area(inv_sw_for(i),     15);
        expand_hit_area(pencil_btn_for(i), 15);
    }
    ESP_LOGI(TAG, "init: armed=[0x%02x 0x%02x 0x%02x] inverted=[0x%02x 0x%02x 0x%02x]",
             s_armed[0], s_armed[1], s_armed[2],
             s_inverted[0], s_inverted[1], s_inverted[2]);
}

bool device_alarms_is_armed(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) return false;
    return armed(idx);
}

bool device_alarms_is_inverted(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) return false;
    return inverted(idx);
}

const char *device_alarms_display_label(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) {
        snprintf(s_label_scratch, sizeof(s_label_scratch), "Unknown");
        return s_label_scratch;
    }
    if (s_custom[idx][0] != '\0') {
        snprintf(s_label_scratch, sizeof(s_label_scratch), "%s", s_custom[idx]);
    } else {
        default_label(idx, s_label_scratch, sizeof(s_label_scratch));
    }
    return s_label_scratch;
}

void device_alarms_toggle_arm(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) return;
    bool now;
    lv_obj_t *sw = sw_for(idx);
    if (sw) {
        now = lv_obj_has_state(sw, LV_STATE_CHECKED);
    } else {
        now = !armed(idx);
    }
    set_armed_bit(idx, now);
    nvs_save_armed();
    ESP_LOGI(TAG, "arm[%d] = %d", idx, now);
}

void device_alarms_toggle_invert(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) return;
    bool now;
    lv_obj_t *isw = inv_sw_for(idx);
    if (isw) {
        now = lv_obj_has_state(isw, LV_STATE_CHECKED);
    } else {
        now = !inverted(idx);
    }
    set_inverted_bit(idx, now);
    nvs_save_inverted();
    ESP_LOGI(TAG, "invert[%d] = %d", idx, now);
}

/* ----- Rename flow (shared rename page) -------------------------------- */
void device_alarms_open_rename(int idx)
{
    if (idx < 0 || idx >= DEVICE_COUNT) return;
    s_rename_target = idx;

    if (objects.rename_subtitle) {
        char sub[64];
        int board  = idx / DEVICES_PER_BOARD;
        int device = (idx % DEVICES_PER_BOARD) + 1;
        snprintf(sub, sizeof(sub), "Switchback Addr %d - Device %d", board, device);
        lv_label_set_text(objects.rename_subtitle, sub);
    }

    if (objects.sensor_rename_input) {
        lv_textarea_set_text(objects.sensor_rename_input, s_custom[idx]);
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

void device_alarms_save_rename(void)
{
    /* No-op if spoor has the active rename instead of us. */
    if (s_rename_target < 0 || s_rename_target >= DEVICE_COUNT) return;

    const char *txt = objects.sensor_rename_input
                          ? lv_textarea_get_text(objects.sensor_rename_input)
                          : "";
    char tmp[DEVICE_LABEL_MAX + 1];
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

void device_alarms_cancel_rename(void)
{
    if (s_rename_target < 0) return;     /* not our rename */
    rename_return_to_alarms();
}

/* ----- MQTT input handler ----------------------------------------------- */
void device_alarms_handle_state(int channel, int state)
{
    /* MQTT channel is 1-based (local/relays/<1..24>/status); convert to
     * 0-based internal index. */
    int idx = channel - 1;
    if (idx < 0 || idx >= DEVICE_COUNT) {
        ESP_LOGW(TAG, "handle_state: channel=%d OUT OF RANGE", channel);
        return;
    }
    int board = idx / DEVICES_PER_BOARD;
    int bit   = idx % DEVICES_PER_BOARD;

    uint8_t prev_byte = s_last_state[board];
    if (state) s_last_state[board] |=  (1u << bit);
    else       s_last_state[board] &= ~(1u << bit);

    /* The "alarm condition" depends on the invert flag:
     *   inverted=0 → fire when state == 1 (relay ON; light left on)
     *   inverted=1 → fire when state == 0 (relay OFF; fridge stopped)
     * Equivalently: effective_active = state XOR inverted. */
    bool inv = inverted(idx);
    bool prev_alarm_active = (((prev_byte >> bit) & 1) != 0) ^ inv;
    bool now_alarm_active  = (state != 0) ^ inv;
    bool is_rising = !prev_alarm_active && now_alarm_active;

    /* If the currently-showing alarm is THIS device and the condition just
     * cleared, dismiss the overlay. Then surface any still-active alarm
     * that was hidden behind this one — own devices first, then sensors.
     * Without this cross-module pass, a fridge alarm clearing would also
     * tear down a still-active light-on alarm. */
    if (s_active_alarm_idx == idx && !now_alarm_active) {
        ESP_LOGI(TAG, "Device %d condition cleared — dismissing alarm", idx);
        spotter_alarm_force_dismiss();
        s_active_alarm_idx = -1;
        if (!device_alarms_try_raise_next(true)) {
            spoor_alarms_try_raise_next(true);
        }
        return;
    }

    if (!now_alarm_active) return;           /* nothing to alarm about */
    if (!armed(idx))       return;

    int64_t now = esp_timer_get_time();
    /* Share the user-set snooze with spoor_alarms — one global snooze
     * preference controls both sensor and device alarms. */
    int64_t snooze_us = (int64_t)spoor_alarms_snooze_secs() * 1000000LL;
    if (!is_rising &&
        s_last_alarm_us[idx] != 0 &&
        (now - s_last_alarm_us[idx]) < snooze_us) {
        return;                              /* steady-state, still snoozing */
    }
    s_last_alarm_us[idx] = now;

    char body[160];
    snprintf(body, sizeof(body),
             "%s %s.\nTap Acknowledge or toggle off in Alarms.",
             device_alarms_display_label(idx),
             inverted(idx) ? "is off" : "is on");
    ESP_LOGI(TAG, "FIRING device alarm: %d (%s) inverted=%d",
             idx, device_alarms_display_label(idx), (int)inverted(idx));
    spotter_alarm_raise_device(device_alarms_display_label(idx), body, idx);
    s_active_alarm_idx = idx;
}

void device_alarms_acknowledged(void)
{
    if (s_active_alarm_idx < 0) return;
    s_last_alarm_us[s_active_alarm_idx] = esp_timer_get_time();
    ESP_LOGI(TAG, "Device %d acknowledged — snooze restarts", s_active_alarm_idx);
    s_active_alarm_idx = -1;
}

void device_alarms_send_toggle(int device_idx)
{
    if (device_idx < 0 || device_idx >= DEVICE_COUNT) {
        ESP_LOGW(TAG, "send_toggle: device_idx=%d OUT OF RANGE", device_idx);
        return;
    }
    int instance = device_idx / DEVICES_PER_BOARD;       /* 0..2 — Switchback board */
    int channel  = device_idx % DEVICES_PER_BOARD;        /* 0..7 — channel within board */
    int can_id   = 0x025 + instance;                      /* matches Headwaters sendRelayToggle */

    /* can/outbound JSON envelope — same shape as Headwaters publishCanMessage
     * in TrailCurrentHeadwaters/containers/backend/src/mqtt.js. The data
     * field is 8 sub-arrays of 8 bits each, MSB first. For our 1-byte
     * payload (channel index), byte 0 = channel; bytes 1-7 = 0. */
    char payload[640];
    int n = snprintf(payload, sizeof(payload),
        "{\"identifier\":\"0x%x\",\"data_length_code\":1,\"data\":["
        "[%d,%d,%d,%d,%d,%d,%d,%d],"
        "[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],"
        "[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],"
        "[0,0,0,0,0,0,0,0]"
        "],\"extd\":0,\"rtr\":0,\"ss\":0,\"self\":0}",
        can_id,
        (channel >> 7) & 1, (channel >> 6) & 1, (channel >> 5) & 1, (channel >> 4) & 1,
        (channel >> 3) & 1, (channel >> 2) & 1, (channel >> 1) & 1, (channel >> 0) & 1);
    if (n < 0 || n >= (int)sizeof(payload)) {
        ESP_LOGE(TAG, "send_toggle: payload formatting failed (n=%d)", n);
        return;
    }
    ESP_LOGI(TAG, "send_toggle: device=%d can_id=0x%x channel=%d",
             device_idx, can_id, channel);
    mqtt_client_publish("can/outbound", payload, 0);
}

bool device_alarms_try_raise_next(bool bypass_snooze)
{
    int64_t now = esp_timer_get_time();
    int64_t snooze_us = (int64_t)spoor_alarms_snooze_secs() * 1000000LL;
    for (int i = 0; i < DEVICE_COUNT; i++) {
        if (!armed(i)) continue;
        int board = i / DEVICES_PER_BOARD;
        int bit   = i % DEVICES_PER_BOARD;
        bool state_high = ((s_last_state[board] >> bit) & 1) != 0;
        bool active = state_high ^ inverted(i);
        if (!active) continue;
        if (!bypass_snooze &&
            s_last_alarm_us[i] != 0 &&
            (now - s_last_alarm_us[i]) < snooze_us) {
            continue;
        }
        char body[160];
        snprintf(body, sizeof(body),
                 "%s %s.\nTap Acknowledge or toggle off in Alarms.",
                 device_alarms_display_label(i),
                 inverted(i) ? "is off" : "is on");
        ESP_LOGI(TAG, "Re-raising hidden device alarm: %d (%s)",
                 i, device_alarms_display_label(i));
        spotter_alarm_raise_device(device_alarms_display_label(i), body, i);
        s_last_alarm_us[i] = now;
        s_active_alarm_idx = i;
        return true;
    }
    return false;
}
