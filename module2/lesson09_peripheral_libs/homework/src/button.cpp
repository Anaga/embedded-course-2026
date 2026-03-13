#include "button.h"
#include <Arduino.h>

namespace drivers {

// TODO: Implement the Button constructor.
//
// Requirements:
//   - Call the DigitalPin base constructor with the correct mode
//     (hint: buttons are active-low)
//   - Initialise _pressed to false and _lastMs to 0
//
// Button::Button(uint8_t pin)
//     : DigitalPin(pin, ???)
//     , _pressed(???)
//     , _lastMs(???)
// {
// }


// TODO: Implement isPressed().
//
// This method should return the current state of _pressed.
// It does NOT read the GPIO directly - the ISR already did that.
//
// bool Button::isPressed() const
// {
// }


// The ISR is already implemented for you.
// Study how debounce works before writing your own code above.
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
