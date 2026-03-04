/**
 * @file Led.cpp
 * @brief LED driver class implementation.
 *
 * Lesson 06 — Classes, Objects, Encapsulation
 * Embedded Systems Course 2026
 */
#include "Led.h"
#include <Arduino.h>

/* --------------------------------------------------------------------------
 * Private helpers
 * -------------------------------------------------------------------------- */

void Led::writeHardware()
{
    uint8_t level;

    if (active_high_) {
        level = state_ ? HIGH : LOW;
    } else {
        level = state_ ? LOW : HIGH;
    }

    digitalWrite(pin_, level);
}

/* --------------------------------------------------------------------------
 * Constructor / Destructor
 * -------------------------------------------------------------------------- */

Led::Led(uint8_t pin, bool active_high)
    : pin_(pin)
    , active_high_(active_high)
    , state_(false)
{
    pinMode(pin_, OUTPUT);
    writeHardware();
}

Led::~Led()
{
    off();
}

/* --------------------------------------------------------------------------
 * Public methods
 * -------------------------------------------------------------------------- */

void Led::on()
{
    state_ = true;
    writeHardware();
}

void Led::off()
{
    state_ = false;
    writeHardware();
}

void Led::toggle()
{
    state_ = !state_;
    writeHardware();
}

bool Led::isOn() const
{
    return state_;
}

uint8_t Led::pin() const
{
    return pin_;
}
