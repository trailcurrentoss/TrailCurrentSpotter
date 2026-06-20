# Build Prompt — TrailCurrent "Spotter" Tow-Vehicle Dashboard in EEZ Studio (LVGL)

You are an embedded-UI engineer. Recreate the **Spotter** tow-vehicle dashboard as an **EEZ Studio LVGL project** that runs on a **Waveshare ESP32-S3 4.3″ capacitive touchscreen (800 × 480, landscape)**. The device mounts in the tow vehicle and talks to the trailer over Wi-Fi/MQTT (TrailCurrent backend). Build the UI faithfully to the spec below, wire it to flow variables, and export LVGL C for PlatformIO/ESP-IDF.

The reference is an interactive HTML mock of the exact design; this document is the source of truth for layout, color, sizing, and behavior. Match it.

---

## 0. Golden rules (read first)

- **Resolution is fixed at 800 × 480.** Design at 1:1, no scaling.
- **This is a DRIVING display.** The Drive screen is read-only and glanceable. Every *interactive* target must be **≥ 44 px** tall; prefer 56–76 px. No tiny buttons.
- **Dark theme only.** Pure-black backgrounds, structural borders, colored glows on engaged states only. No gradients as decoration.
- **System font / clean sans.** Use Montserrat or Roboto (LVGL built-in Montserrat is fine). Numbers are tabular and are the loudest type on screen.
- **No emoji.** Status is color + icon + one-word label.
- Build with **LVGL 8.3+ (or 9.x)**. Use EEZ Studio **Flow** for state/bindings and **native user actions** (C callbacks) for anything that publishes MQTT.

---

## 1. Project setup

1. New EEZ Studio project → **LVGL** template.
2. Display: **Width 800, Height 480**, color depth 16-bit (RGB565), landscape.
3. Target: ESP32-S3, LVGL with the Waveshare RGB panel + GT911 touch driver (configure in firmware, not EEZ).
4. Enable **Flow** support.
5. Create a default screen `scr_main` (see §6 for screen architecture).

---

## 2. Design tokens

Create these as **EEZ "Colors"** (named palette) so widgets reference them by name.

### Color
| Token | Hex | Use |
|---|---|---|
| `bg` | `#000000` | screen background |
| `panel` | `#121212` | cards / tiles / rows |
| `panel-2` | `#0A0A0A` | sub-bars (zone nav, footers) |
| `chrome` | `#060606` | top status bar, tab bar |
| `border` | `#232323` | card borders |
| `border-soft` | `#1F1F1F` | chrome dividers |
| `track-off` | `#2B2B2B` | switch off / gauge remainder |
| `green` | `#52A441` | brand primary, active, gauge fill |
| `green-on` | `#74FE00` | "on"/electric-lime, selected text, success |
| `green-dk` | `#3D7B31` | deep accent |
| `amber` | `#FFC107` | warning, solar, turn signals, low tire |
| `cyan` | `#48E6FE` | info / fresh / cooling |
| `red` | `#FF5453` | danger, brake lamp, critical alarm |
| `text` | `#FFFFFF` | primary text / numbers |
| `text-2` | `#A2A2A2` | secondary |
| `text-3` | `#6F6F6F` | muted labels |

### Type scale (px, weight)
| Style | Size / weight | Use |
|---|---|---|
| `display` | 40, Light | gauge value (battery/solar) |
| `alarm-title` | 30, Bold | full-screen alarm headline |
| `h1` | 23, SemiBold | speed |
| `h2` | 19, SemiBold | zone name, screen titles |
| `tile-name` | 15, SemiBold | light/alarm row names |
| `body` | 13–14, Regular/SemiBold | values, buttons |
| `label` | 11, SemiBold, +0.8 letter-spacing, UPPERCASE | section/eyebrow labels |
| `micro` | 9–10 | tire labels, sub-text |

Add fonts **Montserrat Light/Regular/SemiBold/Bold** at the sizes above (EEZ → Fonts → add from Google Fonts, generate the needed sizes). Enable tabular figures if available; otherwise keep numbers in a fixed-width container and right-align.

