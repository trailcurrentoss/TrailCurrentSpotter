idf_component_register(
    SRCS
        "main.c"
        "actions.c"
        "vars.c"
        "app_state.c"
        "spoor_alarms.c"
        "connectivity_alarm.c"
        "lv_mem_psram.c"
        "ui/ui.c"
        "ui/screens.c"
        "ui/styles.c"
        "ui/images.c"
        "ui/ui_font_fa16.c"
        "ui/ui_font_fa32.c"
        "ui/ui_image_trailer_back.c"
        "ui/ui_image_trailer_side.c"
    INCLUDE_DIRS
        "."
        "ui"
    REQUIRES
        driver
        esp_lcd
        esp_timer
        nvs_flash
        esp_wifi
        esp_netif
        esp_event
        mqtt_client
        sd_config
        wifi_setup
        pendant_config
        audio
    # WHOLE_ARCHIVE makes libmain.a fully included in the final link so the
    # spotter_lv_psram_* allocator symbols (referenced by lvgl__lvgl's
    # lv_mem.c via the -DLV_MEM_CUSTOM_ALLOC redirects in the top-level
    # CMakeLists.txt) are resolvable when lvgl's archive is processed.
    WHOLE_ARCHIVE
)
