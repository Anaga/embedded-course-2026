/**
 * dots.cpp
 *
 * Homework 6 - Bunny Escape Game
 *
 * This file contains the implementation of the point class.
 */

#include "dots.h"

// ============================================================
// Default constructor
// Spawn the point at a random position in the range 0..25
// ============================================================

point::point()
{
    x = (uint8_t)random(0, 26);
    y = (uint8_t)random(0, 26);
}

// ============================================================
// Constructor with explicit coordinates
// ============================================================

point::point(uint8_t x_val, uint8_t y_val)
{
    x = x_val;
    y = y_val;
}

// ============================================================
// Destructor
// ============================================================

point::~point()
{
    // Nothing to free
}

// ============================================================
// Print current coordinates
// ============================================================

void point::print() const
{
    Serial.printf("Point(%u, %u)\n", x, y);
}

// ============================================================
// Manhattan distance
//
// BUG FIX:
// I must avoid unsigned subtraction wrap-around.
// So I compare before subtracting.
// ============================================================

uint8_t point::distance(const point& A, const point& B) const
{
    uint8_t delta_x = (A.x > B.x) ? (A.x - B.x) : (B.x - A.x);
    uint8_t delta_y = (A.y > B.y) ? (A.y - B.y) : (B.y - A.y);

    return (uint8_t)(delta_x + delta_y);
}

// ============================================================
// Move on X with wrap-around
// If x becomes bigger than 25, wrap back to 0
// ============================================================

void point::moveX(uint8_t delta)
{
    x = (uint8_t)(x + delta);

    if (x > 25)
    {
        x = 0;
    }
}

// ============================================================
// Move on Y with wrap-around
// If y becomes bigger than 25, wrap back to 0
// ============================================================

void point::moveY(uint8_t delta)
{
    y = (uint8_t)(y + delta);

    if (y > 25)
    {
        y = 0;
    }
}

// ============================================================
// Getters
// ============================================================

uint8_t point::getX() const
{
    return x;
}

uint8_t point::getY() const
{
    return y;
}