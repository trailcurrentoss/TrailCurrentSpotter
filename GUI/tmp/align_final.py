#!/usr/bin/env python3
"""Visual-center every label using authoritative LVGL glyph ink data.

For each label:
  1. Resolve the font.
  2. Determine effective text (representative real value, or placeholder).
  3. Compute ink_mid from:
       - LVGL glyph descriptors for custom fonts (Roboto Mono digit-only,
         FontAwesome) — per-glyph, so each icon's actual shape determines
         its position.
       - PIL bbox for Montserrat (LVGL built-in, full charset — PIL matches).
  4. Position label.top so (label.top + ink_mid) == row_y_center.

Result: every label is visually centered top-to-bottom within its row,
regardless of font, regardless of whether it's an icon or text.

Arc-aware: icon row_y_center is computed from the arc widget's inner
geometry so icons sit cleanly inside the arc opening, not touching it.
"""

import glob, json, os, re, shutil, time
from PIL import ImageFont

ROOT = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter"
PROJ = f"{ROOT}/GUI/TrailCurrentSpotter.eez-project"

# ---------- font metrics ----------
LVGL_FONT_DIR = (
    "/home/dave/.cache/Espressif/ComponentManager/"
    "service_d92d8f1e/lvgl__lvgl_8.4.0_d7c1ac03/src/font"
)

DESC_RE = re.compile(
    r"\.bitmap_index\s*=\s*\d+,\s*"
    r"\.adv_w\s*=\s*(\d+),\s*"
    r"\.box_w\s*=\s*(\d+),\s*"
    r"\.box_h\s*=\s*(\d+),\s*"
    r"\.ofs_x\s*=\s*(-?\d+),\s*"
    r"\.ofs_y\s*=\s*(-?\d+)"
)

def parse_lvgl_font(path):
    txt = open(path).read()
    lh = int(re.search(r"\.line_height\s*=\s*(\d+)", txt).group(1))
    bl = int(re.search(r"\.base_line\s*=\s*(\d+)", txt).group(1))
    descs = [{"adv_w":int(m[0]),"box_w":int(m[1]),"box_h":int(m[2]),
              "ofs_x":int(m[3]),"ofs_y":int(m[4])} for m in DESC_RE.findall(txt)]
    # Parse cmap to map codepoint -> glyph index
    cmaps = []
    for cm in re.finditer(
        r"\.range_start\s*=\s*(\d+),\s*\.range_length\s*=\s*(\d+),"
        r"\s*\.glyph_id_start\s*=\s*(\d+)",
        txt
    ):
        cmaps.append({
            "range_start": int(cm.group(1)),
            "range_length": int(cm.group(2)),
            "glyph_id_start": int(cm.group(3)),
        })
    # Parse unicode_list arrays
    lists = {}
    for ul in re.finditer(
        r"static const uint16_t unicode_list_(\d+)\[\]\s*=\s*\{([^}]+)\}",
        txt
    ):
        idx = int(ul.group(1))
        values = [int(v.strip(), 0) for v in ul.group(2).split(",")
                  if v.strip()]
        lists[idx] = values
    # Stitch: each cmap[i] uses unicode_list[i]
    cmap_with_list = []
    for i, cm in enumerate(cmaps):
        cmap_with_list.append({**cm, "unicode_list": lists.get(i, [])})
    return {"line_height": lh, "base_line": bl, "descs": descs,
            "cmaps": cmap_with_list}

def lvgl_glyph_index(font, codepoint):
    for cm in font["cmaps"]:
        if cm["unicode_list"]:
            target = codepoint - cm["range_start"]
            if target in cm["unicode_list"]:
                pos = cm["unicode_list"].index(target)
                return cm["glyph_id_start"] + pos
        else:
            if cm["range_start"] <= codepoint < cm["range_start"] + cm["range_length"]:
                return cm["glyph_id_start"] + (codepoint - cm["range_start"])
    return None

def lvgl_char_ink(font, ch):
    """Return (ink_top, ink_bot) of this character within the line."""
    g = lvgl_glyph_index(font, ord(ch))
    if g is None or g >= len(font["descs"]):
        return None
    d = font["descs"][g]
    if d["box_h"] == 0:
        return None
    ink_top = font["line_height"] - font["base_line"] - d["ofs_y"] - d["box_h"]
    ink_bot = font["line_height"] - font["base_line"] - d["ofs_y"]
    return ink_top, ink_bot

def lvgl_text_ink(font, text):
    """Return (ink_top, ink_bot) of the rendered string's union ink bbox."""
    ranges = [lvgl_char_ink(font, c) for c in text]
    ranges = [r for r in ranges if r]
    if not ranges:
        return None
    return min(r[0] for r in ranges), max(r[1] for r in ranges)

# Load every custom LVGL font (the ones we generated)
LVGL_FONTS = {}
for p in sorted(glob.glob(f"{ROOT}/main/ui/ui_font_*.c")):
    name = re.search(r"ui_font_(.+)\.c$", p).group(1)
    LVGL_FONTS[name] = parse_lvgl_font(p)
