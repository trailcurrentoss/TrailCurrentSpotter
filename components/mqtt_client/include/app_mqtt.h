#ifndef APP_MQTT_H
#define APP_MQTT_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Load MQTT settings from pendant_config first (the UI-driven NVS source),
 * falling back to the older "sd_config" NVS namespace for backward compat.
 * Returns true if host + user are present (enough to attempt a connection).
 */
bool mqtt_client_load_settings(void);

/**
 * Register a callback invoked when MQTT goes up or down. The callback runs
 * on the MQTT event task — keep it short and bounce LVGL work onto the
 * LVGL thread (lv_async_call). Pass NULL to clear. Optional.
 */
typedef void (*mqtt_client_state_cb_t)(bool connected);
void mqtt_client_set_state_callback(mqtt_client_state_cb_t cb);

/**
 * Connect to the MQTT broker using loaded settings.
 * Builds mqtts:// URI, creates client with TLS, subscribes on connect.
 * Call this after WiFi has obtained an IP address.
 */
void mqtt_client_connect(void);

/**
 * Process queued incoming MQTT messages.
 * Dequeues messages, parses JSON, updates UI variables.
 * Call this periodically from the main loop.
 */
void mqtt_client_process_messages(void);

/**
 * Check if MQTT client is currently connected to the broker.
 */
bool mqtt_client_is_connected(void);

/**
 * Publish a message to the specified topic.
 * Returns message ID on success, -1 on failure.
 */
int mqtt_client_publish(const char *topic, const char *payload, int payload_len);

/**
 * Stop and destroy the underlying esp_mqtt client. Used by the discovery/OTA
 * paths to release the broker connection (and therefore the TLS socket / TCP
 * port resources) before standing up the local HTTP server on port 80.
 * Call mqtt_client_connect() again to resume normal operation.
 */
void mqtt_client_stop(void);

/**
 * Write the device's canonical hostname ("esp32-XXXXXX" using the last three
 * MAC octets) into out. Returns out. Hostname is used for mDNS advertisement
 * and as the addressing key for discovery/ota MQTT triggers.
 */
const char *mqtt_client_hostname(char *out, size_t out_len);

#endif /* APP_MQTT_H */
