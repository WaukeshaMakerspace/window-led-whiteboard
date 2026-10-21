# Wiring

## Overview

```
 120 V AC wall outlet
        │  3-prong cord, strain relief
        ▼
 ┌──────────────────────┐
 │  Mean Well LRS-200-5 │  L, N, FG (ground) in
 │  in an enclosure     │
 └──┬─────┬─────┬─────┬─┘  +V / -V out
    │     │     │     │
  fuse  fuse  fuse  fuse   10 A inline, on each +5 V feeder
    │     │     │     │
    A     B     C     D    injection points along the strip (see power.md)
    │
    ├──────────────► Nano 5V pin
    │
 1000 µF cap across 5 V / GND at point A

 Nano D6 ──[ 330 Ω ]──► strip DIN (LED 0)
 Nano GND ─────────────► strip GND at point A
```

## Connections

| From | To | Notes |
|------|----|-------|
| Supply +V / -V (pair 1) | Injection point A (LED 0) | 10 A fuse on +V |
| Supply +V / -V (pair 2) | Injection point B | 10 A fuse on +V |
| Supply +V / -V (pair 3) | Injection point C | 10 A fuse on +V |
| Supply +V / -V (pair 4) | Injection point D (LED 379) | 10 A fuse on +V |
| Point A 5 V | Nano **5V** pin | Not VIN. VIN needs 7 to 12 V. |
| Point A GND | Nano GND | Shared ground is required for the data signal |
| Nano D6 | 330 Ω resistor, then strip DIN | Resistor goes near the first LED |
| 1000 µF capacitor | Across 5 V and GND at point A | Rated 10 V or higher; watch polarity |

The Nano is 5 V logic, so no level shifter is needed. (An ESP32 would need a 74AHCT125 level shifter, because it is 3.3 V logic.)

Keep the Nano close to LED 0 so the data wire is short, ideally under 30 cm.

## Control plate

The wall plate (brightness knob and four buttons) connects to the Nano over a Cat5 cable: 5 V, ground, A0 for the knob, and D2 to D5 for the buttons. The pin-by-pin table is in [controls.md](controls.md#wiring). The cable can be as long as needed, because the Nano stays by the strip and only the data wire has to be short.

## AC side

- The LRS-200-5 has open screw terminals carrying 120 V. It must live inside a closed enclosure.
- Use a grounded 3-prong cord with strain relief, and connect the green ground wire to the **FG** terminal.
- A panel mount IEC inlet with a built-in switch and fuse makes it easy to power off for service.
- Keep the supply out of direct sun in the window opening; it derates when hot.

## USB warning

**Turn the LED power supply on before plugging the Nano into a computer.**

The Nano's 5V pin is tied to the strip's 5 V. If USB is connected while the supply is off, the strip tries to draw its power through the Nano's USB circuitry, which can burn out a part on the Nano and stress the computer's USB port. With the supply on, the Nano runs from the supply and USB only carries data.
