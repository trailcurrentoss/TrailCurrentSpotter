#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_timer.h"
#include "driver/i2c.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "lvgl.h"

#include "ui/ui.h"
#include "ui/vars.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "app_mqtt.h"
#include "sd_config.h"

static const char *TAG = "spotter";

/* ============================================================================
 * Display resolution
 * ============================================================================ */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/* ============================================================================
 * CH422G IO expander
 * Uses different I2C addresses per function (no register addressing).
 *   0x24 = system parameter (write IO_OE=1 to enable push-pull EXIO outputs)
 *   0x38 = IO0-7 output data
 * Pin mapping within the 0x38 output byte:
 *   Bit 1 = EXIO1 = Touch RST
 *   Bit 2 = EXIO2 = Backlight enable
 *   Bit 3 = EXIO3 = LCD RST
 *   Bit 4 = EXIO4 = SD_CS
 *   Bit 5 = EXIO5 = USB_SEL
 * ============================================================================ */
#define CH422G_SYS_ADDR   0x24
#define CH422G_OUT_ADDR   0x38

#define CH422G_EXIO1_BIT  (1 << 1)   /* Touch RST */
#define CH422G_EXIO2_BIT  (1 << 2)   /* Backlight enable */
#define CH422G_EXIO3_BIT  (1 << 3)   /* LCD RST */
#define CH422G_EXIO4_BIT  (1 << 4)   /* SD_CS */
#define CH422G_EXIO5_BIT  (1 << 5)   /* USB_SEL */

#define I2C_PORT     I2C_NUM_0
#define I2C_SDA_PIN  8
#define I2C_SCL_PIN  9
#define I2C_FREQ_HZ  400000

static uint8_t ch422g_out = 0;

static esp_err_t ch422g_write(uint8_t addr, uint8_t val)
{
    uint8_t buf = val;
    return i2c_master_write_to_device(I2C_PORT, addr, &buf, 1, pdMS_TO_TICKS(100));
}

static void ch422g_set_bit(uint8_t bit, bool high)
{
    if (high) ch422g_out |= bit;
    else      ch422g_out &= ~bit;
    ch422g_write(CH422G_OUT_ADDR, ch422g_out);
}

static void ch422g_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    i2c_param_config(I2C_PORT, &conf);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);

    /* Enable push-pull output mode for EXIO pins (IO_OE = bit 0) */
    esp_err_t err = ch422g_write(CH422G_SYS_ADDR, 0x01);
    ESP_LOGI(TAG, "CH422G init %s", err == ESP_OK ? "OK" : "FAILED");

    /* Backlight on, touch RST high, LCD RST high, SD CS high, USB_SEL low */
    ch422g_out = CH422G_EXIO1_BIT | CH422G_EXIO2_BIT | CH422G_EXIO3_BIT | CH422G_EXIO4_BIT;
    ch422g_write(CH422G_OUT_ADDR, ch422g_out);
}

/* SD card CS control — called by sd_config component */
void sd_cs_set(bool assert_low)
{
    ch422g_set_bit(CH422G_EXIO4_BIT, !assert_low);
}

/* ============================================================================
 * Backlight (digital on/off via CH422G EXIO2, software dimming via overlay)
 * ============================================================================ */
static uint8_t current_brightness = 255;
static bool screen_timed_out = false;
static lv_obj_t *dimming_overlay = NULL;
static uint32_t last_activity_time = 0;

static void apply_brightness(uint8_t brightness)
{
    if (brightness == 0) {
        ch422g_set_bit(CH422G_EXIO2_BIT, false);
        return;
    }
    ch422g_set_bit(CH422G_EXIO2_BIT, true);

    if (dimming_overlay) {
        lv_opa_t opa = (lv_opa_t)(255 - brightness);
        lv_obj_set_style_bg_opa(dimming_overlay, opa, 0);
    }
}

void set_backlight(uint8_t brightness)
{
    current_brightness = brightness;
    if (!screen_timed_out) {
        apply_brightness(brightness);
    }
}

uint8_t get_backlight(void)
{
    return current_brightness;
}

