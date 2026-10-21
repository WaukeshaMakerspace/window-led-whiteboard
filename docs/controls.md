# Controls

A single-gang wall plate with a brightness knob and four buttons.

## Using it

| Control | What it does |
|---------|--------------|
| **Knob** | Brightness, in every mode. All the way down turns the LEDs off. |
| **White** | Full white, for using the window as a lit whiteboard. Press again for the next shade: bright, neutral, warm. |
| **Back** / **Next** | Previous or next pattern. From white, either one goes back to the last pattern. |
| **Auto** | Rotates through the patterns, 3 minutes each. Press again to stay on the current pattern. Any other button also stops it. |

After a power cut the window comes back in the same mode, shade, and pattern. The brightness always follows the knob.

## Patterns

In the order Back and Next step through them:

| # | Pattern | What it looks like |
|---|---------|--------------------|
| 1 | Rainbow | The full rainbow spread around the window, slowly rotating |
| 2 | Color wash | The whole window drifting through the rainbow as one color |
| 3 | Breathing | The whole window fades up and down, with a new color each breath |
| 4 | Ocean | Blue and teal waves drifting along |
| 5 | Lava | Slow reds, oranges, and yellows, like a lava lamp |
| 6 | Aurora | Greens and purples shimmering like northern lights |
| 7 | Comet | A bright head with a fading tail, one lap every 6 seconds |
| 8 | Scanner | A red eye sweeping back and forth |
| 9 | Juggle | Eight colored dots weaving past each other |
| 10 | Marquee | Warm theater-sign bulbs stepping around the window |
| 11 | Color wipe | One color fills the window, then the next color wipes over it |
| 12 | Confetti | Random colored specks that pop and fade |
| 13 | Starry night | Warm white stars appearing and fading into a dark blue sky |
| 14 | Game day | Packers green and gold bands chasing around the window |

Ideas for later: fireplace, fireworks, storm, bouncing balls, holiday palettes, makerspace colors, a meeting timer.

## The plate

A blank single-gang wall plate (2.75" × 4.5"), stainless steel or nylon, drilled for the knob and four 12 mm buttons and engraved with the labels.

```
 ┌───────────────┐
 │       ◦       │   screw
 │               │
 │      (●)      │   Brightness
 │               │
 │  (●)     (●)  │   White     Auto
 │               │
 │  (●)     (●)  │   Back      Next
 │               │
 │       ◦       │   screw
 └───────────────┘
```

- Drill holes to match the parts you buy: the knob's threaded shaft and the buttons' bodies vary by model.
- Everything on the plate is 5 V, so it mounts on a **low-voltage mounting bracket** (an open ring that clamps into a hole in the drywall) instead of an electrical box. Check that the knob and button bodies fit through the bracket's opening before drilling.
- **Never put the plate in a box that also holds 120 V wiring.**

## Wiring

A Cat5e or Cat6 cable runs from the plate to the Nano. Its 8 wires are exactly enough:

| Cat5 wire | Signal | Nano pin | At the plate |
|-----------|--------|----------|--------------|
| Orange | 5 V | 5V | Knob outer leg |
| White/orange | Ground | GND | Knob other outer leg, and one leg of every button |
| Blue | Knob | A0 | Knob middle leg |
| White/blue | Ground | GND | Second ground, twisted with the knob signal to keep it quiet |
| Green | White button | D2 | White button's other leg |
| White/green | Back button | D3 | Back button's other leg |
| Brown | Next button | D4 | Next button's other leg |
| White/brown | Auto button | D5 | Auto button's other leg |

- The buttons need no resistors; the Nano's internal pull-ups handle it.
- Put a **0.1 µF ceramic capacitor** from A0 to GND at the Nano end. It keeps the brightness from wavering on a long cable.
- If the knob works backwards, swap its two outer legs.

The pins, the Auto interval, and the knob's end points are set in [`Config.h`](../src/WindowLedWhiteboard/Config.h).
