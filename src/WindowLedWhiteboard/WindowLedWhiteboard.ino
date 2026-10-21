// Window LED Whiteboard
// Drives the 380 WS2812B LEDs that replaced the whiteboard in the
// Waukesha Makerspace window. Power and wiring: see docs/ in this repo.
//
// Control plate (docs/controls.md): a brightness knob and four buttons.
//   White  full white; press again for the next shade
//   Back   previous pattern
//   Next   next pattern
//   Auto   rotate through the patterns; press again to stay on the current one
// Each button has a light: White and Auto stay lit while active, Back and
// Next flash when pressed, and all of them glow faintly otherwise.

#include <EEPROM.h>
#include <FastLED.h>

#include "Config.h"
#include "Controls.h"
#include "Patterns.h"

CRGB leds[NUM_LEDS];

Knob knob(KNOB_PIN);
Button whiteButton(WHITE_BUTTON_PIN);
Button backButton(BACK_BUTTON_PIN);
Button nextButton(NEXT_BUTTON_PIN);
Button autoButton(AUTO_BUTTON_PIN);

Light whiteLight(WHITE_LIGHT_PIN);
Light backLight(BACK_LIGHT_PIN);
Light nextLight(NEXT_LIGHT_PIN);
Light autoLight(AUTO_LIGHT_PIN);

// Bright, neutral, and warm white.
const uint32_t WHITE_SHADES[] PROGMEM = {0xFFFFFF, 0xFFD7A0, 0xFFA046};
const uint8_t WHITE_SHADE_COUNT = sizeof(WHITE_SHADES) / sizeof(WHITE_SHADES[0]);

// What the window is showing. Saved to EEPROM so it survives a power cut.
struct State {
  uint8_t version;
  bool white;
  uint8_t shade;
  uint8_t pattern;
  bool autoCycle;
};

// Bump when State changes shape, so old saved bytes are ignored.
const uint8_t STATE_VERSION = 1;
const State DEFAULT_STATE = {STATE_VERSION, true, 0, 0, false};

// Save only after the buttons have been left alone this long, so a run of
// presses costs one EEPROM write instead of many.
const uint32_t SAVE_DELAY_MS = 3000;

State state;
bool saveNeeded = false;
uint32_t lastUserChangeMs = 0;
uint32_t lastAutoStepMs = 0;
uint32_t lastFrameMs = 0;
uint32_t backFlashUntilMs = 0;
uint32_t nextFlashUntilMs = 0;

void loadState() {
  EEPROM.get(0, state);
  if (state.version != STATE_VERSION || state.shade >= WHITE_SHADE_COUNT ||
      state.pattern >= PATTERN_COUNT) {
    state = DEFAULT_STATE;
  }
}

void userChanged(uint32_t now) {
  saveNeeded = true;
  lastUserChangeMs = now;
}

void showPattern(uint8_t pattern) {
  state.white = false;
  state.pattern = pattern;
  FastLED.clear();  // patterns that build on the previous frame start clean
}

void handleButtons(uint32_t now) {
  if (whiteButton.pressed(now)) {
    if (state.white) state.shade = (state.shade + 1) % WHITE_SHADE_COUNT;
    state.white = true;
    state.autoCycle = false;
    userChanged(now);
  }

  // From white, Back and Next return to the last pattern instead of
  // skipping past it.
  if (backButton.pressed(now)) {
    showPattern(state.white ? state.pattern : (state.pattern + PATTERN_COUNT - 1) % PATTERN_COUNT);
    state.autoCycle = false;
    backFlashUntilMs = now + LIGHT_FLASH_MS;
    userChanged(now);
  }
  if (nextButton.pressed(now)) {
    showPattern(state.white ? state.pattern : (state.pattern + 1) % PATTERN_COUNT);
    state.autoCycle = false;
    nextFlashUntilMs = now + LIGHT_FLASH_MS;
    userChanged(now);
  }

  if (autoButton.pressed(now)) {
    state.autoCycle = !state.autoCycle;
    if (state.autoCycle) {
      showPattern(state.pattern);
      lastAutoStepMs = now;
    }
    userChanged(now);
  }
}

void updateLights(uint32_t now) {
  whiteLight.set(state.white);
  autoLight.set(state.autoCycle);
  // Signed difference so the comparison survives millis() wrapping.
  backLight.set(int32_t(backFlashUntilMs - now) > 0);
  nextLight.set(int32_t(nextFlashUntilMs - now) > 0);
}

void setup() {
  delay(500);  // let the supply settle before driving the strip

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLIAMPS);
  FastLED.clear(true);

  knob.begin();
  whiteButton.begin();
  backButton.begin();
  nextButton.begin();
  autoButton.begin();

  loadState();
  updateLights(millis());
}

void loop() {
  uint32_t now = millis();

  handleButtons(now);

  // Auto steps are not saved: they happen all day, and writing each one
  // would wear out the EEPROM within months.
  if (state.autoCycle && now - lastAutoStepMs >= AUTO_INTERVAL_MS) {
    showPattern((state.pattern + 1) % PATTERN_COUNT);
    lastAutoStepMs = now;
  }

  if (saveNeeded && now - lastUserChangeMs >= SAVE_DELAY_MS) {
    EEPROM.put(0, state);  // only rewrites bytes that changed
    saveNeeded = false;
  }

  if (now - lastFrameMs < FRAME_MS) return;
  lastFrameMs = now;

  updateLights(now);
  FastLED.setBrightness(knob.brightness());
  if (state.white) {
    fill_solid(leds, NUM_LEDS, CRGB(pgm_read_dword(&WHITE_SHADES[state.shade])));
  } else {
    drawPattern(state.pattern, now);
  }
  FastLED.show();
}
