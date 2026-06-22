#!/usr/bin/env python3
"""Ink-bbox visual centering for every label in PageDrive + TopStatusBar.

For each label we:
  1. Determine its EFFECTIVE text — placeholders like "--" are replaced with
     a realistic worst-case value ("85", "120", etc.) so positioning matches
     what the user actually sees when MQTT lands. Static labels keep their
     literal text. Icons measure their codepoint glyph.
  2. PIL-measure the ink bbox of that text on the SAME TTF + size LVGL uses.
  3. Compute ink_mid = (y0 + y1) / 2 within the line.
  4. Position label.top so label.top + ink_mid == row_y_center for the
     containing row.

This makes Mont, Roboto Mono, AND FontAwesome glyphs share the same visual
midline within any parent — top-to-bottom centered, exactly what the user
asked for.
"""

import glob, json, os, re, shutil, time
from PIL import ImageFont

ROOT = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter"
PROJ = f"{ROOT}/GUI/TrailCurrentSpotter.eez-project"

# ---- 1. Font TTF paths ----
TTF = {
    "MONTSERRAT_8":  "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_10": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_12": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_14": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_16": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_18": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_22": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_24": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_32": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_36": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "MONTSERRAT_48": "/home/dave/.local/share/fonts/Montserrat-Medium.ttf",
    "roboto_mono_18": f"{ROOT}/ASSETS/RobotoMono-Medium.ttf",
    "roboto_mono_32": f"{ROOT}/ASSETS/RobotoMono-Medium.ttf",
    "roboto_mono_36": f"{ROOT}/ASSETS/RobotoMono-Medium.ttf",
    "roboto_mono_48": f"{ROOT}/ASSETS/RobotoMono-Medium.ttf",
    "fa16": f"{ROOT}/ASSETS/fa-solid-900.ttf",
    "fa32": f"{ROOT}/ASSETS/fa-solid-900.ttf",
}

def font_pxsize(name):
    if name.startswith("MONTSERRAT_") or name.startswith("roboto_mono_"):
        return int(name.rsplit("_", 1)[1])
    if name in ("fa16",): return 16
    if name in ("fa32",): return 32
    raise KeyError(name)

# ---- 2. LVGL line metrics (height + base_line) so we can also pin label height ----
LVGL_FONT_DIR = (
    "/home/dave/.cache/Espressif/ComponentManager/"
    "service_d92d8f1e/lvgl__lvgl_8.4.0_d7c1ac03/src/font"
)

def read_lvgl_metrics(path):
    txt = open(path).read()
    lh = int(re.search(r"\.line_height\s*=\s*(\d+)", txt).group(1))
    bl = int(re.search(r"\.base_line\s*=\s*(\d+)", txt).group(1))
    return lh, bl

LVGL_LH = {}
for p in sorted(glob.glob(f"{ROOT}/main/ui/ui_font_*.c")):
    name = re.search(r"ui_font_(.+)\.c$", p).group(1)
    LVGL_LH[name] = read_lvgl_metrics(p)
for sz in (8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48):
    p = f"{LVGL_FONT_DIR}/lv_font_montserrat_{sz}.c"
    if os.path.exists(p):
        LVGL_LH[f"MONTSERRAT_{sz}"] = read_lvgl_metrics(p)

def line_height(font_name):
    return LVGL_LH[font_name][0]

# ---- 3. PIL ink-bbox measurement, cached ----
_pil_cache = {}
def pil_font(name):
    if name not in _pil_cache:
        _pil_cache[name] = ImageFont.truetype(TTF[name], font_pxsize(name))
    return _pil_cache[name]

def ink_mid(font_name, text):
    """Return (y0, y1, mid) = top/bottom of rendered ink within the line,
    in pixel coords measured from the line's top."""
    f = pil_font(font_name)
    x0, y0, x1, y1 = f.getbbox(text)
    return y0, y1, (y0 + y1) / 2.0

# ---- 4. Load project + helpers ----
with open(PROJ) as fp:
    proj = json.load(fp)

ts = time.strftime("%Y%m%d-%H%M%S")
shutil.copyfile(PROJ, f"{PROJ}.bak.{ts}")
print(f"backup: {PROJ}.bak.{ts}\n")

def find_in(root, ident):
    if isinstance(root, dict):
        if root.get("identifier") == ident:
            return root
        for v in root.values():
            r = find_in(v, ident)
            if r is not None: return r
    elif isinstance(root, list):
        for x in root:
            r = find_in(x, ident)
            if r is not None: return r
    return None

