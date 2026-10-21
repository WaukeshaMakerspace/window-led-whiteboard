# Wiring

## Overview

The Nano lives on the back of the control plate. One Cat5 cable runs from the plate to the start of the strip (injection point A), carrying 5 V and ground up to the Nano and the LED data signal back down.

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
    │  1000 µF capacitor across 5 V / GND at point A
    │
    │  Cat5: 5 V, GND, LED data
    │
 ┌──┴──────────────────────────────┐
 │ Control plate (in the wall)     │
 │   1N5817 diode ──► Nano 5V      │
 │   Nano D6 ──[ 330 Ω ]──► data   │
 │   knob, 4 lit buttons           │
 └─────────────────────────────────┘
```

## Strip end (point A)

| From | To | Notes |
|------|----|-------|
| Supply +V / -V (pair 1) | Injection point A (LED 0) | 10 A fuse on +V |
| Supply +V / -V (pair 2) | Injection point B | 10 A fuse on +V |
| Supply +V / -V (pair 3) | Injection point C | 10 A fuse on +V |
| Supply +V / -V (pair 4) | Injection point D (LED 379) | 10 A fuse on +V |
| 1000 µF capacitor | Across 5 V and GND at point A | Rated 10 V or higher; watch polarity |
| Cat5 5 V and GND wires | Point A 5 V and GND | Powers the Nano and the plate |
| Cat5 data wire | Strip DIN at LED 0 | |

Taking the Nano's power from point A, in the same cable as the data, keeps the data signal and its ground on one path.

## Cat5 between the plate and the strip

| Pair | Wire | Signal |
|------|------|--------|
| Orange | Orange | 5 V |
| Orange | White/orange | GND |
| Green | Green | 5 V |
| Green | White/green | GND |
| Blue | Blue | LED data |
| Blue | White/blue | GND, twisted with the data to keep it clean |
| Brown | Brown, white/brown | Spare |

5 V and ground each use two wires to keep the voltage drop small. The plate draws only about 0.1 A.

**Length:** keep this cable to a few meters (up to about 5 m). The LED data signal gets unreliable over longer runs; if the plate has to be farther away, add a 74AHCT125 buffer chip at the Nano end to drive the data wire.

## Inside the plate

| Part | Nano pin | Other side |
|------|----------|------------|
| Cat5 5 V | 5V, through a 1N5817 diode (stripe toward the Nano) | |
| Cat5 GND | GND | |
| Cat5 data | D6, through a 330 Ω resistor | |
| Knob outer legs | 5V and GND | Swap them if the knob works backwards |
| Knob middle leg | A0 | 0.1 µF ceramic capacitor from A0 to GND |
| White button switch | D2 | GND |
| White button light (+) | D3 | Light (-) to GND |
| Back button switch | D4 | GND |
| Back button light (+) | D5 | Light (-) to GND |
| Next button switch | D7 | GND |
| Next button light (+) | D9 | Light (-) to GND |
| Auto button switch | D8 | GND |
| Auto button light (+) | D10 | Light (-) to GND |

- **Buttons:** no resistors needed; the Nano's internal pull-ups handle it.
- **Button lights:** buy buttons with a **5 V** LED, which have the resistor built in. Plain LEDs need a 330 Ω to 1 kΩ resistor in series. The light pins are PWM pins so the firmware can dim them.
- **Data resistor:** the 330 Ω resistor sits at the Nano end, where it best protects the Nano's pin and damps the signal on the long cable.
- **Diode:** lets someone plug a laptop into the Nano at the plate without the laptop trying to power the strip (see below). It costs about 0.3 V, so the Nano runs at about 4.7 V, which is fine.

The Nano is 5 V logic, so no level shifter is needed. (An ESP32 would need a 74AHCT125 level shifter, because it is 3.3 V logic.)

## AC side

- The LRS-200-5 has open screw terminals carrying 120 V. It must live inside a closed enclosure.
- Use a grounded 3-prong cord with strain relief, and connect the green ground wire to the **FG** terminal.
- A panel mount IEC inlet with a built-in switch and fuse makes it easy to power off for service.
- Keep the supply out of direct sun in the window opening; it derates when hot.
- The control plate is 5 V only. **Never put it in a box that also holds 120 V wiring.**

## USB warning

The Nano's 5V pin connects, through the Cat5, to the strip's 5 V. If a laptop is plugged into the Nano while the LED supply is off, the strip tries to draw its power through the Nano's USB connection, which can burn out a part on the Nano and stress the laptop's USB port.

The **1N5817 diode** in the plate's 5 V feed blocks this, so with it fitted you can program the Nano whether or not the supply is on. If the diode is ever left out, **turn the LED supply on before plugging in USB**.
