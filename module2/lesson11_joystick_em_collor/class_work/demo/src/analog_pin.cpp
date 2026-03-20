#include "analog_pin.h"

namespace drivers {

AnalogPin::AnalogPin(uint8_t pin)
    : _pin(pin)
{
    // No pinMode needed for ADC inputs on ESP32.
    // analogRead() handles the configuration internally.
}

uint16_t AnalogPin::read() const {
    return static_cast<uint16_t>(analogRead(_pin));
}

uint8_t AnalogPin::pin() const { return _pin; }

} // namespace drivers
