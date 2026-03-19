#pragma once
#include <stdint.h>
#include "analog_pin.h"

namespace drivers {
    
class Potentiometer : public AnalogPin {
public:
    explicit Potentiometer(uint8_t pin);
    
    uint16_t readRaw()     const;
    uint8_t  readPercent() const;
    int32_t  map(int32_t outMin,
                 int32_t outMax) const;
};

} // namespace drivers