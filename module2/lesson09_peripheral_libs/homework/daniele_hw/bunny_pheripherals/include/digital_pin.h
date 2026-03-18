#pragma once
#include <stdint.h>

// ------------------------------------------------------------
// drivers::DigitalPin
//
// Base class for any peripheral that owns a single GPIO pin.
// Applies RAII: pinMode() is called in the constructor so the
// pin is ready the moment the object exists.
// ------------------------------------------------------------

namespace drivers {

class DigitalPin {
public:
    // Initialise the pin and configure its direction.
    // mode: INPUT, OUTPUT, INPUT_PULLUP (Arduino constants)
    explicit DigitalPin(uint8_t pin, uint8_t mode);

    // Virtual destructor so derived-class destructors run
    // correctly when deleting through a base pointer.
    virtual ~DigitalPin();

    // Write a digital level to the pin (OUTPUT mode only).
    void write(bool high);

    // Read the current digital level of the pin.
    bool read() const;

    // Return the GPIO number this object owns.
    uint8_t pin() const;

    // Disable copying: two objects must not own the same pin.
    DigitalPin(const DigitalPin&)            = delete;
    DigitalPin& operator=(const DigitalPin&) = delete;

protected:
    uint8_t _pin;
    uint8_t _mode;
};

} // namespace drivers
