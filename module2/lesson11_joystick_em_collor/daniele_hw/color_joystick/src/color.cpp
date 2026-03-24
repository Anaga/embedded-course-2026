#include "color.h"

namespace common {

// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------

em_color::em_color()
    : r(0), g(0), b(0)
{
}

em_color::em_color(uint8_t red, uint8_t green, uint8_t blue)
    : r(red), g(green), b(blue)
{
}

// ---------------------------------------------------------------------------
// Named colors
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
// lerp - linear interpolation between two colors
//
// Per channel:
// result = (a * (255 - t) + b * t) / 255
//
// Intermediate arithmetic uses uint16_t to avoid overflow.
// ---------------------------------------------------------------------------

em_color lerp(em_color a, em_color b, uint8_t t) {
    uint16_t inv = static_cast<uint16_t>(255u - t);

    uint8_t red = static_cast<uint8_t>(
        (static_cast<uint16_t>(a.r) * inv + static_cast<uint16_t>(b.r) * t) / 255u
    );

    uint8_t green = static_cast<uint8_t>(
        (static_cast<uint16_t>(a.g) * inv + static_cast<uint16_t>(b.g) * t) / 255u
    );

    uint8_t blue = static_cast<uint8_t>(
        (static_cast<uint16_t>(a.b) * inv + static_cast<uint16_t>(b.b) * t) / 255u
    );

    return em_color(red, green, blue);
}

} // namespace common