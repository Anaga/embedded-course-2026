#include "digital_pin.h"
#include <Arduino.h>

namespace drivers {

DigitalPin::DigitalPin(uint8_t pin, uint8_t mode)
    : _pin(pin), _mode(mode)
{
    // RAII: configure the GPIO direction immediately.
    pinMode(_pin, _mode);
}

DigitalPin::~DigitalPin()
{
    // Nothing to detach for a plain digital pin.
    // Derived classes (Button) override this if needed.
}

void DigitalPin::write(bool high)
{
    digitalWrite(_pin, high ? HIGH : LOW);
}

bool DigitalPin::read() const
{
    return digitalRead(_pin) == HIGH;
}

uint8_t DigitalPin::pin() const
{
    return _pin;
}

} // namespace drivers
