// The patterns that Back, Next, and Auto step through.
#pragma once

#include <stdint.h>

extern const uint8_t PATTERN_COUNT;

// Draws one frame of pattern `index` into leds[].
void drawPattern(uint8_t index, uint32_t now);
