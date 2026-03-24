#include "analog_pin.h"

namespace drivers {

AnalogPin::AnalogPin(uint8_t pin)
    : _pin(pin)
{
    // On ESP32, analogRead() configures the ADC pin automatically.
    // No explicit pinMode() is required here.
}

uint16_t AnalogPin::read() const {
    return static_cast<uint16_t>(analogRead(_pin));
}

uint8_t AnalogPin::pin() const {
    return _pin;
}

} // namespace drivers