#pragma once
/**
 * dots.h
 *
 * Homework 6 - Bunny Escape Game
 *
 * This file contains the declarations of the point class.
 * I use this class to represent:
 * - the bunny position
 * - the hole position
 *
 * Important fix:
 * The distance() function must correctly compute Manhattan distance
 * without unsigned subtraction wrap-around.
 */

#include <Arduino.h>
#include <stdint.h>

class point
{
private:
    // Coordinates on a 0..25 field
    uint8_t x;
    uint8_t y;

public:
    // Default constructor:
    // spawn at a random position
    point();

    // Constructor with explicit coordinates
    point(uint8_t x_val, uint8_t y_val);

    // Destructor
    ~point();

    // Print current coordinates
    void print() const;

    // Manhattan distance between two points
    // |x1 - x2| + |y1 - y2|
    uint8_t distance(const point& A, const point& B) const;

    // Move helpers with wrap-around
    void moveX(uint8_t delta);
    void moveY(uint8_t delta);

    // Getters
    uint8_t getX() const;
    uint8_t getY() const;
};