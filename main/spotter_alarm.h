#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Public façade for the alarm-overlay machinery built in actions.c.
 *
 * The overlay (full-screen pulsing red wash + center card + acknowledge button)
 * is owned by actions.c. Other modules can raise an alarm via this header
 * without reaching into the static helpers.
 *
 * auto_dismiss_secs > 0 schedules an automatic dismiss after that many
 * seconds; 0 disables auto-dismiss (overlay stays until the user taps
 * Acknowledge). The auto-dismiss timer is single-shot — if the user
 * acknowledges first, the timer is cancelled.
 */
void spotter_alarm_raise(const char *title, const char *body, int auto_dismiss_secs);

/* Force-close the overlay (silently). Safe to call when no overlay is shown. */
void spotter_alarm_force_dismiss(void);

#ifdef __cplusplus
}
#endif
