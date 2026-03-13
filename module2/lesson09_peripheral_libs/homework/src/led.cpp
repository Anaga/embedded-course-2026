#include "led.h"
#include <Arduino.h>

namespace drivers {

// TODO: Implement the Led constructor.
//
// Requirements:
//   - Call DigitalPin base constructor (OUTPUT mode)
//   - Call PwmPin base constructor (pass pin and channel)
//   - Initialise _duty, _fadeTarget, _fadeStepMs, _lastFadeMs to 0
//   - Call PwmPin::setDutyCycle(0) so the LED starts off
//
// Led::Led(uint8_t pin, uint8_t channel)
//     : DigitalPin(pin, ???)
//     , PwmPin(pin, ???)
//     , _duty(???)
//     ...
// {
// }


// TODO: Implement on(), off(), toggle().
//
// Hints:
//   - on()     -> full brightness (duty = 255)
//   - off()    -> duty = 0
//   - toggle() -> if _duty > 0, turn off; otherwise turn on
//   Use setDutyCycle() so _duty and _fadeTarget stay in sync.
//
// void Led::on()     { }
// void Led::off()    { }
// void Led::toggle() { }


// TODO: Implement setDutyCycle().
//
// Requirements:
//   - Store the new value in _duty
//   - Also update _fadeTarget (this cancels any active fade)
//   - Write the value to the hardware via PwmPin::setDutyCycle()
//
// void Led::setDutyCycle(uint8_t duty)
// {
// }


// The fade engine is already implemented for you.
// Study fadeTo() and update() carefully - you will need to
// understand the millis() pattern for the next assignment.

void Led::fadeTo(uint8_t target, uint32_t durationMs)
{
    if (target == _duty) {
        return;
    }

    _fadeTarget = target;

    uint8_t steps = (_duty < target)
                  ? (target - _duty)
                  : (_duty - target);

    _fadeStepMs = (steps > 0) ? (durationMs / steps) : 0;
    _lastFadeMs = millis();
}

void Led::update()
{
    if (_duty == _fadeTarget) {
        return;
    }

    if (millis() - _lastFadeMs < _fadeStepMs) {
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
