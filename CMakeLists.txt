cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(trailcurrent_spotter)

# Route LVGL's heap allocations to PSRAM instead of internal RAM. The LVGL
# component checks LV_MEM_CUSTOM_ALLOC/FREE/REALLOC via #ifndef before
# defaulting to malloc/free/realloc, so a project-wide -D wins. The
# CONFIG_LV_MEM_CUSTOM_INCLUDE in sdkconfig.defaults makes lv_mem.c #include
# our wrapper header (declares the three functions). Body lives in
# main/lv_mem_psram.c. See that file's header comment for rationale.
# Use idf_build_set_property — ESP-IDF's component build system scopes
# add_compile_definitions to the top-level target only; component builds
# (including lvgl__lvgl) won't see it. idf_build_set_property propagates to
# every component compilation.
idf_build_set_property(COMPILE_DEFINITIONS "-DLV_MEM_CUSTOM_ALLOC=spotter_lv_psram_alloc" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DLV_MEM_CUSTOM_FREE=spotter_lv_psram_free" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DLV_MEM_CUSTOM_REALLOC=spotter_lv_psram_realloc" APPEND)
# Make main/ visible to every component compilation so lvgl can find
# lv_mem_psram.h regardless of REQUIRES.
idf_build_set_property(COMPILE_OPTIONS "-I${CMAKE_SOURCE_DIR}/main" APPEND)

