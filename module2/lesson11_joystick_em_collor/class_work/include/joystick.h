#pragma once
#include "analog_pin.h"
#include "button.h"
#include <stdint.h>

namespace drivers {

// ---------------------------------------------------------------------------
// Joystick - reads two analog axes and one push button.
//
// Composition:
//   AnalogPin _x   - X axis potentiometer (ADC)
//   AnalogPin _y   - Y axis potentiometer (ADC)
//   Button    _btn - push button (active-low, debounced)
//
// Axis values are mapped from raw ADC (0-4095) to signed range -100..+100.
// A configurable dead zone suppresses jitter near the center position.
//
// Typical wiring (ESP32-C3):
//   VRx -> GPIO 4
//   VRy -> GPIO 5
//   SW  -> GPIO 6
// ---------------------------------------------------------------------------
class Joystick {
public:
    // pin_x      - GPIO for X axis ADC input.
    // pin_y      - GPIO for Y axis ADC input.
    // pin_btn    - GPIO for push button (active-low, pull-up applied).
    // dead_zone  - values in range (-dead_zone .. +dead_zone) map to 0.
    //              Default 10 units (out of 100).
    Joystick(uint8_t pin_x,
             uint8_t pin_y,
             uint8_t pin_btn,
             uint8_t dead_zone = 10);

    // Read both axes and update button state.
    // Must be called once per loop iteration.
    void update();

    // Returns X axis position in range -100..+100.
    // Negative = left, positive = right.
    int8_t getX() const;

    // Returns Y axis position in range -100..+100.
    // Negative = down, positive = up (depends on module orientation).
    int8_t getY() const;

    // Returns true while the button is held down.
    bool isPressed() const;

    // Returns true exactly once per button press, then resets.
    bool wasPressed();

private:
    AnalogPin _x;
    AnalogPin _y;
    Button    _btn;
    uint8_t   _dz;   // dead zone threshold (0-100)
    int8_t    _vx;   // last mapped X value
    int8_t    _vy;   // last mapped Y value

    // Map raw ADC value (0-4095) to signed -100..+100, apply dead zone.
    int8_t _mapAxis(uint16_t raw) const;
};

} // namespace drivers
