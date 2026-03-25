#pragma once
#include <stdint.h>

namespace common {

// ---------------------------------------------------------------------------
// em_color - compact RGB color container
// Stores three 8-bit channels: r, g, b
// ---------------------------------------------------------------------------
struct em_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    // Default: black
    em_color();

    // Explicit RGB constructor
    em_color(uint8_t red, uint8_t green, uint8_t blue);

    // Named colors
    static const em_color RED;
    static const em_color GREEN;
    static const em_color BLUE;
    static const em_color WHITE;
    static const em_color BLACK;
    static const em_color YELLOW;
    static const em_color CYAN;
    static const em_color MAGENTA;
};

// ---------------------------------------------------------------------------
// lerp - linear interpolation between colors
//
// t = 0   -> result == a
// t = 255 -> result == b
//
// Uses only integer math.
// ---------------------------------------------------------------------------
em_color lerp(em_color a, em_color b, uint8_t t);

} // namespace common

// Aliases so main.cpp can use em_color and lerp directly
using common::em_color;
using common::lerp;