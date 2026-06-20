#pragma once

/*
 * Top-level Spotter state machine.
 *
 *      ┌─── BOOT ────────────────────────────────┐
 *      │ NVS, display, LVGL, ui_init             │
 *      └─────────────────────────────────────────┘
 *                  │
 *                  ▼  no saved SSID
 *      ┌─── WIFI_SETUP ──────────────────────────┐
 *      │ PageWifiSetup — scan + password panel   │
 *      └─────────────────────────────────────────┘
 *                  │  user submits credentials
 *                  ▼
 *      ┌─── WIFI_CONNECTING ─────────────────────┐
 *      │ PageWifiConnecting — spinner            │
 *      └─────────────────────────────────────────┘
 *                  │  IP_EVENT_STA_GOT_IP
 *                  ▼
 *      ┌─── READY (PageDrive + the 4-tab dock) ──┐
 *      └─────────────────────────────────────────┘
 *
 * Adapted from FluidCNC pendant's app_state. Stripped of FluidNC integration.
 */

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_STATE_BOOT = 0,
    APP_STATE_WIFI_SETUP,
    APP_STATE_WIFI_CONNECTING,
    APP_STATE_MQTT_SETUP,        /* PageMqttSetup — enter server/user/pass */
    APP_STATE_MQTT_CONNECTING,   /* PageMqttConnecting — spinner */
    APP_STATE_READY,             /* PageDrive */
} app_state_t;

/* Update the combined top-toolbar label whenever MQTT goes up/down. The label
 * shows "<AXLE> | Connected" or "<AXLE> | Offline" — axle comes from the
 * Setup-page selection, status comes from the MQTT broker. Called from the
 * MQTT client's state callback; also called by axle changes to keep the
 * label consistent. */
void app_state_set_mqtt_connected(bool connected);

esp_err_t app_state_init(void);
void      app_state_set(app_state_t next);
app_state_t app_state_get(void);

/* Repaint the WiFi scan list rows from the latest wifi_setup scan results.
 * Safe from any task. */
void app_state_refresh_wifi_list(void);

/* Update the status caption / spinner on PageWifiSetup. */
void app_state_wifi_show_scanning(void);
void app_state_wifi_show_idle_message(const char *msg);

/* Update the per-page status bar to reflect WiFi connected/disconnected. */
void app_state_refresh_connection_display(void);

#ifdef __cplusplus
}
#endif
