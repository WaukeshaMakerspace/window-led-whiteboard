# Bill of materials

| Component | Description | Qty | Status | Notes |
|-----------|-------------|-----|--------|-------|
| LED strip | WS2812B, 5 V, individually addressable | 380 LEDs | Installed | TBD: LEDs per meter |
| Controller | Arduino Nano (ATmega328P) | 1 | Have | Clones usually need the "Old Bootloader" setting |
| Power supply | Mean Well LRS-200-5, 5 V 40 A 200 W, 120 V AC in | 1 | To buy | See [power.md](../docs/power.md#power-supply) |
| Enclosure | Closed box for the supply, vented | 1 | To buy | Must cover the 120 V terminals |
| AC cord | 3-prong grounded cord with strain relief | 1 | To buy | Or a switched, fused IEC panel inlet plus a standard IEC cord |
| Inline fuse holders | Blade type, for 14 to 16 AWG | 4 | To buy | One per injection feeder |
| Blade fuses | 10 A | 4 + spares | To buy | |
| Feeder wire | 16 AWG stranded, red and black | TBD | To buy | 14 AWG for runs over ~2 m. Length depends on the injection layout. |
| Capacitor | 1000 µF electrolytic, 10 V or higher | 1 | To buy | Across 5 V / GND at the strip input |
| Resistor | 330 Ω, 1/4 W | 1 | To buy | In series on the data line |
| Hookup wire | 22 AWG, for the data line | 1 | Shop stock | |

## Control plate

See [controls.md](../docs/controls.md).

| Component | Description | Qty | Status | Notes |
|-----------|-------------|-----|--------|-------|
| Wall plate | Blank single-gang plate, stainless steel or nylon | 1 | To buy | Drilled and engraved at the shop |
| Mounting bracket | Single-gang low-voltage mounting bracket (open ring, no box) | 1 | To buy | Check the knob and buttons fit through its opening |
| Knob | 10k linear potentiometer (B10K), panel mount, with a knob cap | 1 | To buy | |
| Buttons | 12 mm momentary push buttons, normally open, panel mount | 4 | To buy | |
| Control cable | Cat5e or Cat6 | TBD | To buy or shop stock | Runs from the plate to the Nano |
| Capacitor | 0.1 µF ceramic | 1 | Shop stock | A0 to GND at the Nano |

## Tools

- Soldering iron and solder
- Wire strippers and crimper (for fuse holders and ring or spade terminals)
- Multimeter, for the voltage check in [power.md](../docs/power.md#verifying-it)
