# Bill of materials

| Component | Description | Qty | Status | Notes |
|-----------|-------------|-----|--------|-------|
| LED strip | WS2812B, 5 V, individually addressable | 380 LEDs | Installed | TBD: LEDs per meter |
| Controller | Arduino Nano (ATmega328P) | 1 | Have | Mounts on the back of the control plate. Clones usually need the "Old Bootloader" setting. |
| Power supply | Mean Well LRS-200-5, 5 V 40 A 200 W, 120 V AC in | 1 | To buy | See [power.md](../docs/power.md#power-supply) |
| Enclosure | Closed box for the supply, vented | 1 | To buy | Must cover the 120 V terminals |
| AC cord | 3-prong grounded cord with strain relief | 1 | To buy | Or a switched, fused IEC panel inlet plus a standard IEC cord |
| Inline fuse holders | Blade type, for 14 to 16 AWG | 4 | To buy | One per injection feeder |
| Blade fuses | 10 A | 4 + spares | To buy | |
| Feeder wire | 16 AWG stranded, red and black | TBD | To buy | 14 AWG for runs over ~2 m. Length depends on the injection layout. |
| Capacitor | 1000 µF electrolytic, 10 V or higher | 1 | To buy | Across 5 V / GND at the strip input |
| Resistor | 330 Ω, 1/4 W | 1 | To buy | In series on the data line, at the Nano end |

## Control plate

See [controls.md](../docs/controls.md) and [wiring.md](../docs/wiring.md#inside-the-plate).

| Component | Description | Qty | Status | Notes |
|-----------|-------------|-----|--------|-------|
| Wall plate | 3D printed, single gang, PETG or ASA | 1 | To print | |
| Mounting | Single-gang box or low-voltage mounting bracket | 1 | To buy | Never shared with 120 V wiring |
| Knob | 10k linear potentiometer (B10K), panel mount, with a knob cap | 1 | To buy | |
| Buttons | 12 mm momentary push buttons, normally open, with a **5 V** LED ring | 4 | To buy | The 5 V version has the LED resistor built in |
| Diode | 1N5817 Schottky | 1 | To buy | In the Nano's 5 V feed |
| Capacitor | 0.1 µF ceramic | 1 | Shop stock | A0 to GND |
| Perfboard | Small piece, to carry the Nano and parts on the back of the plate | 1 | Shop stock | |
| Hookup wire | 22 AWG stranded | 1 | Shop stock | Wiring inside the plate |
| Cable | Cat5e or Cat6, plate to injection point A | TBD | To buy or shop stock | Keep it under about 5 m |

## Tools

- Soldering iron and solder
- Wire strippers and crimper (for fuse holders and ring or spade terminals)
- Multimeter, for the voltage check in [power.md](../docs/power.md#verifying-it)
