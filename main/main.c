#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_timer.h"
#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "lvgl.h"

#include "ui/ui.h"
#include "ui/vars.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "app_mqtt.h"
#include "sd_config.h"
#include "audio.h"
#include "rtc_pcf85063.h"

static const char *TAG = "spotter";

/* ============================================================================
 * Display resolution
 * ============================================================================ */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/* ============================================================================
 * IO Extension chip (CH422G family) — Waveshare ESP32-S3-Touch-LCD-4.3C
 *
 * Per the reference firmware in DOCS/.../examples/esp-idf/12_lvgl_transplant/
 * components/io_extension/io_extension.c, this chip is addressed at 0x24 with
 * a register-based protocol (NOT the bit-mapped 0x38 protocol the previous
 * code used). Each operation is a 2-byte I2C write: [register, value].
 *
 *   Register 0x02 → IO mode  (per-pin: 0 input, 1 output). Init to 0xFF.
 *   Register 0x03 → IO output values (8 bits, one per pin).
 *   Register 0x04 → IO input values (read).
 *
 * Pin assignments (from reference io_extension.h):
 *   IO0          unused
 *   IO1 (bit 1)  = touch reset
 *   IO2 (bit 2)  = LCD backlight enable
 *   IO3 (bit 3)  = PA (power amp)
 *   IO4 (bit 4)  = SD card CS
 *   IO5 (bit 5)  = USB/CAN select (0=USB, 1=CAN)
 *   IO6, IO7     unused
 *
 * Initial output cache 0xF7 matches the reference's Last_io_value default
 * (all pins HIGH except bit 3 / PA, kept LOW).
 * ============================================================================ */
#define IO_EXT_ADDR        0x24
#define IO_EXT_REG_MODE    0x02
#define IO_EXT_REG_OUTPUT  0x03

#define IO_EXT_TOUCH_RST_BIT  (1 << 1)
#define IO_EXT_BACKLIGHT_BIT  (1 << 2)
#define IO_EXT_PA_BIT         (1 << 3)
#define IO_EXT_SD_CS_BIT      (1 << 4)
#define IO_EXT_USB_SEL_BIT    (1 << 5)

/* Kept under the old names for back-compat with the touch_init sequence. */
#define CH422G_EXIO1_BIT  IO_EXT_TOUCH_RST_BIT
#define CH422G_EXIO2_BIT  IO_EXT_BACKLIGHT_BIT
#define CH422G_EXIO4_BIT  IO_EXT_SD_CS_BIT

#define I2C_PORT     I2C_NUM_0
#define I2C_SDA_PIN  8
#define I2C_SCL_PIN  9
#define I2C_FREQ_HZ  400000

static uint8_t io_ext_out = 0xF7;   /* Reference's Last_io_value default */

/* New i2c_master_bus API — shared by IO extension, GT911 touch, and (Stage 2)
 * the ES8311 audio codec. Created once in ch422g_init and exposed via
 * spotter_i2c_bus() so the audio component can attach the codec. */
static i2c_master_bus_handle_t i2c_bus = NULL;
static i2c_master_dev_handle_t io_ext_dev = NULL;

i2c_master_bus_handle_t spotter_i2c_bus(void) { return i2c_bus; }

static esp_err_t io_ext_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = { reg, val };
    return i2c_master_transmit(io_ext_dev, buf, 2, 100);
}

/* Read a 16-bit word from the CH422G-family expander.
 *
 * Two-phase I2C transaction: write the 1-byte register address, then read
 * 2 bytes back. Little-endian per the Waveshare reference firmware
 * (DOCS/.../examples/esp-idf/07_display_bmp/components/i2c/i2c.c
 * DEV_I2C_Read_Word): result = high << 8 | low. Used to sample EXIO_ADC
 * (register 0x06) — the onboard battery-voltage divider feeds into it. */
#define IO_EXT_REG_ADC  0x06
static esp_err_t io_ext_read_word(uint8_t reg, uint16_t *out)
{
    uint8_t data[2] = { 0 };
    esp_err_t err = i2c_master_transmit_receive(io_ext_dev, &reg, 1,
                                                data, 2, 100);
    if (err != ESP_OK) return err;
    *out = (uint16_t)data[0] | ((uint16_t)data[1] << 8);
    return ESP_OK;
}

/* Convert the EXIO_ADC raw count to VBAT in millivolts.
 *
 * Empirically calibrated against real hardware: with the CS8501 holding the
 * cell at its 4.20 V termination voltage (DONE LED lit), the I2C read at
 * reg 0x06 returns raw=414 ± 2. That's a clean 10.14 mV/count — meaning
 * Waveshare's U10 firmware is already applying the 20K/10K divider compen-
 * sation and the ADC's reference scale, and returning the battery voltage
 * in CENTIVOLTS (raw=420 ↔ 4.20 V). So the conversion is just raw * 10. */
static uint16_t adc_count_to_vbat_mv(uint16_t raw)
{
    if (raw > 6000) raw = 6000;   /* cap at 60.00 V; well above any sane input */
    return (uint16_t)(raw * 10u);
}

/* 4.2V Li-Po SOC, calibrated for "always under load when on battery".
 *
 * The Spotter draws ~200 mA continuously (LCD backlight + ESP32 WiFi),
 * which sags a small Li-Po by 200-300 mV from its open-circuit voltage
 * the moment the USB charger releases. A naive open-circuit curve would
 * therefore drop from 100% to ~65% on unplug — which is technically
 * "true" but ugly UX (every laptop/phone hides this by calibrating their
 * curve against typical load).
 *
 * The breakpoints below are shifted to match what users expect:
 *   - The whole CV plateau (>= 4.10V) reads 100% so the gauge agrees with
 *     the CS8501's DONE LED.
 *   - The mid-band (3.7-4.0V) — where the cell spends most of its
 *     life under load — is stretched so a typical "discharging from full"
 *     reading lands at 85-90%, not 65%.
 *   - The steep cutoff below 3.5V is unchanged: that's the actual cliff
 *     where the cell is genuinely about to die. */
static uint8_t vbat_mv_to_soc_percent(uint16_t mv)
{
    static const struct { uint16_t mv; uint8_t pct; } pts[] = {
        { 4100, 100 },
        { 4000,  95 },
        { 3900,  85 },
        { 3800,  70 },
        { 3700,  50 },
        { 3600,  30 },
        { 3500,  15 },
        { 3400,   5 },
        { 3300,   0 },
    };
    const int n = sizeof(pts) / sizeof(pts[0]);
    if (mv >= pts[0].mv)     return pts[0].pct;
    if (mv <= pts[n-1].mv)   return pts[n-1].pct;
    for (int i = 0; i < n - 1; i++) {
        if (mv <= pts[i].mv && mv >= pts[i+1].mv) {
            uint32_t span_mv  = pts[i].mv   - pts[i+1].mv;
            uint32_t span_pct = pts[i].pct  - pts[i+1].pct;
            uint32_t over     = mv          - pts[i+1].mv;
            return (uint8_t)(pts[i+1].pct + (over * span_pct) / span_mv);
        }
    }
    return 0;
}

/* Read VBAT once and push SOC + charging state into the top-bar gauge.
 *
 * Charging detection: the CS8501's CHRG/STDBY pins aren't wired to the
 * ESP32, so we infer charging from the voltage holding above the CV
 * plateau (~4.15V). On unplug from a full charge the voltage drops below
 * this within a couple minutes, so the icon flips back to "discharging"
 * without needing the full voltage-trend ring buffer. Good enough for a
 * glanceable gauge. */