# Also Montserrat (line_height + base_line — we'll mostly use PIL for ink)
MONT_METRICS = {}
for sz in (8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48):
    p = f"{LVGL_FONT_DIR}/lv_font_montserrat_{sz}.c"
    if os.path.exists(p):
        MONT_METRICS[f"MONTSERRAT_{sz}"] = parse_lvgl_font(p)

# PIL for Montserrat ink measurement
PIL_TTF_MONT = "/home/dave/.local/share/fonts/Montserrat-Medium.ttf"
_pil_cache = {}
def pil_mont_ink(size, text):
    if size not in _pil_cache:
        _pil_cache[size] = ImageFont.truetype(PIL_TTF_MONT, size)
    f = _pil_cache[size]
    x0, y0, x1, y1 = f.getbbox(text)
    return y0, y1

def ink_range(font_name, text):
    """Authoritative ink range (top, bot) for `text` rendered in `font_name`,
    measured within a single line starting at y=0."""
    if font_name in LVGL_FONTS:
        return lvgl_text_ink(LVGL_FONTS[font_name], text)
    if font_name.startswith("MONTSERRAT_"):
        size = int(font_name.rsplit("_", 1)[1])
        return pil_mont_ink(size, text)
    raise KeyError(font_name)

def line_height(font_name):
    if font_name in LVGL_FONTS:
        return LVGL_FONTS[font_name]["line_height"]
    if font_name in MONT_METRICS:
        return MONT_METRICS[font_name]["line_height"]
    raise KeyError(font_name)

# ---------- project I/O ----------
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

