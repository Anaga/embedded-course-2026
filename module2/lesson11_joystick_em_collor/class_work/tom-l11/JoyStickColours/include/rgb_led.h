#pragma once
#include "pwm_pin.h"
#include "color.h"
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// RgbLed - controls a common-anode RGB LED via three PWM channels.
//
// Active-low: duty 255 = LED off, duty 0 = LED fully on.
// Wiring used in this course:
//   Red   -> GPIO 3  (LEDC channel 0)
//   Green -> GPIO 10 (LEDC channel 1)
//   Blue  -> GPIO 2  (LEDC channel 2)
// ---------------------------------------------------------------------------
class RgbLed {
public:
    RgbLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b);

    // Set color from individual channel values (0-255 each).
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    // Set color from an em_color value.
    void setColor(const common::em_color& c);

    // Turn all channels off.
    void off();

private:
    PwmPin _r;
    PwmPin _g;
    PwmPin _b;
};

} // namespace drivers
