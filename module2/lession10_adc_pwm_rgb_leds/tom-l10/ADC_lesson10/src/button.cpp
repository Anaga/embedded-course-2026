#include "button.h"
#include <Arduino.h>

namespace drivers {

// impliments constructor i think
Button::Button(uint8_t pin)
    : DigitalPin(pin, INPUT_PULLUP)   // base class calls pinMode()
    , _pressed(false)
    , _lastMs(0)
{
// im pretty lost rn ngl
}

bool Button::isPressed() const // here's isPressed, checkes the press state, such useful comment ik
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
