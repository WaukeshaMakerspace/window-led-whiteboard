# Window LED Whiteboard

The window at Waukesha Makerspace that used to hold a whiteboard now holds 380 individually addressable WS2812B LEDs, driven by an Arduino Nano. This repo holds everything needed to build, power, program, and service it.

## Status

- [x] LEDs installed in the window
- [ ] 5 V power supply purchased (see [hardware/bom.md](hardware/bom.md))
- [ ] Power injection wired (see [docs/power.md](docs/power.md))
- [x] Firmware: brightness knob, White / Back / Next / Auto buttons, 14 patterns
- [ ] Control plate built and mounted (see [docs/controls.md](docs/controls.md))
- [ ] More patterns (fireplace, fireworks, holidays, and others)

## Hardware at a glance

| Part | Choice |
|------|--------|
| LEDs | 380 × WS2812B, 5 V |
| Controller | Arduino Nano (ATmega328P, 5 V logic) |
| Power supply | Mean Well LRS-200-5 (5 V, 40 A, 200 W), 120 V AC in |
| Worst case draw | ~23 A at full white, full brightness |
| Controls | Single-gang wall plate: brightness knob, White, Back, Next, Auto |

Full details: [controls and patterns](docs/controls.md), [power budget and injection plan](docs/power.md), [wiring](docs/wiring.md), [installation and servicing](docs/install.md), [bill of materials](hardware/bom.md).

## Using it

Turn the knob for brightness (all the way down is off). **White** lights the window as a whiteboard; press it again for a warmer shade. **Back** and **Next** step through the patterns, and **Auto** rotates through them on its own. Details in [docs/controls.md](docs/controls.md).

## Repo layout

```
docs/                       controls, power budget, wiring, install and service notes
hardware/bom.md             parts list
src/WindowLedWhiteboard/    the Arduino sketch (folder name must match the .ino)
  WindowLedWhiteboard.ino   modes, buttons, saving the current mode
  Config.h                  pins, LED count, and tunable values
  Controls.h/.cpp           knob and button handling
  Patterns.h/.cpp           the patterns
  sketch.yaml               pinned board core and FastLED versions
.github/workflows/          compiles the sketch on every push and pull request
```

## Uploading the sketch

### Arduino IDE

1. Install the **FastLED** library (Library Manager) at the version listed in [src/WindowLedWhiteboard/sketch.yaml](src/WindowLedWhiteboard/sketch.yaml).
2. Open `src/WindowLedWhiteboard/WindowLedWhiteboard.ino`.
3. Board: **Arduino Nano**. Processor: **ATmega328P**. If the upload fails, switch to **ATmega328P (Old Bootloader)**, which most clone Nanos need.
4. **Turn the LED power supply on before plugging in USB** (see the warning in [docs/wiring.md](docs/wiring.md#usb-warning)).
5. Upload.

### arduino-cli

The `sketch.yaml` profiles install the exact board core and FastLED version for you:

```bash
arduino-cli compile --profile nano src/WindowLedWhiteboard
arduino-cli upload --profile nano -p /dev/cu.usbserial-XXXX src/WindowLedWhiteboard
```

Use `--profile nano-old-bootloader` for clone Nanos.

## Safety

The power supply has exposed 120 V screw terminals and can deliver 40 A on the 5 V side. Keep it in a closed enclosure, unplug it before touching any wiring, and keep the inline fuses in place. See [docs/wiring.md](docs/wiring.md).

## License

[MIT](LICENSE)
