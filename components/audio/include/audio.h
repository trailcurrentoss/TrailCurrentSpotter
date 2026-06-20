#pragma once

#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PA enable callback — the codec needs the IO extender's PA bit on before
 * any audio is audible. Owned by main.c (which controls CH422G). */
typedef void (*audio_pa_set_fn_t)(bool enable);

/* Initialize I2S TX + ES8311 codec on the shared I2C bus. Safe to call once
 * during boot — subsequent calls are no-ops. */
esp_err_t spotter_audio_init(i2c_master_bus_handle_t bus, audio_pa_set_fn_t pa_set);

/* Begin a chime sequence: enables PA, opens the codec, primes the tone
 * buffer. Match each start with a stop. */
void spotter_audio_chime_start(void);

/* Play one short "ding" — call repeatedly while the alarm is active. */
void spotter_audio_chime_tick(void);

/* End the chime sequence: closes the codec, mutes the PA. */
void spotter_audio_chime_stop(void);

#ifdef __cplusplus
}
#endif