/* 16-sample moving average over the raw ADC counts (~32 s at the 2 s
 * poll cadence). Two jobs:
 *  - smooth out the ±2-count ADC noise so the displayed % doesn't
 *    twitch on every poll;
 *  - turn the abrupt voltage step at charger-unplug (cell sags 200+ mV
 *    in <1 s under load) into a gradual ~30 s slide, so the gauge
 *    behaves like a phone battery instead of yanking from 100% to 70%.
 * 32 s is short enough that real charge/discharge events still track
 * within a minute. */
#define BATT_AVG_N  16
static uint16_t batt_raw_ring[BATT_AVG_N] = { 0 };
static uint8_t  batt_ring_pos = 0;
static uint8_t  batt_ring_filled = 0;

static uint16_t batt_avg_push(uint16_t raw)
{
    batt_raw_ring[batt_ring_pos] = raw;
    batt_ring_pos = (batt_ring_pos + 1) % BATT_AVG_N;
    if (batt_ring_filled < BATT_AVG_N) batt_ring_filled++;
    uint32_t sum = 0;
    for (uint8_t i = 0; i < batt_ring_filled; i++) sum += batt_raw_ring[i];
    return (uint16_t)(sum / batt_ring_filled);
}

/* Forward decls — these accessors live in actions.c (battery-meter section).
 * poll_battery_meter calls get_enabled() each tick so the gate stays in sync
 * with the toggle; spotter_battery_set_state pushes the result into the
 * top-bar labels (fan-out across all 3 status_bar instances). */
extern void spotter_battery_set_state(uint8_t pct, bool charging);
extern bool spotter_battery_meter_get_enabled(void);

static void poll_battery_meter(void)
{
    /* Gated by the Setup-page "Battery Meter" toggle. When disabled we
     * touch neither the I2C bus (shared with GT911 touch, ES8311 codec,
     * PCF85063 RTC) nor the LVGL labels, so MQTT-driven gauges and the
     * 60 Hz redraw path don't compete with us for cycles when the user
     * has explicitly turned this feature off.
     *
     * On the OFF -> ON transition we clear the moving-average ring so the
     * first displayed reading reflects fresh data, not whatever stale
     * voltage was in the buffer from the previous enabled session. */
    bool enabled = spotter_battery_meter_get_enabled();
    static bool was_enabled = false;
    if (!enabled) {
        if (was_enabled) {
            batt_ring_pos = 0;
            batt_ring_filled = 0;
            was_enabled = false;
        }
        return;
    }
    was_enabled = true;

    uint16_t raw_now = 0;
    esp_err_t err = io_ext_read_word(IO_EXT_REG_ADC, &raw_now);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "battery: I2C ADC read failed: %s", esp_err_to_name(err));
        return;
    }
    uint16_t raw = batt_avg_push(raw_now);
    uint16_t mv  = adc_count_to_vbat_mv(raw);
    uint8_t  soc = vbat_mv_to_soc_percent(mv);
    /* Charging heuristic: above ~4.00 V the cell is either in CV phase or
     * just-finished and resting at the float voltage held by the CS8501.
     * Below that, USB is unplugged (otherwise the charger would have
     * pulled it back up). 4.00 V is far enough below the 4.12-4.16 V
     * rest-after-full plateau that ±2 counts of ADC noise don't flip the
     * icon back and forth. */
    bool charging = (mv > 4000);
    /* Logged once on first read + on every flag flip so the monitor doesn't
     * flood. Keep around so we can re-calibrate if the scale drifts on a
     * different board revision. */
    static int log_count = 0;
    static bool last_charging = false;
    if (log_count++ < 3 || charging != last_charging) {
        ESP_LOGI(TAG, "battery: raw=%u mV=%u soc=%u%% charging=%d",
                 raw, mv, soc, charging);
        last_charging = charging;
    }
    spotter_battery_set_state(soc, charging);
}

static void ch422g_set_bit(uint8_t bit, bool high)
{
    if (high) io_ext_out |= bit;
    else      io_ext_out &= ~bit;
    io_ext_write_reg(IO_EXT_REG_OUTPUT, io_ext_out);
}

/* Audio component asks us to flip the PA bit on/off. */
void spotter_io_ext_set_pa(bool enable)
{
    ch422g_set_bit(IO_EXT_PA_BIT, enable);
}

static void ch422g_init(void)
{
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT,
        .scl_io_num = I2C_SCL_PIN,
        .sda_io_num = I2C_SDA_PIN,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &i2c_bus));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = IO_EXT_ADDR,
        .scl_speed_hz = I2C_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus, &dev_cfg, &io_ext_dev));

    /* All pins as outputs. */
    esp_err_t e1 = io_ext_write_reg(IO_EXT_REG_MODE, 0xFF);
    /* Write the initial output state (matches reference: 0xF7). */
    esp_err_t e2 = io_ext_write_reg(IO_EXT_REG_OUTPUT, io_ext_out);
    ESP_LOGI(TAG, "IO extension init: mode=%s output=%s (val=0x%02x)",
             e1 == ESP_OK ? "OK" : "FAIL",
             e2 == ESP_OK ? "OK" : "FAIL", io_ext_out);
}

/* SD card CS control — called by sd_config component */
void sd_cs_set(bool assert_low)
{
    ch422g_set_bit(IO_EXT_SD_CS_BIT, !assert_low);
}

/* ============================================================================
 * Backlight (digital on/off via CH422G EXIO2, software dimming via overlay)
 * ============================================================================ */
static uint8_t current_brightness = 255;
static bool screen_timed_out = false;
static lv_obj_t *dimming_overlay = NULL;
static uint32_t last_activity_time = 0;

static void apply_brightness(uint8_t brightness)
{
    if (brightness == 0) {
        ch422g_set_bit(CH422G_EXIO2_BIT, false);
        return;
    }
    ch422g_set_bit(CH422G_EXIO2_BIT, true);

    if (dimming_overlay) {
        lv_opa_t opa = (lv_opa_t)(255 - brightness);
        lv_obj_set_style_bg_opa(dimming_overlay, opa, 0);
    }
}

void set_backlight(uint8_t brightness)
{
    current_brightness = brightness;
    if (!screen_timed_out) {
        apply_brightness(brightness);
    }
}

uint8_t get_backlight(void)
{
    return current_brightness;
}

