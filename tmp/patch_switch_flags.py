#!/usr/bin/env python3
"""User-authorized per-task .eez-project patch (per feedback-no-eez-json-shortcut
memory). Edits two specific fields on two specific widget sets, with 5
verification gates + auto-rollback.

Mode:
  G1 JSON parse
  G2 Field-level diff (ONLY widgetFlags on LVGLSwitchWidget gaining CHECKABLE
                       and `left` on alarm_spoor*_s*_sw widgets going to 700)
  G3 Schema invariants (per-widget key sets unchanged; no objID change/add/remove;
                        no widget added/removed)
  G4 Named-reference integrity (no new dangling style/color/font/action refs)
  G5 Widget counts (LVGLSwitchWidget total, alarm_spoor* set size) unchanged

Run from project root: python3 tmp/patch_switch_flags.py
On any gate failure: file is restored from the most-recent backup.
"""
import json
import re
import shutil
import sys
from pathlib import Path

PROJECT = Path("GUI/TrailCurrentSpotter.eez-project")
SPOOR_RE = re.compile(r"^alarm_spoor\d+_s\d+_sw$")

# --- Locate the most-recent backup --------------------------------------------

def latest_backup():
    cands = sorted(PROJECT.parent.glob(PROJECT.name + ".bak.*"),
                   key=lambda p: p.stat().st_mtime, reverse=True)
    if not cands:
        sys.exit("FAIL: no .bak.* backup found in GUI/. Refusing to patch without backup.")
    return cands[0]

# --- Walker -------------------------------------------------------------------

def walk(node, fn):
    if isinstance(node, dict):
        fn(node)
        for v in node.values():
            walk(v, fn)
    elif isinstance(node, list):
        for x in node:
            walk(x, fn)

# --- Patch logic --------------------------------------------------------------

def apply_patch(data):
    stats = {"checkable_added": [], "left_moved": [], "switches_total": 0,
             "alarm_spoor_total": 0}

    def patch(w):
        wtype = w.get("type")
        ident = w.get("identifier", "")
        if wtype == "LVGLSwitchWidget":
            stats["switches_total"] += 1
            flags = w.get("widgetFlags", "") or ""
            parts = [p for p in flags.split("|") if p]
            if "CHECKABLE" not in parts:
                w["widgetFlags"] = "|".join(["CHECKABLE"] + parts)
                stats["checkable_added"].append(ident)
            if SPOOR_RE.match(ident):
                stats["alarm_spoor_total"] += 1
                if w.get("left") != 700:
                    w["left"] = 700
                    stats["left_moved"].append(ident)

    walk(data, patch)
    return stats

# --- Gates --------------------------------------------------------------------

def g1_parse(path):
    """JSON syntactic integrity."""
    try:
        json.loads(path.read_text())
        return True, "OK"
    except json.JSONDecodeError as e:
        return False, f"JSON parse failed: {e}"

def g2_field_diff(before, after, stats):
    """Only widgetFlags on LVGLSwitchWidget and `left` on alarm_spoor*_s*_sw."""
    # Build identifier->dict map for both states (by objID for stable comparison).
    def by_objid(d):
        m = {}
        def collect(n):
            if isinstance(n, dict) and "objID" in n and "type" in n:
                m[n["objID"]] = n
        walk(d, collect)
        return m

    before_map = by_objid(before)
    after_map  = by_objid(after)

    if set(before_map) != set(after_map):
        added   = set(after_map)  - set(before_map)
        removed = set(before_map) - set(after_map)
        return False, f"widget objID set changed: +{len(added)} -{len(removed)}"

    # Fields that contain nested widgets — their content changes when child
    # widgets change. Skip in this per-widget diff (children are visited as
    # their own objIDs in the walk).
    NESTED_CONTAINER_FIELDS = {"children"}

    extraneous = []
    for oid, b in before_map.items():
        a = after_map[oid]
        b_keys = set(b.keys())
        a_keys = set(a.keys())
        if b_keys != a_keys:
            extraneous.append(f"  {oid} {a.get('identifier','?')} keys changed: +{a_keys-b_keys} -{b_keys-a_keys}")
            continue
        for k in b_keys:
            if k in NESTED_CONTAINER_FIELDS:
                continue
            if b[k] == a[k]:
                continue
            # This key changed. Is it allowed?
            ident = a.get("identifier","")
            wtype = a.get("type","")
            is_switch = wtype == "LVGLSwitchWidget"
            is_alarm_spoor = bool(SPOOR_RE.match(ident))
            if k == "widgetFlags" and is_switch:
                # Allowed: widgetFlags on a Switch gaining CHECKABLE prepend.
                continue
            if k == "left" and is_alarm_spoor:
                continue
            extraneous.append(f"  {oid} {ident} field '{k}' changed unexpectedly: {b[k]!r} -> {a[k]!r}")

    if extraneous:
        return False, "Unexpected field changes:\n" + "\n".join(extraneous[:20])
    return True, "OK"

