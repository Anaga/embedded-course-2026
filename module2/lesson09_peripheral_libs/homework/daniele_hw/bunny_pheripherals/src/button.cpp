#include "button.h"
#include <Arduino.h>

namespace drivers {

Button::Button(uint8_t pin)
    : DigitalPin(pin, INPUT_PULLUP),
      _pressed(false),
      _lastMs(0)
{
    _pressed = (digitalRead(_pin) == LOW);
}

bool Button::isPressed() const
{
    return _pressed;
}

void Button::onISR()
{
    uint32_t now = millis();

    if ((now - _lastMs) < DEBOUNCE_MS) {
        return;
    }

    _pressed = (digitalRead(_pin) == LOW);
    _lastMs = now;
}

} // namespace drivers