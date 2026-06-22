#!/usr/bin/env python3
"""Add Roboto Mono font (sizes 18/32/36/48), create LabelDataValue{18,32,36,48}
styles, and apply them to gauge value labels on PageDrive. Centers each
value+unit pair within its parent panel. User validates in EEZ Studio."""

import hashlib, json, os, shutil, sys, time

PROJ = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter/GUI/TrailCurrentSpotter.eez-project"

# ---- digit-width budget per size (PIL-measured on RobotoMono-Medium.ttf) ----
# Each row: (size, worst_case_value_text, slack -> total value-box width)
VALUE_BOX_W = {18: 47, 32: 62, 36: 70, 48: 90}

_seq = [0]
def oid(tag):
    _seq[0] += 1
    h = hashlib.md5(f"robotomono:{tag}:{_seq[0]}".encode()).hexdigest()
    return f"{h[:8]}-{h[8:12]}-{h[12:16]}-{h[16:20]}-{h[20:32]}"

# ---- font entry builder (mirrors fa16/fa32 shape) ----
def build_font_entry(name, size):
    return {
        "objID": oid(f"font:{name}"),
        "name": name,
        "renderingEngine": "LVGL",
        "source": {
            "objID": oid(f"font-src:{name}"),
            "filePath": "../ASSETS/RobotoMono-Medium.ttf",
            "size": size,
        },
        "embeddedFontFile": "",
        "bpp": 4,
        "threshold": 128,
        "glyphs": [],
        "lvglRanges": "0x20,0x2D,0x2E,0x30-0x39",
        "lvglSymbols": "",
        "lvglGlyphs": {"objID": oid(f"font-glyphs:{name}"), "encodings": []},
    }

# ---- style builder (mirrors LabelDefault but with Roboto Mono text_font) ----
def build_data_value_style(size):
    return {
        "objID": oid(f"style:LabelDataValue{size}"),
        "name": f"LabelDataValue{size}",
        "forWidgetType": "LVGLLabelWidget",
        "childStyles": [],
        "definition": {
            "objID": oid(f"style-def:LabelDataValue{size}"),
            "definition": {
                "MAIN": {
                    "DEFAULT": {
                        "text_color": "PrimaryTextColor",
                        "text_font": f"roboto_mono_{size}",
                    },
                },
            },
        },
    }

# ---- tree helpers ----
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

def find_parent_of(root, ident):
    if isinstance(root, dict):
        for v in root.values():
            if isinstance(v, list):
                for c in v:
                    if isinstance(c, dict) and c.get("identifier") == ident:
                        return root, v
            r = find_parent_of(v, ident)
            if r is not None:
                return r
    elif isinstance(root, list):
        for x in root:
            r = find_parent_of(x, ident)
            if r is not None:
                return r
    return None

def set_local_style(node, **props):
    """Set MAIN/DEFAULT properties in localStyles, preserving objIDs."""
    ls = node.setdefault("localStyles", {})
    if "objID" not in ls:
        ls["objID"] = oid("ls")
    defn = ls.setdefault("definition", {})
    main = defn.setdefault("MAIN", {})
    dflt = main.setdefault("DEFAULT", {})
    for k, v in props.items():
        if v is None:
            dflt.pop(k, None)
        else:
            dflt[k] = v
    return node

def apply_data_value(node, size, left, top, width, height, text_align="CENTER"):
    """Convert a label to data-value styling: LabelDataValue<size> + geometry."""
    node["useStyle"] = f"LabelDataValue{size}"
    node["left"] = left
    node["top"] = top
    node["width"] = width
    node["height"] = height
    # Drop text_font override — the style now provides it.
    ls = node.get("localStyles", {})
    if isinstance(ls, dict):
        defn = ls.get("definition", {})
        main = defn.get("MAIN", {}) if isinstance(defn, dict) else {}
        dflt = main.get("DEFAULT", {}) if isinstance(main, dict) else {}
        dflt.pop("text_font", None)
        if text_align:
            dflt["text_align"] = text_align

def build_label(ident, text, useStyle, left, top, width, height, text_align="LEFT",
                text_font=None):
    """Build a fresh LVGLLabelWidget mirroring the project's existing shape."""
    ls_props = {"text_align": text_align}
    if text_font:
        ls_props["text_font"] = text_font
    node = {
        "objID": oid(f"label:{ident}"),
        "type": "LVGLLabelWidget",
        "left": left, "top": top, "width": width, "height": height,
        "customInputs": [], "customOutputs": [],
        "style": {
            "objID": oid(f"label-style:{ident}"),
            "useStyle": "default",
            "conditionalStyles": [], "childStyles": [],
        },
        "timeline": [], "eventHandlers": [],
        "identifier": ident,
        "leftUnit": "px", "topUnit": "px", "widthUnit": "px", "heightUnit": "px",
        "widgetFlags": "CLICK_FOCUSABLE|GESTURE_BUBBLE|PRESS_LOCK|SCROLL_CHAIN_HOR|SCROLL_CHAIN_VER|SCROLL_ELASTIC|SCROLL_MOMENTUM|SCROLL_ON_FOCUS|SCROLL_WITH_ARROW|SNAPPABLE",
        "hiddenFlagType": "literal",
        "clickableFlag": False,
        "clickableFlagType": "literal",
        "flagScrollbarMode": "", "flagScrollDirection": "",
        "scrollSnapX": "", "scrollSnapY": "",
        "checkedStateType": "literal",
        "disabledStateType": "literal",
        "states": "",
        "useStyle": useStyle,
        "localStyles": {
            "objID": oid(f"label-ls:{ident}"),
            "definition": {"MAIN": {"DEFAULT": ls_props}},
        },
        "group": "", "groupIndex": 0,
        "text": text,
        "textType": "literal",
        "longMode": "WRAP",
        "recolor": False,
    }
    return node


