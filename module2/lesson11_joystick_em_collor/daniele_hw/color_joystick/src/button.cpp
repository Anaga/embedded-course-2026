#include "button.h"
#include <Arduino.h>

namespace drivers {

Button::Button(uint8_t pin, uint32_t debounce_ms)
    : DigitalPin(pin, INPUT_PULLUP),
      _debounce_ms(debounce_ms),
      _state(false),
      _prev_state(false),
      _pressed_flag(false),
      _last_change_ms(0)
{
}

void Button::update() {
    // Active-low:
    // LOW  -> pressed
    // HIGH -> released
    bool raw = (digitalRead(_pin) == LOW);

    // Raw input changed: restart debounce timer
    if (raw != _prev_state) {
        _last_change_ms = millis();
        _prev_state = raw;
    }

    // If stable long enough, accept new debounced state
    if ((millis() - _last_change_ms) >= _debounce_ms) {
        if (raw != _state) {
            // Detect new press event
            if (raw) {
                _pressed_flag = true;
            }
            _state = raw;
        }
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