#include "color.h"

namespace common {

// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------

em_color::em_color()
    : r(0), g(0), b(0)
{}

em_color::em_color(uint8_t r, uint8_t g, uint8_t b)
    : r(r), g(g), b(b)
{}

// ---------------------------------------------------------------------------
// Named color constants
// ---------------------------------------------------------------------------

const em_color em_color::RED     = em_color(255,   0,   0);
const em_color em_color::GREEN   = em_color(  0, 255,   0);
const em_color em_color::BLUE    = em_color(  0,   0, 255);
const em_color em_color::WHITE   = em_color(255, 255, 255);
const em_color em_color::BLACK   = em_color(  0,   0,   0);
const em_color em_color::YELLOW  = em_color(255, 255,   0);
const em_color em_color::CYAN    = em_color(  0, 255, 255);
const em_color em_color::MAGENTA = em_color(255,   0, 255);

// ---------------------------------------------------------------------------
// lerp - linear interpolation between two colors.
//
// Formula per channel:
//   result = (a_ch * (255 - t) + b_ch * t) / 255
//
// Uses uint16_t for intermediate products to avoid overflow.
// No floating-point arithmetic.
// ---------------------------------------------------------------------------
em_color lerp(em_color a, em_color b, uint8_t t) {
    uint16_t inv = static_cast<uint16_t>(255u - t);
    uint8_t r  = static_cast<uint8_t>((a.r * inv + b.r * t) / 255u);
    uint8_t g  = static_cast<uint8_t>((a.g * inv + b.g * t) / 255u);
    uint8_t bv = static_cast<uint8_t>((a.b * inv + b.b * t) / 255u);
    return em_color(r, g, bv);
}

} // namespace common
