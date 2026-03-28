#ifndef SD_CONFIG_H
#define SD_CONFIG_H

#include <stdbool.h>

/**
 * Read configuration from SD card (config.env and optional ca.crt).
 * Stores parsed values into NVS namespace "sd_config".
 *
 * SD card CS is managed via CH422G IO expander — the main application
 * must provide the sd_cs_set() function.
 *
 * Returns true if WiFi credentials were found on the SD card.
 */
bool sd_config_read(void);

#endif /* SD_CONFIG_H */
