#!/usr/bin/env python3
"""Add a backlight-brightness row to PageSetup's DISPLAY section.

Mirrors the existing setup_volume_row layout exactly (same row shape, same
label/value/slider sizing, same per-side pad zeroing, same StyleDefaultSlider).
Adds the BrightnessChanged action declaration if missing, then inserts the
new widgets into setup_body alongside the existing volume row.

Edits the .eez-project file directly. The user then reloads EEZ Studio,
visually validates the new widgets render correctly in the canvas, and
exports via Ctrl+B.
"""

import json
import os
import hashlib
import shutil
import sys
import time

PROJ = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter/GUI/TrailCurrentSpotter.eez-project"

_seq = [0]
def oid(tag):
    _seq[0] += 1
    h = hashlib.md5(f"brightness:{tag}:{_seq[0]}".encode()).hexdigest()
    return f"{h[:8]}-{h[8:12]}-{h[12:16]}-{h[16:20]}-{h[20:32]}"


def build_brightness_name():
    return {
        "objID": oid("br_name"),
        "type": "LVGLLabelWidget",
        "left": 14, "top": 8, "width": 350, "height": 22,
        "customInputs": [], "customOutputs": [],
        "style": {"objID": oid("brn_s"), "useStyle": "default",
                  "conditionalStyles": [], "childStyles": []},
        "timeline": [], "eventHandlers": [],
        "identifier": "setup_brightness_name",
        "leftUnit": "px", "topUnit": "px", "widthUnit": "px", "heightUnit": "px",
        "children": [],
        "widgetFlags": "CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|SNAPPABLE",
        "hiddenFlagType": "literal",
        "clickableFlag": False,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "",
        "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal",
        "disabledStateType": "literal",
        "states": "",
        "useStyle": "LabelDefault",
        "localStyles": {"objID": oid("brn_ls")},
        "group": "", "groupIndex": 0,
        "text": "Backlight Brightness",
        "textType": "literal",
        "longMode": "WRAP",
        "recolor": False
    }


def build_brightness_value():
    return {
        "objID": oid("br_value"),
        "type": "LVGLLabelWidget",
        "left": 370, "top": 8, "width": 80, "height": 22,
        "customInputs": [], "customOutputs": [],
        "style": {"objID": oid("brv_s"), "useStyle": "default",
                  "conditionalStyles": [], "childStyles": []},
        "timeline": [], "eventHandlers": [],
        "identifier": "setup_brightness_value",
        "leftUnit": "px", "topUnit": "px", "widthUnit": "px", "heightUnit": "px",
        "children": [],
        "widgetFlags": "CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|SNAPPABLE",
        "hiddenFlagType": "literal",
        "clickableFlag": False,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "",
        "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal",
        "disabledStateType": "literal",
        "states": "",
        "useStyle": "LabelSecondary",
        "localStyles": {
            "objID": oid("brv_ls"),
            "definition": {
                "MAIN": {
                    "DEFAULT": {
                        "text_align": "RIGHT"
                    }
                }
            }
        },
        "group": "", "groupIndex": 0,
        "text": "80%",
        "textType": "literal",
        "longMode": "WRAP",
        "recolor": False
    }


def build_brightness_slider():
    return {
        "objID": oid("br_slider"),
        "type": "LVGLSliderWidget",
        "left": 460, "top": 14, "width": 300, "height": 18,
        "customInputs": [], "customOutputs": [],
        "style": {"objID": oid("brs_s"), "useStyle": "default",
                  "conditionalStyles": [], "childStyles": []},
        "timeline": [],
        "eventHandlers": [
            {
                "objID": oid("brs_eh"),
                "eventName": "VALUE_CHANGED",
                "handlerType": "action",
                "action": "BrightnessChanged",
                "userData": 0
            }
        ],
        "identifier": "setup_brightness_slider",
        "leftUnit": "px", "topUnit": "px", "widthUnit": "px", "heightUnit": "px",
        "children": [],
        "widgetFlags": "CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|SNAPPABLE",
        "hiddenFlagType": "literal",
        "clickableFlag": True,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "",
        "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal",
        "disabledStateType": "literal",
        "states": "",
        "useStyle": "StyleDefaultSlider",
        "localStyles": {"objID": oid("brs_ls")},
        "group": "", "groupIndex": 0,
        "min": 10,
        "minType": "literal",
        "max": 100,
        "maxType": "literal",
        "mode": "NORMAL",
        "value": 80,
        "valueType": "literal",
        "previewValue": 0,
        "valueLeft": 0,
        "valueLeftType": "literal",
        "previewValueLeft": 0,
        "enableAnimation": False
    }


