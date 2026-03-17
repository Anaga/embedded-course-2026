#include "pwm_pin.h"
#include <Arduino.h>

namespace drivers {

// ------------------------------------------------------------
// Constructor
//
// On ESP32 Arduino core 3.x, LEDC API changed.
// We now use ledcAttachChannel(pin, freq, resolution, channel).
// ------------------------------------------------------------
PwmPin::PwmPin(uint8_t pin, uint8_t channel, uint32_t freq, uint8_t bits)
    : _pin(pin),
      _channel(channel),
      _freq(freq),
      _bits(bits)
{
    ledcAttachChannel(_pin, _freq, _bits, _channel);
}

// ------------------------------------------------------------
// Destructor
//
// Detach the pin from LEDC when the object is destroyed.
// ------------------------------------------------------------
PwmPin::~PwmPin()
{
    ledcDetach(_pin);
}

// ------------------------------------------------------------
// Set PWM duty cycle.
//
// With Arduino core 3.x, ledcWrite() uses the pin.
// ------------------------------------------------------------
void PwmPin::setDutyCycle(uint8_t duty)
{
    ledcWrite(_pin, duty);
}

} // namespace drivers
