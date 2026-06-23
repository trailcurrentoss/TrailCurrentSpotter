#include "rtc_pcf85063.h"

#include <string.h>
#include "esp_log.h"

static const char *TAG = "rtc_pcf85063";

#define PCF85063_ADDR     0x51
#define I2C_SPEED_HZ      400000   /* chip supports up to 400 kHz */

/* Register map (PCF85063A datasheet table 6) */
#define REG_CTRL1         0x00
#define REG_CTRL2         0x01
#define REG_SECONDS       0x04     /* bit 7 = OS (oscillator stop) flag */
#define REG_MINUTES       0x05
#define REG_HOURS         0x06
#define REG_DAYS          0x07
#define REG_WEEKDAYS      0x08
#define REG_MONTHS        0x09
#define REG_YEARS         0x0A

#define SECONDS_OS_MASK   0x80

/* The chip's year register is 0..99 (datasheet 8.3 — "the year register
 * holds the year in BCD format"; century is software's job).  We treat
 * 0 as the year 2000 (struct tm.tm_year == 100), giving valid coverage
 * 2000–2099.  Convert between the two representations in one place. */
#define RTC_YEAR_TM_BASE  100      /* 2000 - 1900 */

static i2c_master_dev_handle_t s_dev = NULL;

static uint8_t dec_to_bcd(int v)     { return (uint8_t)(((v / 10) << 4) | (v % 10)); }
static int     bcd_to_dec(uint8_t b) { return ((b >> 4) * 10) + (b & 0x0F); }

esp_err_t rtc_pcf85063_init(i2c_master_bus_handle_t bus)
{
    if (s_dev) return ESP_OK;                      /* already attached */

    i2c_device_config_t cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = PCF85063_ADDR,
        .scl_speed_hz    = I2C_SPEED_HZ,
    };
    esp_err_t err = i2c_master_bus_add_device(bus, &cfg, &s_dev);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "i2c add device: %s", esp_err_to_name(err));
        s_dev = NULL;
        return err;
    }

    /* Make sure the chip is running and in normal-mode 24-hour.  Defaults
     * after power-on-reset are already correct (CTRL1 == 0x00) but a
     * stuck-stopped chip after a brown-out lands here and needs the STOP
     * bit cleared explicitly. */
    uint8_t ctrl1[2] = { REG_CTRL1, 0x00 };
    err = i2c_master_transmit(s_dev, ctrl1, sizeof(ctrl1), 100);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ctrl1 write: %s", esp_err_to_name(err));
        /* Not fatal — the chip is usually already running. */
    }
    ESP_LOGI(TAG, "PCF85063A attached at 0x%02X", PCF85063_ADDR);
    return ESP_OK;
}

esp_err_t rtc_pcf85063_read(struct tm *out)
{
    if (!s_dev || !out) return ESP_ERR_INVALID_ARG;

    /* Burst-read the 7 time/date registers in one transaction (chip
     * supports register-pointer-auto-increment per datasheet 8.4). */
    uint8_t reg = REG_SECONDS;
    uint8_t buf[7] = {0};
    esp_err_t err = i2c_master_transmit_receive(s_dev, &reg, 1, buf, sizeof(buf), 100);
    if (err != ESP_OK) return err;

    if (buf[0] & SECONDS_OS_MASK) {
        /* OS bit set — the oscillator stopped at some point since the
         * last successful write, so the held time is invalid (typically
         * a dead coin cell or first-ever boot). */
        return ESP_ERR_INVALID_STATE;
    }

    memset(out, 0, sizeof(*out));
    out->tm_sec  = bcd_to_dec(buf[0] & 0x7F);
    out->tm_min  = bcd_to_dec(buf[1] & 0x7F);
    out->tm_hour = bcd_to_dec(buf[2] & 0x3F);
    out->tm_mday = bcd_to_dec(buf[3] & 0x3F);
    out->tm_wday = bcd_to_dec(buf[4] & 0x07);
    out->tm_mon  = bcd_to_dec(buf[5] & 0x1F) - 1;             /* chip 1-12 → tm 0-11 */
    out->tm_year = bcd_to_dec(buf[6]) + RTC_YEAR_TM_BASE;     /* chip 0-99 → years-since-1900 */
    return ESP_OK;
}

esp_err_t rtc_pcf85063_write(const struct tm *in)
{
    if (!s_dev || !in) return ESP_ERR_INVALID_ARG;

    int rtc_yr = in->tm_year - RTC_YEAR_TM_BASE;
    if (rtc_yr < 0 || rtc_yr > 99) {
        ESP_LOGW(TAG, "year %d out of chip range (2000-2099)", in->tm_year + 1900);
        return ESP_ERR_INVALID_ARG;
    }

    /* Single burst write: register pointer + 7 BCD bytes.  Bit 7 of the
     * seconds byte is the OS flag, written 0 to clear "oscillator was
     * stopped" so a subsequent read reports valid time. */
    uint8_t buf[8] = {
        REG_SECONDS,
        (uint8_t)(dec_to_bcd(in->tm_sec)  & 0x7F),
        (uint8_t)(dec_to_bcd(in->tm_min)  & 0x7F),
        (uint8_t)(dec_to_bcd(in->tm_hour) & 0x3F),
        (uint8_t)(dec_to_bcd(in->tm_mday) & 0x3F),
        (uint8_t)(dec_to_bcd(in->tm_wday) & 0x07),
        (uint8_t)(dec_to_bcd(in->tm_mon + 1) & 0x1F),    /* tm 0-11 → chip 1-12 */
        (uint8_t)(dec_to_bcd(rtc_yr)),
    };
    return i2c_master_transmit(s_dev, buf, sizeof(buf), 100);
}
