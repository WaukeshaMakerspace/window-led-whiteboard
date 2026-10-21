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

// ---- Control plate (see docs/controls.md and docs/wiring.md) -----------

#define KNOB_PIN         A0

#define WHITE_BUTTON_PIN 2
#define BACK_BUTTON_PIN  4
#define NEXT_BUTTON_PIN  7
#define AUTO_BUTTON_PIN  8

// Button lights. These must be PWM pins (3, 5, 9, 10, 11) so they can dim.
#define WHITE_LIGHT_PIN  3
#define BACK_LIGHT_PIN   5
#define NEXT_LIGHT_PIN   9
#define AUTO_LIGHT_PIN   10

// Button light levels, 0 to 255. Every light glows faintly so the plate is
// easy to find in the dark; the active one is bright.
const uint8_t LIGHT_GLOW = 8;
const uint8_t LIGHT_ON   = 160;

// How long Back and Next light up after a press.
const uint32_t LIGHT_FLASH_MS = 200;

// Knob readings (0 to 1023) at or below KNOB_OFF_AT turn the LEDs off, and
// readings at or above KNOB_FULL_AT are full brightness. The margins cover
// pots that never quite reach either end.
const uint16_t KNOB_OFF_AT  = 20;
const uint16_t KNOB_FULL_AT = 1000;

// How long Auto stays on each pattern.
const uint32_t AUTO_INTERVAL_MS = 3UL * 60 * 1000;

// -----------------------------------------------------------------------

extern CRGB leds[NUM_LEDS];