### Geometry
- Radius: cards/tiles **12–14**, buttons/switches **8–17**, full circles **9999**.
- Borders: **1–2 px**, color `border`. Selected/active flips border to `green` (+ soft glow via `shadow`).
- Spacing unit: 8 px grid (gaps of 6/8/10/12).
- Glows (LVGL `shadow_width` ~14–20, spread small, matching color at ~50% opacity) ONLY on engaged elements (active tab icon, "on" light, blind-spot arc, alarm pulse).

### Icons
Use **Ionicons** rasterized to bitmaps (outline = resting, filled = active), or an LVGL symbol font you generate from the Ionicons SVGs. Needed glyphs: `navigate, speedometer, bulb / bulb-outline, notifications / notifications-outline, options, car-sport, sunny, warning, power, disc, git-branch, chevron-back/forward, restaurant, tv, moon, water, partly-sunny, cube, information-circle, notifications-off`. Size 18–28 px. Never recolor by hue alone — tint with token colors.

---

## 3. Reusable styles (create in EEZ → Styles)

- `card`: bg `panel`, border 1px `border`, radius 12.
- `tile-on`: bg green@10% (`#52A441` 26/255 alpha), border 2px `green`, radius 14.
- `tile-off`: bg `panel`, border 2px `border`, radius 14.
- `chrome-bar`: bg `chrome`, border-bottom/top 1px `border-soft`.
- `switch-track`: off → `track-off`; checked → `green`. Knob white, 28 px, radius full. Track 62 × 34.
- `tab-btn`: transparent; checked → bg green@10%, top border 2px `green`, icon+label tint `green-on`. Unchecked → label/icon `#8A8A8A`.
- `pill-amber`, `pill-red`, `pill-green`: small status pills (used for advisories/badges).
- `gauge-arc-bg` / `gauge-arc-ind`: arc widget styles (see §7).

---

## 4. Global variables (EEZ → Variables, Flow)

Model the live trailer state. Types in parentheses.

**Navigation**
- `view` (enum: `drive|lights|alarms|setup`) = `drive`
- `light_zone` (int index 0..5) = 0

**Telemetry (from MQTT, read-only on UI)**
- `speed_mph` (int)
- `battery_pct` (int), `battery_v` (float), `time_to_go` (string)
- `solar_w` (int), `solar_pct` (int)
- `signal` (enum: `off|left|right|hazard`)  ← turn-signal state from Aftline
- `blind_left` (bool), `blind_right` (bool)  ← BSM sensors
- `interior_temp` (int), `co2_ppm` (int)

**Trailer profile (Setup, persisted to NVS)**
- `axle_count` (int 1..3) = 2
- `has_brakes` (bool) = true
- `has_breakaway` (bool) = true

**Tires (array, length 2×axle_count)** — each: `psi` (int), `temp` (int), `status` (enum `ok|warn|danger`), `label` (string e.g. "L1").

**Lights (array of 22)** — each: `id`, `zone` (0..5), `zone_label`, `icon`, `name`, `on` (bool), `level` (int).
Zones in order: `Galley, Living, Bedroom, Bath, Exterior, Storage`.

**Alarm triggers (array)** — each: `id`, `group` (`Doors & Cabinets|Lighting|Appliances|Safety`), `name`, `armed` (bool).
Defaults that MUST match: every door/cabinet armed; **Bathroom Light armed = true**; **Refrigerator armed = false**; Water Pump armed; CO₂ & Smoke armed.

**Events**
- `cabinet_event` (bool) = false  ← set true when a Picket sensor fires while driving
- Derived (Flow expressions):
  - `galley_armed` = lookup alarms where id==`galleyCab` → armed
  - `full_alarm` = `cabinet_event && galley_armed`
  - `muted_alarm` = `cabinet_event && !galley_armed`
  - `lights_on_count` = count(lights where on)
  - `armed_count` = count(alarms where armed)

---

## 5. Actions (EEZ → Actions; mix of Flow + native)

- `nav_set(view)` — set `view`.
- `light_toggle(id)` — flip `lights[id].on`; **native**: publish MQTT to that light's Torrent channel.
- `lights_all_off()` / `zone_all_on(zone)` / `zone_all_off(zone)`.
- `zone_prev()` / `zone_next()` — wrap `light_zone` 0..5.
- `light_zone_set(i)`.
- `alarm_toggle(id)` — flip `alarms[id].armed`; **native**: persist to NVS, update the gateway's alert ruleset.
- `axle_set(n)` / `brakes_toggle()` (when turning off, force `has_breakaway=false`) / `breakaway_toggle()` (no-op if `!has_brakes`).
- `cabinet_clear()` — `cabinet_event=false`.
- Sim-only (omit on production firmware): `sig_set`, `bs_set`, `cabinet_trigger`. The HTML mock's "Demo" panel is a presenter aid; on the device these come from MQTT.

