#pragma once

/*
 * Persistent configuration for Spotter (NVS-backed, namespace "spotter").
 *
 * Stores WiFi credentials entered through the touchscreen on first boot.
 * Adapted from the FluidCNC pendant's pendant_config — slimmed to WiFi only
 * since Spotter has no FluidNC/units state.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PENDANT_CFG_SSID_MAX  33    /* 32 + NUL */
#define PENDANT_CFG_PASS_MAX  65    /* 64 + NUL */
#define PENDANT_CFG_HOST_MAX  65    /* hostname/IP + NUL */
#define PENDANT_CFG_USER_MAX  65    /* MQTT username + NUL */
#define PENDANT_CFG_MPASS_MAX 129   /* MQTT password + NUL */

typedef struct {
    char     wifi_ssid[PENDANT_CFG_SSID_MAX];
    char     wifi_pass[PENDANT_CFG_PASS_MAX];

    /* MQTT (TrailCurrent server) — connected over TLS with cert verification
     * skipped at the TLS layer (CONFIG_ESP_TLS_INSECURE) so self-signed certs
     * just work. mqtt_port defaults to 8883. */
    char     mqtt_host[PENDANT_CFG_HOST_MAX];
    char     mqtt_user[PENDANT_CFG_USER_MAX];
    char     mqtt_pass[PENDANT_CFG_MPASS_MAX];
    uint16_t mqtt_port;
} pendant_config_t;

/* Initialize NVS namespace and load cached config. Safe to call once. */
esp_err_t pendant_config_init(void);

/* Pointer to the in-memory cached config. Read-only access; mutate via setters. */
const pendant_config_t *pendant_config_get(void);

/* True if a non-empty SSID is saved. */
bool pendant_config_has_wifi(void);

/* True if mqtt_host AND mqtt_user are saved (mqtt_pass may be empty for some
 * broker configurations, but a host + user is the minimum to attempt a
 * connection). */
bool pendant_config_has_mqtt(void);

/* Write SSID + password to NVS and update cache. password may be empty for open APs. */
esp_err_t pendant_config_set_wifi(const char *ssid, const char *pass);

/* Write MQTT host / user / password / port to NVS and update cache. port=0 means
 * use default (8883). */
esp_err_t pendant_config_set_mqtt(const char *host, const char *user,
                                  const char *pass, uint16_t port);

/* Erase WiFi creds from NVS and cache. */
esp_err_t pendant_config_clear_wifi(void);
/* Erase MQTT config. */
esp_err_t pendant_config_clear_mqtt(void);

#ifdef __cplusplus
}
#endif