static void create_dimming_overlay(void)
{
    dimming_overlay = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(dimming_overlay);
    lv_obj_set_size(dimming_overlay, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(dimming_overlay, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(dimming_overlay, LV_OPA_TRANSP, 0);
    lv_obj_add_flag(dimming_overlay, LV_OBJ_FLAG_FLOATING);
    lv_obj_clear_flag(dimming_overlay, LV_OBJ_FLAG_CLICKABLE);
}

/* ============================================================================
 * Screen timeout
 * ============================================================================ */
static lv_obj_t *wake_overlay = NULL;

static void wake_overlay_cb(lv_event_t *e)
{
    (void)e;
    /* First touch wakes the screen — absorb it */
    screen_timed_out = false;
    apply_brightness(current_brightness);
    last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
    if (wake_overlay) {
        lv_obj_del(wake_overlay);
        wake_overlay = NULL;
    }
}

static void handle_screen_timeout(void)
{
    int32_t timeout_minutes = get_var_screen_timeout_value();
    if (timeout_minutes <= 0 || screen_timed_out) return;

    /* Check if driving and keep-on-while-driving is enabled */
    if (get_var_keep_screen_on_while_driving() && get_var_current_speed_value() > 0) {
        last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
        return;
    }

    uint32_t now = (uint32_t)(esp_timer_get_time() / 1000);
    uint32_t elapsed_ms = now - last_activity_time;

    if (elapsed_ms >= (uint32_t)(timeout_minutes * 60 * 1000)) {
        screen_timed_out = true;
        apply_brightness(0);

        /* Create fullscreen overlay to absorb the wake touch */
        wake_overlay = lv_obj_create(lv_layer_top());
        lv_obj_remove_style_all(wake_overlay);
        lv_obj_set_size(wake_overlay, SCREEN_WIDTH, SCREEN_HEIGHT);
        lv_obj_set_style_bg_color(wake_overlay, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(wake_overlay, LV_OPA_COVER, 0);
        lv_obj_add_event_cb(wake_overlay, wake_overlay_cb, LV_EVENT_CLICKED, NULL);
    }
}

/* ============================================================================
 * NVS settings
 * ============================================================================ */
#define USER_SETTINGS_NVS_NAMESPACE "user_settings"

/* Defined below in the Clock section but called from restore_user_settings. */
void    clock_set_timezone_index(int32_t idx);
int32_t clock_get_timezone_index(void);

/* Defined in the Clock section below; declared up here because
 * restore_user_settings writes to it on boot. */
static bool s_clock_format_24h;

/* Battery-meter accessors live in actions.c — declared here because
 * restore_user_settings / persist_user_settings call them on boot and on
 * every settings-write cycle. */
extern void spotter_battery_meter_set_enabled(bool enabled);
extern bool spotter_battery_meter_get_enabled(void);
extern void spotter_paint_battery_meter(void);

static void restore_user_settings(void)
{
    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READONLY, &nvs) != ESP_OK) {
        ESP_LOGI(TAG, "No saved user settings, using defaults");
        return;
    }

    int32_t theme = 0;
    nvs_get_i32(nvs, "selectedTheme", &theme);
    set_var_selected_theme(theme);

    int32_t timeout = 0;
    nvs_get_i32(nvs, "screenTimeout", &timeout);
    set_var_screen_timeout_value(timeout);

    uint8_t keep_on = 1;
    nvs_get_u8(nvs, "onWhileDriving", &keep_on);
    set_var_keep_screen_on_while_driving(keep_on != 0);

    uint8_t brightness = 0;
    if (nvs_get_u8(nvs, "brightness", &brightness) == ESP_OK && brightness > 0) {
        set_backlight(brightness);
    }

    int32_t tz_idx = 5;  /* New York */
    nvs_get_i32(nvs, "tzIndex", &tz_idx);
    clock_set_timezone_index(tz_idx);
    if (objects.setup_timezone_dropdown) {
        lv_dropdown_set_selected(objects.setup_timezone_dropdown, (uint16_t)tz_idx);
    }

    uint8_t fmt24 = 0;
    nvs_get_u8(nvs, "clockFmt24h", &fmt24);
    s_clock_format_24h = (fmt24 != 0);
    if (objects.setup_clock_format_sw) {
        if (s_clock_format_24h) lv_obj_add_state(objects.setup_clock_format_sw,   LV_STATE_CHECKED);
        else                    lv_obj_clear_state(objects.setup_clock_format_sw, LV_STATE_CHECKED);
    }

    uint8_t batt_meter = 0;
    nvs_get_u8(nvs, "battMeter", &batt_meter);
    spotter_battery_meter_set_enabled(batt_meter != 0);

    nvs_close(nvs);
    ESP_LOGI(TAG, "User settings restored (theme=%d, timeout=%d)", (int)theme, (int)timeout);
}

/* ============================================================================
 * Clock — POSIX TZ + system time from Bearing (via MQTT local/gps/time)
 * ============================================================================
 * Pattern lifted from Milepost (which drives the same clock off CAN frame
 * 0x06). On Spotter the UTC datetime arrives over MQTT instead of CAN, but
 * everything downstream — system-time seeding, POSIX TZ application, the
 * 1 Hz display tick — is identical.
 *
 * The dropdown options in PageSetup mirror this array (same order):
 *   "Alaska / Chicago, Illinois / Denver, Colorado / Hawaii /
 *    Los Angeles / New York / Phoenix" */
static const char *TIMEZONE_POSIX[] = {
    "AKST9AKDT,M3.2.0/2:00:00,M11.1.0/2:00:00",  /* 0 Alaska */
    "CST6CDT,M3.2.0/2:00:00,M11.1.0/2:00:00",    /* 1 Chicago */
    "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00",    /* 2 Denver */
    "HST10",                                      /* 3 Hawaii (no DST) */
    "PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00",    /* 4 Los Angeles */
    "EST5EDT,M3.2.0/2:00:00,M11.1.0/2:00:00",    /* 5 New York */
    "MST7",                                       /* 6 Phoenix (no DST) */
};
#define TIMEZONE_COUNT (sizeof(TIMEZONE_POSIX) / sizeof(TIMEZONE_POSIX[0]))

static int32_t s_tz_index = 5;         /* New York default */
static bool    s_system_time_set = false;
static int     s_last_clock_min  = -1;
/* s_clock_format_24h is declared near restore_user_settings (it's read at
 * boot from NVS). Lives in this section logically — the 12 / 24-hour mode
 * affects both the top-bar clock and the full-screen PageClockMode shown
 * while TrailCurrent connectivity is lost. Persisted in NVS under
 * "clockFmt24h". Default = 12-hour (bool's zero-init). */

static void clock_apply_user_tz(void)
{
    int idx = s_tz_index;
    if (idx < 0 || idx >= (int)TIMEZONE_COUNT) idx = 5;
    setenv("TZ", TIMEZONE_POSIX[idx], 1);
    tzset();
    set_var_current_time_zone_string(TIMEZONE_POSIX[idx]);
}

/* Two formats, one source of truth.
 *
 * clock_format_top_bar (toolbar chip): "HH:MM" only — the 36 px chip can't
 * fit "HH:MM AM/PM" at MONTSERRAT_14 (would need ~58 px and clip on the
 * left at runtime).
 *
 * clock_format_full (Setup-page row + anywhere else with room): "HH:MM"
 * in 24-hour mode, "H:MM AM/PM" in 12-hour mode.
 *
 * Both memoize via the caller (one strftime per minute). */
static void clock_format_top_bar(const struct tm *ti, char *buf, size_t n)
{
    if (s_clock_format_24h) {
        snprintf(buf, n, "%02d:%02d", ti->tm_hour, ti->tm_min);
    } else {
        int h12 = ti->tm_hour % 12;
        if (h12 == 0) h12 = 12;
        snprintf(buf, n, "%d:%02d", h12, ti->tm_min);
    }
}

static void clock_format_full(const struct tm *ti, char *buf, size_t n)
{
    if (s_clock_format_24h) {
        snprintf(buf, n, "%02d:%02d", ti->tm_hour, ti->tm_min);
    } else {
        int h12 = ti->tm_hour % 12;
        if (h12 == 0) h12 = 12;
        snprintf(buf, n, "%d:%02d %s",
                 h12, ti->tm_min, ti->tm_hour >= 12 ? "PM" : "AM");
    }
}

void spotter_clock_paint_mode(bool force);
void spotter_clock_paint_stats(void);

static void clock_update_toolbar(bool force)
{
    if (!s_system_time_set) return;

    time_t now;
    time(&now);
    struct tm ti;
    localtime_r(&now, &ti);

    if (!force && ti.tm_min == s_last_clock_min) return;
    s_last_clock_min = ti.tm_min;

    char buf[12];
    clock_format_top_bar(&ti, buf, sizeof(buf));

    lv_obj_t *labels[] = {
        objects.drive_status_bar__status_time,
        objects.alarms_status_bar__status_time,
        objects.setup_status_bar__status_time,
    };
    for (size_t i = 0; i < sizeof(labels) / sizeof(*labels); i++) {
        if (labels[i]) lv_label_set_text(labels[i], buf);
    }

    /* Date / Time info rows on PageSetup — uses the FULL format
     * ("9:43 AM" in 12-hour mode, "21:43" in 24-hour mode). The Setup row
     * has horizontal room, unlike the toolbar chip. Date is rendered
     * separately as "Sat, Jun 22, 2026" with the leading-space fix for %e. */
    if (objects.setup_time_value) {
        char full_buf[12];
        clock_format_full(&ti, full_buf, sizeof(full_buf));
        lv_label_set_text(objects.setup_time_value, full_buf);
    }
    if (objects.setup_date_value) {
        char date_buf[40];
        strftime(date_buf, sizeof(date_buf), "%a, %b %e, %Y", &ti);
        for (char *p = date_buf; *p; p++) {
            if (*p == ' ' && *(p + 1) == ' ') { memmove(p, p + 1, strlen(p)); }
        }
        lv_label_set_text(objects.setup_date_value, date_buf);
    }

    /* The full-screen PageClockMode (shown while TrailCurrent connectivity
     * is lost) needs the same once-per-minute repaint. Its label set is
     * different (huge hero clock + AM/PM + date), hence a separate painter. */
    spotter_clock_paint_mode(force);
}

/* Paint the full-screen clock-mode display. Called on every minute tick from
 * clock_update_toolbar (which is itself the 2 Hz tick in app_main). Safe to
 * call whether or not PageClockMode is currently the active screen — the
 * label writes are cheap and do nothing visible until the screen is loaded.
 *
 * The clock face is two labels (digit_hh, digit_mm) each carrying a two-digit
 * pair inside its own panel, plus a separate AM/PM chip.  Leading-zero
 * formatting keeps both panels populated in both 12-hour and 24-hour modes
 * so the layout doesn't collapse on single-digit hours. */
/* Day-of-week names (Sunday=0). Matches struct tm.tm_wday. */
static const char *const DAY_NAMES_UPPER[7] = {
    "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
    "THURSDAY", "FRIDAY", "SATURDAY",
};

void spotter_clock_paint_mode(bool force)
{
    if (!objects.page_clock_mode) return;

    lv_obj_t *ampm_lbl = objects.clock_ampm;

    if (!s_system_time_set) {
        if (objects.digit_hh)   lv_label_set_text(objects.digit_hh, "--");
        if (objects.digit_mm)   lv_label_set_text(objects.digit_mm, "--");
        if (objects.clock_dow)  lv_label_set_text(objects.clock_dow, "--");
        if (objects.clock_seconds) lv_label_set_text(objects.clock_seconds, "");
        if (ampm_lbl)           lv_obj_add_flag(ampm_lbl, LV_OBJ_FLAG_HIDDEN);
        if (objects.clock_date_label) lv_label_set_text(objects.clock_date_label, "--");
        return;
    }

    time_t now;
    time(&now);
    struct tm ti;
    localtime_r(&now, &ti);

    /* Day-of-week (e.g. "MONDAY") above the time. */
    if (objects.clock_dow && ti.tm_wday >= 0 && ti.tm_wday <= 6) {
        lv_label_set_text(objects.clock_dow, DAY_NAMES_UPPER[ti.tm_wday]);
    }

    int h, m = ti.tm_min;
    int sec = ti.tm_sec;
    if (s_clock_format_24h) {
        h = ti.tm_hour;
        if (ampm_lbl) lv_obj_add_flag(ampm_lbl, LV_OBJ_FLAG_HIDDEN);
    } else {
        h = ti.tm_hour % 12;
        if (h == 0) h = 12;
        if (ampm_lbl) {
            lv_obj_clear_flag(ampm_lbl, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ampm_lbl, ti.tm_hour >= 12 ? "PM" : "AM");
        }
    }

    char buf[4];
    /* 12-hour hours 1-9 render as a single digit (no leading zero) to
     * match the mockup's "7:50 PM" look. 24-hour mode zero-pads. */
    if (s_clock_format_24h) snprintf(buf, sizeof(buf), "%02d", h);
    else                    snprintf(buf, sizeof(buf), "%d",   h);
    if (objects.digit_hh) lv_label_set_text(objects.digit_hh, buf);
    snprintf(buf, sizeof(buf), "%02d", m);
    if (objects.digit_mm) lv_label_set_text(objects.digit_mm, buf);

    /* Seconds subscript — small mono digits, updated once per second by
     * spotter_clock_tick_seconds() below.  Repaint here so the value is
     * fresh whenever a minute tick fires too. */
    if (objects.clock_seconds) {
        snprintf(buf, sizeof(buf), "%02d", sec);
        lv_label_set_text(objects.clock_seconds, buf);
    }

    if (objects.clock_date_label) {
        char date_buf[40];
        /* Long-form date matches the mockup: "June 22, 2026". The label
         * was renamed off LabelDataValue48 in the new layout so letters
         * render now. */
        strftime(date_buf, sizeof(date_buf), "%B %e, %Y", &ti);
        /* %e leaves a leading space on 1-digit days — collapse it. */
        for (char *p = date_buf; *p; p++) {
            if (*p == ' ' && *(p + 1) == ' ') { memmove(p, p + 1, strlen(p)); }
        }
        lv_label_set_text(objects.clock_date_label, date_buf);
    }

    /* Refresh the three stat cards + the "X min ago" timestamp on the same
     * cadence as the clock minute tick. The painter reads cached values
     * from vars.c (battery / solar) so we never lose the most recent
     * MQTT-delivered reading. */
    spotter_clock_paint_stats();

    (void)force;
}

/* ----------------------------------------------------------------------------
 * Seconds tick + colon blink
 *
 * The connectivity-alarm subsystem owns the page-load transition, but the
 * clock-mode painters above only fire once per minute via clock_update_toolbar.
 * The seconds subscript and the colon-blink animation need higher-frequency
 * updates, so we run a dedicated 500 ms LVGL timer.
 *   - Every tick: flip the text-opacity of clock_colon (the ":" between HH and
 *     MM) so the colon appears to blink.
 *   - Every other tick (i.e. once per second): refresh clock_seconds.
 * The timer runs unconditionally — when PageClockMode is not the active
 * screen the label writes are cheap and invisible.
 * --------------------------------------------------------------------------*/
static lv_timer_t *s_clock_blink_timer = NULL;
static bool        s_colon_visible     = true;
static int         s_last_sec_painted  = -1;

static void clock_blink_cb(lv_timer_t *t)
{
    (void)t;
    /* Toggle colon visibility */
    s_colon_visible = !s_colon_visible;
    uint8_t opa = s_colon_visible ? 255 : 46; /* per spec: 1.0 -> 0.18 */
    if (objects.clock_colon) {
        lv_obj_set_style_text_opa(objects.clock_colon, opa,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    /* Once-per-second seconds-label refresh (only when system time is
     * valid; otherwise the seconds label stays at its placeholder). */
    if (s_system_time_set && objects.clock_seconds) {
        time_t now;
        time(&now);
        struct tm ti;
        localtime_r(&now, &ti);
        if (ti.tm_sec != s_last_sec_painted) {
            s_last_sec_painted = ti.tm_sec;
            char buf[4];
            snprintf(buf, sizeof(buf), "%02d", ti.tm_sec);
            lv_label_set_text(objects.clock_seconds, buf);
        }
    }
}

void spotter_clock_blink_start(void)
{
    if (s_clock_blink_timer) return;
    s_clock_blink_timer = lv_timer_create(clock_blink_cb, 500, NULL);
}

/* ----------------------------------------------------------------------------
 * Frozen-data card painters for PageClockMode
 *
 * The three stat cards (Battery, Solar, Fresh) on the clock screen show the
 * most recent values that arrived over MQTT before connectivity dropped.
 * They re-paint on every minute tick (cheap label writes) and on entry to
 * clock mode so the user sees fresh data immediately.
 *
 * Fresh tank data is not currently delivered from any TrailCurrent device,
 * so that card stays as a "No tank data" placeholder until the relevant
 * MQTT topics get wired through vars.c.
 * --------------------------------------------------------------------------*/

/* Map raw solar status string to a short human-readable phrase. Mirrors the
 * lookup table in vars.c::set_var_solar_status() — kept in sync. */
static const char *solar_status_short(const char *raw)
{
    if (!raw || !*raw)                          return "--";
    if (strcmp(raw, "solar") == 0)              return "Charging, solar";
    if (strcmp(raw, "shore") == 0)              return "Shore power";
    if (strcmp(raw, "not_charging") == 0)       return "Not charging";
    if (strcmp(raw, "float") == 0)              return "Charging, float";
    if (strcmp(raw, "absorption") == 0)         return "Charging, absorption";
    if (strcmp(raw, "bulk") == 0)               return "Charging, bulk";
    return raw;
}

/* Format "X min ago" / "Xh Ym ago" / "Just now" / "--" depending on age.
 * Buffer must be at least 16 bytes. */
static void format_ago(char *buf, size_t n, time_t last, time_t now)
{
    if (last <= 0)         { snprintf(buf, n, "--");           return; }
    long age = (long)(now - last);
    if (age < 0) age = 0;
    if (age < 45)          { snprintf(buf, n, "Just now");     return; }
    if (age < 90)          { snprintf(buf, n, "1 min ago");    return; }
    long mins = (age + 30) / 60;
    if (mins < 60)         { snprintf(buf, n, "%ld min ago", mins);          return; }
    long hours = mins / 60;
    long rem   = mins % 60;
    if (hours < 24)        { snprintf(buf, n, "%ldh %ldm ago", hours, rem);  return; }
    long days = hours / 24;
    snprintf(buf, n, "%ld day%s ago", days, days == 1 ? "" : "s");
}

extern time_t spotter_last_data_time(void);

void spotter_clock_paint_stats(void)
{
    if (!objects.page_clock_mode) return;

    time_t now;
    time(&now);
    time_t last = spotter_last_data_time();
    bool   have_data = (last > 0);

    /* ---- "X min ago" header label ---- */
    if (objects.clock_ago_label) {
        char buf[20];
        format_ago(buf, sizeof(buf), last, now);
        lv_label_set_text(objects.clock_ago_label, buf);
    }

    /* ---- Battery card ----
     * Each value is guarded individually so a partial sync (voltage came
     * in but SoC hasn't yet, etc.) doesn't render "0%" or "0.0 V". */
    int32_t bat_pct  = get_var_battery_soc_percentage();
    float   bat_v    = get_var_battery_voltage();
    bool    have_pct = (bat_pct > 0);
    bool    have_v   = (bat_v   > 0.5f);    /* anything < 0.5 V is "no reading" */

    if (objects.clock_bat_value) {
        if (have_pct) {
            int pct = (int)bat_pct;
            if (pct < 0)   pct = 0;
            if (pct > 100) pct = 100;
            char buf[8];
            snprintf(buf, sizeof(buf), "%d", pct);
            lv_label_set_text(objects.clock_bat_value, buf);
        } else {
            lv_label_set_text(objects.clock_bat_value, "--");
        }
    }
    if (objects.clock_bat_sub) {
        if (have_v) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.1f V, house bank", bat_v);
            lv_label_set_text(objects.clock_bat_sub, buf);
        } else if (have_data) {
            lv_label_set_text(objects.clock_bat_sub, "house bank");
        } else {
            lv_label_set_text(objects.clock_bat_sub, "Waiting for data");
        }
    }

    /* ---- Solar card ---- */
    int32_t     sol_w        = get_var_solar_wattage();
    const char *sol_status   = get_var_solar_status();
    bool        have_solar_w = (sol_w != 0) || have_data;     /* 0 W IS a valid reading once we've ever seen data */
    bool        have_status  = (sol_status != NULL && sol_status[0] != '\0');

    if (objects.clock_sol_value) {
        if (have_solar_w) {
            char buf[8];
            snprintf(buf, sizeof(buf), "%d", (int)sol_w);
            lv_label_set_text(objects.clock_sol_value, buf);
        } else {
            lv_label_set_text(objects.clock_sol_value, "--");
        }
    }
    if (objects.clock_sol_sub) {
        if (have_status) {
            lv_label_set_text(objects.clock_sol_sub,
                              solar_status_short(sol_status));
        } else if (have_data) {
            lv_label_set_text(objects.clock_sol_sub, "--");
        } else {
            lv_label_set_text(objects.clock_sol_sub, "Waiting for data");
        }
    }

    /* ---- Fresh card ---- placeholder until tank MQTT topics are wired ---- */
    if (objects.clock_fresh_value) lv_label_set_text(objects.clock_fresh_value, "--");
    if (objects.clock_fresh_sub)   lv_label_set_text(objects.clock_fresh_sub,   "No tank data");
}

/* Public hooks for actions.c — flip the 12/24 setting and force an immediate
 * repaint of both the top-bar and the full-screen clock. */
void clock_set_format_24h(bool on)
{
    s_clock_format_24h = on;
    s_last_clock_min = -1;
    clock_update_toolbar(true);
}

bool clock_get_format_24h(void) { return s_clock_format_24h; }

/* Called from vars.c whenever Bearing's UTC datetime lands. ISO format:
 * "YYYY-MM-DD HH:MM:SS". First call seeds the clock with settimeofday();
 * later calls re-sync only on drift > 2 s to avoid 1 Hz GNSS yank-back. */
void spotter_clock_set_from_iso_utc(const char *iso_utc)
{
    if (!iso_utc || !*iso_utc) return;

    struct tm tm_utc = {0};
    if (strptime(iso_utc, "%Y-%m-%d %H:%M:%S", &tm_utc) == NULL) return;

    /* Reject pre-fix garbage (GNSS pre-lock: 1970/2000/etc.) */
    int year = tm_utc.tm_year + 1900;
    if (year < 2025 || year > 2099) return;

    setenv("TZ", "UTC0", 1);
    tzset();
    tm_utc.tm_isdst = 0;
    time_t gnss_epoch = mktime(&tm_utc);
    /* Restore the user's TZ regardless of what happens next */
    clock_apply_user_tz();
    if (gnss_epoch <= 0) return;

    if (s_system_time_set) {
        time_t now;
        time(&now);
        time_t diff = gnss_epoch > now ? gnss_epoch - now : now - gnss_epoch;
        if (diff <= 2) return;
    }

    struct timeval tv = { .tv_sec = gnss_epoch, .tv_usec = 0 };
    settimeofday(&tv, NULL);
    s_system_time_set = true;
    s_last_clock_min = -1;
    clock_update_toolbar(true);

    /* Persist to the battery-backed RTC so the next power-on (even
     * without TrailCurrent reachable) starts from this fresh sync.
     * tm_utc was normalised by the earlier mktime() call — same UTC
     * instant, broken-down fields valid. */
    esp_err_t we = rtc_pcf85063_write(&tm_utc);
    if (we != ESP_OK) ESP_LOGW(TAG, "RTC write failed: %s", esp_err_to_name(we));
}

/* Public entry points so actions.c can drive TZ changes. */
void clock_set_timezone_index(int32_t idx)
{
    if (idx < 0 || idx >= (int)TIMEZONE_COUNT) return;
    s_tz_index = idx;
    clock_apply_user_tz();
    s_last_clock_min = -1;
    clock_update_toolbar(true);
}

int32_t clock_get_timezone_index(void) { return s_tz_index; }
int32_t clock_get_timezone_count(void) { return (int32_t)TIMEZONE_COUNT; }

static void persist_user_settings(void)
{
    if (!get_var_user_settings_changed()) return;

    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) != ESP_OK) return;

    nvs_set_i32(nvs, "selectedTheme", get_var_selected_theme());
    nvs_set_i32(nvs, "screenTimeout", get_var_screen_timeout_value());
    nvs_set_u8(nvs, "onWhileDriving", get_var_keep_screen_on_while_driving() ? 1 : 0);
    nvs_set_u8(nvs, "brightness", get_backlight());
    nvs_set_i32(nvs, "tzIndex", clock_get_timezone_index());
    nvs_set_u8(nvs, "clockFmt24h", s_clock_format_24h ? 1 : 0);
    nvs_set_u8(nvs, "battMeter", spotter_battery_meter_get_enabled() ? 1 : 0);
    nvs_commit(nvs);
    nvs_close(nvs);

    set_var_user_settings_changed(false);
    ESP_LOGI(TAG, "User settings persisted");
}

