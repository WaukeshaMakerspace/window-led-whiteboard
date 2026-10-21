#include "Controls.h"

#include "Config.h"

namespace {

const uint32_t DEBOUNCE_MS = 25;

// Ignore knob changes smaller than this (out of 1023), so a knob at rest
// can't flicker the whole window between two brightness steps.
const uint16_t KNOB_HYSTERESIS = 4;

}  // namespace

void Button::begin() {
  pinMode(pin_, INPUT_PULLUP);
}

bool Button::pressed(uint32_t now) {
  bool down = digitalRead(pin_) == LOW;
  if (down != lastReadDown_) {
    lastReadDown_ = down;
    lastChangeMs_ = now;
  }
  if (down == stableDown_ || now - lastChangeMs_ < DEBOUNCE_MS) return false;
  stableDown_ = down;
  return down;
}

void Light::set(bool on) {
  analogWrite(pin_, on ? LIGHT_ON : LIGHT_GLOW);
}

void Knob::begin() {
  uint16_t reading = analogRead(pin_);
  filtered_ = reading << 3;
  settled_ = reading;
}

uint8_t Knob::brightness() {
  // Exponential moving average to smooth out reading noise.
  filtered_ = filtered_ - (filtered_ >> 3) + analogRead(pin_);
  uint16_t reading = filtered_ >> 3;
  if (reading > settled_ + KNOB_HYSTERESIS || reading + KNOB_HYSTERESIS < settled_) {
    settled_ = reading;
  }

  if (settled_ <= KNOB_OFF_AT) return 0;

  // Square the position so most of the dial's travel goes to the dim end,
  // which is where eyes notice changes.
  uint8_t position = map(min(settled_, KNOB_FULL_AT), KNOB_OFF_AT, KNOB_FULL_AT, 1, 255);
  return (uint16_t(position) * position + 255) >> 8;
}
