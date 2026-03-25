#include "PwmPin.h"
#include <Arduino.h>

namespace drivers {

static const uint32_t PWM_FREQ = 5000;
static const uint8_t PWM_RESOLUTION = 8;

PwmPin::PwmPin(uint8_t pin)
    : _pin(pin)
{
    ledcAttach(_pin, PWM_FREQ, PWM_RESOLUTION);
}

void PwmPin::write(uint8_t value) {
    ledcWrite(_pin, value);
}

} // namespace drivers