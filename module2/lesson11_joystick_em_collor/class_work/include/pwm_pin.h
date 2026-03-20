#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace drivers {

// ---------------------------------------------------------------------------
// PwmPin - single PWM output channel using the ESP32 LEDC peripheral.
// Supports both the legacy (Arduino Core 2.x) and the new (3.x) LEDC API.
// ---------------------------------------------------------------------------
class PwmPin {
public:
    // pin      - GPIO number.
    // channel  - LEDC channel (0-7). Each pin must use a unique channel.
    // freq_hz  - PWM frequency in Hz (default 5000).
    // resolution - bit resolution (default 8 -> values 0-255).
    PwmPin(uint8_t pin,
           uint8_t channel,
           uint32_t freq_hz    = 5000,
           uint8_t  resolution = 8);

    // Write duty cycle. Range: 0 to (2^resolution - 1).
    void write(uint32_t duty);

    uint8_t pin()     const;
    uint8_t channel() const;

private:
    uint8_t  _pin;
    uint8_t  _channel;
    uint32_t _freq_hz;
    uint8_t  _resolution;
};

} // namespace drivers