STYLE_BY_NAME = {s["name"]: s for s in proj["lvglStyles"]["styles"]}
def style_font(name):
    s = STYLE_BY_NAME.get(name)
    if not s: return None
    return ((s.get("definition") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {}).get("text_font")

def resolved_font(node):
    ls = ((node.get("localStyles") or {}).get("definition") or {}) \
        .get("MAIN", {}).get("DEFAULT", {})
    if ls.get("text_font"):
        return ls["text_font"]
    return style_font(node.get("useStyle")) or "MONTSERRAT_14"

def center_label(node, row_y_center, *, effective_text=None, height=None):
    font = resolved_font(node)
    if effective_text is None:
        effective_text = node.get("text", "") or "M"
    rng = ink_range(font, effective_text)
    if rng is None:
        # Fallback: pure line-height center
        mid = line_height(font) / 2
    else:
        mid = (rng[0] + rng[1]) / 2
    new_top = int(round(row_y_center - mid))
    node["top"] = new_top
    lh = line_height(font)
    node["height"] = height or lh
    return new_top, mid, font

# ---------- STATUS BAR (800x46) ----------
status_root = next(uw for uw in proj["userWidgets"] if uw["name"] == "TopStatusBar")
bar_h = status_root["height"]
bar_y = bar_h / 2.0
bar = status_root["components"][0]
print(f"=== StatusBar (h={bar_h}, row_y={bar_y}) ===")

for ident, eff in [
    ("status_brand_icon",   None),
    ("status_brand_text",   "SPOTTER"),
    ("status_link_label",   "SINGLE | Offline"),
    ("status_wifi_icon",    None),
    ("status_signal_left",  None),
    ("status_signal_right", None),
    ("status_speed_value",  "85"),
    ("status_speed_unit",   "MPH"),
    ("status_time",         "23:45"),
]:
    n = find_in(bar, ident)
    if not n: continue
    top, mid, font = center_label(n, bar_y, effective_text=eff)
    print(f"  {ident:22s} font={font:18s} mid={mid:5.1f} top={top}")

dot = find_in(bar, "status_link_dot")
dot["top"] = int(bar_y - dot["height"] / 2)
print(f"  status_link_dot      (panel)               top={dot['top']}")

# ---------- PAGEDRIVE ----------
drive = next(p for p in proj["userPages"] if p["name"] == "PageDrive")

# Battery card (256x280) — arc at (16,36,210,210), inner radius = 105-20 = 85
# Arc center y_local = 36 + 105 = 141
# Inner top: y=141-85=56  (where the inner edge of the arc reaches top)
# Inner bottom: y=141+85=226 (but arc opens at bottom 45° wedge)
print(f"\n=== drive_card_bat (256x280, arc inside_top=56) ===")

# Icon row: visually centered inside the arc's upper opening, well above value.
# Place icon's INK CENTER at y = 76 (~10px below the arc inner_top, gives clearance
# from arc curve at upper-left/upper-right corners and from value below).
ICON_ROW_Y = 76
center_label(find_in(drive, "drive_batt_icon_1"), ICON_ROW_Y)
print(f"  drive_batt_icon_1   ink-centered at y={ICON_ROW_Y}, top={find_in(drive,'drive_batt_icon_1')['top']}")

# Hero value row: y_center at midpoint between icon and volts row
HERO_Y = 138
for ident, eff in [("drive_bat_value", "85"), ("drive_bat_pct_sym", "%")]:
    n = find_in(drive, ident)
    top, mid, font = center_label(n, HERO_Y, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} mid={mid:5.1f} top={top}")

# Volts row at y_center=185
VOLTS_Y = 185
for ident, eff in [("drive_bat_volts", "12.6"), ("drive_bat_volts_unit", "V")]:
    n = find_in(drive, ident)
    top, mid, font = center_label(n, VOLTS_Y, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} mid={mid:5.1f} top={top}")

# Remaining row at bottom
REMAIN_Y = 257
n = find_in(drive, "drive_bat_remain")
top, mid, font = center_label(n, REMAIN_Y, effective_text="8h 30m left")
print(f"  drive_bat_remain     font={font:18s} mid={mid:5.1f} top={top}")

# Solar card — mirror battery
print(f"\n=== drive_card_solar (256x280) ===")
center_label(find_in(drive, "drive_solar_icon"), ICON_ROW_Y)
print(f"  drive_solar_icon    top={find_in(drive,'drive_solar_icon')['top']}")
for ident, eff in [("drive_solar_value", "450"), ("drive_solar_unit_sym", "W")]:
    n = find_in(drive, ident)
    top, mid, font = center_label(n, HERO_Y, effective_text=eff)
    print(f"  {ident:24s} font={font:18s} mid={mid:5.1f} top={top}")
n = find_in(drive, "drive_solar_units_label")
top, mid, font = center_label(n, VOLTS_Y, effective_text="watts in")
print(f"  drive_solar_units_label  font={font:18s} mid={mid:5.1f} top={top}")
n = find_in(drive, "drive_solar_pct")
top, mid, font = center_label(n, REMAIN_Y, effective_text="Solar charging")
print(f"  drive_solar_pct          font={font:18s} mid={mid:5.1f} top={top}")

# Tire title block
print(f"\n=== drive_card_tires title rows ===")
top, mid, font = center_label(find_in(drive, "drive_tire_title"), 21,
                              effective_text="TIRE PRESSURE")
print(f"  drive_tire_title  top={find_in(drive,'drive_tire_title')['top']}")
top, mid, font = center_label(find_in(drive, "drive_tire_sub"), 44,
                              effective_text="Single | Target 65 PSI")
print(f"  drive_tire_sub    top={find_in(drive,'drive_tire_sub')['top']}")

# Tire cells (110x66) — psi value in upper area, label in lower strip
print(f"\n=== tire cells ===")
# In a 110x66 cell, the visible psi area should be roughly the top 2/3,
# label in bottom 1/3.
PSI_Y = 24   # row_center for big psi number
LBL_Y = 52   # row_center for L1/R1 label
for cell_ident in ("drive_tire_l1", "drive_tire_r1",
                   "drive_tire_l2", "drive_tire_r2",
                   "drive_tire_l3", "drive_tire_r3"):
    cell = find_in(drive, cell_ident)
    psi = next(c for c in cell["children"] if c.get("identifier","").endswith("_psi"))
    lbl = next(c for c in cell["children"] if c.get("identifier","").endswith("_lbl"))
    center_label(psi, PSI_Y, effective_text="65")
    center_label(lbl, LBL_Y, effective_text=lbl["text"])
psi = find_in(drive, "drive_tire_l1_psi")
lbl = find_in(drive, "drive_tire_l1_lbl")
print(f"  psi top={psi['top']} (font={resolved_font(psi)}), "
      f"lbl top={lbl['top']} (font={resolved_font(lbl)})")

# BSM warning (240x26)
print(f"\n=== drive_bsm_warning ===")
bsm = find_in(drive, "drive_bsm_warning")
row_y = bsm["height"] / 2
center_label(find_in(drive, "drive_bsm_warn_icon"), row_y)
center_label(find_in(drive, "drive_bsm_warn_text"), row_y,
             effective_text="VEHICLE IN BLIND SPOT")
print(f"  icon top={find_in(drive,'drive_bsm_warn_icon')['top']}, "
      f"text top={find_in(drive,'drive_bsm_warn_text')['top']}")

# Drive chips (152x60)
print(f"\n=== drive chips ===")
CHIP_IND_Y = 18      # indicator/icon row
CHIP_LBL_Y = 44      # label row
for chip_ident, label_text in [
    ("drive_chip_run",   "RUNNING"),
    ("drive_chip_left",  "LEFT"),
    ("drive_chip_brake", "BRAKE"),
    ("drive_chip_right", "RIGHT"),
    ("drive_chip_rev",   "REVERSE"),
]:
    chip = find_in(drive, chip_ident)
    for c in chip["children"]:
        cid = c.get("identifier","")
        if cid.endswith("_lbl"):
            center_label(c, CHIP_LBL_Y, effective_text=label_text)
        elif cid.endswith("_icon"):
            center_label(c, CHIP_IND_Y)
        elif c.get("type") == "LVGLPanelWidget":
            # indicator dot
            c["top"] = int(CHIP_IND_Y - c["height"] / 2)
print(f"  drive_chip_run_lbl top={find_in(drive,'drive_chip_run_lbl')['top']}")

# Write back
with open(PROJ, "w") as f:
    json.dump(proj, f, indent=2)
    f.write("\n")
print(f"\nwrote: {PROJ}")
