#pragma once
#include "digital_pin.h"
#include <stdint.h>
#include <Arduino.h>

// ------------------------------------------------------------
// drivers::Button
//
// Derived from DigitalPin (INPUT_PULLUP, active-low).
// Uses an ISR for edge detection + software debounce.
//
// Usage:
//   drivers::Button btn(0);
//   void IRAM_ATTR isr() { btn.onISR(); }
//   attachInterrupt(0, isr, CHANGE);
//   // in loop():
//   if (btn.isPressed()) { ... }
// ------------------------------------------------------------

namespace drivers {

class Button : public DigitalPin {
public:
    explicit Button(uint8_t pin);

    // Returns true while the button is held down.
    // Updated by onISR() - safe to call from loop().
    bool isPressed() const;

    // Call this from the ISR attached to this button's pin.
    // Handles debounce internally.
    void IRAM_ATTR onISR();

    static const uint32_t DEBOUNCE_MS = 50;

private:
    volatile bool     _pressed;
    volatile uint32_t _lastMs;
};

} // namespace drivers