STYLE_BY_NAME = {s["name"]: s for s in proj["lvglStyles"]["styles"]}

def style_text_font(name):
    s = STYLE_BY_NAME.get(name)
    if not s: return None
    return ((s.get("definition") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {}).get("text_font")

def resolved_font(node):
    ls = ((node.get("localStyles") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {})
    if ls.get("text_font"):
        return ls["text_font"]
    return style_text_font(node.get("useStyle")) or "MONTSERRAT_14"

# ---- 5. Center one label's ink at a given row_y_center ----
def center_label(node, row_y_center, *, effective_text=None, min_height=None):
    """Place node.top so its ink mid lands at row_y_center, and grow the
    label box to at least line_height so glyphs never clip."""
    font = resolved_font(node)
    if effective_text is None:
        effective_text = node.get("text", "")
    if not effective_text:
        # Empty placeholder — use an "M" as a generic centering reference.
        effective_text = "M"
    y0, y1, mid = ink_mid(font, effective_text)
    new_top = int(round(row_y_center - mid))
    node["top"] = new_top
    lh = line_height(font)
    needed = max(lh, min_height or 0)
    if node.get("height", 0) < needed:
        node["height"] = needed
    return new_top, mid, font

# ---- 6. STATUS BAR (TopStatusBar, 800x46) ----
status_root = next(uw for uw in proj["userWidgets"] if uw["name"] == "TopStatusBar")
bar_h = status_root["height"]
bar_center = bar_h / 2.0      # 23
bar = status_root["components"][0]
print(f"=== StatusBar (height={bar_h}, row_center={bar_center}) ===")

# Effective text: use the worst-case real value for variable labels.
PLAN_STATUSBAR = [
    ("status_brand_icon",    None),                 # icon — use codepoint as is
    ("status_brand_text",    "SPOTTER"),
    ("status_link_label",    "SINGLE | Offline"),
    ("status_wifi_icon",     None),
    ("status_signal_left",   None),
    ("status_signal_right",  None),
    ("status_speed_value",   "85"),                 # realistic 2-digit speed
    ("status_speed_unit",    "MPH"),
    ("status_time",          "23:45"),              # realistic time
]
for ident, eff in PLAN_STATUSBAR:
    n = find_in(bar, ident)
    if not n: continue
    top, mid, font = center_label(n, bar_center, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} text={eff!r:18s} ink_mid={mid:5.1f} top={top}")

# Link dot (10x10 panel) — visually center
link_dot = find_in(bar, "status_link_dot")
link_dot["top"] = int(bar_center - link_dot["height"] / 2)
print(f"  status_link_dot         (panel)             top={link_dot['top']}")

# ---- 7. DRIVE PAGE GAUGE CARDS ----
drive = next(p for p in proj["userPages"] if p["name"] == "PageDrive")

# Battery card 256x280
print(f"\n=== drive_card_bat (256x280) ===")
# Three logical rows top-to-bottom:
#   Row A: battery icon          row_center ≈ 60
#   Row B: hero value + %        row_center ≈ 130 (hero block visually centered in card)
#   Row C: volts value + V       row_center ≈ 195
#   Row D: remaining text        row_center ≈ 255
BAT_ROWS = {
    "drive_batt_icon_1":      (60,  None),
    "drive_bat_value":        (130, "85"),
    "drive_bat_pct_sym":      (130, "%"),
    "drive_bat_volts":        (195, "12.6"),
    "drive_bat_volts_unit":   (195, "V"),
    "drive_bat_remain":       (255, "8h 30m left"),
}
for ident, (yc, eff) in BAT_ROWS.items():
    n = find_in(drive, ident)
    if not n: continue
    top, mid, font = center_label(n, yc, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} text={eff!r:14s} row_y={yc} ink_mid={mid:5.1f} top={top}")

# Solar card 256x280 — mirror battery's row centers so cards align
print(f"\n=== drive_card_solar (256x280) ===")
SOLAR_ROWS = {
    "drive_solar_icon":          (60,  None),
    "drive_solar_value":         (130, "450"),
    "drive_solar_unit_sym":      (130, "W"),
    "drive_solar_units_label":   (195, "watts in"),
    "drive_solar_pct":           (255, "Solar charging"),
}
for ident, (yc, eff) in SOLAR_ROWS.items():
    n = find_in(drive, ident)
    if not n: continue
    top, mid, font = center_label(n, yc, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} text={eff!r:18s} row_y={yc} ink_mid={mid:5.1f} top={top}")

# ---- 8. TIRE TITLE BLOCK (drive_card_tires 256x280) ----
print(f"\n=== drive_card_tires title rows ===")
# Two stacked rows at the top of the tire card:
#   Row A: "TIRE PRESSURE" at y_center=20
#   Row B: "Single | Target 65 PSI" at y_center=42
title = find_in(drive, "drive_tire_title")
sub = find_in(drive, "drive_tire_sub")
for n, yc, eff in [(title, 20, "TIRE PRESSURE"),
                   (sub, 42, "Single | Target 65 PSI")]:
    top, mid, font = center_label(n, yc, effective_text=eff)
    print(f"  {n['identifier']:24s} font={font:18s} row_y={yc} ink_mid={mid:5.1f} top={top}")

# ---- 9. TIRE CELLS (110x66) ----
print(f"\n=== tire cells ===")
# Inside a 110x66 cell:
#   Row A: psi value at y_center=22  (upper area for the big number)
#   Row B: L1/R1 etc subtitle at y_center=53
for cell_ident in ("drive_tire_l1", "drive_tire_r1",
                   "drive_tire_l2", "drive_tire_r2",
                   "drive_tire_l3", "drive_tire_r3"):
    cell = find_in(drive, cell_ident)
    psi = next(c for c in cell["children"] if c.get("identifier","").endswith("_psi"))
    lbl = next(c for c in cell["children"] if c.get("identifier","").endswith("_lbl"))
    center_label(psi, 22, effective_text="65")
    center_label(lbl, 53, effective_text=lbl["text"])
# Print one as a sample
psi = find_in(drive, "drive_tire_l1_psi")
lbl = find_in(drive, "drive_tire_l1_lbl")
print(f"  psi top={psi['top']} (font={resolved_font(psi)}), "
      f"lbl top={lbl['top']} (font={resolved_font(lbl)})")

# ---- 10. BSM warning row (drive_bsm_warning 240x26) ----
print(f"\n=== drive_bsm_warning (icon + text horizontal row) ===")
bsm_panel = find_in(drive, "drive_bsm_warning")
bsm_h = bsm_panel["height"]
row_y = bsm_h / 2     # 13
bsm_icon = find_in(drive, "drive_bsm_warn_icon")
bsm_text = find_in(drive, "drive_bsm_warn_text")
center_label(bsm_icon, row_y)
center_label(bsm_text, row_y, effective_text="VEHICLE IN BLIND SPOT")
print(f"  icon top={bsm_icon['top']}, text top={bsm_text['top']} (row_y={row_y})")

# ---- 11. DRIVE CHIPS (152x60) — RUNNING / LEFT / BRAKE / RIGHT / REVERSE ----
print(f"\n=== drive chips (152x60) ===")
# In each chip:
#   Row A: indicator dot OR icon at y_center=18 (upper third)
#   Row B: label at y_center=44 (lower third)
CHIP_INDICATOR_Y = 18
CHIP_LABEL_Y = 44
chip_specs = [
    ("drive_chip_run",   None, "RUNNING"),
    ("drive_chip_left",  "drive_chip_left_icon", "LEFT"),
    ("drive_chip_brake", None, "BRAKE"),
    ("drive_chip_right", "drive_chip_right_icon", "RIGHT"),
    ("drive_chip_rev",   None, "REVERSE"),
]
for chip_ident, icon_ident, label_text in chip_specs:
    chip = find_in(drive, chip_ident)
    for c in chip["children"]:
        cid = c.get("identifier","")
        if cid.endswith("_lbl"):
            center_label(c, CHIP_LABEL_Y, effective_text=label_text)
        elif icon_ident and cid == icon_ident:
            center_label(c, CHIP_INDICATOR_Y)
        elif c.get("type") == "LVGLPanelWidget" and (cid.endswith("_dot") or "indicator" in cid):
            # dot panels — center their box
            c["top"] = int(CHIP_INDICATOR_Y - c["height"] / 2)
chip_lbl = find_in(drive, "drive_chip_run_lbl")
print(f"  sample: drive_chip_run_lbl top={chip_lbl['top']}")

# ---- Write back ----
with open(PROJ, "w") as fp:
    json.dump(proj, fp, indent=2)
    fp.write("\n")
print(f"\nwrote: {PROJ}")
