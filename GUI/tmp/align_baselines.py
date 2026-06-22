#!/usr/bin/env python3
"""Re-baseline-align every multi-label horizontal grouping in the project.

Computes each label's `top` from:
  - the font's current LVGL line metrics (line_height, base_line)
  - the parent panel's height
  - a chosen baseline anchor for the group (typically the largest label,
    placed so its cap-height is visually centered in the parent's row zone)

No values are derived from previous `top` positions — every position is
recomputed from current state. User validates in EEZ Studio.
"""

import glob, hashlib, json, os, re, shutil, sys, time

ROOT = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter"
PROJ = f"{ROOT}/GUI/TrailCurrentSpotter.eez-project"
LVGL_FONT_DIR = (
    "/home/dave/.cache/Espressif/ComponentManager/"
    "service_d92d8f1e/lvgl__lvgl_8.4.0_d7c1ac03/src/font"
)

# ---- 1. Resolve true LVGL line metrics for every font we use ----
def read_metrics(path):
    txt = open(path).read()
    lh = int(re.search(r"\.line_height\s*=\s*(\d+)", txt).group(1))
    bl = int(re.search(r"\.base_line\s*=\s*(\d+)", txt).group(1))
    return {"line_height": lh, "base_line": bl, "ascent": lh - bl}

FONTS = {}
# Roboto Mono — generated under main/ui/
for p in sorted(glob.glob(f"{ROOT}/main/ui/ui_font_roboto_mono_*.c")):
    sz = int(re.search(r"_(\d+)\.c$", p).group(1))
    FONTS[f"roboto_mono_{sz}"] = read_metrics(p)
# FontAwesome — generated under main/ui/
for p in sorted(glob.glob(f"{ROOT}/main/ui/ui_font_fa*.c")):
    name = re.search(r"ui_font_(fa\d+)\.c$", p).group(1)
    FONTS[name] = read_metrics(p)
# Montserrat — LVGL built-ins
for sz in (8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48):
    p = f"{LVGL_FONT_DIR}/lv_font_montserrat_{sz}.c"
    if os.path.exists(p):
        FONTS[f"MONTSERRAT_{sz}"] = read_metrics(p)

print("Font metrics (line_height / base_line / ascent):")
for k, v in FONTS.items():
    print(f"  {k:24s} lh={v['line_height']:3d}  bl={v['base_line']}  asc={v['ascent']:3d}")

# ---- 2. Load project + helpers ----
with open(PROJ) as f:
    proj = json.load(f)

ts = time.strftime("%Y%m%d-%H%M%S")
shutil.copyfile(PROJ, f"{PROJ}.bak.{ts}")
print(f"\nbackup: {PROJ}.bak.{ts}")

def find_in(root, ident):
    if isinstance(root, dict):
        if root.get("identifier") == ident:
            return root
        for v in root.values():
            r = find_in(v, ident)
            if r is not None:
                return r
    elif isinstance(root, list):
        for x in root:
            r = find_in(x, ident)
            if r is not None:
                return r
    return None

# Build a style index for resolving useStyle text_font
STYLE_BY_NAME = {s["name"]: s for s in proj["lvglStyles"]["styles"]}

