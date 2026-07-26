#pragma once

/* Widget-write guards — skip the LVGL call when the new value matches the
 * current one. LVGL 8's setters unconditionally invalidate the widget and
 * (for labels) reallocate the text buffer, so under a fast MQTT stream a
 * long tail of "same value again" updates churns PSRAM and inflates the
 * per-frame dirty region. Both effects widen the visible tear window and
 * fragment the heap, eventually starving LVGL of a contiguous block for
 * arc-mask allocations. Guarding at the setter side is O(1) and touches
 * only the call site — no LVGL patches. */

#include "lvgl.h"
#include <string.h>

static inline void label_set_text_if_changed(lv_obj_t *label, const char *text)
{
    if (!label || !text) return;
    const char *cur = lv_label_get_text(label);
    if (cur && strcmp(cur, text) == 0) return;
    lv_label_set_text(label, text);
}

static inline void arc_set_value_if_changed(lv_obj_t *arc, int16_t value)
{
    if (!arc) return;
    if (lv_arc_get_value(arc) == value) return;
    lv_arc_set_value(arc, value);
}

static inline void state_set_if_changed(lv_obj_t *obj, lv_state_t st, bool on)
{
    if (!obj) return;
    bool cur = lv_obj_has_state(obj, st);
    if (cur == on) return;
    if (on) lv_obj_add_state(obj, st);
    else    lv_obj_clear_state(obj, st);
}
