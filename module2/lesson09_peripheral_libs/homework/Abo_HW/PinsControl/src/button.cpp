#include "button.h"

namespace drivers {

Button::Button(uint8_t pin)
    : DigitalPin(pin, INPUT_PULLUP)   // base class calls pinMode()
    , _pressed(false)
    , _lastMs(0)
{
}

bool Button::isPressed() const
{
    return _pressed;
}

void IRAM_ATTR Button::onISR()
{
    uint32_t now = millis();

    // Ignore edges that arrive within the debounce window.
    if (now - _lastMs < DEBOUNCE_MS) {
        return;
    }

    // Active-low: pin reads LOW when button is pressed.
    _pressed = (digitalRead(_pin) == LOW);
    _lastMs  = now;
}

} // namespace drivers
