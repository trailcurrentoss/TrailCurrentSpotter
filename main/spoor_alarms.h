#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Spoor alarms — tracks the 24 Switchback digital inputs (3 boards × 8
 * sensors), the per-sensor "armed" flag, the per-sensor custom label, and
 * the alarm snooze timing.
 *
 *   armed  : if cleared, an active input never raises the overlay.
 *   custom : if non-empty, used in place of the default "Sensor N" in the
 *            row label AND as the overlay's body title.
 *   snooze : seconds after Acknowledge before the same sensor may raise
 *            the overlay again (so a held-open vent doesn't trap the user
 *            in a loop while they're fixing it).
 *
 * Alarms stay on screen until the user taps Acknowledge or the sensor
 * returns to normal — there is no auto-dismiss show timer.
 *
 * Storage is NVS namespace "spoor".
 */

#define SPOOR_ADDR_COUNT        3
#define SPOOR_SENSORS_PER_ADDR  8
#define SPOOR_SENSOR_COUNT      (SPOOR_ADDR_COUNT * SPOOR_SENSORS_PER_ADDR)
#define SPOOR_LABEL_MAX         24

#define SPOOR_SNOOZE_SECS_MIN     10
#define SPOOR_SNOOZE_SECS_MAX     180
#define SPOOR_SNOOZE_SECS_DEFAULT 30

/* Load NVS state and paint every alarm row's switch state + label text,
 * plus the two PageSetup sliders + value labels. Call after ui_init(). */
void spoor_alarms_init(void);

/* MQTT entry — process_message() dispatches here for local/spoor/<n>/inputs.
 * inputs_bitmask: bit i set = sensor (i+1) active. */
void spoor_alarms_handle_inputs(int addr, uint8_t inputs_bitmask);

/* Action plumbing (called from main/actions.c). */
void spoor_alarms_toggle_arm(int sensor_index);
void spoor_alarms_open_rename(int sensor_index);
void spoor_alarms_save_rename(void);
void spoor_alarms_cancel_rename(void);
void spoor_alarms_set_snooze_secs(int s);

/* Notify the spoor module that the currently-showing alarm was acknowledged
 * by the user. Resets the per-sensor snooze clock so the snooze window
 * starts NOW (not from when the alarm originally fired). Call this from
 * every code path that dismisses the overlay in response to a user tap on
 * Acknowledge. No-op when no spoor alarm is currently active. */
void spoor_alarms_acknowledged(void);

/* Read-only accessors (currently unused outside the module; kept for tests). */
int  spoor_alarms_snooze_secs(void);
bool spoor_alarms_is_armed(int sensor_index);

/* Returns custom label if set, else "Sensor N". Pointer is valid until
 * the next call. */
const char *spoor_alarms_display_label(int sensor_index);

#ifdef __cplusplus
}
#endif
