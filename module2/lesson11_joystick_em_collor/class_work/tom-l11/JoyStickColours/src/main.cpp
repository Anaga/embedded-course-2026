#include <Arduino.h>
#include "joystick.h"
#include "rgb_led.h"
#include "color.h"

using namespace drivers;
using namespace common;

// ---------------------------------------------------------------------------
// Hardware wiring
//   Joystick VRx -> GPIO 4  (ADC1 CH4)
//   Joystick VRy -> GPIO 5  (ADC1 CH5)
//   Joystick SW  -> GPIO 6  (active-low, pull-up)
//   RGB LED R    -> GPIO 3  (active-low, common anode)
//   RGB LED G    -> GPIO 10 (active-low, common anode)
//   RGB LED B    -> GPIO 2  (active-low, common anode)
// ---------------------------------------------------------------------------

Joystick joy(4, 0, 6);       // pin_x, pin_y, pin_btn
RgbLed   led(3, 10, 2);      // pin_r, pin_g, pin_b

void setup() {
    Serial.begin(115200);
    Serial.println("Lesson 11 class work & homework.");
}

void loop() {
    joy.update();

    int8_t  x = joy.getX();   // -100..+100
    int8_t  y = joy.getY();   // -100..+100

    // Map X axis (-100..+100) to lerp parameter (0..200).
    // t=0 -> full RED, t=200 -> close to full BLUE.
    // Note: lerp() expects 0-255; 200 gives a visible blue without
    // needing to clamp, and avoids a cast overflow.
    uint8_t t_x = static_cast<uint8_t>(x + 100);  // 0..200
    em_color c = lerp(em_color::RED, em_color::BLUE, t_x);

    uint8_t t_y = static_cast<uint8_t>(y + 100);  // 0..200
    em_color cc = lerp(em_color::GREEN, em_color::YELLOW, t_y);

    em_color final_color = lerp(c, cc, t_x);

    if (joy.wasPressed()) {
        // Flash white on button press.
        led.setColor(em_color::WHITE);
        delay(120);
    } else {
        led.setColor(final_color);
    }

    // Debug output every 200 ms.
    static uint32_t last_print = 0;
    if (millis() - last_print >= 200) {
        last_print = millis();
        Serial.print("X=");
        Serial.print(x);
        Serial.print("  Y=");
        Serial.print(y);
        Serial.print("  btn=");
        Serial.print(joy.isPressed() ? "DOWN" : "up");
        Serial.print("  t=");
        Serial.print(t_x);
        Serial.print("  color=");
        Serial.print(c.r);
        Serial.print(",");
        Serial.print(c.g);
        Serial.print(",");
        Serial.println(c.b);
    }

    delay(20);
}