> All write-actions that change trailer hardware must publish to the existing TrailCurrent MQTT topics and reflect the **retained** confirmed state back into the variables (optimistic UI + confirm).

---

## 6. Screen architecture

One page `scr_main` with three stacked regions; the middle swaps by `view`.

```
scr_main (800×480, bg=bg, flex column)
├── TopStatusBar      (height 46, chrome-bar)            ← always visible
├── ContentArea       (flex 1, position relative)        ← swaps by `view`
│    ├── pnl_drive    (hidden unless view==drive)
│    ├── pnl_lights   (hidden unless view==lights)
│    ├── pnl_alarms   (hidden unless view==alarms)
│    └── pnl_setup    (hidden unless view==setup)
├── BottomTabBar      (height 66, chrome-bar)            ← always visible
└── pnl_alarm_overlay (full-bleed, hidden unless full_alarm, z-top)
```

**Show/hide** each content panel by binding its `hidden` flag to `view != "<name>"` (Flow). (Alternatively use `lv_tabview` with the tab bar at the bottom and hidden tab buttons, driving the active tab from `view` — but the explicit-panels approach gives full styling control. Prefer explicit panels.)

### TopStatusBar (h46, padding 0 16)
- Left: `navigate` icon (green) + "SPOTTER" (label, green, letter-spacing 2.5) + divider + green dot + `"<AXLE LABEL> · Linked"` where axle label = SINGLE/TANDEM/TRIPLE AXLE from `axle_count`.
- Right: left & right **turn-signal chevrons** (◀ ▶) — dim `#2E2E22`; when `signal` includes that side, tint `amber` + glow + **blink** (LVGL anim toggling opacity ~0.8 s). Then divider, **speed** (h1 number + "MPH" micro), then clock "2:18".

### BottomTabBar (h66) — 4 equal tab buttons
Each tab = vertical icon (25) + label (12): **Drive** (`speedometer`), **Lights** (`bulb`), **Alarms** (`notifications`), **Setup** (`options`).
- Bind `checked` to `view=="<name>"`; on click → `nav_set`.
- Checked style = `tab-btn` active (green-on tint, 2px green top border, faint green bg). Unchecked tint `#8A8A8A`.

---

## 7. Screen: DRIVE (`pnl_drive`)

Glanceable cluster. Column layout, padding 10/12.

**Row A — cluster (flex 1), 3 columns `0.82 / 1.36 / 0.82`:**

- **Battery dial (left).** `lv_arc` 146×146: rotation 135°, range 270°, value 0–100 bound to `battery_pct`; arc-bg `track-off`, indicator `green`, rounded ends, width ~14. Center child panel (circle, bg radial dark) with `battery_pct` in `display` font + "%" + "12.9 V". Caption below: "BATTERY" (label) / "`time_to_go` left" (green).
- **TPMS rig (center).** Build the top-down trailer schematic — see §7.1.
- **Solar dial (right).** Same arc, value bound to `solar_pct`, indicator `green` (value text `solar_w` + "watts in", `sunny` amber icon). Caption "SOLAR" / "`solar_pct`% of array".

Blind-spot **sonar arcs** overlay the center column's left & right edges — see §7.2.

**Row B — advisories (auto height, only when present):**
- `lights_on_count > 0` → amber advisory bar: `bulb` + "`lights_on_count` interior lights on" + zones list + a big **All Off** button (≥ 44 px). Tapping the text area → `nav_set(lights)`.
- `muted_alarm` → grey advisory bar: `notifications-off` + "Galley cabinet open · monitoring only" / "Alarm muted for this device" + **Alarms** button → `nav_set(alarms)`.