static void create_dimming_overlay(void)
{
    dimming_overlay = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(dimming_overlay);
    lv_obj_set_size(dimming_overlay, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(dimming_overlay, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(dimming_overlay, LV_OPA_TRANSP, 0);
    lv_obj_add_flag(dimming_overlay, LV_OBJ_FLAG_FLOATING);
    lv_obj_clear_flag(dimming_overlay, LV_OBJ_FLAG_CLICKABLE);
}

/* ============================================================================
 * Screen timeout
 * ============================================================================ */
static lv_obj_t *wake_overlay = NULL;

static void wake_overlay_cb(lv_event_t *e)
{
    (void)e;
    /* First touch wakes the screen — absorb it */
    screen_timed_out = false;
    apply_brightness(current_brightness);
    last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
    if (wake_overlay) {
        lv_obj_del(wake_overlay);
        wake_overlay = NULL;
    }
}

static void handle_screen_timeout(void)
{
    int32_t timeout_minutes = get_var_screen_timeout_value();
    if (timeout_minutes <= 0 || screen_timed_out) return;

    /* Check if driving and keep-on-while-driving is enabled */
    if (get_var_keep_screen_on_while_driving() && get_var_current_speed_value() > 0) {
        last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
        return;
    }

    uint32_t now = (uint32_t)(esp_timer_get_time() / 1000);
    uint32_t elapsed_ms = now - last_activity_time;

    if (elapsed_ms >= (uint32_t)(timeout_minutes * 60 * 1000)) {
        screen_timed_out = true;
        apply_brightness(0);

        /* Create fullscreen overlay to absorb the wake touch */
        wake_overlay = lv_obj_create(lv_layer_top());
        lv_obj_remove_style_all(wake_overlay);
        lv_obj_set_size(wake_overlay, SCREEN_WIDTH, SCREEN_HEIGHT);
        lv_obj_set_style_bg_color(wake_overlay, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(wake_overlay, LV_OPA_COVER, 0);
        lv_obj_add_event_cb(wake_overlay, wake_overlay_cb, LV_EVENT_CLICKED, NULL);
    }
}

/* ============================================================================
 * NVS settings
 * ============================================================================ */
#define USER_SETTINGS_NVS_NAMESPACE "user_settings"

static void restore_user_settings(void)
{
    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READONLY, &nvs) != ESP_OK) {
        ESP_LOGI(TAG, "No saved user settings, using defaults");
        return;
    }

    int32_t theme = 0;
    nvs_get_i32(nvs, "selectedTheme", &theme);
    set_var_selected_theme(theme);

    int32_t timeout = 0;
    nvs_get_i32(nvs, "screenTimeout", &timeout);
    set_var_screen_timeout_value(timeout);

    uint8_t keep_on = 1;
    nvs_get_u8(nvs, "onWhileDriving", &keep_on);
    set_var_keep_screen_on_while_driving(keep_on != 0);

    char tz[100] = {0};
    size_t tz_len = sizeof(tz);
    if (nvs_get_str(nvs, "timeZone", tz, &tz_len) == ESP_OK) {
        set_var_current_time_zone_string(tz);
    }

    /* Restore timezone dropdown selection */
    const char *tz_items[] = {
        "ASKT9AKDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "CST6CDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "HST11HDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "EST5EDT,M3.2.0/2:00:00,M11.1.0/2:00:00",
        "MST7"
    };
    for (int i = 0; i < 7; i++) {
        if (strcmp(tz_items[i], tz) == 0) {
            lv_dropdown_set_selected(objects.drop_down_selected_time_zone, i);
            break;
        }
    }

    nvs_close(nvs);
    ESP_LOGI(TAG, "User settings restored (theme=%d, timeout=%d)", (int)theme, (int)timeout);
}

static void persist_user_settings(void)
{
    if (!get_var_user_settings_changed()) return;

    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) != ESP_OK) return;

    nvs_set_i32(nvs, "selectedTheme", get_var_selected_theme());
    nvs_set_i32(nvs, "screenTimeout", get_var_screen_timeout_value());
    nvs_set_u8(nvs, "onWhileDriving", get_var_keep_screen_on_while_driving() ? 1 : 0);
    nvs_set_str(nvs, "timeZone", get_var_current_time_zone_string());
    nvs_commit(nvs);
    nvs_close(nvs);

    set_var_user_settings_changed(false);
    ESP_LOGI(TAG, "User settings persisted");
}

/* ============================================================================
 * RGB LCD panel (double-buffered with vsync synchronization)
 * ============================================================================ */
static esp_lcd_panel_handle_t panel_handle = NULL;
static SemaphoreHandle_t vsync_sem = NULL;

static IRAM_ATTR bool on_vsync(esp_lcd_panel_handle_t panel,
                                const esp_lcd_rgb_panel_event_data_t *edata,
                                void *user_ctx)
{
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(vsync_sem, &woken);
    return woken == pdTRUE;
}

