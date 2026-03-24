#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// DigitalPin - base class for one GPIO configured with a fixed mode.
// Typical modes: INPUT, INPUT_PULLUP, OUTPUT
// ---------------------------------------------------------------------------
class DigitalPin {
public:
    DigitalPin(uint8_t pin, uint8_t mode);

    // Returns GPIO number
    uint8_t pin() const;

    // Returns configured pin mode
    uint8_t mode() const;

protected:
    uint8_t _pin;
    uint8_t _mode;
};

} // namespace drivers

// Alias so derived modules can use DigitalPin directly
using drivers::DigitalPin;