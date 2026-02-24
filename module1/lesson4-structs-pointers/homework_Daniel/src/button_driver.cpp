/**
 * @file button_driver.cpp
 * @brief Debounced button driver implementation.
 *
 * Lesson 4 - Structs and Pointers to Structs
 * Embedded Systems Course 2026
 *
 * Debounce algorithm
 * ------------------
 * Every call to button_update() reads the raw pin level.
 * If the raw level differs from the last raw level, the timestamp is
 * recorded. If the raw level stays different from the stable state for
 * at least debounce_ms milliseconds, the stable state is updated and
 * (if it was a press transition) _event_pending is set.
 *
 *   raw pin ──────┐       ┌──────────────────────
 *                 └───────┘   bounce zone
 *
 *   stable  ──────────────────────────────────────┐
 *                         |<-- debounce_ms ------->|
 *                                                  v confirmed press
 */

#include "button_driver.h"
#include <Arduino.h>

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */

/** Read the raw logical level from the pin (before debounce). */
static bool read_raw(const Button_t *b)
{
    bool physical = (digitalRead(b->pin) == HIGH);
    return b->active_high ? physical : !physical;
}

/* --------------------------------------------------------------------------
 * API implementation
 * -------------------------------------------------------------------------- */

void button_init(Button_t *b)
{
    uint8_t mode = b->active_high ? INPUT : INPUT_PULLUP;
    pinMode(b->pin, mode);

    /* Capture initial state so first button_update() has a valid baseline */
    bool initial        = read_raw(b);
    b->_last_raw        = initial;
    b->_stable_state    = initial;
    b->_last_change     = millis();
    b->_event_pending   = false;
}

void button_update(Button_t *b)
{
    bool raw = read_raw(b);
    uint32_t now = millis();

    if (raw != b->_last_raw) {
        /* Level changed — restart the debounce timer */
        b->_last_raw    = raw;
        b->_last_change = now;
        return;
    }

    /* Raw level has been stable for debounce_ms */
    if ((now - b->_last_change) >= b->debounce_ms) {
        if (raw != b->_stable_state) {
            b->_stable_state = raw;
            /* Only fire an event on the press edge (inactive -> active) */
            if (raw == true) {
                b->_event_pending = true;
            }
        }
    }
}

bool button_pressed(Button_t *b)
{
    button_update(b);

    if (b->_event_pending) {
        b->_event_pending = false;
        return true;
    }
    return false;
}

bool button_state(const Button_t *b)
{
    return b->_stable_state;
}

void button_init_array(Button_t *buttons, uint8_t count)
{
    for (uint8_t i = 0; i < count; i++) {
        button_init(&buttons[i]);
    }
}
