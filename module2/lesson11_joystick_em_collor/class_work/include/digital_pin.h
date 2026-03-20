#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace drivers {

// ---------------------------------------------------------------------------
// DigitalPin - base class for a single GPIO pin with a fixed direction.
// ---------------------------------------------------------------------------
class DigitalPin {
public:
    explicit DigitalPin(uint8_t pin, uint8_t mode);

    uint8_t pin()  const;
    uint8_t mode() const;

protected:
    uint8_t _pin;
    uint8_t _mode;
};

} // namespace drivers
