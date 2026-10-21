# Installation and servicing

## Where everything is

**TBD:** fill in once installed.

| Part | Location |
|------|----------|
| LED strip | The window that used to hold the whiteboard |
| Data input (LED 0) | TBD: which corner, which direction the strip runs |
| Power supply enclosure | TBD |
| Control plate (with the Nano behind it) | TBD |
| Cat5 from the plate to point A | TBD: route |
| Power switch / plug | TBD |

## Photos

TODO: add photos to `docs/images/` and link them here:

- The full window, lit
- Inside the power supply enclosure, with the terminals labeled
- Each injection point
- The data connection at LED 0
- The back of the control plate, showing the Nano and its wiring

## Updating the sketch

1. Take out the control plate's two screws and ease it out of the wall to reach the Nano's USB port.
2. Plug in a laptop. With the 1N5817 diode fitted, the LED supply can be on or off (see the [USB warning](wiring.md#usb-warning)).
3. Upload from the Arduino IDE or arduino-cli as described in the [README](../README.md#uploading-the-sketch).
4. Commit the change to this repo so the next person has it.

## Powering off for service

1. Switch off or unplug the supply at the wall.
2. Wait a minute for the supply's capacitors to drain before touching the 5 V wiring.
3. Never open the supply enclosure while it is plugged in.

## Troubleshooting

| Symptom | Likely cause |
|---------|--------------|
| Nothing lights, and the button lights are off too | Supply off, blown feeder fuse at point A, or the Cat5 to the plate is loose |
| Nothing lights, but the button lights glow | The data wire is loose, at LED 0 or at the plate |
| Everything works up to LED N, nothing after | Dead LED or broken data connection at LED N. A WS2812B passes data along to the next LED, so one dead LED blacks out everything after it. Bridge or replace that LED. |
| Far end of a section looks dim, yellow, or orange on white | Voltage drop. Check that section's injection point and fuse, and see [power.md](power.md#verifying-it). |
| Random flicker or wrong colors | Data ground (white/blue Cat5 wire) not connected at both ends, missing 330 Ω data resistor, or the Cat5 is longer than about 5 m (see [wiring.md](wiring.md#cat5-between-the-plate-and-the-strip)) |
| First LED flickers or dies early | Missing 1000 µF capacitor at point A, or the strip was connected while powered |
| Nano resets when the LEDs get bright | A loose 5 V or GND wire in the Cat5, or the Nano is running from a laptop's USB instead of the supply |
| Knob works backwards | Its two outer legs are swapped. Swap them back. |
| Brightness wavers with the knob untouched | Missing 0.1 µF capacitor from A0 to GND, or a loose knob wire. See [wiring.md](wiring.md#inside-the-plate). |
| One button does nothing | Its wire to the Nano or its ground connection is loose |
| One button light never lights | Its LED is wired backwards, it isn't the 5 V version, or its wire is loose |