/* ============================================================================
 * RGB LCD panel (double-buffered with vsync synchronization)
 * ============================================================================ */
static esp_lcd_panel_handle_t panel_handle = NULL;
static SemaphoreHandle_t vsync_sem = NULL;

static IRAM_ATTR bool on_vsync(esp_lcd_panel_handle_t panel,
                                const esp_lcd_rgb_panel_event_data_t *edata,
                                void *user_ctx)
{
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(vsync_sem, &woken);
    return woken == pdTRUE;
}

static void lcd_init(void)
{
    vsync_sem = xSemaphoreCreateBinary();

    /* Matches Waveshare ESP32-S3-Touch-LCD-4.3C reference, see
     * DOCS/.../examples/esp-idf/12_lvgl_transplant/components/rgb_lcd_port/
     * rgb_lcd_port.c. Key differences from prior config: pclk_active_neg=1
     * (panel expects active-low PCLK), 4/8/8 sync timings instead of 10/10/20,
     * 16 MHz PCLK instead of 14, sram_trans_align=4 added. */
    esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz = 16 * 1000 * 1000,
            .h_res = SCREEN_WIDTH,
            .v_res = SCREEN_HEIGHT,
            .hsync_pulse_width = 4,
            .hsync_back_porch = 8,
            .hsync_front_porch = 8,
            .vsync_pulse_width = 4,
            .vsync_back_porch = 8,
            .vsync_front_porch = 8,
            .flags.pclk_active_neg = 1,
        },
        .data_width = 16,
        .bits_per_pixel = 16,
        .num_fbs = 2,
        /* Bumped from SCREEN_WIDTH*10 → *20 to reduce DMA interrupt
         * frequency. Each bounce now holds ~1ms of pixel data which
         * gives the PSRAM refill plenty of headroom and noticeably
         * cuts visible tearing/flicker on this 800x480 panel. */
        .bounce_buffer_size_px = SCREEN_WIDTH * 20,
        .sram_trans_align = 4,
        .psram_trans_align = 64,
        .de_gpio_num = 5,
        .pclk_gpio_num = 7,
        .vsync_gpio_num = 3,
        .hsync_gpio_num = 46,
        .disp_gpio_num = -1,
        .data_gpio_nums = {
            /* B3..B7 */ 14, 38, 18, 17, 10,
            /* G2..G7 */ 39,  0, 45, 48, 47, 21,
            /* R3..R7 */  1,  2, 42, 41, 40,
        },
        .flags.fb_in_psram = true,
    };

    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    esp_lcd_rgb_panel_event_callbacks_t cbs = { .on_vsync = on_vsync };
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, NULL));

    ESP_LOGI(TAG, "RGB LCD initialized (800x480, 14MHz, double-buffered)");
}