**Row C — 7-pin lamp strip (h46):** equal cells RUNNING (green), LEFT, [BRAKE only if `has_brakes`], RIGHT, REVERSE. Each = icon + label. LEFT/RIGHT cells blink amber overlay when `signal` matches (same anim as top bar). BRAKE always lit red (it's the brake circuit feedback). Built from Aftline 7-pin data.

### 7.1 TPMS rig (data-driven by `axle_count`)
A vertical schematic centered in the column:
- Small **truck** rounded rect (54×32) at top, with a windshield strip + 2 mirror nubs.
- **A-frame hitch** triangle + green coupler dot. If `has_breakaway`: tiny "BREAKAWAY ARMED" row (green `git-branch` + micro label).
- **Trailer body**: rounded rect, width 104, **height = {1:118, 2:158, 3:194}[axle_count]**. Roof-AC nub + center spine line.
- For **each axle** (count = `axle_count`): a horizontal axle bar across the body, a **left tire** and **right tire** (14×30 dark rounded rects with 1.5px border colored by tire status: ok `#343434`, warn `amber`, danger `red`; + matching glow), and **PSI readouts** just outside each tire: big number (18 px) tinted by status + micro "`label` · `temp`°".
- Axle vertical positions: evenly spaced, `top = (i+1) * bodyH / (axle_count+1)`.
- Caption under body: "TIRE PSI · target 65".
- Implement axles with a **repeat/array** in Flow (or generate widgets in native code at init from `axle_count`, rebuilding on change). One low tire (rear-right, `warn`/amber) is the realistic default.

### 7.2 Blind-spot sonar arcs
On each side of the center column, three concentric "(((" / ")))" arcs (use 3 stacked `lv_arc` quarter/half arcs, or pre-rendered bitmaps in 3 color states).
- Clear → dim `#242424`. Vehicle present → `amber` + glow + a small rotated `car-sport` glyph. Vehicle present **and** turn signal toward that side → `red` + **blink** (BLIS behavior).
- When either side is occupied, show a top-center "VEHICLE IN BLIND SPOT" pill (amber, or red if dangerous).

---

## 8. Screen: LIGHTS (`pnl_lights`) — paged by zone

Column layout:
- **Zone pager header (h ~72):** big **‹** button (54×54) + center {zone icon + `zone_label` (h2) + "zone N of 6 · X on"} + big **›** button (54×54). Arrows → `zone_prev/next`.
- **Tile grid (flex 1, scrollable):** 2 columns, gap 10. One tile per light in the current zone. **Tile = 76 px tall**, icon (28, `bulb` filled+glow when on / `bulb-outline` dim when off) + name (15) + state ("On · 70%" green / "Off" muted). Whole tile is the touch target → `light_toggle(id)`. On = `tile-on`, off = `tile-off`.
- **Footer bar:** **All On** (green) + **All Off** buttons for the zone, center **pager dots** (one per zone, active = green-on), and an **Off · All** (all zones) button. All buttons ≥ 44 px.

Zones & lights (22 total) — match exactly:
- Galley: Overhead(on,70), Countertop, Sink, Pantry
- Living: Ceiling, Accent(on,40), Reading L, Reading R(on,85), Dinette
- Bedroom: Overhead, Vanity, Reading L, Reading R
- Bath: Overhead, Mirror, Shower
- Exterior: Porch(on,100), Awning, Scare, Entry Step
- Storage: Pass-Thru, Wardrobe

Tabs/zone buttons should show a small green dot when that zone has any light on.

---

## 9. Screen: ALARMS (`pnl_alarms`) — alarm-trigger config

This is the screen that decides **what raises an alarm while driving**.
- **Header (h ~62):** "Alarm Triggers" (h2) / "What raises an alarm while driving" (micro) on the left; right shows "`armed_count` / total armed" with a `notifications` icon (green).
- **Scrollable list** grouped by `group`. Each group: an UPPERCASE label + a right-aligned rule hint ("Alarm if opened" / "Alarm if left on" / "Alarm if running" / "Always recommended"). Under it, **rows 58 px tall**: name (14) left, **`lv_switch` (62×34, green when armed)** right → `alarm_toggle(id)`.
- Defaults must include **Refrigerator = OFF** and **Bathroom Light = ON** (the canonical example: an RV fridge running shouldn't alarm, but a bathroom light left on should).

Behavior tie-in (Flow): when `cabinet_event` becomes true, if the triggering device (`galleyCab`) is **armed** → show the full-screen alarm overlay; if **disarmed** → show only the muted advisory on Drive. Generalize this: any Picket/appliance/light event consults its `armed` flag to decide alarm-vs-silent-log.

---

## 10. Screen: SETUP (`pnl_setup`) — trailer profile

Scrollable, padding 14, gap 17.
- **Axle Configuration:** 3 big selectable cards (Single/2 · Tandem/4 · Triple/6) each with a mini top-down rig glyph (body outline + N tire ticks). Selected = green border + green-on text + faint green bg. Tap → `axle_set(n)` (drives the TPMS rig tire count).
- **Braking & Safety:** two 62-px rows with switches — "Electric Trailer Brakes" (`brakes_toggle`) and "Breakaway Switch" (`breakaway_toggle`). When brakes are off, **dim the breakaway row (opacity 0.4), force it off**, and change its subtext to "Requires electric trailer brakes". Turning brakes off also removes the BRAKE lamp on Drive.
- **Info note:** "Interior lighting and alarm triggers each have their own tab in the bar below."

---

## 11. Full-screen alarm overlay (`pnl_alarm_overlay`)

Bound `hidden = !full_alarm`, on top of everything (including tab bar).
- Dark-red radial bg. Center: 92-px red circle with `warning` icon, **pulsing** (LVGL shadow/scale anim, ~1.4 s). Headline "CABINET DOOR OPEN" (`alarm-title`). Sub: "Galley · driver-side latch released while moving" + "Picket · sensor 04 · `speed_mph` mph".
- Big **Acknowledge** button (white, ~16 px text, ≥ 56 px) → `cabinet_clear()`.

---

## 12. Live data — MQTT mapping (firmware side)

Subscribe and bind variables to these TrailCurrent sources (topic names per your Headwaters config):
| Variable | Source module |
|---|---|
| `speed_mph`, heading | Bearing (GNSS) |
| tires[] psi/temp/status | TPMS sensors |
| `signal`, 7-pin lamps | Aftline (trailer wiring monitor) |
| `battery_*`, `solar_*`, `time_to_go` | Solstice |
| `interior_temp`, `co2_ppm` | Borealis |
| door/cabinet events → `cabinet_event` | Picket |
| light states | Torrent channels |
| `blind_left/right` | BSM proximity sensors |

Use **retained** messages for current state; debounce sensor inputs; honor "foreground only" / graceful-degradation patterns. Alarm decisions run against the `armed` flags configured on the Alarms screen.

---

## 13. Touch & safety guidance

- Min target 44 px; primary actions 56–76 px. Generous spacing so a moving-vehicle tap doesn't hit the wrong control.
- Drive screen: no required interaction; only the advisory "All Off"/"Alarms" buttons are tappable.
- High contrast; never encode status by color alone — always pair with icon + word.
- Animations limited to: turn-signal blink, blind-spot blink, alarm pulse, gauge value tweens (~200 ms). No decorative motion.

---

## 14. Acceptance checklist

- [ ] 800×480, four screens reachable from the persistent bottom tab bar; top status bar persists.
- [ ] Axle setting renders 2 / 4 / 6 tires with correct PSI readouts; one low tire shows amber.
- [ ] Brakes off → BRAKE lamp gone + breakaway disabled/dimmed; breakaway off → no "armed" badge.
- [ ] Lights: 6 zones paged via tabs/arrows/dots; tiles toggle; zone + global all-off work; zone dots show on-state.
- [ ] Alarms: grouped switches; Refrigerator off + Bathroom Light on by default; arming a device changes whether its event alarms.
- [ ] Cabinet event → full-screen alarm when galley armed; quiet Drive advisory when disarmed; Acknowledge clears.
- [ ] Blind-spot arcs light amber on presence, red+blink when signaling into an occupied side.
- [ ] All interactive targets ≥ 44 px; dark theme + token colors throughout.
- [ ] Exports LVGL C; builds for ESP32-S3; variables bound to MQTT.

---

### Reference
The interactive HTML mock (`Spotter Dashboard.dc.html`) demonstrates every state. When in doubt about spacing, color, or behavior, match it pixel-for-pixel. Powered-by parity target: same firmware architecture as TrailCurrent **Milepost/Fireside** LVGL displays, purpose-built for the tow-vehicle context.
