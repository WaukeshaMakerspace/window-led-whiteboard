# Power

## Budget

Worst case is every LED at full white and full brightness. The WS2812B datasheet puts that at 20 mA per color channel, so 60 mA per LED. Real strips often measure 40 to 50 mA, but we size for the spec.

| Load | Current |
|------|---------|
| 380 LEDs × 60 mA | 22.8 A |
| Arduino Nano | ~0.05 A |
| **Total** | **~23 A (about 115 W)** |

With 25% headroom the minimum is about 29 A, so anything below a 30 A supply is too small.

## Power supply

**Mean Well LRS-200-5** (5 V, 40 A, 200 W, 120 V AC input).

- At the worst case it runs at about 57% load, so it stays cool with no fan.
- It is UL listed, which matters for an unattended install in a space open to the public.
- Its output can be trimmed slightly with the V.ADJ screw. Setting about 5.1 V at the terminals helps offset voltage drop along the wiring. Do not go above 5.3 V, the WS2812B maximum.
- It has several +V and -V output terminals, so each injection feeder gets its own pair (see below).

The smaller LRS-150-5 (22 A) cannot cover full white. Unbranded "5V 40A" supplies are cheaper but are not a good fit for something that runs unattended.

## Software ceiling

The sketch calls `FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLIAMPS)`, which dims the whole frame whenever FastLED estimates the draw would exceed the limit. It is set to 32 A (80% of the supply). With 380 LEDs the strip can never reach that, so it never dims anything today; it exists so that adding LEDs or changing the supply later cannot silently overload things. Lower it if you ever want a hard cap on heat or power.

## Power injection

A single feed at one end will not reach full brightness: the copper on the strip is thin, so voltage drops along its length and the far end turns dim and orange on white. Power has to be fed in at several points.

**Plan:** feed 5 V and GND at both ends and about every 100 to 130 LEDs, which is about 4 points for 380 LEDs.

| Point | Near LED | Serves about |
|-------|----------|--------------|
| A | 0 (data input end) | LEDs 0 to 63 |
| B | ~127 | LEDs 64 to 190 |
| C | ~254 | LEDs 191 to 316 |
| D | 379 (far end) | LEDs 317 to 379 |

Exact points depend on how the strip is laid out in the window. **TBD:** strip density (LEDs per meter), whether it is one continuous run or several segments, and the grid shape. Once known, update this table and the feeder lengths below.

Rules for injection:

- Each feeder is its own pair of wires from its own +V/-V terminals on the supply. Do not daisy chain feeders.
- Connect **both** 5 V and GND at every point.
- Do not connect the 5 V of two separately powered supplies together. With one supply this is not an issue.

## Feeders and fuses

| Item | Spec |
|------|------|
| Feeder wire, runs under ~2 m | 16 AWG stranded, red and black |
| Feeder wire, runs over ~2 m | 14 AWG stranded |
| Fuse, one per feeder | 10 A blade fuse in an inline holder, on the +5 V wire, close to the supply |

At full white the middle feeders (B and C) carry up to about 8 A and the end feeders about 4 A. The fuse is there so a pinched or shorted wire cannot pull the full 40 A the supply can deliver.

## Verifying it

After the injection wiring is done:

1. In the sketch, temporarily set `BRIGHTNESS` to `255` and replace the `loop()` body with `fill_solid(leds, NUM_LEDS, CRGB::White); FastLED.show();`.
2. Upload and let it run for a minute.
3. With a multimeter, measure 5 V to GND at each injection point and at the LEDs halfway between points.
4. Everything should read about **4.7 V or higher** and look the same shade of white. If a section reads lower or looks yellow, add an injection point there or use heavier wire.
5. Feel the feeders and the supply. Warm is fine; hot means a wire is undersized.
6. Restore the sketch.
