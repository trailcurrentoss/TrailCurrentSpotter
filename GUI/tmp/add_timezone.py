#!/usr/bin/env python3
"""
Insert a Time Zone section into PageSetup:
  - Section title "TIME ZONE" at top=454, after Brightness
  - Dropdown widget with 7 US timezone options at top=482
  - Action "TimezoneChange" added to the project's actions list
  - Shift down setup_alarm_timing_title, setup_alarm_snooze_row,
    setup_audio_title, setup_volume_row, setup_reset_conn_title,
    setup_reset_conn_btn by 96 px to make room.
"""
import json, sys, uuid, shutil
from pathlib import Path

PROJECT = Path(
    "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter/GUI/"
    "TrailCurrentSpotter.eez-project"
)

SHIFT = 96  # px (title 18 + gap 8 + dropdown ~50 + gap 20)
SHIFTED_IDENTIFIERS = {
    "setup_alarm_timing_title",
    "setup_alarm_snooze_row",
    "setup_audio_title",
    "setup_volume_row",
    "setup_reset_conn_title",
    "setup_reset_conn_btn",
}

def uid():
    return str(uuid.uuid4())

with PROJECT.open() as fp:
    doc = json.load(fp)

# --- 1. Add action 'TimezoneChange' if missing ----------------------------
actions = doc.get("actions", [])
if not any(a.get("name") == "TimezoneChange" for a in actions):
    actions.append({
        "objID": uid(),
        "components": [],
        "connectionLines": [],
        "localVariables": [],
        "userProperties": [],
        "name": "TimezoneChange",
    })
    print("Added action TimezoneChange")
else:
    print("Action TimezoneChange already exists")

# --- 2. Find PageSetup and its setup_body panel ---------------------------
def find_pageSetup(pages):
    for p in pages:
        if p.get("name") == "PageSetup":
            return p
    raise SystemExit("PageSetup not found")

def find_by_identifier(node, ident):
    if isinstance(node, dict):
        if node.get("identifier") == ident:
            return node
        for v in node.values():
            r = find_by_identifier(v, ident)
            if r is not None:
                return r
    elif isinstance(node, list):
        for v in node:
            r = find_by_identifier(v, ident)
            if r is not None:
                return r
    return None

page = find_pageSetup(doc["userPages"])
setup_body = find_by_identifier(page, "setup_body")
if setup_body is None:
    raise SystemExit("setup_body not found in PageSetup")

# --- 3. Shift down later sections to make room ---------------------------
children = setup_body["children"]
shifted_count = 0
for child in children:
    ident = child.get("identifier")
    if ident in SHIFTED_IDENTIFIERS:
        before = child["top"]
        # Only shift if not already shifted
        if before < 600 or ident == "setup_alarm_timing_title" and before == 614:
            pass  # already shifted check below
        # idempotency: shift only if current top matches original
        original = {
            "setup_alarm_timing_title": 518,
            "setup_alarm_snooze_row":   546,
            "setup_audio_title":        626,
            "setup_volume_row":         654,
            "setup_reset_conn_title":   734,
            "setup_reset_conn_btn":     762,
        }
        if before == original[ident]:
            child["top"] = before + SHIFT
            shifted_count += 1
            print(f"  shifted {ident}: {before} -> {child['top']}")
        else:
            print(f"  {ident} already at {before}, skipping")

# --- 4. Skip insert if timezone section already there --------------------
if any(c.get("identifier") == "setup_timezone_title" for c in children):
    print("setup_timezone_title already present, skipping widget insert")
else:
    title = {
        "objID": uid(),
        "type": "LVGLLabelWidget",
        "left": 14, "top": 454, "width": 772, "height": 18,
        "customInputs": [], "customOutputs": [],
        "style": {
            "objID": uid(), "useStyle": "default",
            "conditionalStyles": [], "childStyles": [],
        },
        "timeline": [], "eventHandlers": [],
        "identifier": "setup_timezone_title",
        "leftUnit": "px", "topUnit": "px",
        "widthUnit": "px", "heightUnit": "px",
        "children": [],
        "widgetFlags": ("CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|"
                        "SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|"
                        "SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|"
                        "SNAPPABLE"),
        "hiddenFlagType": "literal",
        "clickableFlag": True,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "", "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal", "disabledStateType": "literal",
        "states": "",
        "useStyle": "LabelDefault",
        "localStyles": {
            "objID": uid(),
            "definition": {
                "MAIN": {
                    "DEFAULT": {
                        "text_color": "AccentColor",
                        "text_font": "MONTSERRAT_16",
                    }
                }
            },
        },
        "group": "", "groupIndex": 0,
        "text": "TIME ZONE",
        "textType": "literal",
        "longMode": "WRAP",
        "recolor": False,
    }

    dropdown = {
        "objID": uid(),
        "type": "LVGLDropdownWidget",
        "left": 14, "top": 482, "width": 772, "height": 50,
        "customInputs": [], "customOutputs": [],
        "style": {
            "objID": uid(), "useStyle": "default",
            "conditionalStyles": [], "childStyles": [],
        },
        "timeline": [],
        "eventHandlers": [
            {
                "objID": uid(),
                "eventName": "VALUE_CHANGED",
                "handlerType": "action",
                "action": "TimezoneChange",
                "userData": 0,
            }
        ],
        "identifier": "setup_timezone_dropdown",
        "leftUnit": "px", "topUnit": "px",
        "widthUnit": "px", "heightUnit": "px",
        "children": [],
        "widgetFlags": ("CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLLABLE|"
                        "SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|"
                        "SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|"
                        "SNAPPABLE"),
        "hiddenFlagType": "literal",
        "clickableFlag": True,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "", "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal", "disabledStateType": "literal",
        "states": "",
        "localStyles": {"objID": uid()},
        "group": "", "groupIndex": 0,
        "options": ("Alaska\nChicago, Illinois\nDenver, Colorado\nHawaii\n"
                    "Los Angeles\nNew York\nPhoenix"),
        "optionsType": "literal",
        "selected": 5,             # default index: New York
        "selectedType": "literal",
        "direction": "top",        # opens upward so popup doesn't overflow
    }

    children.append(title)
    children.append(dropdown)
    print("Inserted setup_timezone_title and setup_timezone_dropdown")

# Backup and write back
backup = PROJECT.with_suffix(PROJECT.suffix + ".bak.tz_pre")
if not backup.exists():
    shutil.copy(PROJECT, backup)
    print(f"Wrote backup: {backup}")

with PROJECT.open("w") as fp:
    json.dump(doc, fp, indent=2, ensure_ascii=False)
    fp.write("\n")
print(f"Updated: {PROJECT}  (shifted {shifted_count} rows)")
