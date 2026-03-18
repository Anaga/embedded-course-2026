#pragma once

#include <stdint.h>

namespace drivers {

// ------------------------------------------------------------
// PWM pin driver
//
// This class wraps ESP32 LEDC PWM functionality.
// It is used as a low-level driver for brightness control.
// ------------------------------------------------------------
class PwmPin {
public:
    PwmPin(uint8_t pin, uint8_t channel, uint32_t freq = 5000, uint8_t bits = 8);
    virtual ~PwmPin();

    void setDutyCycle(uint8_t duty);

protected:
    uint8_t _pin;
    uint8_t _channel;
    uint32_t _freq;
    uint8_t _bits;
};

} // namespace drivers