#pragma once
#include <stdint.h>

// ------------------------------------------------------------
// drivers::PwmPin
//
// Wrapper around the ESP32 LEDC peripheral (Arduino Core 2.x
// API: ledcSetup / ledcAttachPin / ledcWrite).
//
// Each PwmPin owns one LEDC channel for its lifetime.
// The caller is responsible for passing a unique channel number
// (0-5 on ESP32-C3).
// ------------------------------------------------------------

namespace drivers {

class PwmPin {
public:
    // pin     : GPIO number
    // channel : LEDC channel (0-5)
    // freq    : PWM frequency in Hz (default 5000)
    // bits    : resolution in bits (default 8 -> 0-255)
    PwmPin(uint8_t  pin,
           uint8_t  channel,
           uint32_t freq = 5000,
           uint8_t  bits = 8);

    // Detaches the pin from the LEDC channel on destruction.
    virtual ~PwmPin();

    // Set duty cycle. Range: 0 - (2^bits - 1).
    // With default 8-bit resolution: 0 = off, 255 = full on.
    void setDutyCycle(uint8_t duty);

    PwmPin(const PwmPin&)            = delete;
    PwmPin& operator=(const PwmPin&) = delete;

private:
    uint8_t  _pin;
    uint8_t  _channel;
    uint32_t _freq;
    uint8_t  _bits;
};

} // namespace drivers
