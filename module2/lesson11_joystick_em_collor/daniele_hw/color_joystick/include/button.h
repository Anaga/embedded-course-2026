#pragma once

#include "digital_pin.h"
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// Button - debounced digital input
//
// Active-low with internal pull-up:
//   released -> HIGH
//   pressed  -> LOW
//
// Call update() once per loop iteration.
// isPressed()  -> true while button is held down
// wasPressed() -> true once per new press event
// ---------------------------------------------------------------------------
class Button : public DigitalPin {
public:
    explicit Button(uint8_t pin, uint32_t debounce_ms = 20);

    // Update internal debounced state
    void update();

    // Current stable state
    bool isPressed() const;

    // Edge event: returns true once per press
    bool wasPressed();

private:
    uint32_t _debounce_ms;
    bool     _state;          // debounced stable state
    bool     _prev_state;     // last raw sampled state
    bool     _pressed_flag;   // latched on release->press transition
    uint32_t _last_change_ms; // timestamp of last raw change
};

} // namespace drivers

// Alias so other files can use Button directly if needed
using drivers::Button;