/* ============================================================================
 * GT911 touch
 * ============================================================================ */
static esp_lcd_touch_handle_t touch_handle = NULL;

/* Per the Waveshare ESP32-S3-Touch-LCD-4.3C reference (DOCS/.../examples/esp-idf/
 * 12_lvgl_transplant/components/touch/gt911.c), the GT911 latches its I2C address
 * on the rising edge of RST based on the INT pin state:
 *   INT low  → 0x5D (default)
 *   INT high → 0x14 (backup)
 * Touch RST is on the CH422G IO expander (EXIO1); touch INT is GPIO 4. We must
 * drive INT low ourselves before releasing RST — the driver only handles this
 * if both RST and INT are real GPIOs it can control, and our RST isn't. */
#define TOUCH_INT_GPIO  GPIO_NUM_4

static void touch_init(void)
{
    /* 1. Configure INT as output so we can hold it low during reset. */
    gpio_config_t int_out = {
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pin_bit_mask = BIT64(TOUCH_INT_GPIO),
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&int_out);

    /* 2. RST low (via CH422G EXIO1), wait. */
    ch422g_set_bit(CH422G_EXIO1_BIT, false);
    vTaskDelay(pdMS_TO_TICKS(100));

    /* 3. INT low → selects 0x5D after RST release. */
    gpio_set_level(TOUCH_INT_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(100));

    /* 4. Release RST while INT is held low → chip wakes up at 0x5D. */
    ch422g_set_bit(CH422G_EXIO1_BIT, true);
    vTaskDelay(pdMS_TO_TICKS(200));

    /* 5. Reconfigure INT as input for normal operation. */
    gpio_config_t int_in = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = BIT64(TOUCH_INT_GPIO),
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&int_in);

    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    /* New i2c_master_bus driver — the touch panel attaches as another device
     * on the shared bus. scl_speed_hz is honored here (the GT911 happily runs
     * at 400 kHz alongside the IO expander). */
    tp_io_config.scl_speed_hz = I2C_FREQ_HZ;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c_v2(i2c_bus, &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = SCREEN_WIDTH,
        .y_max = SCREEN_HEIGHT,
        /* rst stays NC because RST is on the CH422G, not a real GPIO; we handled
         * RST manually above. int_gpio_num=-1 too — we poll via touch_read_data
         * rather than using interrupt-driven mode. */
        .rst_gpio_num = -1,
        .int_gpio_num = -1,
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    esp_err_t r = esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &touch_handle);
    if (r != ESP_OK) {
        ESP_LOGE(TAG, "GT911 init failed (0x%x) — continuing without touch", r);
        touch_handle = NULL;
        return;
    }
    ESP_LOGI(TAG, "GT911 touch initialized at 0x5D");
}

