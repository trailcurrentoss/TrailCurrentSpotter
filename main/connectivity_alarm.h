#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Connectivity alarm — switches the active screen to PageClockMode when the
 * Spotter loses WiFi or MQTT connectivity for long enough that the dashboard
 * data would be stale. The clock-mode screen carries a non-pulsing warning
 * strip ("No TrailCurrent Connection"), a large monospaced clock fed from the
 * RTC, and a settings-gear shortcut. No chime, no acknowledge required — the
 * device is intentionally usable as a quiet clock while the trailer is
 * disconnected.
 *
 * A short debounce (CONNECTIVITY_ALARM_DEBOUNCE_MS) suppresses the swap for
 * routine blips so PageClockMode only takes over when a drop actually lasts.
 * On reconnect we restore the screen the user was on before the drop.
 *
 * The swap only fires once the device is in APP_STATE_READY — during
 * boot/setup the user is intentionally not yet connected, so no swap.
 *
 * Real alarms (sensor trips, device-relay state changes) still raise the
 * full alarm overlay with chime via spotter_alarm_raise(). Only connectivity
 * loss is routed through PageClockMode.
 *
 * All API functions must be called on the LVGL thread (or via lv_async_call)
 * because they touch screen state.
 */

#define CONNECTIVITY_ALARM_DEBOUNCE_MS 10000

void connectivity_alarm_init(void);

void connectivity_alarm_set_wifi(bool connected);
void connectivity_alarm_set_mqtt(bool connected);

/* Re-evaluate the current wifi/mqtt state without requiring an edge.
 * Call once when the app first reaches APP_STATE_READY so a cold boot
 * with saved creds but no reachable trailer falls through to
 * PageClockMode (after the standard debounce) instead of sitting on the
 * dashboard with placeholder data. set_wifi/set_mqtt early-return on
 * no-state-change, which means a cold boot — where the link was never
 * up to begin with — never triggers the swap on its own. */
void connectivity_alarm_evaluate(void);

/* Tell the connectivity-alarm subsystem the user navigated away from
 * PageClockMode on their own (e.g. tapped the gear-icon settings shortcut).
 * Clears the auto-restore-on-reconnect bookkeeping so reconnect does not
 * yank the user off whatever screen they intentionally moved to. */
void connectivity_clock_user_left(void);

#ifdef __cplusplus
}
#endif
