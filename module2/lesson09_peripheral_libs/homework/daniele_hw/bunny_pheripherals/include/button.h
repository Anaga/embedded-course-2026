#pragma once

#include "digital_pin.h"
#include <stdint.h>

namespace drivers {

// Active-low button driver using INPUT_PULLUP.
// LOW  -> pressed
// HIGH -> released
class Button : public DigitalPin {
public:
    explicit Button(uint8_t pin);

    // Return the last debounced logical state.
    bool isPressed() const;

    // Called by the external ISR wrapper.
    void onISR();

    static const uint32_t DEBOUNCE_MS = 80;

private:
    volatile bool _pressed;
    volatile uint32_t _lastMs;
};

} // namespace drivers