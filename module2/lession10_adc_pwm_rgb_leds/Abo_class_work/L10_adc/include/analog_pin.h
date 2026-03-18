#pragma once
#include <stdint.h>

// ------------------------------------------------------------
// drivers::AnalogPin
//
// Thin wrapper around analogRead().
// ESP32-C3 ADC is 12-bit (0-4095), reference 3.3 V.
// Only ADC1 channels are usable (GPIO0-GPIO4); ADC2 is shared
// with Wi-Fi and must be avoided.
// ------------------------------------------------------------

namespace drivers {

class AnalogPin {
public:
    explicit AnalogPin(uint8_t pin);

    // Raw 12-bit ADC reading (0 - 4095).
    uint16_t read()     const;

    // Converted to volts (0.0 - 3.3 V).
    float    readVolt() const;

    uint8_t  pin()      const;

    AnalogPin(const AnalogPin&)            = delete;
    AnalogPin& operator=(const AnalogPin&) = delete;

private:
    uint8_t _pin;
};

} // namespace drivers
