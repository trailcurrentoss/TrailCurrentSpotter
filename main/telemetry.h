#pragma once

/*
 * Connectivity telemetry — publishes a periodic heartbeat plus discrete
 * event notifications to MQTT so the device's WiFi/MQTT link can be
 * monitored from any client on the same broker.
 *
 * Two topics, both under the device's hostname so multiple Spotters on the
 * same broker don't collide:
 *
 *   local/spotter/<hostname>/telemetry  — 10 s heartbeat
 *   local/spotter/<hostname>/events     — one message per state transition
 *
 * Heartbeat payload (JSON):
 *   {
 *     "uptime_s":      seconds since boot,
 *     "wifi":          "connected"|"connecting"|"disconnected"|"scanning"|"failed"|"idle",
 *     "rssi":          dBm (only when associated; omitted otherwise),
 *     "bssid":         "aa:bb:cc:dd:ee:ff" (only when associated),
 *     "ch":            primary channel (only when associated),
 *     "ip":            "x.y.z.w" or "0.0.0.0",
 *     "mqtt":          "up"|"down",
 *     "wifi_drops":    count of STA_DISCONNECTED since boot,
 *     "mqtt_drops":    count of MQTT_EVENT_DISCONNECTED since boot,
 *     "last_wifi_rsn": last raw wifi_err_reason_t,
 *     "last_mqtt_etyp":last esp_mqtt_error_codes_t.error_type,
 *     "last_mqtt_err": last esp_transport_sock_errno,
 *     "heap":          free internal heap bytes
 *   }
 *
 * Event payload (JSON):
 *   {
 *     "uptime_s": ...,
 *     "kind":     "wifi_down" | "wifi_up" | "mqtt_down" | "mqtt_up",
 *     ... per-kind extras (raw_reason / err_type / sock_errno / rssi_at_drop)
 *   }
 *
 * Events that occur while MQTT is down are queued in a small RAM ring buffer
 * and drained on the next "mqtt_up" so the full disconnect timeline survives
 * a broker outage. Heartbeats are NOT queued — only the latest snapshot
 * matters.
 */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Wire telemetry up. Registers itself as the wifi_setup link-event sink and
 * builds the MQTT topic strings using the device hostname. Safe to call
 * before MQTT is up — heartbeats only publish once mqtt_client_is_connected()
 * returns true. */
void telemetry_init(void);

/* Call ~1 Hz from the main loop. Publishes a heartbeat every 10 s when MQTT
 * is connected. No-op otherwise. */
void telemetry_tick(void);

/* Called by mqtt_client.c so we don't have to import its private state. */
void telemetry_on_mqtt_state(bool connected);

/* Called by mqtt_client.c from MQTT_EVENT_ERROR with the underlying error
 * codes so the *next* disconnect event carries useful detail (the disconnect
 * event itself doesn't include them). */
void telemetry_on_mqtt_error(int error_type, int sock_errno, int tls_last_esp_err,
                             int tls_stack_err, int connect_return_code);

#ifdef __cplusplus
}
#endif
