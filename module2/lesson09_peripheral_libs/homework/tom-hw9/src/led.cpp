#include "led.h"
#include <Arduino.h>

namespace drivers {

Led::Led(uint8_t pin, uint8_t channel)
    : DigitalPin(pin, OUTPUT)    // base: pinMode(pin, OUTPUT)
    , PwmPin(pin, channel)       // base: ledcSetup + ledcAttachPin
    , _duty(0)
    , _fadeTarget(0)
    , _fadeStepMs(0)
    , _lastFadeMs(0) // initialiser list?? me thinks
{
    // Start with LED off.
    PwmPin::setDutyCycle(0);
}

void Led::on()
{
    setDutyCycle(255);
}

void Led::off()
{
    setDutyCycle(0);
}

// is using the cycle so _duty & _fade Target are untouched 
void Led::toggle()
{
    setDutyCycle(_duty > 0 ? 0 : 255);
}

// storing value on both if i understand it right
void Led::setDutyCycle(uint8_t duty)
{
    _duty       = duty;
    _fadeTarget = duty;           // cancel any active fade
    PwmPin::setDutyCycle(_duty);
}

void Led::fadeTo(uint8_t target, uint32_t durationMs)
{
    if (target == _duty) {
        return;
    }

    _fadeTarget = target;

    // Divide the total duration evenly across the number of
    // steps needed to reach the target value.
    uint8_t steps = (_duty < target)
                  ? (target - _duty)
                  : (_duty - target);

    _fadeStepMs = (steps > 0) ? (durationMs / steps) : 0;
    _lastFadeMs = millis();
}

void Led::update()
{
    // Nothing to do if already at target.
    if (_duty == _fadeTarget) {
        return;
    }

    // Wait until the next step interval has elapsed.
    if (millis() - _lastFadeMs < _fadeStepMs) {
        return;
    }

    // Advance one step toward the target.
    if (_duty < _fadeTarget) {
        _duty++;
    } else {
        _duty--;
    }

    PwmPin::setDutyCycle(_duty);
    _lastFadeMs = millis();
}

} // namespace drivers
