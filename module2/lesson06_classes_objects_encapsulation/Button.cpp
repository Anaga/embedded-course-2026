/**
 * @file Button.cpp
 * @brief Button driver class implementation.
 *
 * Lesson 06 — Classes, Objects, Encapsulation
 * Embedded Systems Course 2026
 */
#include "Button.h"
#include <Arduino.h>

/* --------------------------------------------------------------------------
 * Private helpers
 * -------------------------------------------------------------------------- */

bool Button::readRaw() const
{
    bool physical = (digitalRead(pin_) == HIGH);
    return active_high_ ? physical : !physical;
}

/* --------------------------------------------------------------------------
 * Constructor
 * -------------------------------------------------------------------------- */

Button::Button(uint8_t pin, bool active_high, uint16_t debounce_ms)
    : pin_(pin)
    , active_high_(active_high)
    , debounce_ms_(debounce_ms)
    , last_raw_(false)
    , stable_state_(false)
    , last_change_(0)
    , event_pending_(false)
{
    uint8_t mode = active_high_ ? INPUT : INPUT_PULLUP;
    pinMode(pin_, mode);

    /* Capture initial state so the first update() has a valid baseline */
    bool initial    = readRaw();
    last_raw_       = initial;
    stable_state_   = initial;
    last_change_    = millis();
}

/* --------------------------------------------------------------------------
 * Public methods
 * -------------------------------------------------------------------------- */

void Button::update()
{
    bool     raw = readRaw();
    uint32_t now = millis();

    if (raw != last_raw_) {
        /* Level changed — restart the debounce timer */
        last_raw_    = raw;
        last_change_ = now;
        return;
    }

    /* Raw level has been stable for debounce_ms_ */
    if ((now - last_change_) >= debounce_ms_) {
        if (raw != stable_state_) {
            stable_state_ = raw;
            /* Fire an event only on the press edge (inactive -> active) */
            if (raw == true) {
                event_pending_ = true;
            }
        }
    }
}

bool Button::pressed()
{
    update();

    if (event_pending_) {
        event_pending_ = false;
        return true;
    }
    return false;
}

bool Button::state() const
{
    return stable_state_;
}

uint8_t Button::pin() const
{
    return pin_;
}
