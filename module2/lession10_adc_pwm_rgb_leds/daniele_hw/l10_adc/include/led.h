#pragma once

#include <stdint.h>
#include "pwmPin.h"

namespace drivers {

class Led : public PwmPin {
public:
    Led(uint8_t pin, bool activeLow = false);

    void setBrightness(uint8_t value);

private:
    bool _activeLow;
};

} // namespace drivers