/**
 * @file Led.h
 * @brief LED driver class with active-high / active-low support.
 *
 * Lesson 06 — Classes, Objects, Encapsulation
 * Embedded Systems Course 2026
 * Hardware: ESP32-C3 Super Mini
 */
#pragma once

#include <stdint.h>

class Led {
private:
    uint8_t pin_;
    bool    active_high_;
    bool    state_;

    /**
     * @brief Write the physical GPIO level based on logical state.
     */
    void writeHardware();

public:
    /**
     * @brief Construct a new Led object.
     *
     * Configures the pin as OUTPUT and turns the LED off.
     *
     * @param pin         GPIO pin number
     * @param active_high true = HIGH turns LED on, false = LOW turns LED on
     */
    Led(uint8_t pin, bool active_high = true);

    /**
     * @brief Destructor — turns the LED off.
     */
    ~Led();

    /** @brief Turn the LED on. */
    void on();

    /** @brief Turn the LED off. */
    void off();

    /** @brief Toggle the LED state. */
    void toggle();

    /** @brief Return true if the LED is currently on. */
    bool isOn() const;

    /** @brief Return the GPIO pin number. */
    uint8_t pin() const;
};
