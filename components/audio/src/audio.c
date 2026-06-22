#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "audio.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/i2s_std.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *TAG = "audio";

#define AUDIO_NVS_NS       "audio"
#define AUDIO_NVS_KEY_VOL  "vol"
#define AUDIO_VOLUME_DEFAULT 80

/* I2S pinout per Waveshare ESP32-S3-Touch-LCD-4.3C reference. */
#define I2S_NUM     I2S_NUM_1
#define I2S_MCLK    GPIO_NUM_6
#define I2S_BCLK    GPIO_NUM_44
#define I2S_WS      GPIO_NUM_16
#define I2S_DOUT    GPIO_NUM_15

#define SAMPLE_RATE      16000
#define TONE_HZ          1760
#define TONE_MS          140
#define TONE_AMPLITUDE   12000   /* int16_t — leave headroom */

static i2s_chan_handle_t      s_tx_chan = NULL;
static esp_codec_dev_handle_t s_play_dev = NULL;
static audio_pa_set_fn_t      s_pa_set = NULL;
static bool                   s_started = false;
static bool                   s_inited  = false;

/* Pre-rendered tone burst (stereo, 16-bit). Built once in init. */
static int16_t *s_tone_buf = NULL;
static size_t   s_tone_bytes = 0;

/* The chime runs on its own pinned task — esp_codec_dev_write blocks for the
 * full tone duration (~140 ms) which would stall the LVGL task that drives
 * the pulse animation and touch input. The LVGL-side tick just signals via
 * counting semaphore. */
static TaskHandle_t      s_chime_task = NULL;
static SemaphoreHandle_t s_chime_sem  = NULL;
static volatile bool     s_chime_run  = false;

static uint8_t s_volume_pct = AUDIO_VOLUME_DEFAULT;

static void nvs_load_volume(void)
{
    nvs_handle_t h;
    esp_err_t r = nvs_open(AUDIO_NVS_NS, NVS_READONLY, &h);
    if (r != ESP_OK) return;   /* missing namespace -> keep default */
    uint8_t v = 0;
    if (nvs_get_u8(h, AUDIO_NVS_KEY_VOL, &v) == ESP_OK && v <= 100) {
        s_volume_pct = v;
    }
    nvs_close(h);
}

static void nvs_save_volume(void)
{
    nvs_handle_t h;
    if (nvs_open(AUDIO_NVS_NS, NVS_READWRITE, &h) != ESP_OK) return;
    nvs_set_u8(h, AUDIO_NVS_KEY_VOL, s_volume_pct);
    nvs_commit(h);
    nvs_close(h);
}