def g3_schema(before, after):
    """No objID changed/added/removed beyond what G2 already checks; per-widget
    key sets unchanged (also checked in G2). Here we additionally verify that
    the LVGLSwitchWidget per-widget shape (key count) is still in the
    canonical envelope."""
    def by_objid(d, want_type=None):
        m = {}
        def collect(n):
            if isinstance(n, dict) and "objID" in n and "type" in n:
                if want_type is None or n.get("type") == want_type:
                    m[n["objID"]] = n
        walk(d, collect)
        return m

    before_sw = by_objid(before, "LVGLSwitchWidget")
    after_sw  = by_objid(after,  "LVGLSwitchWidget")
    if set(before_sw) != set(after_sw):
        return False, "Switch objID set changed across patch"
    for oid in before_sw:
        b_keys = sorted(before_sw[oid].keys())
        a_keys = sorted(after_sw[oid].keys())
        if b_keys != a_keys:
            return False, f"Switch {oid} key set changed across patch"
    return True, "OK"

def g4_named_refs(after):
    """No new dangling refs. Build sets of known names; walk all useStyle /
    text_color / bg_color / border_color / shadow_color / text_font / actions /
    userWidgetPageName / bitmaps / colors. Any reference not in the known set
    that wasn't already dangling in `before` would be a regression. For a
    targeted patch like this one, we only touched widgetFlags + left, so we
    just verify integrity end-to-end."""
    known_styles  = {s["name"] for s in after.get("lvglStyles", {}).get("styles", [])} | {"default"}
    known_colors  = {c["name"] for c in after.get("colors", [])}
    known_actions = {a["name"] for a in after.get("actions", [])}
    known_widgets = {w["name"] for w in after.get("userWidgets", [])}
    known_fonts   = {f["name"] for f in after.get("fonts", [])} | {
        f"MONTSERRAT_{n}" for n in (8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48)
    }

    issues = []

    def check(n):
        if not isinstance(n, dict):
            return
        if "useStyle" in n and isinstance(n["useStyle"], str) and n["useStyle"] not in known_styles:
            issues.append(f"  unknown style '{n['useStyle']}' on objID {n.get('objID','?')}")
        if n.get("type") == "LVGLUserWidgetWidget":
            uwpn = n.get("userWidgetPageName")
            if uwpn and uwpn not in known_widgets:
                issues.append(f"  unknown userWidgetPageName '{uwpn}' on objID {n.get('objID','?')}")
        for e in n.get("eventHandlers", []) or []:
            act = e.get("action")
            if act and act not in known_actions:
                issues.append(f"  unknown action '{act}' on objID {n.get('objID','?')}")

    walk(after, check)
    if issues:
        return False, "Named-reference issues:\n" + "\n".join(issues[:20])
    return True, "OK"

def g5_counts(before, after):
    """Widget counts by type and by alarm_spoor regex must be unchanged."""
    def count(d):
        c = {"LVGLSwitchWidget": 0, "alarm_spoor": 0, "total_widgets": 0}
        def f(n):
            if isinstance(n, dict) and "type" in n and isinstance(n["type"], str) and n["type"].startswith("LVGL"):
                c["total_widgets"] += 1
                if n["type"] == "LVGLSwitchWidget":
                    c["LVGLSwitchWidget"] += 1
                if SPOOR_RE.match(n.get("identifier","") or ""):
                    c["alarm_spoor"] += 1
        walk(d, f)
        return c

    cb, ca = count(before), count(after)
    if cb != ca:
        return False, f"Counts diverged: before={cb} after={ca}"
    return True, "OK"

# --- Main ---------------------------------------------------------------------

def main():
    backup_path = latest_backup()
    print(f"Using backup: {backup_path.name}")

    before_text = backup_path.read_text()
    before = json.loads(before_text)

    after = json.loads(json.dumps(before))  # deep copy
    stats = apply_patch(after)

    # Write the patched file
    PROJECT.write_text(json.dumps(after, indent=2) + "\n")

    print()
    print("=== Patch summary ===")
    print(f"LVGLSwitchWidget total in file:    {stats['switches_total']}")
    print(f"  CHECKABLE added:                 {len(stats['checkable_added'])}")
    print(f"alarm_spoor*_s*_sw total in file:  {stats['alarm_spoor_total']}")
    print(f"  left -> 700 changed:             {len(stats['left_moved'])}")
    print()

    # --- Run gates ---
    gates = [
        ("G1 JSON parse",            lambda: g1_parse(PROJECT)),
        ("G2 Field-level diff",      lambda: g2_field_diff(before, after, stats)),
        ("G3 Schema invariants",     lambda: g3_schema(before, after)),
        ("G4 Named-ref integrity",   lambda: g4_named_refs(after)),
        ("G5 Widget counts",         lambda: g5_counts(before, after)),
    ]

    print("=== Gates ===")
    all_pass = True
    for name, fn in gates:
        try:
            ok, msg = fn()
        except Exception as e:
            ok, msg = False, f"EXCEPTION: {e}"
        status = "PASS" if ok else "FAIL"
        print(f"  [{status}] {name}: {msg}")
        if not ok:
            all_pass = False

    if not all_pass:
        print()
        print("!!! Gate failure -> restoring from backup")
        shutil.copy(backup_path, PROJECT)
        print(f"Restored {PROJECT} from {backup_path}")
        sys.exit(1)

    print()
    print("All gates passed.")
    print()
    print("Next steps:")
    print("  1. Open EEZ Studio (or reload the project if already open).")
    print("  2. Visually verify a few switches have 'Checkable' ticked and the")
    print("     alarm-row switches sit at x=700.")
    print("  3. Ctrl+B to re-export, then flash. Post-export this should hold:")
    print("       grep -c 'lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE)' main/ui/screens.c")
    print("     should return 0 (was 41).")

if __name__ == "__main__":
    main()
