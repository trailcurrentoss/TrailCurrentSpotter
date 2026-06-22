idf_component_register(
    SRCS "src/audio.c"
    INCLUDE_DIRS "include"
    REQUIRES driver esp_driver_i2c esp_driver_i2s esp_codec_dev nvs_flash
)