static esp_err_t build_tone_buffer(void)
{
    size_t samples = (SAMPLE_RATE * TONE_MS) / 1000;
    s_tone_bytes = samples * 2 * sizeof(int16_t);   /* stereo */
    /* PSRAM — internal RAM is precious (mbedTLS / WiFi static buffers). The
     * I2S DMA copies the tone burst into its own internal buffer at write time,
     * so the source can live in slow PSRAM. */
    s_tone_buf = heap_caps_malloc(s_tone_bytes, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    if (!s_tone_buf) {
        /* Fall back to internal if PSRAM allocation failed. */
        s_tone_buf = heap_caps_malloc(s_tone_bytes, MALLOC_CAP_8BIT);
        if (!s_tone_buf) return ESP_ERR_NO_MEM;
    }

    /* Sine wave with a short raised-cosine attack/decay envelope so the burst
     * doesn't click at the edges. */
    const size_t ramp = samples / 12;
    for (size_t i = 0; i < samples; i++) {
        float t = (float)i / (float)SAMPLE_RATE;
        float w = sinf(2.0f * 3.14159265f * TONE_HZ * t);
        float env = 1.0f;
        if (i < ramp)              env = 0.5f * (1.0f - cosf(3.14159265f * i / ramp));
        else if (i > samples-ramp) env = 0.5f * (1.0f - cosf(3.14159265f * (samples-i) / ramp));
        int16_t v = (int16_t)(w * env * TONE_AMPLITUDE);
        s_tone_buf[i*2]     = v;
        s_tone_buf[i*2 + 1] = v;
    }
    return ESP_OK;
}

static void chime_task(void *arg)
{
    (void)arg;
    for (;;) {
        if (xSemaphoreTake(s_chime_sem, portMAX_DELAY) == pdTRUE) {
            if (s_chime_run && s_play_dev && s_tone_buf) {
                esp_codec_dev_write(s_play_dev, s_tone_buf, s_tone_bytes);
            }
        }
    }
}

esp_err_t spotter_audio_init(i2c_master_bus_handle_t bus, audio_pa_set_fn_t pa_set)
{
    if (s_inited) return ESP_OK;
    if (!bus) return ESP_ERR_INVALID_ARG;
    s_pa_set = pa_set;

    /* Restore saved chime volume (default 80 if not present). */
    nvs_load_volume();

    /* I2S TX channel. */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true;
    ESP_RETURN_ON_ERROR(i2s_new_channel(&chan_cfg, &s_tx_chan, NULL), TAG, "i2s_new_channel");

    i2s_std_config_t std_cfg = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = I2S_MCLK, .bclk = I2S_BCLK, .ws = I2S_WS,
            .dout = I2S_DOUT, .din = GPIO_NUM_NC,
            .invert_flags = { false, false, false },
        },
    };
    ESP_RETURN_ON_ERROR(i2s_channel_init_std_mode(s_tx_chan, &std_cfg), TAG, "i2s_init_std");
    ESP_RETURN_ON_ERROR(i2s_channel_enable(s_tx_chan), TAG, "i2s_enable");

    /* Codec data interface (binds to the I2S TX channel). */
    audio_codec_i2s_cfg_t i2s_cfg = {
        .port = I2S_NUM,
        .tx_handle = s_tx_chan,
        .rx_handle = NULL,
    };
    const audio_codec_data_if_t *data_if = audio_codec_new_i2s_data(&i2s_cfg);
    if (!data_if) { ESP_LOGE(TAG, "audio_codec_new_i2s_data failed"); return ESP_FAIL; }

    /* I2C control interface for the ES8311 on the shared bus. */
    audio_codec_i2c_cfg_t i2c_cfg = {
        .port = 0,
        .addr = ES8311_CODEC_DEFAULT_ADDR,
        .bus_handle = bus,
    };
    const audio_codec_ctrl_if_t *ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
    if (!ctrl_if) { ESP_LOGE(TAG, "audio_codec_new_i2c_ctrl failed"); return ESP_FAIL; }

    const audio_codec_gpio_if_t *gpio_if = audio_codec_new_gpio();

    esp_codec_dev_hw_gain_t gain = { .pa_voltage = 5, .codec_dac_voltage = 3.3 };
    es8311_codec_cfg_t es_cfg = {
        .ctrl_if = ctrl_if,
        .gpio_if = gpio_if,
        .codec_mode = ESP_CODEC_DEV_WORK_MODE_DAC,
        .pa_pin = GPIO_NUM_NC,
        .pa_reverted = false,
        .master_mode = false,
        .use_mclk = true,
        .digital_mic = false,
        .invert_mclk = false,
        .invert_sclk = false,
        .hw_gain = gain,
    };
    const audio_codec_if_t *codec_if = es8311_codec_new(&es_cfg);
    if (!codec_if) { ESP_LOGE(TAG, "es8311_codec_new failed"); return ESP_FAIL; }

    esp_codec_dev_cfg_t dev_cfg = {
        .dev_type = ESP_CODEC_DEV_TYPE_OUT,
        .codec_if = codec_if,
        .data_if  = data_if,
    };
    s_play_dev = esp_codec_dev_new(&dev_cfg);
    if (!s_play_dev) { ESP_LOGE(TAG, "esp_codec_dev_new failed"); return ESP_FAIL; }

    ESP_RETURN_ON_ERROR(build_tone_buffer(), TAG, "build_tone_buffer");

    s_chime_sem = xSemaphoreCreateCounting(8, 0);
    xTaskCreatePinnedToCore(chime_task, "chime", 4096, NULL, 5, &s_chime_task, 0);

    s_inited = true;
    ESP_LOGI(TAG, "ES8311 ready (16 kHz stereo, MCLK=6 BCLK=44 WS=16 DOUT=15) — "
                  "heap internal free=%u largest=%u",
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
             (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
    return ESP_OK;
}

void spotter_audio_chime_start(void)
{
    if (!s_inited || s_started) return;
    if (s_pa_set) s_pa_set(true);
    esp_codec_dev_sample_info_t fs = {
        .sample_rate = SAMPLE_RATE,
        .channel = 2,
        .bits_per_sample = 16,
    };
    esp_codec_dev_open(s_play_dev, &fs);
    esp_codec_dev_set_out_vol(s_play_dev, (int)s_volume_pct);
    s_chime_run = true;
    s_started = true;
}

uint8_t spotter_audio_get_volume(void)
{
    return s_volume_pct;
}

void spotter_audio_set_volume(uint8_t volume_pct)
{
    if (volume_pct > 100) volume_pct = 100;
    if (volume_pct == s_volume_pct) return;
    s_volume_pct = volume_pct;
    /* Apply live if a chime is currently playing. ES8311 accepts 0..100. */
    if (s_inited && s_started && s_play_dev) {
        esp_codec_dev_set_out_vol(s_play_dev, (int)s_volume_pct);
    }
    nvs_save_volume();
}

void spotter_audio_chime_tick(void)
{
    if (!s_inited || !s_started) return;
    xSemaphoreGive(s_chime_sem);
}

void spotter_audio_chime_stop(void)
{
    if (!s_inited || !s_started) return;
    s_chime_run = false;
    /* Drain any pending ticks. */
    while (xSemaphoreTake(s_chime_sem, 0) == pdTRUE) { }
    esp_codec_dev_close(s_play_dev);
    if (s_pa_set) s_pa_set(false);
    s_started = false;
}