/* ============================================================================
 * LVGL tick, display driver, touch input (direct mode, vsync-synced)
 * ============================================================================ */
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static void lvgl_tick_cb(void *arg)
{
    (void)arg;
    lv_tick_inc(1);
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area,
                           lv_color_t *color_map)
{
    /* Direct mode + 2 framebuffers: panel_draw_bitmap with the just-rendered
     * buffer queues a tear-free swap at the next vsync. Then wait on the
     * vsync semaphore so we don't return to LVGL (which would immediately
     * start rendering into the OTHER buffer) until the swap has been latched
     * by the panel hardware. Order matters — calling draw_bitmap AFTER
     * taking the sem queues against a stale vsync and the swap visibly
     * lags by one frame, which shows up as flicker on rapidly-changing
     * widgets like the battery arc. Pattern matches the Waveshare
     * ESP32-S3-Touch-LCD-4.3C lvgl_port reference. */
    if (lv_disp_flush_is_last(drv)) {
        esp_lcd_panel_draw_bitmap(panel_handle, 0, 0,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, color_map);
        xSemaphoreTake(vsync_sem, portMAX_DELAY);
    }
    lv_disp_flush_ready(drv);
}

static void lvgl_touch_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    if (!touch_handle) {
        data->state = LV_INDEV_STATE_REL;
        return;
    }
    esp_lcd_touch_read_data(touch_handle);

    esp_lcd_touch_point_data_t pt;
    uint8_t count = 0;
    if (esp_lcd_touch_get_data(touch_handle, &pt, &count, 1) == ESP_OK && count > 0) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = pt.x;
        data->point.y = pt.y;
        last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

