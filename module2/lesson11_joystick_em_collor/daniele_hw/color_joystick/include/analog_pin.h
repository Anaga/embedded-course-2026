#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// AnalogPin - wraps a single ADC input pin.
// read() returns raw ADC value in range 0..4095.
// ---------------------------------------------------------------------------
class AnalogPin {
public:
    explicit AnalogPin(uint8_t pin);

    // Returns raw ADC value.
    uint16_t read() const;

    // Returns GPIO number associated with this ADC pin.
    uint8_t pin() const;

private:
    uint8_t _pin;
};

} // namespace drivers

// Alias so other modules can use AnalogPin directly
using drivers::AnalogPin;