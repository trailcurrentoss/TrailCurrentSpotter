#pragma once

#include <time.h>
#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Battery-backed RTC on the Waveshare ESP32-S3-Touch-LCD-4.3C board —
 * NXP PCF85063A, I2C address 0x51.  The chip stores time in BCD and runs
 * off the panel's coin-cell when main power drops, so the time survives
 * across power cycles even when TrailCurrent is unreachable.
 *
 * Convention: this driver stores and returns UTC.  The local timezone
 * is applied by the platform's TZ machinery (tzset / localtime_r) — the
 * RTC chip itself knows nothing about timezones or DST.  All times
 * passed to rtc_pcf85063_write must be UTC; rtc_pcf85063_read returns
 * UTC.
 *
 * All API functions are synchronous and safe to call from any task; the
 * underlying I2C transfers complete in well under a millisecond.
 */

esp_err_t rtc_pcf85063_init(i2c_master_bus_handle_t bus);

/* Read current UTC time. On success *out is populated. tm_yday and
 * tm_isdst are zeroed. Returns:
 *   ESP_OK              — read succeeded, time is valid
 *   ESP_ERR_INVALID_STATE — chip reports oscillator was stopped (cold
 *                            boot with dead coin cell) — *out untouched
 *   ESP_ERR_* on bus errors. */
esp_err_t rtc_pcf85063_read(struct tm *out);

/* Write the given UTC time. Clears the OS (oscillator-stopped) bit so a
 * subsequent read will report ESP_OK. */
esp_err_t rtc_pcf85063_write(const struct tm *in);

#ifdef __cplusplus
}
#endif
