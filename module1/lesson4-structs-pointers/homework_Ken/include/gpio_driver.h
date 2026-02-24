#pragma once

/**
 * @file gpio_driver.h
 * @brief GPIO pin abstraction using structs.
 *
 * Lesson 4 - Structs and Pointers to Structs
 * Embedded Systems Course 2026
 *
 * This driver wraps a GPIO pin's configuration inside a struct,
 * keeping all pin-specific data in one place and exposing a clean
 * pointer-based API.
 *
 * Usage:
 *   GpioPin_t led = { .pin = 8, .output = true, .active_high = true };
 *   gpio_pin_init(&led);
 *   gpio_pin_set(&led, true);
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
 * @brief Describes a single GPIO pin and its electrical behaviour.
 *
 * Fields
 * ------
 *   pin         - GPIO number (ESP32-C3: 0-21, avoid strapping pins)
 *   output      - true = OUTPUT, false = INPUT
 *   active_high - true  = logical HIGH means pin is HIGH (3.3 V)
 *                 false = logical HIGH means pin is LOW  (0 V, active-low)
 *   pull_up     - enable internal pull-up (only relevant for input pins)
 *
 * Memory layout on ESP32-C3 (RISC-V, 32-bit):
 *   pin         uint8_t  - 1 byte  @ offset 0
 *   (padding)            - 1 byte  @ offset 1
 *   output      bool     - 1 byte  @ offset 2
 *   active_high bool     - 1 byte  @ offset 3
 *   pull_up     bool     - 1 byte  @ offset 4
 *   (padding)            - 3 bytes @ offset 5-7
 *   Total: 8 bytes (verified by static_assert in gpio_driver.cpp)
 */
typedef struct {
    uint8_t  pin;
    bool     output;
    bool     active_high;
    bool     pull_up;
} GpioPin_t;

/* --------------------------------------------------------------------------
 * API
 * -------------------------------------------------------------------------- */

/**
 * @brief Initialise the pin direction and pull-up.
 *
 * Must be called before gpio_pin_set() or gpio_pin_read().
 *
 * @param p  Pointer to an initialised GpioPin_t.
 */
void gpio_pin_init(GpioPin_t *p);

/**
 * @brief Set the logical state of an output pin.
 *
 * Translates the logical state to the correct physical voltage level,
 * honouring the active_high field.
 *
 * @param p      Pointer to an output GpioPin_t.
 * @param state  Logical state: true = active, false = inactive.
 */
void gpio_pin_set(GpioPin_t *p, bool state);

/**
 * @brief Toggle the logical state of an output pin.
 *
 * Reads the current physical level and inverts it.
 *
 * @param p  Pointer to an output GpioPin_t.
 */
void gpio_pin_toggle(GpioPin_t *p);

/**
 * @brief Read the logical state of an input pin.
 *
 * Translates the physical voltage level to a logical state,
 * honouring the active_high field.
 *
 * @param p  Pointer to an input GpioPin_t.
 * @return   true if the pin is in its active logical state.
 */
bool gpio_pin_read(GpioPin_t *p);

/* --------------------------------------------------------------------------
 * Utility
 * -------------------------------------------------------------------------- */

/**
 * @brief Initialise every pin in an array.
 *
 * Convenience wrapper that calls gpio_pin_init() for each element.
 *
 * @param pins  Pointer to the first element of a GpioPin_t array.
 * @param count Number of elements.
 */
void gpio_pin_init_array(GpioPin_t *pins, uint8_t count);

#ifdef __cplusplus
}
#endif
