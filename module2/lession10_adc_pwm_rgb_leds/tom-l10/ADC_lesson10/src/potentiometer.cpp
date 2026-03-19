#include "potentiometer.h"
#include <Arduino.h>

namespace drivers {
    
Potentiometer::Potentiometer(uint8_t pin): AnalogPin(pin) {}

uint16_t Potentiometer::readRaw() const {
    return analogRead(_pin);
}
uint8_t Potentiometer::readPercent() const {
    return (uint8_t)(readRaw() * 100UL/ 4095UL);
}
int32_t Potentiometer::map(
        int32_t outMin,
        int32_t outMax) const {
    return ::map(readRaw(),
                0, 4095,
                outMin, outMax);
}

} // namespace drivers
