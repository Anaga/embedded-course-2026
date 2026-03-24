#include "digital_pin.h"

namespace drivers {

DigitalPin::DigitalPin(uint8_t pin, uint8_t mode)
    : _pin(pin),
      _mode(mode)
{
    pinMode(_pin, _mode);
}

uint8_t DigitalPin::pin() const {
    return _pin;
}

uint8_t DigitalPin::mode() const {
    return _mode;
}

} // namespace drivers