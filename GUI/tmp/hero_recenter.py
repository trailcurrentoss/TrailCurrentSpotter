#!/usr/bin/env python3
"""Hero-recenter value+unit pairs on the most-common display width.

Hero widths (per user direction + RV solar wattage research):
  - Battery percent:  2 digits  "85"   (3-digit "100" is rare full-charge)
  - Battery volts:    4 chars   "12.6" (always %.1f format)
  - Solar wattage:    3 digits  "250"  (typical RV travel-trailer reading)
  - Tire PSI:         2 digits  "65"   (typical trailer pressure)

Value boxes are sized to EXACTLY the hero width (no slack) so the hero case
fills the box perfectly and is dead-centered on the parent panel. Edge-case
values (1- or 3-digit battery%, 4-digit kilowatt solar, etc.) overflow LEFT
of the value box since text_align is RIGHT — they extend into the icon
margin which is a different vertical band, no collision.

Horizontal-only pass: vertical positions from align_final.py are preserved.
"""

import json, re, shutil, time
from PIL import ImageFont

ROOT = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter"
PROJ = f"{ROOT}/GUI/TrailCurrentSpotter.eez-project"

# ---- exact LVGL glyph widths ----
# Roboto Mono is monospace — every glyph has the same adv_w/16 px width.
RM_ADV = {18: 10.8125, 32: 19.1875, 36: 21.625, 48: 28.8125}

def rm_text_w(size, text):
    """Width in pixels for a Roboto Mono string at the given size."""
    return int(round(len(text) * RM_ADV[size]))

# Montserrat widths from the actual TTF (matches LVGL built-in renderer).
PIL_MONT = ImageFont.truetype("/home/dave/.local/share/fonts/Montserrat-Medium.ttf", 1)
_mont_pil = {}
def mont_text_w(size, text):
    if size not in _mont_pil:
        _mont_pil[size] = ImageFont.truetype(
            "/home/dave/.local/share/fonts/Montserrat-Medium.ttf", size)
    f = _mont_pil[size]
    x0, y0, x1, y1 = f.getbbox(text)
    return x1 - x0

# ---- load project ----
with open(PROJ) as f:
    proj = json.load(f)
ts = time.strftime("%Y%m%d-%H%M%S")
shutil.copyfile(PROJ, f"{PROJ}.bak.{ts}")
print(f"backup: {PROJ}.bak.{ts}\n")

def find_in(root, ident):
    if isinstance(root, dict):
        if root.get("identifier") == ident: return root
        for v in root.values():
            r = find_in(v, ident)
            if r is not None: return r
    elif isinstance(root, list):
        for x in root:
            r = find_in(x, ident)
            if r is not None: return r
    return None

drive = next(p for p in proj["userPages"] if p["name"] == "PageDrive")

# ---- helper: hero-recenter a (value, unit) pair on a panel ----
def hero_recenter(panel_w, value_node, value_w, gap, unit_node, unit_w):
    """Resize and reposition value+unit so the pair is dead-centered on
    a `panel_w`-wide parent. value_node right-aligned; unit_node left-aligned."""
    pair_w = value_w + gap + unit_w
    pair_x = (panel_w - pair_w) // 2
    value_node["left"] = pair_x
    value_node["width"] = value_w
    unit_node["left"] = pair_x + value_w + gap
    unit_node["width"] = unit_w
    return pair_x, pair_x + pair_w

CARD_W = 256

# ---- 1. Battery percent (2-digit hero) ----
bat_value = find_in(drive, "drive_bat_value")
bat_pct = find_in(drive, "drive_bat_pct_sym")
val_w = rm_text_w(48, "85")            # 58
unit_w = mont_text_w(22, "%") + 3      # 22 (3 px slack on the unit)
x0, x1 = hero_recenter(CARD_W, bat_value, val_w, 4, bat_pct, unit_w)
print(f"battery%   value={val_w}px unit={unit_w}px pair=[{x0}..{x1}] center={(x0+x1)//2}")

# ---- 2. Battery volts (4-char hero "12.6") ----
bat_volts = find_in(drive, "drive_bat_volts")
bat_volts_unit = find_in(drive, "drive_bat_volts_unit")
val_w = rm_text_w(18, "12.6")          # 43
unit_w = mont_text_w(18, "V") + 3      # ~16
x0, x1 = hero_recenter(CARD_W, bat_volts, val_w, 3, bat_volts_unit, unit_w)
print(f"battery V  value={val_w}px unit={unit_w}px pair=[{x0}..{x1}] center={(x0+x1)//2}")

# ---- 3. Solar watts (3-digit hero "250") ----
solar_value = find_in(drive, "drive_solar_value")
solar_unit = find_in(drive, "drive_solar_unit_sym")
val_w = rm_text_w(36, "250")           # 65
unit_w = mont_text_w(22, "W") + 3      # 28
x0, x1 = hero_recenter(CARD_W, solar_value, val_w, 4, solar_unit, unit_w)
print(f"solar W    value={val_w}px unit={unit_w}px pair=[{x0}..{x1}] center={(x0+x1)//2}")

# ---- 4. Tire PSI cells (2-digit hero "65", centered in 110 cell) ----
# No unit pair — value centered alone, CENTER text_align so hero "65" is
# dead-centered and edge "120" expands symmetrically left and right.
TIRE_CELL_W = 110
psi_w = rm_text_w(32, "65")            # 38
for cell_ident in ("drive_tire_l1", "drive_tire_r1",
                   "drive_tire_l2", "drive_tire_r2",
                   "drive_tire_l3", "drive_tire_r3"):
    cell = find_in(drive, cell_ident)
    psi = next(c for c in cell["children"] if c.get("identifier","").endswith("_psi"))
    psi["width"] = psi_w
    psi["left"] = (TIRE_CELL_W - psi_w) // 2
    # Keep CENTER text alignment so the hero is dead-centered
    ls = psi.setdefault("localStyles", {}).setdefault("definition", {})
    main = ls.setdefault("MAIN", {})
    dflt = main.setdefault("DEFAULT", {})
    dflt["text_align"] = "CENTER"
print(f"tire psi   value={psi_w}px centered in {TIRE_CELL_W}px → left={(TIRE_CELL_W-psi_w)//2}")

# Ensure all value labels keep RIGHT alignment, units LEFT
for n, align in [(bat_value, "RIGHT"), (bat_pct, "LEFT"),
                 (bat_volts, "RIGHT"), (bat_volts_unit, "LEFT"),
                 (solar_value, "RIGHT"), (solar_unit, "LEFT")]:
    ls = n.setdefault("localStyles", {}).setdefault("definition", {})
    main = ls.setdefault("MAIN", {})
    dflt = main.setdefault("DEFAULT", {})
    dflt["text_align"] = align

with open(PROJ, "w") as f:
    json.dump(proj, f, indent=2)
    f.write("\n")
print(f"\nwrote: {PROJ}")
