#pragma once

#include <stdint.h>

namespace drivers {

class PwmPin {
public:
    explicit PwmPin(uint8_t pin);
    void write(uint8_t value);

protected:
    uint8_t _pin;
};

} // namespace drivers