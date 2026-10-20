# Installation and servicing

## Where everything is

**TBD:** fill in once installed.

| Part | Location |
|------|----------|
| LED strip | The window that used to hold the whiteboard |
| Data input (LED 0) | TBD: which corner, which direction the strip runs |
| Power supply enclosure | TBD |
| Arduino Nano | TBD |
| Power switch / plug | TBD |

## Photos

TODO: add photos to `docs/images/` and link them here:

- The full window, lit
- Inside the power supply enclosure, with the terminals labeled
- Each injection point
- The Nano and the data connection to LED 0

## Updating the sketch

1. Make sure the LED power supply is **on** (see the [USB warning](wiring.md#usb-warning)).
2. Plug a laptop into the Nano's USB port.
3. Upload from the Arduino IDE or arduino-cli as described in the [README](../README.md#uploading-the-sketch).
4. Commit the change to this repo so the next person has it.

## Powering off for service

1. Switch off or unplug the supply at the wall.
2. Wait a minute for the supply's capacitors to drain before touching the 5 V wiring.
3. Never open the supply enclosure while it is plugged in.

## Troubleshooting

| Symptom | Likely cause |
|---------|--------------|
| Nothing lights | Supply off, blown feeder fuse at point A, or data wire loose at LED 0 |
| Everything works up to LED N, nothing after | Dead LED or broken data connection at LED N. A WS2812B passes data along to the next LED, so one dead LED blacks out everything after it. Bridge or replace that LED. |
| Far end of a section looks dim, yellow, or orange on white | Voltage drop. Check that section's injection point and fuse, and see [power.md](power.md#verifying-it). |
| Random flicker or wrong colors | Missing shared ground between Nano and strip, missing 330 Ω data resistor, or a long data wire |
| First LED flickers or dies early | Missing 1000 µF capacitor at point A, or the strip was connected while powered |
| Nano resets when the LEDs get bright | Nano is powered from USB instead of the supply, or a weak connection on the Nano 5V wire |
