/**
 * @file point.h
 * @brief Base point class — updated for inheritance.
 *
 * Lesson 07 — Inheritance, Templates, Data Structures
 * Embedded Systems Course 2026
 *
 * Changes from Lesson 6 dots.h:
 *   - x, y are now PROTECTED (children can access)
 *   - Added #pragma once
 *   - Implementation moved to point.cpp
 *   - Added const to read-only methods
 *   - Added moveX() and moveY() methods
 *   - Added getters
 */
#pragma once

#include <stdint.h>

class point {
protected:
    uint8_t x;
    uint8_t y;

public:
    point();
    point(uint8_t x_val, uint8_t y_val);
    virtual ~point();

    virtual void print() const;

    void moveX(uint8_t delta);
    void moveY(uint8_t delta);

    uint8_t getX() const;
    uint8_t getY() const;

    uint8_t distanceTo(const point& other) const;
};
