#include "pwm_pin.h"

namespace drivers {

PwmPin::PwmPin(uint8_t pin,
               uint8_t channel,
               uint32_t freq_hz,
               uint8_t resolution)
    : _pin(pin),
      _channel(channel),
      _freq_hz(freq_hz),
      _resolution(resolution)
{
    // ESP32 Arduino Core 3.x API
    ledcAttach(_pin, _freq_hz, _resolution);
}

void PwmPin::write(uint32_t duty) {
    // ESP32 Arduino Core 3.x API
    ledcWrite(_pin, duty);
}

uint8_t PwmPin::pin() const {
    return _pin;
}

uint8_t PwmPin::channel() const {
    return _channel;
}

uint32_t PwmPin::frequency() const {
    return _freq_hz;
}

uint8_t PwmPin::resolution() const {
    return _resolution;
}

} // namespace drivers