static void lcd_init(void)
{
    vsync_sem = xSemaphoreCreateBinary();

    esp_lcd_rgb_panel_config_t panel_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = {
            .pclk_hz = 14000000,
            .h_res = SCREEN_WIDTH,
            .v_res = SCREEN_HEIGHT,
            .hsync_pulse_width = 10,
            .hsync_back_porch = 10,
            .hsync_front_porch = 20,
            .vsync_pulse_width = 10,
            .vsync_back_porch = 10,
            .vsync_front_porch = 10,
            .flags.pclk_active_neg = false,
        },
        .data_width = 16,
        .bits_per_pixel = 16,
        .num_fbs = 2,
        .bounce_buffer_size_px = SCREEN_WIDTH * 20,
        .psram_trans_align = 64,
        .de_gpio_num = 5,
        .pclk_gpio_num = 7,
        .vsync_gpio_num = 3,
        .hsync_gpio_num = 46,
        .disp_gpio_num = -1,
        .data_gpio_nums = {
            /* B[0:4] */
            14, 38, 18, 17, 10,
            /* G[0:5] */
            39, 0, 45, 48, 47, 21,
            /* R[0:4] */
            1, 2, 42, 41, 40,
        },
        .flags.fb_in_psram = true,
    };

    ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    esp_lcd_rgb_panel_event_callbacks_t cbs = { .on_vsync = on_vsync };
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, NULL));

    ESP_LOGI(TAG, "RGB LCD initialized (800x480, 14MHz, double-buffered)");
}

/* ============================================================================
 * GT911 touch
 * ============================================================================ */
static esp_lcd_touch_handle_t touch_handle = NULL;

static void touch_init(void)
{
    /* Pulse touch RST via CH422G EXIO1 */
    ch422g_set_bit(CH422G_EXIO1_BIT, false);
    vTaskDelay(pdMS_TO_TICKS(10));
    ch422g_set_bit(CH422G_EXIO1_BIT, true);
    vTaskDelay(pdMS_TO_TICKS(100));

    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)I2C_PORT,
                                              &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = SCREEN_WIDTH,
        .y_max = SCREEN_HEIGHT,
        .rst_gpio_num = -1,
        .int_gpio_num = -1,
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &touch_handle));
    ESP_LOGI(TAG, "GT911 touch initialized");
}

/* ============================================================================
 * LVGL tick, display driver, touch input (direct mode, vsync-synced)
 * ============================================================================ */
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static void lvgl_tick_cb(void *arg)
{
    (void)arg;
    lv_tick_inc(1);
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area,
                           lv_color_t *color_map)
{
    if (lv_disp_flush_is_last(drv)) {
        xSemaphoreTake(vsync_sem, portMAX_DELAY);
        esp_lcd_panel_draw_bitmap(panel_handle, 0, 0,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, color_map);
    }
    lv_disp_flush_ready(drv);
}

static void lvgl_touch_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    esp_lcd_touch_read_data(touch_handle);

    esp_lcd_touch_point_data_t pt;
    uint8_t count = 0;
    if (esp_lcd_touch_get_data(touch_handle, &pt, &count, 1) == ESP_OK && count > 0) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = pt.x;
        data->point.y = pt.y;
        last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

static void lvgl_init(void)
{
    lv_init();

    /* 1ms tick timer */
    const esp_timer_create_args_t tick_args = {
        .callback = lvgl_tick_cb,
        .name = "lvgl_tick",
    };
    esp_timer_handle_t tick_timer;
    ESP_ERROR_CHECK(esp_timer_create(&tick_args, &tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(tick_timer, 1000));

    /* Get both PSRAM framebuffers for tear-free double-buffered direct mode */
    void *fb[2] = {NULL, NULL};
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_get_frame_buffer(panel_handle, 2,
                                                        &fb[0], &fb[1]));

    uint32_t buf_size = SCREEN_WIDTH * SCREEN_HEIGHT;
    lv_disp_draw_buf_init(&draw_buf, (lv_color_t *)fb[0],
                          (lv_color_t *)fb[1], buf_size);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.direct_mode = 1;
    lv_disp_drv_register(&disp_drv);

    /* Touch input */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lvgl_touch_read_cb;
    lv_indev_drv_register(&indev_drv);

    ESP_LOGI(TAG, "LVGL initialized (direct mode)");
}

/* ============================================================================
 * WiFi
 * ============================================================================ */
static char wifi_connected_ip[20] = {0};
static int wifi_retry_count = 0;
#define WIFI_MAX_RETRIES 5

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT) {
        switch (event_id) {
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGI(TAG, "WiFi connected to AP");
            wifi_retry_count = 0;
            set_var_wifi_connected(true);
            break;
        case WIFI_EVENT_STA_DISCONNECTED: {
            set_var_wifi_connected(false);
            if (wifi_retry_count < WIFI_MAX_RETRIES) {
                wifi_retry_count++;
                ESP_LOGI(TAG, "WiFi retry %d/%d...", wifi_retry_count, WIFI_MAX_RETRIES);
                esp_wifi_connect();
            } else {
                ESP_LOGW(TAG, "WiFi max retries reached");
            }
            break;
        }
        default:
            break;
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        snprintf(wifi_connected_ip, sizeof(wifi_connected_ip),
                 IPSTR, IP2STR(&event->ip_info.ip));
        ESP_LOGI(TAG, "Got IP: %s", wifi_connected_ip);
        mqtt_client_connect();
    }
}

