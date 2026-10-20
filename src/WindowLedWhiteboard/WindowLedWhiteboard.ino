// Window LED Whiteboard
// Drives the 380 WS2812B LEDs that replaced the whiteboard in the
// Waukesha Makerspace window. Power and wiring: see docs/ in this repo.
//
// Starter sketch: a slow rainbow across the whole window, enough to prove
// the wiring and power injection work.

#include <FastLED.h>

// ---- Configuration ----------------------------------------------------

#define LED_PIN     6
#define NUM_LEDS    380
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// 0 to 255. The power supply can handle 255 at full white (~23 A), but a
// window at full brightness is blinding; tune this to taste.
const uint8_t BRIGHTNESS = 128;

// FastLED dims the frame if its estimated draw would exceed this. Set to 80%
// of the 40 A supply; 380 LEDs never reach it, so it only matters if the LED
// count or supply changes. See docs/power.md.
const uint32_t MAX_MILLIAMPS = 32000;

const uint16_t FRAME_MS = 1000 / 60;

// -----------------------------------------------------------------------

CRGB leds[NUM_LEDS];

void setup() {
  delay(500);  // let the supply settle before driving the strip

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
}

void loop() {
  static uint8_t startHue = 0;

  fill_rainbow_circular(leds, NUM_LEDS, startHue++);
  FastLED.show();
  delay(FRAME_MS);
}
