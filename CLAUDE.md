# CLAUDE.md

This file provides guidance to Claude Code when working with this repository.

## Project overview

380 WS2812B LEDs installed in the Waukesha Makerspace window that used to hold a whiteboard, driven by an Arduino Nano and powered by a 5 V 40 A Mean Well LRS-200-5. A 3D printed single-gang wall plate (brightness knob plus lit White, Back, Next, Auto buttons) controls it. The Nano is mounted on the back of the plate; one Cat5 carries 5 V, ground, and LED data between the plate and the start of the strip. Standalone hardware project: no network, database, or API.

## Directory structure

```
src/WindowLedWhiteboard/   Arduino sketch (folder name must match the .ino file)
  WindowLedWhiteboard.ino  mode state machine, button handling, EEPROM save/restore
  Config.h                 pins, LED count, tunable values
  Controls.h/.cpp          Button (debounced) and Knob (smoothed, perceptual curve)
  Patterns.h/.cpp          pattern functions and the PATTERNS table
  sketch.yaml              arduino-cli profiles pinning the AVR core and FastLED
docs/                      controls.md, power.md, wiring.md, install.md (this is the design documentation)
hardware/bom.md            parts list and purchase status
.github/workflows/         CI compiles the sketch with the `nano` profile
```

## Hardware constraints

- **RAM:** the Nano has 2,048 bytes of SRAM, and globals use about 1,718 (83%), leaving roughly 330 bytes for the stack. arduino-cli's "Low memory available" warning is expected. The LED buffer is 1,140 bytes (380 × 3). FastLED 3.10 also links in the hardware serial port (`Serial`, about 175 bytes) even though the sketch never uses it; the reference comes through link-time optimization and was not traced. If RAM gets tight, that is the first thing to reclaim. Avoid large arrays, `String`, and extra per-LED buffers, and put constant tables in `PROGMEM`.
- **Patterns:** each pattern draws one frame into `leds[]` from `now`. It either computes every LED from the time or builds on the previous frame already in `leds[]` (fading trails). No pattern may keep its own per-LED buffer. Fast movers fill the gap back to last frame's position so trails stay solid at ~40 to 60 fps.
- **Input timing:** `FastLED.show()` disables interrupts for about 11.4 ms per frame (380 × 30 µs). Buttons and the knob are polled between frames, which is fine for them, but a rotary encoder would miss steps; that is why brightness is a potentiometer.
- **EEPROM:** only user button presses mark state for saving, and saving waits 3 seconds after the last press. Auto's pattern steps are deliberately not saved, since writing every few minutes all day would wear out the EEPROM within months.
- **Power:** full white at full brightness is about 23 A. If `NUM_LEDS`, the supply, or the brightness ceiling changes, update `docs/power.md` to match.
- **Logic level:** the Nano is 5 V logic and drives the strip directly. An ESP32 would need a 74AHCT125 level shifter.

## Pins

| Component | Pin | Notes |
|-----------|-----|-------|
| LED data | D6 | Through a 330 Ω resistor at the Nano end, then over Cat5 |
| Brightness knob | A0 | 10k linear pot; 0.1 µF to GND |
| White button / light | D2 / D3 | Button: INPUT_PULLUP to GND. Light: 5 V LED on a PWM pin. |
| Back button / light | D4 / D5 | |
| Next button / light | D7 / D9 | |
| Auto button / light | D8 / D10 | |

Lights must stay on PWM pins (3, 5, 9, 10, 11) so `Light::set` can dim them. Free for later: D11, D12, A1 to A3, A6 and A7 (analog only). Keep A4 and A5 free for an I2C real-time clock. Avoid D13 for buttons: the onboard LED fights the internal pull-up. D0 and D1 are the USB serial port.

## Build

```bash
arduino-cli compile --profile nano src/WindowLedWhiteboard
```

The `sketch.yaml` profile installs the pinned core and library. Renovate does not understand `sketch.yaml`, so FastLED and `arduino:avr` bumps are manual: change both profiles and confirm CI passes.

## Code style

- Configuration (pins, LED count, power ceiling, knob end points, Auto interval) lives in `Config.h`.
- `#define` for pins and FastLED template arguments, `const` for tunable values.
- To add a pattern: write the function in `Patterns.cpp`, add it to `PATTERNS`, and add a row to the pattern table in `docs/controls.md` (the table order must match `PATTERNS`). Patterns that wrap around the window should use sizes that divide `NUM_LEDS` so the loop has no seam.
- Don't use `Serial` in committed code: its buffers cost RAM the sketch can't spare.

## Related documentation

- [FastLED documentation](https://fastled.io/docs/)
- Architecture repo: `../waukesha-makers-architecture/`
