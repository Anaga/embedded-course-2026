#include "pwm_pin.h"

namespace drivers {

PwmPin::PwmPin(uint8_t pin,
               uint8_t channel,
               uint32_t freq_hz,
               uint8_t  resolution)
    : _pin(pin),
      _channel(channel),
      _freq_hz(freq_hz),
      _resolution(resolution)
{
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    // Arduino Core 3.x: new single-call API.
    ledcAttach(_pin, _freq_hz, _resolution);
#else
    // Arduino Core 2.x: channel-based setup.
    ledcSetup(_channel, _freq_hz, _resolution);
    ledcAttachPin(_pin, _channel);
#endif
}

void PwmPin::write(uint32_t duty) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWrite(_pin, duty);
#else
    ledcWrite(_channel, duty);
#endif
}

uint8_t PwmPin::pin()     const { return _pin; }
uint8_t PwmPin::channel() const { return _channel; }

} // namespace drivers
