/**
 * @file Button.h
 * @brief Button driver class with software debounce.
 *
 * Lesson 06 — Classes, Objects, Encapsulation
 * Embedded Systems Course 2026
 * Hardware: ESP32-C3 Super Mini
 */
#pragma once

#include <stdint.h>

class Button {
private:
    uint8_t  pin_;
    bool     active_high_;
    uint16_t debounce_ms_;

    /* Internal state — managed by update() */
    bool     last_raw_;
    bool     stable_state_;
    uint32_t last_change_;
    bool     event_pending_;

    /**
     * @brief Read the physical pin and return the logical state.
     *
     * If active_high_ is false, the reading is inverted so that
     * "pressed" always returns true regardless of wiring polarity.
     */
    bool readRaw() const;

public:
    /**
     * @brief Construct a new Button object.
     *
     * Configures the pin as INPUT (or INPUT_PULLUP if active_high is false)
     * and captures the initial state.
     *
     * @param pin         GPIO pin number
     * @param active_high true = HIGH when pressed, false = LOW when pressed
     * @param debounce_ms debounce window in milliseconds (default 50)
     */
    Button(uint8_t pin, bool active_high = false, uint16_t debounce_ms = 50);

    /**
     * @brief Poll the button and update the debounce state machine.
     *
     * Call this at least once per loop() iteration.
     */
    void update();

    /**
     * @brief Return true exactly once per press event.
     *
     * Calls update() internally, so you do not need to call both.
     */
    bool pressed();

    /**
     * @brief Return the current stable (debounced) state.
     */
    bool state() const;

    /** @brief Return the GPIO pin number. */
    uint8_t pin() const;
};
