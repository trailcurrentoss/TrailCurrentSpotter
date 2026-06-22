#!/usr/bin/env python3
"""Set design-time text/value on every widget that's populated by incoming MQTT
data so the canvas matches what `spotter_paint_placeholders()` writes at boot
and on connectivity loss.

Targets:
  drive_bat_value     87              -> --
  drive_bat_volts     12.9 V          -> -- V
  drive_bat_remain    13h 40m left    -> -- left
  drive_bat_arc       value=87        -> value=0
  drive_solar_value   410             -> --
  drive_solar_pct     70% of capacity -> No data
  drive_solar_arc     value=70        -> value=0
  drive_tire_l1_psi   65              -> --
  drive_tire_r1_psi   65              -> --
  (l2/r2/l3/r3_psi are already --)
  status_speed_value  0               -> --
  status_link_label   TANDEM | Linked -> SINGLE | Offline
"""

import json, shutil, sys, time

PROJ = "/media/dave/extstorage/TrailCurrent/Product/TrailCurrentSpotter/GUI/TrailCurrentSpotter.eez-project"

LABEL_TARGETS = {
    "drive_bat_value":    "--",
    "drive_bat_volts":    "-- V",
    "drive_bat_remain":   "-- left",
    "drive_solar_value":  "--",
    "drive_solar_pct":    "No data",
    "drive_tire_l1_psi":  "--",
    "drive_tire_r1_psi":  "--",
    "drive_tire_l2_psi":  "--",
    "drive_tire_r2_psi":  "--",
    "drive_tire_l3_psi":  "--",
    "drive_tire_r3_psi":  "--",
    "status_speed_value": "--",
    "status_link_label":  "SINGLE | Offline",
}
ARC_TARGETS = {
    "drive_bat_arc":   0,
    "drive_solar_arc": 0,
}


def walk(node, changes):
    if isinstance(node, dict):
        ident = node.get("identifier")
        if ident in LABEL_TARGETS and node.get("type") == "LVGLLabelWidget":
            new = LABEL_TARGETS[ident]
            old = node.get("text")
            if old != new:
                node["text"] = new
                changes.append(f"label {ident}: {old!r} -> {new!r}")
        if ident in ARC_TARGETS and node.get("type") == "LVGLArcWidget":
            new = ARC_TARGETS[ident]
            old = node.get("value")
            if old != new:
                node["value"] = new
                changes.append(f"arc {ident}: value {old} -> {new}")
        for v in node.values():
            walk(v, changes)
    elif isinstance(node, list):
        for x in node:
            walk(x, changes)


def main():
    ts = time.strftime("%Y%m%d-%H%M%S")
    shutil.copyfile(PROJ, PROJ + ".bak." + ts)

    with open(PROJ) as f:
        proj = json.load(f)

    changes = []
    walk(proj, changes)

    if not changes:
        print("No changes needed.")
        return

    with open(PROJ, "w") as f:
        json.dump(proj, f, indent=2)
        f.write("\n")

    print(f"Backup: {PROJ}.bak.{ts}")
    print(f"Applied {len(changes)} change(s):")
    for c in changes:
        print(f"  {c}")


if __name__ == "__main__":
    main()
