#pragma once
#include "digital_pin.h"
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// Button - debounced digital input, active-low with internal pull-up.
//
// Call update() once per loop iteration.
// isPressed()  - current stable state (true = held down).
// wasPressed() - returns true exactly once per press event, then resets.
// ---------------------------------------------------------------------------
class Button : public DigitalPin {
public:
    // pin        - GPIO number.
    // debounce_ms - minimum stable time in ms (default 20).
    explicit Button(uint8_t pin, uint32_t debounce_ms = 20);

    // Must be called every loop iteration.
    void update();

    bool isPressed()  const;
    bool wasPressed();

private:
    uint32_t _debounce_ms;
    bool     _state;
    bool     _prev_state;
    bool     _pressed_flag;
    uint32_t _last_change_ms;
};

} // namespace drivers