static void lvgl_init(void)
{
    lv_init();

    /* 1ms tick timer */
    const esp_timer_create_args_t tick_args = {
        .callback = lvgl_tick_cb,
        .name = "lvgl_tick",
    };
    esp_timer_handle_t tick_timer;
    ESP_ERROR_CHECK(esp_timer_create(&tick_args, &tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(tick_timer, 1000));

    /* Get both PSRAM framebuffers for tear-free double-buffered direct mode */
    void *fb[2] = {NULL, NULL};
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_get_frame_buffer(panel_handle, 2,
                                                        &fb[0], &fb[1]));

    uint32_t buf_size = SCREEN_WIDTH * SCREEN_HEIGHT;
    lv_disp_draw_buf_init(&draw_buf, (lv_color_t *)fb[0],
                          (lv_color_t *)fb[1], buf_size);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.direct_mode = 1;
    lv_disp_drv_register(&disp_drv);

    /* Touch input — defaults tuned for the 4.3" cap-touch panel.
     *
     *   scroll_limit (default 10 px): how far the finger has to move before
     *   LVGL gives up on "this press belongs to the widget" and transfers it
     *   to the parent's scroll. Default 10 is too low — when a user drags
     *   to scroll PageSetup, the slider or switch under their finger has
     *   already captured the press and updated its value before LVGL
     *   recognises the gesture as a scroll. 20 px keeps deliberate slider
     *   adjustments working (a focused horizontal nudge is well over 20 px)
     *   while letting "swipe up to scroll" win cleanly.
     *
     *   scroll_throw (default 10): velocity decay per frame, as a percent.
     *   At 10 a single swipe dies down quickly so the user has to keep
     *   stroking to get anywhere. Drop to 5 for ~2× more momentum per
     *   swipe; scrolling a 1100-px-tall settings page takes 2 flicks
     *   instead of 4. */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lvgl_touch_read_cb;
    indev_drv.scroll_limit = 20;
    indev_drv.scroll_throw = 5;
    lv_indev_drv_register(&indev_drv);

    ESP_LOGI(TAG, "LVGL initialized (direct mode)");
}

/* ============================================================================
 * WiFi — now owned by the wifi_setup component + app_state machine. Boot path:
 *   1. esp_netif + default event loop init (done in app_main before the state
 *      machine, since wifi_setup_init() assumes both are up).
 *   2. app_state_init() calls wifi_setup_init() (which installs WIFI/IP event
 *      handlers and starts the STA driver) and decides the first screen based
 *      on saved credentials (PageWifiConnecting if creds saved, PageWifiSetup
 *      otherwise).
 * Old wifi_init/wifi_auto_connect/wifi_event_handler are replaced by that.
 * ============================================================================ */

/* ============================================================================
 * Warning indicators (checked periodically in main loop)
 * ============================================================================ */
static void update_warning_indicators(void)
{
    /* The old Home page warning labels (label_warning_icon_lights / _water etc.)
     * no longer exist in the new 4-screen design. PageDrive surfaces lights state
     * via the lights tab indicator and the blind-spot pill; water status is not
     * yet surfaced on the dashboard. Stubbed until equivalent widgets are added
     * to the new GUI. */
}

/* ============================================================================
 * Version
 * ============================================================================ */
#define CURRENT_VERSION "0.2.0"

/* ============================================================================
 * app_main
 * ============================================================================ */
extern void spotter_set_active_tab(int index);
extern void spotter_apply_axle_count(int axles);
extern void spotter_paint_placeholders(void);
extern void spotter_paint_volume(void);
extern void spotter_paint_brightness(void);
/* Battery-meter accessors are declared above restore_user_settings (which
 * is where they're first called). The forward declarations live near the
 * NVS settings block. */

#include "app_state.h"
#include "pendant_config.h"
#include "spoor_alarms.h"
#include "device_alarms.h"
#include "connectivity_alarm.h"

/* fix_keyboard_alignment used to live here and force keyboard geometry from
 * C. It was the canonical example of canvas-device divergence: any time the
 * JSON moved a keyboard, the stale C call dragged it back. Removed in favor
 * of style-based pinning in the .eez-project (align: TOP_LEFT plus
 * min_width/max_width/min_height/max_height on every keyboard's localStyles).
 * That style override defeats lv_keyboard's internal layout pass without
 * needing any C help. If a keyboard still misbehaves, fix the style in EEZ
 * Studio — do NOT reintroduce a C-side geometry override. The eezstudio
 * skill's "EEZ Studio is the single source of truth" rule is structural,
 * not advisory. */

/* Heap diagnostic — prints internal-RAM free and largest contiguous block,
 * which is what mbedTLS needs for a TLS handshake. Drop these around every
 * init that might consume internal RAM. */
static void log_heap(const char *where)
{
    ESP_LOGI(TAG, "[heap @ %s] internal free=%u largest=%u  total_free=%u",
             where,
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
             (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL),
             (unsigned)esp_get_free_heap_size());
}

