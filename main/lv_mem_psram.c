#include "lv_mem_psram.h"

#include "esp_heap_caps.h"

/* MALLOC_CAP_SPIRAM forces PSRAM; MALLOC_CAP_8BIT means byte-addressable
 * (LVGL needs this for label text, image buffers, etc.). If PSRAM is
 * unavailable for any reason, heap_caps_malloc returns NULL — same failure
 * mode as a regular malloc out-of-memory. */
#define LV_PSRAM_CAPS  (MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT)

void *spotter_lv_psram_alloc(size_t size)
{
    return heap_caps_malloc(size, LV_PSRAM_CAPS);
}

void spotter_lv_psram_free(void *ptr)
{
    /* heap_caps_free handles NULL safely and dispatches to the correct
     * heap based on the pointer's region (internal vs PSRAM). */
    heap_caps_free(ptr);
}

void *spotter_lv_psram_realloc(void *ptr, size_t size)
{
    return heap_caps_realloc(ptr, size, LV_PSRAM_CAPS);
}
