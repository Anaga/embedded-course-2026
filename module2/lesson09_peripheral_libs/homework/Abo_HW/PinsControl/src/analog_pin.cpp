#include "analog_pin.h"
#include <Arduino.h>

namespace drivers {

AnalogPin::AnalogPin(uint8_t pin)
    : _pin(pin)
{
    // ADC pins do not need pinMode() on ESP32-C3 -
    // analogRead() configures them automatically.
}

uint16_t AnalogPin::read() const
{
    return static_cast<uint16_t>(analogRead(_pin));
}

float AnalogPin::readVolt() const
{
    return analogRead(_pin) / 4095.0f * 3.3f;
}

uint8_t AnalogPin::pin() const
{
    return _pin;
}

} // namespace drivers
