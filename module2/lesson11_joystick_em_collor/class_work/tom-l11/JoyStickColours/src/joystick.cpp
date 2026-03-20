#include "joystick.h"
#include <Arduino.h>

namespace drivers {

Joystick::Joystick(uint8_t pin_x,
                   uint8_t pin_y,
                   uint8_t pin_btn,
                   uint8_t dead_zone)
    : _x(pin_x),
      _y(pin_y),
      _btn(pin_btn),
      _dz(dead_zone),
      _vx(0),
      _vy(0)
{}

void Joystick::update() {
    _vx = _mapAxis(_x.read());
    _vy = _mapAxis(_y.read());
    _btn.update();
}

int8_t Joystick::getX() const { return _vx; }
int8_t Joystick::getY() const { return _vy; }

bool Joystick::isPressed() const { return _btn.isPressed(); }
bool Joystick::wasPressed()      { return _btn.wasPressed(); }

int8_t Joystick::_mapAxis(uint16_t raw) const {
    // Map 0-4095 to -100..+100.
    int16_t v = static_cast<int16_t>(map(raw, 0, 4095, -100, 100));

    // Apply dead zone: suppress jitter near center.
    if (v > -static_cast<int16_t>(_dz) && v < static_cast<int16_t>(_dz)) {
        return 0;
    }
    return static_cast<int8_t>(v);
}

} // namespace drivers