def style_text_font(style_name):
    s = STYLE_BY_NAME.get(style_name)
    if not s:
        return None
    return ((s.get("definition") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {}).get("text_font")

def resolved_font(node):
    """Resolve a label's effective text_font: localStyles override beats style override."""
    ls = ((node.get("localStyles") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {})
    if ls.get("text_font"):
        return ls["text_font"]
    f = style_text_font(node.get("useStyle"))
    return f or "MONTSERRAT_14"  # LVGL default

def font_ascent(node):
    f = resolved_font(node)
    if f not in FONTS:
        raise KeyError(f"font {f!r} not in FONTS table; add its .c file or LVGL source")
    return FONTS[f]["ascent"]

def set_top(node, top, h=None):
    node["top"] = int(top)
    if h is not None:
        node["height"] = int(h)

def baseline_align_to(anchor_node, *siblings):
    """Pin every sibling's top so its baseline = anchor's baseline.
    Returns the shared baseline y (within parent local coords)."""
    anchor_baseline = anchor_node["top"] + font_ascent(anchor_node)
    for s in siblings:
        s["top"] = int(anchor_baseline - font_ascent(s))
    return anchor_baseline

def center_in(parent_h, anchor_node, *siblings, row_y_center=None):
    """Place anchor so its visible cap-height is centered around row_y_center
    (default: parent_h // 2). Then baseline-align siblings to anchor.
    Returns (anchor_top, shared_baseline)."""
    if row_y_center is None:
        row_y_center = parent_h // 2
    asc = font_ascent(anchor_node)
    # Cap-height of digits ≈ ascent for digit-only Roboto Mono and ≈ ascent-x_height_above
    # for Montserrat. For visual centering of a label's main visible body, use ascent itself
    # as the proxy for visible height (cap_top..baseline). Center: visible_top + visible_bot = 2*center
    # → top + asc/2 = center? Actually visible: top to top+asc. Center = top + asc/2.
    # So: top = center - asc/2.
    anchor_top = int(row_y_center - asc / 2)
    anchor_node["top"] = anchor_top
    baseline = anchor_top + asc
    for s in siblings:
        s["top"] = int(baseline - font_ascent(s))
    return anchor_top, baseline

# ---- 3. Find every node + its parent panel for reporting ----
def find_with_parent(root, ident, current_parent=None):
    if isinstance(root, dict):
        if root.get("identifier") == ident:
            return root, current_parent
        new_parent = root if root.get("type") in (
            "LVGLPanelWidget", "LVGLScreenWidget", "LVGLButtonWidget"
        ) else current_parent
        for v in root.values():
            if isinstance(v, (dict, list)):
                r = find_with_parent(v, ident, new_parent)
                if r[0] is not None:
                    return r
    elif isinstance(root, list):
        for x in root:
            r = find_with_parent(x, ident, current_parent)
            if r[0] is not None:
                return r
    return None, None

# ===== STATUS BAR (TopStatusBar user widget, 800x46) =====
status_root = next(uw for uw in proj["userWidgets"] if uw["name"] == "TopStatusBar")
bar_h = status_root["height"]
print(f"\n=== StatusBar (width={status_root['width']}, height={bar_h}) ===")

bar = status_root["components"][0]   # root panel
speed_val = find_in(bar, "status_speed_value")
speed_unit = find_in(bar, "status_speed_unit")
status_time = find_in(bar, "status_time")
brand_text = find_in(bar, "status_brand_text")
link_label = find_in(bar, "status_link_label")

# Anchor: status_speed_value (M22, largest text) — center it visually in the bar.
# Then align M14 siblings to that baseline.
top, baseline = center_in(bar_h, speed_val, speed_unit, status_time, brand_text, link_label)
print(f"  anchor=status_speed_value font={resolved_font(speed_val)} asc={font_ascent(speed_val)}")
print(f"  speed_value top={speed_val['top']} (cap-centered at y={bar_h//2})")
print(f"  shared baseline = {baseline}")
print(f"  speed_unit top={speed_unit['top']} (M14 ascent={font_ascent(speed_unit)})")
print(f"  status_time top={status_time['top']}")
print(f"  brand_text top={brand_text['top']}")
print(f"  link_label top={link_label['top']}")

# ===== PAGEDRIVE — battery hero (drive_card_bat 256x280) =====
drive = next(p for p in proj["userPages"] if p["name"] == "PageDrive")
bat_card = find_in(drive, "drive_card_bat")
print(f"\n=== drive_card_bat ({bat_card['width']}x{bat_card['height']}) ===")

bat_value = find_in(drive, "drive_bat_value")
bat_pct = find_in(drive, "drive_bat_pct_sym")
# Center the hero row vertically around y=120 of the 280-tall card (below the
# icon at y=67..103, above the volts row).
HERO_ROW_Y = 120
top, baseline = center_in(bat_card["height"], bat_value, bat_pct,
                          row_y_center=HERO_ROW_Y)
print(f"  bat_value ({resolved_font(bat_value)} asc={font_ascent(bat_value)}): top={bat_value['top']}, baseline={baseline}")
print(f"  bat_pct_sym ({resolved_font(bat_pct)} asc={font_ascent(bat_pct)}): top={bat_pct['top']}")
# Make the unit box tall enough to never clip the glyph (line_height + slack).
m22_lh = FONTS[resolved_font(bat_pct)]["line_height"]
bat_pct["height"] = m22_lh
# Same for bat_value: ensure box >= line_height.
rm48_lh = FONTS[resolved_font(bat_value)]["line_height"]
if bat_value["height"] < rm48_lh:
    bat_value["height"] = rm48_lh
# Volts row: place at y ~ 180 of the 280-tall card.
bat_volts = find_in(drive, "drive_bat_volts")
bat_volts_unit = find_in(drive, "drive_bat_volts_unit")
VOLTS_ROW_Y = 180
top, baseline = center_in(bat_card["height"], bat_volts, bat_volts_unit,
                          row_y_center=VOLTS_ROW_Y)
m18_lh = FONTS[resolved_font(bat_volts_unit)]["line_height"]
bat_volts_unit["height"] = m18_lh
rm18_lh = FONTS[resolved_font(bat_volts)]["line_height"]
if bat_volts["height"] < rm18_lh:
    bat_volts["height"] = rm18_lh
print(f"  bat_volts ({resolved_font(bat_volts)} asc={font_ascent(bat_volts)}): top={bat_volts['top']}, baseline={baseline}")
print(f"  bat_volts_unit ({resolved_font(bat_volts_unit)} asc={font_ascent(bat_volts_unit)}): top={bat_volts_unit['top']}")

# Battery icon: center vertically in the upper zone (y=0..HERO_ROW_Y-25).
bat_icon = find_in(drive, "drive_batt_icon_1")
ICON_ROW_Y = 60   # upper-middle of the 280-tall card, above the hero
asc_icon = font_ascent(bat_icon)
bat_icon["top"] = int(ICON_ROW_Y - bat_icon["height"] / 2)
print(f"  drive_batt_icon_1 (fa32): top={bat_icon['top']} (centered at y={ICON_ROW_Y})")

# Remaining ("-- left") sits at bottom of card.
bat_remain = find_in(drive, "drive_bat_remain")
REMAIN_ROW_Y = 260
asc_rem = font_ascent(bat_remain)
bat_remain["top"] = int(REMAIN_ROW_Y - asc_rem / 2)
bat_remain["height"] = FONTS[resolved_font(bat_remain)]["line_height"]
print(f"  drive_bat_remain ({resolved_font(bat_remain)} asc={asc_rem}): top={bat_remain['top']}")

# ===== PAGEDRIVE — solar hero (drive_card_solar 256x280) =====
solar_card = find_in(drive, "drive_card_solar")
print(f"\n=== drive_card_solar ({solar_card['width']}x{solar_card['height']}) ===")

solar_value = find_in(drive, "drive_solar_value")
solar_unit = find_in(drive, "drive_solar_unit_sym")
solar_icon = find_in(drive, "drive_solar_icon")
solar_units_label = find_in(drive, "drive_solar_units_label")  # "watts in"
solar_pct = find_in(drive, "drive_solar_pct")

# Solar icon at the same upper position as battery icon.
solar_icon["top"] = int(ICON_ROW_Y - solar_icon["height"] / 2)
print(f"  drive_solar_icon (fa32): top={solar_icon['top']}")

# Hero row at y=120 (same as battery hero).
top, baseline = center_in(solar_card["height"], solar_value, solar_unit,
                          row_y_center=HERO_ROW_Y)
m22_lh = FONTS[resolved_font(solar_unit)]["line_height"]
solar_unit["height"] = m22_lh
rm36_lh = FONTS[resolved_font(solar_value)]["line_height"]
if solar_value["height"] < rm36_lh:
    solar_value["height"] = rm36_lh
print(f"  drive_solar_value ({resolved_font(solar_value)} asc={font_ascent(solar_value)}): top={solar_value['top']}, baseline={baseline}")
print(f"  drive_solar_unit_sym ({resolved_font(solar_unit)} asc={font_ascent(solar_unit)}): top={solar_unit['top']}")

# "watts in" label below the value (same vertical pos as battery volts row).
asc_wi = font_ascent(solar_units_label)
solar_units_label["top"] = int(VOLTS_ROW_Y - asc_wi / 2)
solar_units_label["height"] = FONTS[resolved_font(solar_units_label)]["line_height"]
print(f"  drive_solar_units_label ({resolved_font(solar_units_label)} asc={asc_wi}): top={solar_units_label['top']}")

# Solar pct ("No data") at bottom of card.
asc_pct = font_ascent(solar_pct)
solar_pct["top"] = int(REMAIN_ROW_Y - asc_pct / 2)
solar_pct["height"] = FONTS[resolved_font(solar_pct)]["line_height"]
print(f"  drive_solar_pct ({resolved_font(solar_pct)} asc={asc_pct}): top={solar_pct['top']}")

# ===== PAGEDRIVE — tire cells (110x66 each) =====
print("\n=== tire cells (drive_tire_*_psi 110x66) ===")
# Inside a 110x66 cell:
#   - psi value (RM32) centered around y = 22 (upper 2/3)
#   - L1/R1 etc subtitle (M14) centered around y = 52 (bottom strip)
PSI_ROW_Y = 22
LBL_ROW_Y = 53
for cell_ident in ("drive_tire_l1", "drive_tire_r1",
                   "drive_tire_l2", "drive_tire_r2",
                   "drive_tire_l3", "drive_tire_r3"):
    cell = find_in(drive, cell_ident)
    psi = next(c for c in cell["children"] if c.get("identifier","").endswith("_psi"))
    lbl = next(c for c in cell["children"] if c.get("identifier","").endswith("_lbl"))
    asc_psi = font_ascent(psi)
    psi_lh = FONTS[resolved_font(psi)]["line_height"]
    psi["top"] = int(PSI_ROW_Y - asc_psi / 2)
    if psi["height"] < psi_lh:
        psi["height"] = psi_lh
    asc_lbl = font_ascent(lbl)
    lbl_lh = FONTS[resolved_font(lbl)]["line_height"]
    lbl["top"] = int(LBL_ROW_Y - asc_lbl / 2)
    if lbl["height"] < lbl_lh:
        lbl["height"] = lbl_lh
print(f"  psi top={psi['top']} (asc={asc_psi}), lbl top={lbl['top']} (asc={asc_lbl})")

# ===== Tire title row (TIRE PRESSURE / Single | Target 65 PSI) =====
tire_title = find_in(drive, "drive_tire_title")
tire_sub = find_in(drive, "drive_tire_sub")
asc_tt = font_ascent(tire_title)
asc_ts = font_ascent(tire_sub)
tire_title["top"] = 14
tire_title["height"] = FONTS[resolved_font(tire_title)]["line_height"]
tire_sub["top"] = 14 + tire_title["height"] + 2
tire_sub["height"] = FONTS[resolved_font(tire_sub)]["line_height"]
print(f"\n=== tire_title rows ===")
print(f"  tire_title top={tire_title['top']} h={tire_title['height']}")
print(f"  tire_sub top={tire_sub['top']} h={tire_sub['height']}")

# ===== Bottom-dock chips on PageDrive (RUNNING / LEFT / BRAKE / RIGHT / REVERSE) =====
# Each chip: 152x60. Contains an indicator dot OR icon + a label.
# Align label baseline near the bottom of the chip; icon centered in upper strip.
print("\n=== drive chips (152x60) ===")
CHIP_LBL_Y = 47   # bottom-third of chip
for chip_ident in ("drive_chip_run", "drive_chip_left", "drive_chip_brake",
                   "drive_chip_right", "drive_chip_rev"):
    chip = find_in(drive, chip_ident)
    for c in chip["children"]:
        cid = c.get("identifier", "")
        if cid.endswith("_lbl"):
            asc = font_ascent(c)
            lh = FONTS[resolved_font(c)]["line_height"]
            c["top"] = int(CHIP_LBL_Y - asc / 2)
            if c["height"] < lh:
                c["height"] = lh

# ===== Write back =====
with open(PROJ, "w") as f:
    json.dump(proj, f, indent=2)
    f.write("\n")
print(f"\nwrote: {PROJ}")
