#pragma once

#include <stdint.h>
#include "led.h"
#include "pwmPin.h"

namespace drivers {

class RgbLed : public Led {
public:
    RgbLed(uint8_t rPin,
           uint8_t gPin,
           uint8_t bPin);

    void setColor(uint8_t r,
                  uint8_t g,
                  uint8_t b);

    void off();

private:
    PwmPin _green;
    PwmPin _blue;
    // red channel is inherited from Led
};

} // namespace drivers