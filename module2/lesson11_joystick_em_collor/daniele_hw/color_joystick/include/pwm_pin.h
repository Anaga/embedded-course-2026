#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// PwmPin - single PWM output using ESP32 LEDC
//
// Supports both:
// - Arduino ESP32 Core 2.x  -> channel-based API
// - Arduino ESP32 Core 3.x  -> pin-based API
//
// Typical use:
//   PwmPin led_r(3, 0);
//   led_r.write(128);   // 50% duty with 8-bit resolution
// ---------------------------------------------------------------------------
class PwmPin {
public:
    PwmPin(uint8_t pin,
           uint8_t channel,
           uint32_t freq_hz = 5000,
           uint8_t resolution = 8);

    // Write PWM duty cycle
    // For 8-bit resolution: 0..255
    void write(uint32_t duty);

    uint8_t pin() const;
    uint8_t channel() const;
    uint32_t frequency() const;
    uint8_t resolution() const;

private:
    uint8_t  _pin;
    uint8_t  _channel;
    uint32_t _freq_hz;
    uint8_t  _resolution;
};

} // namespace drivers

// Alias so other files can use PwmPin directly
using drivers::PwmPin;