static void wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    /* Register event handlers */
    esp_event_handler_instance_t wifi_handler;
    esp_event_handler_instance_t ip_handler;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &wifi_handler));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &ip_handler));

    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "WiFi initialized (STA mode)");
}

static void wifi_auto_connect(void)
{
    nvs_handle_t nvs;
    if (nvs_open("sd_config", NVS_READONLY, &nvs) != ESP_OK) {
        ESP_LOGW(TAG, "No sd_config NVS namespace");
        return;
    }

    char ssid[33] = {0};
    char pass[65] = {0};
    size_t len;

    len = sizeof(ssid);
    if (nvs_get_str(nvs, "wifiSSID", ssid, &len) != ESP_OK || strlen(ssid) == 0) {
        ESP_LOGW(TAG, "No WiFi SSID in NVS");
        nvs_close(nvs);
        return;
    }

    len = sizeof(pass);
    nvs_get_str(nvs, "wifiPass", pass, &len);
    nvs_close(nvs);

    ESP_LOGI(TAG, "Auto-connecting to WiFi: %s", ssid);

    wifi_config_t wifi_cfg = {0};
    strncpy((char *)wifi_cfg.sta.ssid, ssid, sizeof(wifi_cfg.sta.ssid) - 1);
    strncpy((char *)wifi_cfg.sta.password, pass, sizeof(wifi_cfg.sta.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg));
    esp_wifi_connect();
}

/* ============================================================================
 * Warning indicators (checked periodically in main loop)
 * ============================================================================ */
static void update_warning_indicators(void)
{
    bool any_lights_on = (get_var_pdm01_device01_status() > 0) ||
                         (get_var_pdm01_device02_status() > 0) ||
                         (get_var_pdm01_device03_status() > 0) ||
                         (get_var_pdm01_device04_status() > 0) ||
                         (get_var_pdm01_device05_status() > 0) ||
                         (get_var_pdm01_device08_status() > 0);

    if (any_lights_on) {
        lv_obj_add_state(objects.label_warning_icon_lights, LV_STATE_CHECKED);
        lv_obj_add_state(objects.label_warning_text_lights, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.label_warning_icon_lights, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.label_warning_text_lights, LV_STATE_CHECKED);
    }

    if (get_var_pdm01_device07_status() > 0) {
        lv_obj_add_state(objects.label_warning_icon_water, LV_STATE_CHECKED);
        lv_obj_add_state(objects.label_warning_text_water, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.label_warning_icon_water, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.label_warning_text_water, LV_STATE_CHECKED);
    }
}

/* ============================================================================
 * Version
 * ============================================================================ */
#define CURRENT_VERSION "0.2.0"

/* ============================================================================
 * app_main
 * ============================================================================ */
extern void setup_light_buttons(void);

void app_main(void)
{
    /* NVS */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* Hardware init */
    ch422g_init();

    /* SD card config (reads config.env, stores to NVS) */
    bool sd_config_found = sd_config_read();
    ESP_LOGI(TAG, "SD config %s", sd_config_found ? "loaded" : "not found");

    /* Display */
    lcd_init();
    touch_init();
    lvgl_init();

    /* EEZ Studio UI */
    ui_init();
    create_dimming_overlay();
    setup_light_buttons();

    /* Restore user settings */
    restore_user_settings();

    /* Set version label */
    lv_label_set_text(objects.label_version_number, CURRENT_VERSION);

    /* WiFi + MQTT */
    wifi_init();
    bool has_mqtt = mqtt_client_load_settings();

    /* Auto-connect WiFi from NVS credentials */
    wifi_auto_connect();

    /* Set MAC address label */
    uint8_t mac[6] = {0};
    esp_wifi_get_mac(WIFI_IF_STA, mac);
    char mac_str[18];
    snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    set_var_mcu_mac_address(mac_str);

    last_activity_time = (uint32_t)(esp_timer_get_time() / 1000);

    ESP_LOGI(TAG, "Setup complete (MQTT config: %s)", has_mqtt ? "yes" : "no");

    /* Main loop */
    uint32_t warning_check_time = 0;

    while (1) {
        lv_timer_handler();

        /* Process MQTT messages */
        mqtt_client_process_messages();

        /* Persist settings if changed */
        persist_user_settings();

        /* Screen timeout */
        handle_screen_timeout();

        /* Warning indicators (every ~33ms) */
        uint32_t now = (uint32_t)(esp_timer_get_time() / 1000);
        if (now - warning_check_time >= 33) {
            update_warning_indicators();
            warning_check_time = now;
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
