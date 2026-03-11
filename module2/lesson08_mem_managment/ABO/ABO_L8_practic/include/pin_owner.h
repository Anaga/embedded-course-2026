// pin_owner.h
// Lesson 8: RAII demonstration class
//
// PinOwner wraps a single GPIO pin. The constructor configures the pin
// (acquires the resource), and the destructor resets it to a safe state
// (releases the resource). The compiler guarantees the destructor runs
// when the object goes out of scope -- even on early return.

#ifndef PIN_OWNER_H
#define PIN_OWNER_H

#include <Arduino.h>
#include <stdint.h>

class PinOwner {
    uint8_t pin_;
    bool    active_low_;

public:
    // Constructor: configure the pin and set it to OFF.
    // For active-low LEDs (common anode), OFF means HIGH.
    // For active-high LEDs, OFF means LOW.
    PinOwner(uint8_t pin, bool active_low = false)
        : pin_(pin), active_low_(active_low)
    {
        pinMode(pin_, OUTPUT);
        off();
        Serial.printf("[PinOwner] Acquired pin %u (active_low=%s)\n",
                      pin_, active_low_ ? "true" : "false");
    }

    // Destructor: turn LED off and release pin to INPUT (safe/high-Z).
    // This runs automatically when the object leaves scope.
    ~PinOwner() {
        off();
        pinMode(pin_, INPUT);
        Serial.printf("[PinOwner] Released pin %u\n", pin_);
    }

    // Turn the LED on
    void on() {
        digitalWrite(pin_, active_low_ ? LOW : HIGH);
    }

    // Turn the LED off
    void off() {
        digitalWrite(pin_, active_low_ ? HIGH : LOW);
    }

    // Set LED to a specific state (true = on)
    void set(bool state) {
        if (state) {
            on();
        } else {
            off();
        }
    }

    // Toggle LED and return the new state
    bool toggle() {
        bool current = (digitalRead(pin_) == (active_low_ ? LOW : HIGH));
        set(!current);
        return !current;
    }

    // Read the current pin number (useful for diagnostics)
    uint8_t pin() const { return pin_; }

    // -- Prevent copying (pin is a unique resource) --
    PinOwner(const PinOwner&)            = delete;
    PinOwner& operator=(const PinOwner&) = delete;
};

#endif // PIN_OWNER_H
