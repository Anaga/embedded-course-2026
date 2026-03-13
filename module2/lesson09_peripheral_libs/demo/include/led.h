#pragma once
#include "digital_pin.h"
#include "pwm_pin.h"
#include <stdint.h>

// ------------------------------------------------------------
// drivers::Led
//
// Inherits DigitalPin (for on/off/toggle) and PwmPin (for
// brightness control and fade).
//
// Non-blocking fade: call update() every loop() iteration.
// fadeTo() sets the target and duration; update() moves the
// duty cycle one step at a time using a millis() timer.
//
// Usage:
//   drivers::Led red(3, 0);   // GPIO3, LEDC channel 0
//   red.fadeTo(255, 1000);     // fade to full in 1 s
//   // in loop():
//   red.update();
// ------------------------------------------------------------

namespace drivers {

class Led : public DigitalPin, public PwmPin {
public:
    // pin     : GPIO number
    // channel : LEDC channel (must be unique per Led instance)
    Led(uint8_t pin, uint8_t channel);

    void on();
    void off();
    void toggle();

    // Immediately set brightness (0-255).
    void setDutyCycle(uint8_t duty);

    // Start a non-blocking fade to target brightness over
    // durationMs milliseconds. Call update() every loop().
    void fadeTo(uint8_t target, uint32_t durationMs);

    // Advance the fade by one step if the timer has elapsed.
    // Must be called every loop() iteration.
    void update();

private:
    uint8_t  _duty;
    uint8_t  _fadeTarget;
    uint32_t _fadeStepMs;
    uint32_t _lastFadeMs;
};

} // namespace drivers
