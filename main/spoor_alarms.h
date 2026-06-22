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
 * starts NOW (not from when the alarm originally fired). Returns the
 * 0-based sensor index that was acked, or -1 if no spoor alarm was active.
 *
 * Call only when the overlay was raised by spoor_alarms (i.e. it's a sensor
 * alarm, not a device alarm) — otherwise the wrong module's snooze clock
 * advances, silently suppressing an alarm the user never saw. */
int spoor_alarms_acknowledged(void);

/* Scan for any armed sensor whose input is currently active and raise its
 * alarm. Returns true if an alarm was raised. Called after another alarm
 * is dismissed so a still-active sensor that was hidden behind the
 * dismissed overlay comes back into view.
 *
 *   bypass_snooze=true  → ignore the snooze gate. Use when the dismiss
 *                          freed up the user's attention (auto-dismiss on
 *                          condition clear, or user Acknowledge — see
 *                          exclude_idx below for the ack case).
 *   bypass_snooze=false → respect the snooze gate.
 *   exclude_idx         → 0..23 to skip a specific sensor in the scan
 *                          (the just-acked one — its condition is still
 *                          active, so without exclusion bypass_snooze=true
 *                          would immediately re-raise it). -1 = no exclusion.
 */
bool spoor_alarms_try_raise_next(bool bypass_snooze, int exclude_idx);

/* Read-only accessors (currently unused outside the module; kept for tests). */
int  spoor_alarms_snooze_secs(void);
bool spoor_alarms_is_armed(int sensor_index);

/* Returns custom label if set, else "Sensor N". Pointer is valid until
 * the next call. */
const char *spoor_alarms_display_label(int sensor_index);

#ifdef __cplusplus
}
#endif
