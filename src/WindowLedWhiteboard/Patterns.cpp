// Each pattern draws one frame into leds[] from the current time. The Nano
// has only a few hundred bytes of RAM to spare, so a pattern either computes
// every LED from the time or builds on the previous frame already in leds[]
// (fading trails). None keeps its own per-LED buffer.
//
// To add a pattern: write the function, add it to PATTERNS, and describe it
// in docs/controls.md.

#include "Patterns.h"

#include "Config.h"

namespace {

typedef void (*Pattern)(uint32_t now);

const uint8_t BREATHING_HUES[] PROGMEM = {
  HUE_RED, HUE_ORANGE, HUE_GREEN, HUE_AQUA, HUE_BLUE, HUE_PURPLE,
};

// Greens and purples, with dark gaps between the bands of light.
const TProgmemRGBPalette16 AuroraColors_p PROGMEM = {
  0x000000, 0x001A08, 0x00501C, 0x00A040, 0x20FF70, 0x00A060, 0x006060, 0x002040,
  0x000000, 0x100030, 0x400080, 0x8020C0, 0x400080, 0x00A040, 0x00501C, 0x000000,
};

// Fills from one LED to another, inclusive, in either direction.
void fillBetween(uint16_t from, uint16_t to, const CRGB& color) {
  if (from > to) {
    uint16_t swap = from;
    from = to;
    to = swap;
  }
  fill_solid(leds + from, to - from + 1, color);
}

// Smooth moving noise mapped through a palette. `spread` sets how far apart
// the blobs are along the strip; a larger `slowness` drifts more slowly.
void paletteNoise(const TProgmemRGBPalette16& palette, uint32_t now, uint8_t spread,
                  uint8_t slowness) {
  uint16_t t = now / slowness;
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, inoise8(i * spread, t));
  }
}

// ---- Calm --------------------------------------------------------------

// The full rainbow spread around the window, slowly rotating.
void rainbow(uint32_t now) {
  fill_rainbow_circular(leds, NUM_LEDS, now / 40);
}

// The whole window drifting through the rainbow as one color.
void colorWash(uint32_t now) {
  fill_solid(leds, NUM_LEDS, CHSV(now / 120, 255, 255));
}

// The whole window fades up and down, changing color while it's dark.
void breathing(uint32_t now) {
  const uint32_t BREATH_MS = 5000;
  uint8_t phase = (now % BREATH_MS) * 256 / BREATH_MS;
  uint8_t hue = pgm_read_byte(&BREATHING_HUES[(now / BREATH_MS) % sizeof(BREATHING_HUES)]);
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, ease8InOutQuad(triwave8(phase))));
}

void ocean(uint32_t now) {
  paletteNoise(OceanColors_p, now, 20, 8);
}

void lava(uint32_t now) {
  paletteNoise(LavaColors_p, now, 12, 16);
}

void aurora(uint32_t now) {
  paletteNoise(AuroraColors_p, now, 8, 12);
}

// ---- Motion ------------------------------------------------------------

// A bright head with a fading tail, one lap of the window every 6 seconds.
void comet(uint32_t now) {
  const uint32_t LAP_MS = 6000;
  const uint16_t MAX_GAP = 16;
  static uint16_t lastHead = 0;

  uint16_t head = (now % LAP_MS) * NUM_LEDS / LAP_MS;
  CRGB color = CHSV(now / 100, 200, 255);
  fadeToBlackBy(leds, NUM_LEDS, 24);

  // The head moves a few LEDs per frame, so fill back to last frame's head
  // for a solid tail. A big gap means the pattern just started.
  uint16_t gap = (head + NUM_LEDS - lastHead) % NUM_LEDS;
  if (gap > MAX_GAP) gap = 0;
  for (uint16_t i = 0; i <= gap; i++) {
    leds[(head + NUM_LEDS - i) % NUM_LEDS] = color;
  }
  lastHead = head;
}

// A red eye sweeping back and forth.
void scanner(uint32_t) {
  const uint16_t MAX_GAP = 24;
  static uint16_t lastPos = 0;

  uint16_t pos = beatsin16(12, 0, NUM_LEDS - 1);
  fadeToBlackBy(leds, NUM_LEDS, 16);
  uint16_t gap = pos > lastPos ? pos - lastPos : lastPos - pos;
  fillBetween(gap > MAX_GAP ? pos : lastPos, pos, CRGB::Red);
  lastPos = pos;
}

// Eight colored dots weaving past each other.
void juggle(uint32_t) {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  uint8_t hue = 0;
  for (uint8_t i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(hue, 200, 255);
    hue += 32;
  }
}

// Theater-sign bulbs stepping around the window. SPACING should divide
// NUM_LEDS so the loop has no seam.
void marquee(uint32_t now) {
  const uint8_t SPACING = 4;
  const CRGB BULB(255, 150, 50);
  uint8_t lit = (now / 150) % SPACING;
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = (i % SPACING == lit) ? BULB : CRGB::Black;
  }
}

// One color fills the window, then the next color wipes over it.
void colorWipe(uint32_t now) {
  const uint32_t WIPE_MS = 8000;
  uint32_t wipe = now / WIPE_MS;
  uint16_t edge = (now % WIPE_MS) * NUM_LEDS / WIPE_MS;
  fill_solid(leds, edge, CHSV(wipe * 40, 255, 255));
  fill_solid(leds + edge, NUM_LEDS - edge, CHSV((wipe - 1) * 40, 255, 255));
}

// ---- Sparkle -----------------------------------------------------------

// Random colored specks that pop and fade.
void confetti(uint32_t now) {
  fadeToBlackBy(leds, NUM_LEDS, 8);
  for (uint8_t i = 0; i < 3; i++) {
    leds[random16(NUM_LEDS)] += CHSV(now / 40 + random8(64), 200, 255);
  }
}

// Warm white stars appearing and fading into a dark blue sky.
void starryNight(uint32_t) {
  const CRGB SKY(0, 0, 20);
  const CRGB STAR(255, 230, 180);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    nblend(leds[i], SKY, 6);
  }
  if (random8() < 96) leds[random16(NUM_LEDS)] = STAR;
}

// ---- Local -------------------------------------------------------------

// Packers green and gold bands chasing around the window. 2 * BAND should
// divide NUM_LEDS so the loop has no seam.
void gameDay(uint32_t now) {
  const CRGB GREEN(0, 140, 30);
  const CRGB GOLD(255, 160, 0);
  const uint8_t BAND = 10;
  uint8_t shift = (now / 60) % (2 * BAND);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = ((i + 2 * BAND - shift) / BAND) % 2 ? GOLD : GREEN;
  }
}

const Pattern PATTERNS[] PROGMEM = {
  rainbow, colorWash, breathing, ocean, lava, aurora,
  comet, scanner, juggle, marquee, colorWipe,
  confetti, starryNight,
  gameDay,
};

}  // namespace

const uint8_t PATTERN_COUNT = sizeof(PATTERNS) / sizeof(PATTERNS[0]);

void drawPattern(uint8_t index, uint32_t now) {
  Pattern draw = reinterpret_cast<Pattern>(pgm_read_ptr(&PATTERNS[index]));
  draw(now);
}
