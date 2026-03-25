#include "rgb_led.h"

namespace drivers {

RgbLed::RgbLed(uint8_t pin_r, uint8_t pin_g, uint8_t pin_b)
    : _r(pin_r, 0),
      _g(pin_g, 1),
      _b(pin_b, 2)
{
}

void RgbLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
    // Common-cathode: write PWM directly
    _r.write(r);
    _g.write(g);
    _b.write(b);
}

void RgbLed::setColor(const em_color& c) {
    setColor(c.r, c.g, c.b);
}

void RgbLed::off() {
    _r.write(0);
    _g.write(0);
    _b.write(0);
}

} // namespace drivers