#!/usr/bin/env python3
"""Restructure all three sliders on PageSetup to a two-line layout:

    [name label .................. value]
    [-------- slider full width --------]

And shift everything below the new brightness row down to make room.

Issues this fixes (reported on hardware after deploying the brightness row):

1) setup_info_banner overlaps setup_brightness_row at y~386 because the
   brightness row was inserted without shifting the section below it.
2) The brightness slider's right edge sits in the scrollbar's touch zone
   so the user can't drag it without grabbing the scrollbar — same
   problem (now noticed) on the snooze and volume sliders.

The fix:
- Each slider row grows from h=38 (single line) to h=60 (two lines).
- name moves to row-local (14, 4, 400, 22)
- value moves to row-local (692, 4, 70, 22) — right-aligned at the row's
  right side, well clear of the slider knob below
- slider moves to row-local (14, 34, 720, 18) — full width across the row
  ending at row-local x=734, which is body-x 748, leaving ~42 px before
  the scrollbar's touch zone (body width 800)

Downstream widgets shift down to absorb the +22 height delta on each row
that grows (brightness pushes info_banner down by +72; snooze growing by
+22 pushes audio_title further; volume growing by +22 pushes reset_*
further still).
"""

import json
import shutil
import sys
import time

PROJ = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter/GUI/TrailCurrentSpotter.eez-project"

# Final on-page layout under setup_body (body-local y):
#   theme buttons (unchanged) end at y=370
#   y=384 h=60  brightness_row    (h was 38, now 60 — children stacked)
#   y=458 h=40  info_banner       (was y=386)
#   y=518 h=18  alarm_timing_title (was y=446)
#   y=546 h=60  snooze_row        (was y=470 h=38 — restacked)
#   y=626 h=18  audio_title       (was y=518)
#   y=654 h=60  volume_row        (was y=542 h=38 — restacked)
#   y=734 h=18  reset_conn_title  (was y=600)
#   y=762 h=56  reset_conn_btn    (was y=624)

# Y/height changes on widgets inside setup_body. Format:
#   identifier -> (expected_old_top, new_top, expected_old_height_or_None, new_height_or_None)
# height_or_None: None means don't change the height.
SETUP_BODY_CHANGES = [
    ("setup_brightness_row",     384, 384,   38,  60),  # height grows
    ("setup_info_banner",        386, 458, None,None),
    ("setup_alarm_timing_title", 446, 518, None,None),
    ("setup_alarm_snooze_row",   470, 546,   38,  60),  # height grows
    ("setup_audio_title",        518, 626, None,None),
    ("setup_volume_row",         542, 654,   38,  60),  # height grows
    ("setup_reset_conn_title",   600, 734, None,None),
    ("setup_reset_conn_btn",     624, 762, None,None),
]

# Reshape children inside each slider row (row-local coords). Same layout
# applied to all three rows for visual consistency.
ROW_NAME   = (14,   4, 400, 22)
ROW_VALUE  = (692,  4,  70, 22)
ROW_SLIDER = (14,  34, 720, 18)

SLIDER_ROWS = [
    # (row identifier, name child, value child, slider child)
    ("setup_brightness_row",    "setup_brightness_name",    "setup_brightness_value",    "setup_brightness_slider"),
    ("setup_alarm_snooze_row",  "setup_alarm_snooze_name",  "setup_alarm_snooze_value",  "setup_alarm_snooze_slider"),
    ("setup_volume_row",        "setup_volume_name",        "setup_volume_value",        "setup_volume_slider"),
]


def find_node(root, ident):
    if isinstance(root, dict):
        if root.get("identifier") == ident:
            return root
        for v in root.values():
            r = find_node(v, ident)
            if r is not None:
                return r
    elif isinstance(root, list):
        for x in root:
            r = find_node(x, ident)
            if r is not None:
                return r
    return None


def find_page(proj, name):
    for p in proj["userPages"]:
        if p.get("name") == name:
            return p
    raise KeyError(name)


def apply_pos(node, l=None, t=None, w=None, h=None):
    if l is not None: node["left"]   = l
    if t is not None: node["top"]    = t
    if w is not None: node["width"]  = w
    if h is not None: node["height"] = h


def main():
    ts = time.strftime("%Y%m%d-%H%M%S")
    backup = PROJ + ".bak." + ts
    shutil.copyfile(PROJ, backup)
    print(f"backup: {backup}")

    with open(PROJ, "r") as f:
        proj = json.load(f)

    page = find_page(proj, "PageSetup")

    # 1) Apply y/height changes for widgets directly inside setup_body
    for ident, old_top, new_top, old_h, new_h in SETUP_BODY_CHANGES:
        node = find_node(page, ident)
        if node is None:
            print(f"WARN: {ident} not found, skipping", file=sys.stderr)
            continue
        cur_top = node.get("top")
        cur_h   = node.get("height")
        # Idempotency: if already at new state, skip silently
        if cur_top == new_top and (new_h is None or cur_h == new_h):
            print(f"already-applied: {ident} (top={new_top}, h={cur_h})")
            continue
        # Only mutate if at expected old state (avoid clobbering manual edits)
        if cur_top != old_top:
            print(f"WARN: {ident} top={cur_top}, expected {old_top}; leaving alone",
                  file=sys.stderr)
            continue
        if old_h is not None and cur_h != old_h:
            print(f"WARN: {ident} height={cur_h}, expected {old_h}; leaving alone",
                  file=sys.stderr)
            continue
        apply_pos(node, t=new_top, h=new_h)
        print(f"shifted: {ident}  top {old_top}->{new_top}"
              + (f"  height {old_h}->{new_h}" if new_h is not None else ""))

    # 2) Restack children inside each slider row
    for row_ident, name_ident, value_ident, slider_ident in SLIDER_ROWS:
        row = find_node(page, row_ident)
        if row is None:
            print(f"ERROR: {row_ident} not found", file=sys.stderr)
            sys.exit(1)
        for child_ident, dims in [
            (name_ident,   ROW_NAME),
            (value_ident,  ROW_VALUE),
            (slider_ident, ROW_SLIDER),
        ]:
            node = find_node(row, child_ident)
            if node is None:
                print(f"ERROR: {child_ident} not found inside {row_ident}", file=sys.stderr)
                sys.exit(1)
            l, t, w, h = dims
            before = (node.get("left"), node.get("top"), node.get("width"), node.get("height"))
            apply_pos(node, l=l, t=t, w=w, h=h)
            print(f"restacked: {child_ident} {before} -> ({l}, {t}, {w}, {h})")

    with open(PROJ, "w") as f:
        json.dump(proj, f, indent=2)
        f.write("\n")
    print(f"wrote {PROJ}")


if __name__ == "__main__":
    main()
