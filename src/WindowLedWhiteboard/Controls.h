// The control plate: a brightness knob and momentary buttons.
#pragma once

#include <Arduino.h>

// A momentary button wired between its pin and ground. Uses the Nano's
// internal pull-up, so no resistor is needed.
class Button {
 public:
  explicit Button(uint8_t pin) : pin_(pin) {}
  void begin();
  // True once per press, after the contacts stop bouncing.
  bool pressed(uint32_t now);

 private:
  uint8_t pin_;
  bool stableDown_ = false;
  bool lastReadDown_ = false;
  uint32_t lastChangeMs_ = 0;
};

// A 10k linear potentiometer: outer legs to 5 V and ground, middle leg to
// the pin.
class Knob {
 public:
  explicit Knob(uint8_t pin) : pin_(pin) {}
  void begin();
  // Brightness from 0 (off) to 255.
  uint8_t brightness();

 private:
  uint8_t pin_;
  uint16_t filtered_ = 0;  // 8x the smoothed reading
  uint16_t settled_ = 0;   // smoothed reading after hysteresis, 0 to 1023
};