def main():
    ts = time.strftime("%Y%m%d-%H%M%S")
    shutil.copyfile(PROJ, f"{PROJ}.bak.{ts}")
    print(f"backup: {PROJ}.bak.{ts}")

    with open(PROJ) as f:
        proj = json.load(f)

    # ---- 1. Add Roboto Mono fonts (idempotent) ----
    existing_fonts = {f["name"] for f in proj["fonts"]}
    added_fonts = []
    for sz in (18, 32, 36, 48):
        name = f"roboto_mono_{sz}"
        if name not in existing_fonts:
            proj["fonts"].append(build_font_entry(name, sz))
            added_fonts.append(name)
    print(f"fonts added: {added_fonts}")

    # ---- 2. Add per-size LabelDataValue styles (idempotent) ----
    styles = proj["lvglStyles"]["styles"]
    existing_styles = {s["name"] for s in styles}
    added_styles = []
    for sz in (18, 32, 36, 48):
        name = f"LabelDataValue{sz}"
        if name not in existing_styles:
            styles.append(build_data_value_style(sz))
            added_styles.append(name)
    print(f"styles added: {added_styles}")

    # ---- 3. Apply to gauge value labels on PageDrive ----
    drive = find_page(proj, "PageDrive")

    # 3a. Battery percent — drive_card_bat (256×280)
    #   pair = [90 RIGHT value][4 gap][24 LEFT "%"] = 118 px wide
    #   pair_x = (256 - 118) // 2 = 69
    bat_value = find_node(drive, "drive_bat_value")
    bat_pct = find_node(drive, "drive_bat_pct_sym")
    if bat_value and bat_pct:
        apply_data_value(bat_value, 48, left=69, top=103, width=90, height=60,
                         text_align="RIGHT")
        # Unit: keep Montserrat 22 (LabelDefault + localStyles font),
        #       reposition + size to its planned 24 px box, LEFT aligned.
        bat_pct["left"] = 69 + 90 + 4   # = 163
        bat_pct["top"] = 115
        bat_pct["width"] = 24
        bat_pct["height"] = 28
        set_local_style(bat_pct, text_align="LEFT")

    # 3b. Solar wattage — drive_card_solar (256×280)
    #   pair = [70 RIGHT value][4 gap][30 LEFT "W"] = 104 → pair_x = (256-104)//2 = 76
    solar_value = find_node(drive, "drive_solar_value")
    solar_unit = find_node(drive, "drive_solar_unit_sym")
    if solar_value and solar_unit:
        apply_data_value(solar_value, 36, left=76, top=115, width=70, height=50,
                         text_align="RIGHT")
        solar_unit["left"] = 76 + 70 + 4   # = 150
        solar_unit["top"] = 127
        solar_unit["width"] = 30
        solar_unit["height"] = 24
        set_local_style(solar_unit, text_align="LEFT")

    # 3c. Tire PSI — six panels (110×66), value alone, no unit pair
    #   keep at full panel width, centered text
    for psi_id in ("drive_tire_l1_psi", "drive_tire_r1_psi",
                   "drive_tire_l2_psi", "drive_tire_r2_psi",
                   "drive_tire_l3_psi", "drive_tire_r3_psi"):
        psi = find_node(drive, psi_id)
        if psi:
            apply_data_value(psi, 32, left=0, top=6, width=110, height=38,
                             text_align="CENTER")

    # 3d. Battery volts — split into value + unit
    #   pair = [47 RIGHT value][3 gap][17 LEFT "V"] = 67 → pair_x = (256-67)//2 = 94
    bat_volts = find_node(drive, "drive_bat_volts")
    if bat_volts:
        apply_data_value(bat_volts, 18, left=94, top=163, width=47, height=22,
                         text_align="RIGHT")
        # Reset placeholder so it doesn't still show " V"
        bat_volts["text"] = "--"

        # Add sibling unit label "V" if it doesn't already exist.
        bat_card = find_node(drive, "drive_card_bat")
        if bat_card and find_node(bat_card, "drive_bat_volts_unit") is None:
            unit_node = build_label(
                ident="drive_bat_volts_unit",
                text="V",
                useStyle="LabelDefault",
                left=94 + 47 + 3,   # = 144
                top=163,
                width=17, height=22,
                text_align="LEFT",
                text_font="MONTSERRAT_18",
            )
            bat_card["children"].append(unit_node)
            print("added widget: drive_bat_volts_unit")

    # ---- 4. Write back ----
    with open(PROJ, "w") as f:
        json.dump(proj, f, indent=2)
        f.write("\n")

    print(f"wrote: {PROJ}")
    print(f"font count: {len(proj['fonts'])}")
    print(f"style count: {len(proj['lvglStyles']['styles'])}")


if __name__ == "__main__":
    main()
