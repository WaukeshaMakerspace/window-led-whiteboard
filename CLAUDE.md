# CLAUDE.md

This file provides guidance to Claude Code when working with this repository.

## Project overview

380 WS2812B LEDs installed in the Waukesha Makerspace window that used to hold a whiteboard, driven by an Arduino Nano and powered by a 5 V 40 A Mean Well LRS-200-5. Standalone hardware project: no network, database, or API.

## Directory structure

```
src/WindowLedWhiteboard/   Arduino sketch (folder name must match the .ino file)
  sketch.yaml              arduino-cli profiles pinning the AVR core and FastLED
docs/                      power.md, wiring.md, install.md (this is the design documentation)
hardware/bom.md            parts list and purchase status
.github/workflows/         CI compiles the sketch with the `nano` profile
```

## Hardware constraints

- **RAM:** the Nano has 2,048 bytes of SRAM. The LED buffer uses 1,140 (380 × 3) and FastLED adds about 460 more, so the starter sketch already sits at 78% and arduino-cli prints a "Low memory available" warning (expected). That leaves roughly 450 bytes for stack and everything else: avoid large arrays, `String`, and extra per-LED buffers, and put constant tables in `PROGMEM`.
- **Power:** full white at full brightness is about 23 A. If `NUM_LEDS`, the supply, or the brightness ceiling changes, update `docs/power.md` to match.
- **Logic level:** the Nano is 5 V logic and drives the strip directly. An ESP32 would need a 74AHCT125 level shifter.

## Pins

| Component | Pin | Notes |
|-----------|-----|-------|
| LED data | D6 | Through a 330 Ω resistor |

## Build

```bash
arduino-cli compile --profile nano src/WindowLedWhiteboard
```

The `sketch.yaml` profile installs the pinned core and library. Renovate does not understand `sketch.yaml`, so FastLED and `arduino:avr` bumps are manual: change both profiles and confirm CI passes.

## Code style

- Configuration (pins, LED count, brightness, power ceiling) lives in the block at the top of the sketch.
- `#define` for pins and FastLED template arguments, `const` for tunable values.

## Related documentation

- [FastLED documentation](https://fastled.io/docs/)
- Architecture repo: `../waukesha-makers-architecture/`
