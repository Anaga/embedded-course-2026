#include "led.h"

namespace drivers {

Led::Led(uint8_t pin, bool activeLow)
    : PwmPin(pin), _activeLow(activeLow) {}

void Led::setBrightness(uint8_t value) {
    if (_activeLow) {
        value = 255 - value;
    }
    write(value);
}

} // namespace drivers