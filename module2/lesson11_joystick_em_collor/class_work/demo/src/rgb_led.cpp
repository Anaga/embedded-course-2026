#include "rgb_led.h"

namespace drivers {

// Common-anode RGB LED: duty 255 = off, duty 0 = full brightness.
// Channels 0, 1, 2 are assigned to R, G, B respectively.

RgbLed::RgbLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b)
    : _r(pin_r, 0),
      _g(pin_g, 1),
      _b(pin_b, 2)
{}

void RgbLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
    // Invert because common-anode: 0 = full brightness, 255 = off.
    _r.write(255u - r);
    _g.write(255u - g);
    _b.write(255u - b);
}

void RgbLed::setColor(const common::em_color& c) {
    setColor(c.r, c.g, c.b);
}

void RgbLed::off() {
    _r.write(255);
    _g.write(255);
    _b.write(255);
}

} // namespace drivers
