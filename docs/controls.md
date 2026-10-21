# Controls

A 3D printed single-gang wall plate with a brightness knob and four lit buttons. The Nano is mounted on the back of the plate.

## Using it

| Control | What it does |
|---------|--------------|
| **Knob** | Brightness, in every mode. All the way down turns the LEDs off. |
| **White** | Full white, for using the window as a lit whiteboard. Press again for the next shade: bright, neutral, warm. |
| **Back** / **Next** | Previous or next pattern. From white, either one goes back to the last pattern. |
| **Auto** | Rotates through the patterns, 3 minutes each. Press again to stay on the current pattern. Any other button also stops it. |

The button lights show what the window is doing: **White** stays lit in white mode, **Auto** stays lit while rotating, and **Back** and **Next** flash when pressed. All four glow faintly the rest of the time, so the plate is easy to find in a dark room.

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

A 3D printed plate at standard single-gang size, so it mounts like a light switch cover.

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

| Detail | Value |
|--------|-------|
| Outline | 2.75" × 4.5" (69.85 × 114.3 mm), standard single gang |
| Screw holes | On the center line, 3.28" (83.3 mm) apart, for 6-32 screws |
| Face thickness | About 3 mm, within the clamping range of most panel buttons and pots |
| Buttons | 12 mm momentary, normally open, with a 5 V LED ring. 16 mm buttons need a "midway" size plate (same screw spacing, larger outline). |
| Knob | 10k linear potentiometer (B10K) with a panel nut |
| Material | PETG or ASA. Both handle heat and stress better than PLA. |
| Labels | Raised or recessed text, a two-color print, or a laser-engraved overlay |

- Size the button and knob holes to the parts you actually buy; models vary.
- The Nano mounts on the back of the plate (for example on a small perfboard with the resistor, diode, and capacitor). Leave room for it below or beside the button and knob bodies, and make sure everything fits through the box or bracket opening.
- To reprogram the Nano, take out the two plate screws and ease the plate out to reach its USB port.
- Mount it on a single-gang box or a low-voltage mounting bracket. **Never in a box that also holds 120 V wiring.**

Wiring for the plate is in [wiring.md](wiring.md#inside-the-plate). The pins, light levels, Auto interval, and the knob's end points are set in [`Config.h`](../src/WindowLedWhiteboard/Config.h).
