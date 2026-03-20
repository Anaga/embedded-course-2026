#include "button.h"

namespace drivers {

Button::Button(uint8_t pin, uint32_t debounce_ms)
    : DigitalPin(pin, INPUT_PULLUP),
      _debounce_ms(debounce_ms),
      _state(false),
      _prev_state(false),
      _pressed_flag(false),
      _last_change_ms(0)
{}

void Button::update() {
    // Active-low: LOW means button is pressed.
    bool raw = (digitalRead(_pin) == LOW);

    if (raw != _prev_state) {
        _last_change_ms = millis();
        _prev_state = raw;
    }

    if ((millis() - _last_change_ms) >= _debounce_ms) {
        if (raw && !_state) {
            // Transition: released -> pressed
            _pressed_flag = true;
        }
        _state = raw;
    }
}

bool Button::isPressed() const {
    return _state;
}

bool Button::wasPressed() {
    if (_pressed_flag) {
        _pressed_flag = false;
        return true;
    }
    return false;
}

} // namespace drivers