def build_brightness_row():
    """The brightness row sits inside the DISPLAY section, directly under
    the theme light/dark buttons (which end at y=370). top=384 keeps a
    14px gap below the buttons and a 14px gap above the existing
    setup_alarm_timing_title at y=446."""
    return {
        "objID": oid("br_row"),
        "type": "LVGLPanelWidget",
        "left": 14, "top": 384, "width": 772, "height": 38,
        "customInputs": [], "customOutputs": [],
        "style": {"objID": oid("brr_s"), "useStyle": "default",
                  "conditionalStyles": [], "childStyles": []},
        "timeline": [], "eventHandlers": [],
        "identifier": "setup_brightness_row",
        "leftUnit": "px", "topUnit": "px", "widthUnit": "px", "heightUnit": "px",
        "children": [
            build_brightness_name(),
            build_brightness_value(),
            build_brightness_slider(),
        ],
        "widgetFlags": "CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|SNAPPABLE",
        "hiddenFlagType": "literal",
        "clickableFlag": False,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "",
        "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal",
        "disabledStateType": "literal",
        "states": "",
        "useStyle": "StylePanelDefault",
        "localStyles": {
            "objID": oid("brr_ls"),
            "definition": {
                "MAIN": {
                    "DEFAULT": {
                        "bg_opa": 0,
                        "border_width": 0,
                        "pad_top": 0,
                        "pad_bottom": 0,
                        "pad_left": 0,
                        "pad_right": 0
                    }
                }
            }
        },
        "group": "", "groupIndex": 0
    }


def find_page(proj, name):
    for p in proj["userPages"]:
        if p.get("name") == name:
            return p
    raise KeyError(name)


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


def main():
    # Backup before any mutation
    ts = time.strftime("%Y%m%d-%H%M%S")
    backup = PROJ + ".bak." + ts
    shutil.copyfile(PROJ, backup)
    print(f"backup: {backup}")

    with open(PROJ, "r") as f:
        proj = json.load(f)

    # 1) Add BrightnessChanged action declaration if missing
    actions = proj.get("actions", [])
    if not any(a.get("name") == "BrightnessChanged" for a in actions):
        actions.append({
            "objID": oid("act_brightness"),
            "components": [],
            "connectionLines": [],
            "localVariables": [],
            "userProperties": [],
            "name": "BrightnessChanged",
        })
        proj["actions"] = actions
        print("added action: BrightnessChanged")
    else:
        print("action BrightnessChanged already exists; skipping")

    # 2) Locate setup_body inside PageSetup
    page = find_page(proj, "PageSetup")
    setup_body = find_node(page, "setup_body")
    if setup_body is None:
        print("ERROR: could not find setup_body inside PageSetup", file=sys.stderr)
        sys.exit(1)

    # 3) Idempotency: only add if not present
    if find_node(setup_body, "setup_brightness_slider") is not None:
        print("setup_brightness_slider already present; skipping widget add")
    else:
        setup_body["children"].append(build_brightness_row())
        print("added widget: setup_brightness_row "
              "(setup_brightness_name, setup_brightness_value, setup_brightness_slider)")

    # 4) Write back with EEZ Studio's conventions (2-space indent, trailing LF)
    with open(PROJ, "w") as f:
        json.dump(proj, f, indent=2)
        f.write("\n")
    print(f"wrote {PROJ}")


if __name__ == "__main__":
    main()
