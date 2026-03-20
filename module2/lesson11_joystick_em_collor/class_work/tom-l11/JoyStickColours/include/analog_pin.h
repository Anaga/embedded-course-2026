#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace drivers {

// ---------------------------------------------------------------------------
// AnalogPin - wraps a single ADC input pin.
// read() returns raw 12-bit ADC value: 0-4095.
// ---------------------------------------------------------------------------
class AnalogPin {
public:
    explicit AnalogPin(uint8_t pin);

    // Returns raw ADC value 0-4095.
    uint16_t read() const;

    uint8_t pin() const;

private:
    uint8_t _pin;
};

} // namespace drivers
