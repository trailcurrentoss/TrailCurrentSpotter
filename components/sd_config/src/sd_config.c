#include "sd_config.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "nvs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const char *TAG = "SD_CONFIG";

#define MOUNT_POINT "/sdcard"
#define NVS_NAMESPACE "sd_config"

/* SD card SPI pins (Waveshare ESP32-S3-Touch-LCD-4.3) */
#define SD_SPI_MOSI  11
#define SD_SPI_MISO  13
#define SD_SPI_CLK   12

/* CS is managed by CH422G IO expander — provided by main app */
extern void sd_cs_set(bool assert_low);

static bool parse_line(const char *line, char *key, size_t key_size,
                       char *value, size_t value_size) {
    const char *eq = strchr(line, '=');
    if (!eq || eq == line)
        return false;

    size_t klen = eq - line;
    if (klen >= key_size)
        klen = key_size - 1;
    memcpy(key, line, klen);
    key[klen] = '\0';

    /* Trim trailing whitespace from key */
    while (klen > 0 && (key[klen - 1] == ' ' || key[klen - 1] == '\t')) {
        key[--klen] = '\0';
    }

    const char *vstart = eq + 1;
    /* Trim leading whitespace from value */
    while (*vstart == ' ' || *vstart == '\t')
        vstart++;

    size_t vlen = strlen(vstart);
    /* Trim trailing whitespace/newline from value */
    while (vlen > 0 && (vstart[vlen - 1] == ' ' || vstart[vlen - 1] == '\t' ||
                         vstart[vlen - 1] == '\r' || vstart[vlen - 1] == '\n')) {
        vlen--;
    }
    if (vlen >= value_size)
        vlen = value_size - 1;
    memcpy(value, vstart, vlen);
    value[vlen] = '\0';

    return klen > 0;
}

bool sd_config_read(void) {
    ESP_LOGI(TAG, "Attempting to read config from SD card...");

    /* Assert CS LOW via CH422G IO expander */
    sd_cs_set(true);

    /* Initialize SPI bus */
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = SD_SPI_MOSI,
        .miso_io_num = SD_SPI_MISO,
        .sclk_io_num = SD_SPI_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init SPI bus: %s", esp_err_to_name(ret));
        sd_cs_set(false);
        return false;
    }

    /* Mount SD card via SPI
     * CS pin is held LOW by CH422G, pass -1 as gpio_cs */
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = -1;  /* CS managed externally via CH422G */
    slot_config.host_id = SPI2_HOST;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024,
    };

    sdmmc_card_t *card = NULL;
    ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config,
                                   &mount_config, &card);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGW(TAG, "Failed to mount SD card filesystem");
        } else {
            ESP_LOGW(TAG, "Failed to initialize SD card: %s", esp_err_to_name(ret));
        }
        spi_bus_free(SPI2_HOST);
        sd_cs_set(false);
        return false;
    }

    ESP_LOGI(TAG, "SD card mounted (%s)", card->cid.name);

    /* Open NVS */
    nvs_handle_t nvs;
    ret = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open NVS: %s", esp_err_to_name(ret));
        esp_vfs_fat_sdcard_unmount(MOUNT_POINT, card);
        spi_bus_free(SPI2_HOST);
        sd_cs_set(false);
        return false;
    }

    /* Clear old connection keys (SD card is single source of truth) */
    nvs_erase_key(nvs, "wifiSSID");
    nvs_erase_key(nvs, "wifiPass");
    nvs_erase_key(nvs, "mqttHost");
    nvs_erase_key(nvs, "mqttPort");
    nvs_erase_key(nvs, "mqttUser");
    nvs_erase_key(nvs, "mqttPass");
    nvs_erase_key(nvs, "mqttCaCert");
    ESP_LOGI(TAG, "Cleared old NVS connection settings");

    /* Read config.env */
    FILE *f = fopen(MOUNT_POINT "/config.env", "r");
    if (!f) {
        ESP_LOGW(TAG, "config.env not found on SD card");
        nvs_close(nvs);
        esp_vfs_fat_sdcard_unmount(MOUNT_POINT, card);
        spi_bus_free(SPI2_HOST);
        sd_cs_set(false);
        return false;
    }

    ESP_LOGI(TAG, "Reading config.env...");
    bool found_wifi = false;
    char line[256];
    char key[64];
    char value[192];

    while (fgets(line, sizeof(line), f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\0' || *p == '\n' || *p == '\r' || *p == '#')
            continue;

        if (!parse_line(p, key, sizeof(key), value, sizeof(value)))
            continue;

        if (strcmp(key, "WIFI_SSID") == 0 && strlen(value) > 0) {
            nvs_set_str(nvs, "wifiSSID", value);
            ESP_LOGI(TAG, "WiFi SSID: %s", value);
            found_wifi = true;
        } else if (strcmp(key, "WIFI_PWD") == 0) {
            nvs_set_str(nvs, "wifiPass", value);
            ESP_LOGI(TAG, "WiFi password set");
        } else if (strcmp(key, "MQTT_HOST") == 0 && strlen(value) > 0) {
            nvs_set_str(nvs, "mqttHost", value);
            ESP_LOGI(TAG, "MQTT Host: %s", value);
        } else if (strcmp(key, "MQTT_PORT") == 0 && strlen(value) > 0) {
            int port = atoi(value);
            if (port > 0 && port <= 65535) {
                nvs_set_u16(nvs, "mqttPort", (uint16_t)port);
                ESP_LOGI(TAG, "MQTT Port: %d", port);
            }
        } else if (strcmp(key, "MQTT_USER") == 0 && strlen(value) > 0) {
            nvs_set_str(nvs, "mqttUser", value);
            ESP_LOGI(TAG, "MQTT User: %s", value);
        } else if (strcmp(key, "MQTT_PASS") == 0 && strlen(value) > 0) {
            nvs_set_str(nvs, "mqttPass", value);
            ESP_LOGI(TAG, "MQTT password set");
        }
    }
    fclose(f);

    /* Read CA certificate if present */
    f = fopen(MOUNT_POINT "/ca.crt", "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        long cert_size = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (cert_size > 0 && cert_size < 8192) {
            char *cert_buf = malloc(cert_size + 1);
            if (cert_buf) {
                size_t read_len = fread(cert_buf, 1, cert_size, f);
                cert_buf[read_len] = '\0';
                nvs_set_str(nvs, "mqttCaCert", cert_buf);
                ESP_LOGI(TAG, "CA cert stored (%ld bytes)", cert_size);
                free(cert_buf);
            }
        }
        fclose(f);
    } else {
        ESP_LOGI(TAG, "ca.crt not found (optional)");
    }

    nvs_commit(nvs);
    nvs_close(nvs);

    /* Unmount SD card and free SPI bus */
    esp_vfs_fat_sdcard_unmount(MOUNT_POINT, card);
    spi_bus_free(SPI2_HOST);
    sd_cs_set(false);

    ESP_LOGI(TAG, "Config read complete (WiFi found: %s)", found_wifi ? "yes" : "no");
    return found_wifi;
}
