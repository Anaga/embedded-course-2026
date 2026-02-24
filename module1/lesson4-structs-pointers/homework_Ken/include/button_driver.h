#pragma once

/**
 * @file button_driver.h
 * @brief Debounced button input using a struct.
 *
 * Lesson 4 - Structs and Pointers to Structs
 * Embedded Systems Course 2026
 *
 * Demonstrates how a struct can hold both configuration AND state,
 * enabling stateful, debounced input without global variables.
 *
 * Usage:
 *   Button_t btn = {
 *       .pin         = 9,
 *       .active_high = false,   // active-low (pulled to GND when pressed)
 *       .debounce_ms = 50,
 *   };
 *   button_init(&btn);
 *
 *   // In loop():
 *   if (button_pressed(&btn)) {
 *       // fires once per press, debounced
 *   }
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * Data type
 * -------------------------------------------------------------------------- */

/**
 * @brief Holds both the configuration and the debounce state of one button.
 *
 * Configuration fields (set by caller before button_init):
 *   pin         - GPIO number
 *   active_high - true  = button drives pin HIGH when pressed
 *                 false = button drives pin LOW  when pressed (typical with pull-up)
 *   debounce_ms - minimum stable time in milliseconds to accept a state change
 *
 * State fields (managed internally by the driver - do not write these):
 *   _last_raw      - last raw digital level read from the pin
 *   _stable_state  - last debounced logical state
 *   _last_change   - timestamp (millis()) of the last raw level change
 *   _event_pending - true when a new press event is waiting to be consumed
 */
typedef struct {
    /* --- configuration (set before button_init) --- */
    uint8_t  pin;
    bool     active_high;
    uint16_t debounce_ms;

    /* --- internal state (managed by driver) --- */
    bool     _last_raw;
    bool     _stable_state;
    uint32_t _last_change;
    bool     _event_pending;
} Button_t;

/* --------------------------------------------------------------------------
 * API
 * -------------------------------------------------------------------------- */

/**
 * @brief Initialise the GPIO pin and reset all internal state fields.
 *
 * Sets up INPUT or INPUT_PULLUP based on active_high, then calls
 * button_update() once to capture the initial state.
 *
 * @param b  Pointer to a Button_t with configuration fields filled in.
 */
void button_init(Button_t *b);

/**
 * @brief Update the debounce state machine.
 *
 * Must be called regularly (e.g. every loop iteration).
 * Reads the pin and applies debounce logic; sets _event_pending on
 * a confirmed press transition.
 *
 * @param b  Pointer to an initialised Button_t.
 */
void button_update(Button_t *b);

/**
 * @brief Returns true once per confirmed button press.
 *
 * Calls button_update() internally, then checks and clears _event_pending.
 * Suitable for simple polling in loop().
 *
 * @param b  Pointer to an initialised Button_t.
 * @return   true on the first call after a new press is confirmed, false otherwise.
 */
bool button_pressed(Button_t *b);

/**
 * @brief Returns the current stable logical state (not edge-triggered).
 *
 * Returns true while the button is held down, false while released.
 * Does NOT call button_update() - call button_update() or button_pressed() first.
 *
 * @param b  Pointer to an initialised Button_t.
 * @return   Current debounced logical state.
 */
bool button_state(const Button_t *b);

/**
 * @brief Initialise every button in an array.
 *
 * @param buttons  Pointer to the first element of a Button_t array.
 * @param count    Number of elements.
 */
void button_init_array(Button_t *buttons, uint8_t count);

#ifdef __cplusplus
}
#endif
