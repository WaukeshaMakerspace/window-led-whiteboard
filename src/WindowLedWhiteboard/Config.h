// Window LED Whiteboard configuration: pins, LED count, and tunable values.
#pragma once

#include <FastLED.h>

// ---- LEDs --------------------------------------------------------------

#define LED_PIN     6
#define NUM_LEDS    380
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// FastLED dims the frame if its estimated draw would exceed this. Set to 80%
// of the 40 A supply; 380 LEDs never reach it, so it only matters if the LED
// count or supply changes. See docs/power.md.
const uint32_t MAX_MILLIAMPS = 32000;

const uint16_t FRAME_MS = 1000 / 60;

// ---- Control plate (see docs/controls.md) ------------------------------

#define KNOB_PIN         A0
#define WHITE_BUTTON_PIN 2
#define BACK_BUTTON_PIN  3
#define NEXT_BUTTON_PIN  4
#define AUTO_BUTTON_PIN  5

// Knob readings (0 to 1023) at or below KNOB_OFF_AT turn the LEDs off, and
// readings at or above KNOB_FULL_AT are full brightness. The margins cover
// pots that never quite reach either end.
const uint16_t KNOB_OFF_AT  = 20;
const uint16_t KNOB_FULL_AT = 1000;

// How long Auto stays on each pattern.
const uint32_t AUTO_INTERVAL_MS = 3UL * 60 * 1000;

// -----------------------------------------------------------------------

extern CRGB leds[NUM_LEDS];
