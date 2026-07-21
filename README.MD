# TrailCurrent Spotter

Touchscreen remote monitor for the [TrailCurrent](https://trailcurrent.com) modular vehicle system, built on the Waveshare ESP32-S3 4.3" touch display with LVGL GUI. Connects directly to the local MQTT broker over WiFi for real-time data and control.

## Hardware Overview

- **Display:** [Waveshare ESP32-S3 4.3" capacitive touchscreen](https://www.waveshare.com/product/arduino/boards-kits/esp32-s3/esp32-s3-touch-lcd-4.3.htm?aff_id=Trailcurrent) (800x480 RGB) — small form factor ideal for in-car usage where space is limited, and the ESP32-S3 provides more than sufficient performance for displaying real-time status alerts and alarms while driving
- **Microcontroller:** ESP32-S3 with 8MB flash, PSRAM (QIO OPI)
- **IO Expander:** CH422G I2C IO expander for display control
- **SD Card:** MicroSD slot (SPI on GPIO 11/12/13, CS via CH422G IO expander)
- **Communication:** WiFi — connects directly to the local Mosquitto MQTT broker (TLS on port 8883)
- **Key Features:**
  - Multi-page touch interface with bottom navigation bar
  - Real-time vehicle status via MQTT subscriptions
  - Light and accessory control via MQTT publish
  - SD card configuration — no on-screen credential entry needed
  - Configurable themes and screen timeout
  - Timezone-aware date/time display
  - User settings persisted in NVS (non-volatile storage)
  - 3D-printable enclosure with battery compartment

## GUI Pages

| Page | Function |
|------|----------|
| **Home** | Status dashboard with warning indicators (lights, water, power, doors, cabinets, stabilizers) |
| **Trailer** | Trailer-specific monitoring and controls |
| **Power** | Battery voltage, state of charge, shore power status, PDM device control |
| **Solar** | Solar charge controller status and wattage |
| **Air** | Temperature (F), humidity, and air quality readings |
| **Settings** | Display theme, screen timeout, gateway MAC address, timezone, connectivity, about/version |

The GUI is designed with [EEZ Studio](https://www.envox.hr/eez/studio/studio-introduction.html) and rendered using LVGL 8.4.0.

## Device Configuration

Configuration is loaded from a `config.env` file and optional `ca.crt` on a MicroSD card. This avoids typing long credentials on the small touch keyboard.

**Setup steps:**

1. Create a file called `config.env` on a MicroSD card (FAT32 formatted)
2. Add your configuration values:

```
WIFI_SSID=YourNetworkName
WIFI_PWD=YourWiFiPassword
MQTT_HOST=192.168.1.100
MQTT_PORT=8883
MQTT_USER=mqttuser
MQTT_PASS=mqttpassword
```

3. Optionally copy the Mosquitto CA certificate as `ca.crt` to the SD card root for TLS server verification
4. Insert the SD card into the device and power on (or restart)
5. The device reads the config and CA cert, saves both to NVS, and connects automatically
6. The SD card can be removed after the first boot — settings persist in NVS

**Notes:**
- `MQTT_HOST` should be an IP address (ESP32 does not resolve `.local` mDNS hostnames)
- `MQTT_PORT` defaults to 8883 if omitted
- TLS encryption is always used; if no `ca.crt` is provided, certificate verification is skipped but the connection remains encrypted
- If no configuration exists (no SD card and no saved NVS values), the device shows "Configuration Required — Insert SD card with config.env and ca.crt then restart"
- Re-inserting an SD card will clear all previous connection settings and replace them with the new values on next boot

## Communication Protocol

The remote connects directly to the Mosquitto MQTT broker over TLS (port 8883). No intermediate server is required for real-time operation.

**Subscribe (status updates from CAN bus devices via MQTT):**

| Topic | Data Fields |
|-------|-------------|
| `local/lights/+/status` | `state` (0/1), `brightness` (0-255) |
| `local/energy/status` | `battery_percent`, `battery_voltage`, `solar_watts`, `charge_type` |
| `local/airquality/temphumid` | `temperature` (Celsius — converted to F on device), `humidity` |
| `local/gps/latlon` | `latitude`, `longitude` |
| `local/gps/alt` | `altitudeFeet` |
| `local/gps/details` | `numberOfSatellites`, `speedOverGround`, `courseOverGround`, `gnssMode` |

**Publish (commands to devices):**

| Topic | Payload |
|-------|---------|
| `local/lights/{id}/command` | `{"state": 0\|1}` |

The MQTT client uses the ESP-IDF native `esp_mqtt_client` for event-driven, non-blocking message delivery.

## Firmware Setup

**Prerequisites:**
- [PlatformIO](https://platformio.org/) (CLI or IDE plugin)

**Build and upload:**
```bash
# Build firmware
pio run

# Upload to board (serial)
pio run -t upload
```

No secrets files are needed in the source. Device configuration (WiFi credentials, MQTT broker details) is loaded at runtime from an SD card — see [Device Configuration](#device-configuration) above.

## Case Design

A 3D-printable enclosure is included in the `CAD/` directory (FreeCAD format). The case accommodates a battery and physical buttons alongside the built-in touch interface.

![Case Design](ASSETS/CaseDesign.png)

## Project Structure

```
├── ASSETS/                       # Images and documentation assets
│   └── CaseDesign.png
├── CAD/                          # 3D-printable enclosure (FreeCAD)
│   └── TrailCurrentSpotter.FCStd
├── GUI/                          # EEZ Studio GUI project
│   └── TrailCurrentSpotter.eez-project
├── src/                          # Firmware source
│   ├── main.cpp                  # Application entry, LVGL setup, IO expander init, boot flow
│   ├── globals.h                 # Version, debug macros
│   ├── sdConfig.h / sdConfig.cpp # SD card config.env and ca.crt reader
│   ├── wifiHelper.h / .cpp       # WiFi connection management
│   ├── mqttClient.h / .cpp       # MQTT client (ESP-IDF native, TLS, pub/sub)
│   ├── actions.cpp               # UI event handlers (navigation, settings, themes, controls)
│   ├── vars.cpp                  # State variables, LVGL widget updates, time conversion
│   └── ui/                       # Generated LVGL UI code (from EEZ Studio — do not edit)
│       ├── screens.h / screens.c # Screen and widget object definitions
│       ├── styles.h / styles.c   # Theme styles
│       ├── vars.h                # Variable getter/setter declarations
│       ├── actions.h             # Action function declarations
│       ├── images.h / images.c   # Embedded images
│       └── fonts/                # Custom fonts (FontAwesome icons)
├── lib/                          # Local libraries
│   └── ESP32_Display_Panel/      # Waveshare display driver (ESP-IDF based)
├── 8MB_no_ota.csv                # Flash partition table
└── platformio.ini                # Build configuration
```

## Dependencies

| Library | Source | Purpose |
|---------|--------|---------|
| LVGL 8.4.0 | PlatformIO registry | GUI framework |
| ArduinoJson 7.x | PlatformIO registry | JSON parsing for MQTT messages |
| ESP-IDF MQTT | Built-in (ESP-IDF) | Native MQTT client with TLS support |
| ESP32_Display_Panel | Local (`lib/`) | Waveshare display and touch driver |
| SD / SPI | ESP32 Arduino built-in | SD card access for config.env and ca.crt |
| WiFi | ESP32 Arduino built-in | WiFi connectivity |

## Troubleshooting

**Screen flickers, shows garbage pixels, or won't wake correctly after long idle periods.**

*The symptom.* After the device has been powered on for a while — especially in a warm cabin — the screen may briefly flicker, show corrupt pixels, or fail to redraw after it goes to sleep. In the worst case only a full power cycle brings it back. Our sibling product Milepost hit an almost-identical problem in early 2026, so the diagnosis and fix are shared between them.

*What was actually happening.* The ESP32-S3 uses an external memory chip called PSRAM as scratch space for the picture it draws to the screen, and it re-reads that memory hundreds of times per second to refill the display. On this hardware the PSRAM was being clocked at 120 MHz — the fastest advertised speed, but Espressif's own docs flag it as *experimental* and not thermally stable. As the chip warmed up during normal use, occasional reads came back corrupt. The display then painted garbage pixels or dropped a frame, which is the flicker you saw. A smaller secondary contributor: every time you save a setting, the flash chip briefly disables the instruction cache, and if the display's refill code happens to be paged out of on-chip memory at that instant, the panel underruns.

*What was changed (2026-07-20).*

1. **PSRAM slowed from 120 MHz to 80 MHz.** This is the mainline-supported speed and is stable across the full operating temperature range. Flash was slowed to match (they have to run at the same speed).
2. **Display + DMA interrupt handlers pinned to on-chip memory** (`CONFIG_LCD_RGB_ISR_IRAM_SAFE`, `CONFIG_GDMA_ISR_IRAM_SAFE`). The display keeps refilling even during the brief flash-cache-disable windows that every settings save and OTA update produce.
3. **Display told to self-heal from underruns** (`CONFIG_LCD_RGB_RESTART_IN_VSYNC`). If a refill ever misses its deadline, the panel restarts cleanly at the next frame boundary instead of latching a corrupted picture.
4. **Main task and its interrupts moved to CPU1** (`CONFIG_ESP_MAIN_TASK_AFFINITY_CPU1`). WiFi lives on CPU0 and can generate long interrupt bursts, so putting the display on the quieter core removes that source of contention.
5. **Safety net on the UI thread.** The frame-done wait in `lvgl_flush_cb` is bounded to 100 ms. If the display ever wedges, the UI logs an error and keeps running instead of freezing the whole app.
6. **Boot banner and periodic diagnostics.** The first log line after any reboot now names exactly why the device restarted (`POWERON`, `PANIC`, `TASK_WDT`, `BROWNOUT`, etc.). Every 10 seconds the firmware prints a `[diag]` line with a display-refresh counter, an underrun counter, and heap-free numbers.

*Confirmed by a 2 h serial log on 2026-07-20:* 720 diagnostic samples, the refresh counter (`vsync_d`) stayed locked at 390–391 per 10 s window (the panel's actual rate at the configured 14 MHz pixel clock), zero underrun events, zero errors, zero unexpected reboots.

*If the symptom ever comes back — usually after an ESP-IDF or LVGL upgrade:*

- Check `sdkconfig` still has all of these (some ESP-IDF version bumps regenerate `sdkconfig` from defaults and can silently drop options):
  - `CONFIG_SPIRAM_SPEED_80M=y` — **not** `120M`
  - `CONFIG_ESPTOOLPY_FLASHFREQ_80M=y`
  - `CONFIG_LCD_RGB_ISR_IRAM_SAFE=y`
  - `CONFIG_GDMA_ISR_IRAM_SAFE=y`
  - `CONFIG_LCD_RGB_RESTART_IN_VSYNC=y`
  - `CONFIG_ESP_MAIN_TASK_AFFINITY_CPU1=y`
- Run a soak test and watch the `[diag]` line. `vsync_d` should be ~390 per 10 s window and `flush_to_d` should stay at 0. Any non-zero `flush_to_d`, or `vsync_d` dropping to 0 while the log keeps printing, means the fix has regressed.

## License

MIT License - See LICENSE file for details.

This is open source hardware and software. You are free to use, modify, and distribute under the terms of the MIT license.

## Contributing

Improvements and contributions are welcome! Please submit issues or pull requests.
