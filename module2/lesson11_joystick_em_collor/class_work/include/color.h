#pragma once
#include <stdint.h>

namespace common {

// ---------------------------------------------------------------------------
// em_color - a compact 3-byte RGB color value.
// Storage: uint8_t r, g, b  (0-255 each).
// No floating-point arithmetic; safe for MCU use.
// ---------------------------------------------------------------------------
struct em_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    // Construct black (r=g=b=0) by default.
    em_color();

    // Construct from explicit channel values.
    em_color(uint8_t r, uint8_t g, uint8_t b);

    // Named color constants.
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
// lerp - linear interpolation between two colors.
//
//   t == 0   -> result equals a
//   t == 255 -> result equals b
//   t == 128 -> approximately 50/50 mix
//
// Uses integer arithmetic only (no float).
// ---------------------------------------------------------------------------
em_color lerp(em_color a, em_color b, uint8_t t);

} // namespace common
