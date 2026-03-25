#pragma once

#include <stdint.h>

namespace drivers {

class AnalogPin {
public:
    explicit AnalogPin(uint8_t pin)
        : _pin(pin) {}

protected:
    uint8_t _pin;
};

} // namespace drivers