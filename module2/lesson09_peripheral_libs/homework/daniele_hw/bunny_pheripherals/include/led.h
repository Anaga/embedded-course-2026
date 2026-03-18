#pragma once

#include "digital_pin.h"
#include "pwm_pin.h"
#include <stdint.h>

namespace drivers {

// ------------------------------------------------------------
// LED driver
//
// This class combines digital GPIO logic and PWM brightness
// control. It also supports a simple non-blocking fade.
//
// fadeTo() starts a fade.
// update() must be called periodically inside loop().
// ------------------------------------------------------------
class Led : public DigitalPin, public PwmPin {
public:
    Led(uint8_t pin, uint8_t channel);

    void on();
    void off();
    void toggle();

    void setDutyCycle(uint8_t duty);

    void fadeTo(uint8_t target, uint32_t durationMs);
    void update();

private:
    uint8_t _duty;
    uint8_t _fadeTarget;
    uint32_t _fadeStepMs;
    uint32_t _lastFadeMs;
};

} // namespace drivers