void app_main(void)
{
    /* NVS */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    log_heap("app_main start");

    /* Hardware init */
    ch422g_init();
    log_heap("after ch422g_init");

    /* Battery-backed RTC (PCF85063A at 0x51) — attach to the shared I2C
     * bus and, if the chip is holding a valid time, seed the system clock
     * immediately so the device shows the correct time even without
     * connectivity. The chip's coin-cell keeps the oscillator running
     * across power cycles. */
    if (rtc_pcf85063_init(i2c_bus) == ESP_OK) {
        struct tm rtc_utc;
        esp_err_t rr = rtc_pcf85063_read(&rtc_utc);
        if (rr == ESP_OK) {
            int year = rtc_utc.tm_year + 1900;
            if (year >= 2025 && year < 2099) {
                /* Treat RTC fields as UTC: temporarily switch TZ to UTC for
                 * mktime so it doesn't apply a local offset, then restore
                 * a sane local TZ immediately so any caller of localtime_r
                 * between now and restore_user_settings (PageClockMode
                 * paints, top-bar clock, etc.) doesn't see UTC.
                 * clock_apply_user_tz uses s_tz_index, which is initialised
                 * to NY (5); restore_user_settings later overrides with the
                 * persisted tzIndex from NVS. Without this restore, the
                 * clock face renders in UTC whenever NVS doesn't (yet)
                 * carry user-settings — e.g. fresh install. */
                setenv("TZ", "UTC0", 1);
                tzset();
                rtc_utc.tm_isdst = 0;
                time_t epoch = mktime(&rtc_utc);
                if (epoch > 0) {
                    struct timeval tv = { .tv_sec = epoch, .tv_usec = 0 };
                    settimeofday(&tv, NULL);
                    s_system_time_set = true;
                    s_last_clock_min = -1;
                    ESP_LOGI(TAG, "RTC seeded system clock: %04d-%02d-%02d %02d:%02d:%02d UTC",
                             year, rtc_utc.tm_mon + 1, rtc_utc.tm_mday,
                             rtc_utc.tm_hour, rtc_utc.tm_min, rtc_utc.tm_sec);
                }
                clock_apply_user_tz();
            } else {
                ESP_LOGW(TAG, "RTC year out of range (%d) — ignoring", year);
            }
        } else if (rr == ESP_ERR_INVALID_STATE) {
            ESP_LOGW(TAG, "RTC oscillator stopped — first boot or dead coin cell. "
                          "Waiting for TrailCurrent UTC to seed the clock.");
        } else {
            ESP_LOGW(TAG, "RTC read failed: %s", esp_err_to_name(rr));
        }
    }
    log_heap("after rtc_init");

    /* SD card config (reads config.env, stores to NVS) */
    bool sd_config_found = sd_config_read();
    ESP_LOGI(TAG, "SD config %s", sd_config_found ? "loaded" : "not found");

    /* Display */
    lcd_init();
    log_heap("after lcd_init");
    touch_init();
    log_heap("after touch_init");
    lvgl_init();
    log_heap("after lvgl_init");

    /* Audio — ES8311 codec on the shared I2C bus, I2S TX1. PA enable is
     * routed through the IO extender's PA bit (CH422G EXIO3). */
    {
        esp_err_t are = spotter_audio_init(i2c_bus, spotter_io_ext_set_pa);
        ESP_LOGI(TAG, "Audio init: %s", are == ESP_OK ? "OK" : esp_err_to_name(are));
    }
    log_heap("after audio_init");

    /* EEZ Studio UI */
    ui_init();
    create_dimming_overlay();

    /* Start the 500 ms clock-mode blink timer (drives the HH:MM colon
     * dot animation + seconds-subscript refresh on PageClockMode). Runs
     * unconditionally — when the page isn't active the label writes are
     * cheap and invisible. */
    spotter_clock_blink_start();

    /* Paint placeholders ("--", "Waiting for data...", etc.) into every
     * widget that's supposed to show data from TrailCurrent. Replaced by
     * real values as MQTT messages arrive (set_var_* setters push directly
     * to widgets). Without this the static placeholder text from the
     * .eez-project (e.g. "65" PSI) would look like real data. */
    spotter_paint_placeholders();

    /* Default axle config = single (1). Cascades into top-status text,
     * tire card subtitle, tire-cell visibility, and setup-button checked
     * state across all 4 dashboard pages. Persist this in NVS later if we
     * want the user's chosen axle count to survive reboot. */
    spotter_apply_axle_count(1);

    /* Reflect persisted chime volume into the Setup slider + "NN%" label. */
    spotter_paint_volume();

    /* Restore user settings (loads brightness from NVS via set_backlight) */
    restore_user_settings();

    /* Reflect the restored brightness into the Setup slider + "NN%" label. */
    spotter_paint_brightness();

    /* Reflect the restored battery-meter on/off into the Setup switch and
     * paint the placeholder gauge. */
    spotter_paint_battery_meter();
    ESP_LOGI(TAG, "Spotter firmware version %s", CURRENT_VERSION);

    /* MQTT client config (loaded but not connected — happens after WiFi). */
    bool has_mqtt = mqtt_client_load_settings();

    /* Persistent config (WiFi credentials), then the state machine drives
     * the rest: PageWifiSetup if no creds, PageWifiConnecting otherwise.
     * Both screens require ui_init() to have run. */
    ESP_ERROR_CHECK(pendant_config_init());

    /* LVGL's keyboard widget defaults to its own internal alignment that
     * overrides the left/top we author in the .eez-project (the keyboard
     * rendered at y=290 instead of declared y=100, extending 100px off-
     * screen). Force align: TOP_LEFT and re-pin the positions from C so
     * the JSON x/y is honored. Has to happen AFTER ui_init() (objects
     * are created there) but BEFORE app_state_init() loads the screens. */
    /* Keyboard geometry is now pinned via style (align: TOP_LEFT plus
     * min_width/max_width/min_height/max_height in each keyboard's
     * localStyles in the .eez-project). With those style overrides in
     * place LVGL's lv_keyboard internal layout no longer hijacks the
     * authored position/size, so the C-side fix_keyboard_alignment()
     * calls are unnecessary — AND actively harmful, because they
     * silently diverge from the canvas whenever the JSON moves and the
     * C call doesn't (exactly what just happened with sensor_rename_kb
     * moving from (8,200) to (8,140), where the stale C call dragged
     * the keyboard back over the new footer).
     *
     * EEZ Studio's canvas is the single source of truth for keyboard
     * geometry. If a keyboard is off on the device, fix the style pin
     * in EEZ Studio — do NOT add a C override here. */

    /* Initialize connectivity_alarm BEFORE app_state_init so the very first
     * wifi/mqtt state callbacks (which fire on event tasks the moment
     * wifi_setup_init / mqtt_client_set_state_callback run) land in a
     * fully-initialized module. */
    connectivity_alarm_init();
    ESP_ERROR_CHECK(app_state_init());
    spoor_alarms_init();
    device_alarms_init();

    last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);

    ESP_LOGI(TAG, "Setup complete (MQTT config: %s)", has_mqtt ? "yes" : "no");

    /* Main loop */
    uint32_t warning_check_time = 0;

    while (1) {
        lv_timer_handler();

        /* Process MQTT messages */
        mqtt_client_process_messages();

        /* Persist settings if changed */
        persist_user_settings();

        /* Screen timeout */
        handle_screen_timeout();

        /* Warning indicators (every ~33ms) */
        uint32_t now = (uint32_t)(esp_timer_get_time() / 1000);
        if (now - warning_check_time >= 33) {
            update_warning_indicators();
            warning_check_time = now;
        }

        /* Top-toolbar clock — minute-resolution display, polled at 0.5 Hz
         * so the rollover from XX:59 to XX:00 doesn't lag more than a tick. */
        static uint32_t clock_tick_ms = 0;
        if (now - clock_tick_ms >= 2000) {
            clock_update_toolbar(false);
            clock_tick_ms = now;
        }

        /* Battery gauge — 0.5 Hz I2C poll of the IO extender's ADC.
         * Internally gated by the "Battery Meter" toggle: when off, the
         * call returns immediately without touching I2C, so it doesn't
         * compete with MQTT-driven gauges or the 60 Hz redraw path for
         * shared bus time. First reading after toggling on takes ~2s. */
        static uint32_t battery_tick_ms = 0;
        if (now - battery_tick_ms >= 2000) {
            poll_battery_meter();
            battery_tick_ms = now;
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
