#include "pwm_pin.h"
#include <Arduino.h>

namespace drivers {

PwmPin::PwmPin(uint8_t pin, uint8_t channel, uint32_t freq, uint8_t bits)
    : _pin(pin), _channel(channel), _freq(freq), _bits(bits)
{
    // RAII: configure the LEDC channel and attach the pin.
    // Arduino Core 2.x API (compatible with ESP32-C3).
    ledcSetup(_channel, _freq, _bits);
    ledcAttachPin(_pin, _channel);
}

PwmPin::~PwmPin()
{
    ledcDetachPin(_pin);
}

void PwmPin::setDutyCycle(uint8_t duty)
{
    ledcWrite(_channel, duty);
}

} // namespace drivers
