#pragma once

#include "pwm_pin.h"
#include "color.h"
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// RgbLed - controls a common-cathode RGB LED via three PWM channels.
//
// Active-high:
//   duty 0   = LED off
//   duty 255 = LED fully on
//
// Wiring used in this project:
//   Red   -> GPIO 3
//   Green -> GPIO 10
//   Blue  -> GPIO 2
// ---------------------------------------------------------------------------
class RgbLed {
public:
    RgbLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);

    // Set color from individual channel values (0..255 each)
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    // Set color from em_color
    void setColor(const em_color& c);

    // Turn LED off
    void off();

private:
    PwmPin _r;
    PwmPin _g;
    PwmPin _b;
};

} // namespace drivers

// Alias so main.cpp can use RgbLed directly
using drivers::RgbLed;