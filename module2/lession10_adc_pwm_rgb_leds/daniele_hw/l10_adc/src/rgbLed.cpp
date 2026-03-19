#include "rgbLed.h"

namespace drivers {

RgbLed::RgbLed(uint8_t rPin,
               uint8_t gPin,
               uint8_t bPin)
    : Led(rPin),       // RED channel (inherited)
      _green(gPin),
      _blue(bPin)
{
}

void RgbLed::setColor(uint8_t r,
                      uint8_t g,
                      uint8_t b)
{
    setBrightness(r); // RED (inherited from Led)
    _green.write(g);  // GREEN
    _blue.write(b);   // BLUE
}

void RgbLed::off()
{
    setColor(0, 0, 0);
}

} // namespace drivers