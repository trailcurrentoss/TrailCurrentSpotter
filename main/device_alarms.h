#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Device alarms — tracks the 24 Switchback relay outputs (3 boards × 8
 * relays). MQTT source: local/relays/<1..24>/status with payload
 * {"state": 0|1}, published by the Headwaters CAN bridge.
 *
 * Same model as spoor_alarms (which handles digital inputs), with one
 * extra per-device bit:
 *   - armed bit per device (NVS-persisted) — alarm watching is enabled
 *   - inverted bit per device (NVS-persisted) — fire when device is OFF
 *     instead of ON. Use case: "fridge stopped" alarm (fire on relay off)
 *     vs "light left on" alarm (fire on relay on).
 *   - custom label per device (NVS-persisted, "Device N" default)
 *   - rising-edge fire / steady-state snooze gate (edge direction
 *     respects the invert flag)
 *   - sticky overlay (cleared by Acknowledge or the alarm condition
 *     returning to normal)
 *
 * The rename UI (page_rename_sensor) is shared with spoor_alarms. Only one
 * rename can be in flight at a time; save/cancel actions dispatch to whichever
 * module currently has a rename target.
 *
 * Storage is NVS namespace "device".
 */

#define DEVICE_BOARD_COUNT       3
#define DEVICES_PER_BOARD        8
#define DEVICE_COUNT             (DEVICE_BOARD_COUNT * DEVICES_PER_BOARD)
#define DEVICE_LABEL_MAX         24

void device_alarms_init(void);

/* MQTT entry — call from process_message() for local/relays/<channel>/status.
 * channel is 1..24 (matches the topic suffix); state is 0 or 1. Out-of-range
 * channels are ignored with a warning. */
void device_alarms_handle_state(int channel, int state);

/* Action plumbing (called from main/actions.c). */
void device_alarms_toggle_arm(int device_index);
void device_alarms_toggle_invert(int device_index);
void device_alarms_open_rename(int device_index);
/* The save/cancel paths are no-ops unless THIS module has the active rename.
 * Safe to call from a generic save/cancel action that fans out to both
 * spoor_alarms and device_alarms. */
void device_alarms_save_rename(void);
void device_alarms_cancel_rename(void);

/* Acknowledge hook — resets the snooze clock for the currently-showing
 * device alarm (no-op when no device alarm is active). */
void device_alarms_acknowledged(void);

/* Mirror of spoor_alarms_try_raise_next() — see spoor_alarms.h. Called from
 * dismiss paths to surface a still-active device alarm that was hidden by
 * the dismissed overlay. */
bool device_alarms_try_raise_next(bool bypass_snooze);

/* Read-only accessors. */
bool device_alarms_is_armed(int device_index);
bool device_alarms_is_inverted(int device_index);
const char *device_alarms_display_label(int device_index);

#ifdef __cplusplus
}
#endif
