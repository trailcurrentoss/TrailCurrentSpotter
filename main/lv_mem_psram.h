#pragma once

#include <stddef.h>

/*
 * LVGL custom memory allocator — routes lv_mem_alloc / free / realloc to
 * PSRAM via esp_heap_caps. Wired in through:
 *   1. CONFIG_LV_MEM_CUSTOM_INCLUDE="lv_mem_psram.h" in sdkconfig.defaults
 *      → lv_mem.c #includes this header.
 *   2. -DLV_MEM_CUSTOM_ALLOC=spotter_lv_psram_alloc etc. in the project
 *      CMakeLists.txt → overrides LVGL's default malloc/free/realloc.
 *
 * Why: LVGL's widget tree grows the heap by ~200 KB after ui_init() on this
 * project. Stock malloc puts those in internal RAM, fragmenting it down to
 * single-KB free blocks. mbedTLS then can't allocate the contiguous chunks
 * it needs for a TLS handshake. Putting LVGL in the 8 MB PSRAM pool keeps
 * internal RAM mostly free for WiFi/LWIP/mbedTLS.
 *
 * Cost: PSRAM access is ~8x slower per cycle than internal RAM. Widget
 * traversal during draw is the hot path; with a 33 ms refresh budget and
 * mostly idle frames this is acceptable for Spotter. If frame jank becomes
 * visible, switch the high-touch draw buffers to MALLOC_CAP_INTERNAL.
 */

#ifdef __cplusplus
extern "C" {
#endif

void *spotter_lv_psram_alloc(size_t size);
void  spotter_lv_psram_free(void *ptr);
void *spotter_lv_psram_realloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif
