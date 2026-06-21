#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Connectivity alarm — fires a full-screen alarm overlay when the Spotter
 * loses WiFi or MQTT connectivity for long enough that incoming sensor
 * alarms could be missed. Two messages, both via spotter_alarm_raise():
 *
 *   "Lost WiFi Connection"          — WiFi link is down
 *   "Lost TrailCurrent Connection"  — WiFi is up but MQTT broker is unreachable
 *
 * A short debounce (CONNECTIVITY_ALARM_DEBOUNCE_MS) suppresses alarms for
 * routine blips so the user only sees a banner when a drop actually
 * threatens reliability. The alarm auto-dismisses as soon as connectivity
 * is restored.
 *
 * The alarm only fires once the device is in APP_STATE_READY — during
 * boot/setup the user is intentionally not yet connected, so no alarm.
 *
 * All API functions must be called on the LVGL thread (or via
 * lv_async_call) because they touch the alarm overlay machinery.
 */

#define CONNECTIVITY_ALARM_DEBOUNCE_MS 10000

void connectivity_alarm_init(void);

void connectivity_alarm_set_wifi(bool connected);
void connectivity_alarm_set_mqtt(bool connected);

#ifdef __cplusplus
}
#endif
