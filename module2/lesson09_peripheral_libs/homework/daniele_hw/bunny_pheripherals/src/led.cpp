#include "led.h"
#include <Arduino.h>

namespace drivers {

// ------------------------------------------------------------
// Constructor
//
// The LED starts OFF.
// We initialize both base classes:
// - DigitalPin for GPIO role
// - PwmPin for PWM role
// ------------------------------------------------------------
Led::Led(uint8_t pin, uint8_t channel)
    : DigitalPin(pin, OUTPUT),
      PwmPin(pin, channel),
      _duty(0),
      _fadeTarget(0),
      _fadeStepMs(0),
      _lastFadeMs(0)
{
    PwmPin::setDutyCycle(0);
}

// ------------------------------------------------------------
// Turn LED fully ON.
// ------------------------------------------------------------
void Led::on()
{
    setDutyCycle(255);
}

// ------------------------------------------------------------
// Turn LED fully OFF.
// ------------------------------------------------------------
void Led::off()
{
    setDutyCycle(0);
}

// ------------------------------------------------------------
// Toggle LED between fully OFF and fully ON.
// ------------------------------------------------------------
void Led::toggle()
{
    if (_duty > 0) {
        off();
    } else {
        on();
    }
}

// ------------------------------------------------------------
// Set duty cycle immediately.
//
// This also updates the fade target so the LED does not keep
// following an older fade request.
// ------------------------------------------------------------
void Led::setDutyCycle(uint8_t duty)
{
    _duty = duty;
    _fadeTarget = duty;
    PwmPin::setDutyCycle(duty);
}

// ------------------------------------------------------------
// Start a non-blocking fade from current duty to target duty.
//
// durationMs is distributed across the number of PWM steps.
// ------------------------------------------------------------
void Led::fadeTo(uint8_t target, uint32_t durationMs)
{
    // If I am already fading (or already set) toward this target,
    // I do not need to restart the fade.
    if (target == _fadeTarget) {
        return;
    }

    _fadeTarget = target;

    uint8_t steps = (_duty < target) ? (target - _duty)
                                     : (_duty - target);

    _fadeStepMs = (steps > 0) ? (durationMs / steps) : 0;
    _lastFadeMs = millis();
}

// ------------------------------------------------------------
// Advance the fade engine.
//
// This function must be called repeatedly in loop().
// ------------------------------------------------------------
void Led::update()
{
    if (_duty == _fadeTarget) {
        return;
    }

    if ((millis() - _lastFadeMs) < _fadeStepMs) {
        return;
    }

    if (_duty < _fadeTarget) {
        _duty++;
    } else {
        _duty--;
    }

    PwmPin::setDutyCycle(_duty);
    _lastFadeMs = millis();
}

} // namespace drivers
