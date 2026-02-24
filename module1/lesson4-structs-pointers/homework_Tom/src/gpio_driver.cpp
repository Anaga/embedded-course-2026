/**
 * @file gpio_driver.cpp
 * @brief GPIO driver implementation.
 *
 * Lesson 4 - Structs and Pointers to Structs
 * Embedded Systems Course 2026
 */

#include "gpio_driver.h"
#include <Arduino.h>

/* --------------------------------------------------------------------------
 * Compile-time size check
 *
 * The struct has 4 fields: uint8_t(1) + bool(1) + bool(1) + bool(1) = 4 bytes.
 * With natural alignment on a 32-bit target the compiler may add padding after
 * pin (to align the next field) — check with sizeof() in setup() if curious.
 * -------------------------------------------------------------------------- */
static_assert(sizeof(GpioPin_t) >= 4, "GpioPin_t smaller than expected");

/* --------------------------------------------------------------------------
 * API implementation
 * -------------------------------------------------------------------------- */

void gpio_pin_init(GpioPin_t *p)
{
    uint8_t mode;

    if (p->output) {
        mode = OUTPUT;
    } else if (p->pull_up) {
        mode = INPUT_PULLUP;
    } else {
        mode = INPUT;
    }

    pinMode(p->pin, mode);

    /* Drive outputs to their inactive state on init */
    if (p->output) {
        gpio_pin_set(p, false);
    }
}

void gpio_pin_set(GpioPin_t *p, bool state)
{
    /* Translate logical state -> physical level */
    bool level = p->active_high ? state : !state;
    digitalWrite(p->pin, level ? HIGH : LOW);
}

void gpio_pin_toggle(GpioPin_t *p)
{
    /* Read current physical level and invert */
    bool current_level = (digitalRead(p->pin) == HIGH);
    digitalWrite(p->pin, current_level ? LOW : HIGH);
}

bool gpio_pin_read(GpioPin_t *p)
{
    bool raw = (digitalRead(p->pin) == HIGH);
    /* Translate physical level -> logical state */
    return p->active_high ? raw : !raw;
}

void gpio_pin_init_array(GpioPin_t *pins, uint8_t count)
{
    /* Pointer arithmetic: iterate through each element */
    for (uint8_t i = 0; i < count; i++) {
        gpio_pin_init(&pins[i]);
    }
}
