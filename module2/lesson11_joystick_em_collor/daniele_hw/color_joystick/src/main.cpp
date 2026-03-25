#include <Arduino.h>
#include "joystick.h"
#include "rgb_led.h"
#include "color.h"

// ---------------------------------------------------------------------------
// Lesson 11 homework - 2D Color Mapping
//
// X axis: RED   -> BLUE
// Y axis: GREEN -> YELLOW
//
// final_color = lerp(color_x, color_y, t_x)
//
// Button: flash WHITE
//
// Wiring:
// Joystick: X=4, Y=0, Button=6
// RGB LED : R=3, G=10, B=2
//
// NOTE:
// This version assumes COMMON CATHODE RGB LED.
// ---------------------------------------------------------------------------

Joystick joy(4, 0, 6, 45);   // pin_x, pin_y, pin_btn, dead_zone
RgbLed   led(3, 10, 2);      // pin_r, pin_g, pin_b

void setup() {
    Serial.begin(115200);
    Serial.println("Lesson 11 homework - 2D color mapping started.");
}

void loop() {
    joy.update();

    int8_t x = joy.getX();   // -100 .. +100
    int8_t y = joy.getY();   // -100 .. +100

    // Homework mapping style: -100..+100 -> 0..200
    uint8_t t_x = static_cast<uint8_t>(x + 100);
    uint8_t t_y = static_cast<uint8_t>(y + 100);

    // Blend for X axis
    em_color color_x = lerp(em_color::RED, em_color::BLUE, t_x);

    // Blend for Y axis
    em_color color_y = lerp(em_color::GREEN, em_color::YELLOW, t_y);

    // Final blend between the two intermediate colors
    em_color final_color = lerp(color_x, color_y, t_x);

    if (joy.wasPressed()) {
        led.setColor(em_color::WHITE);
        delay(120);
    } else {
        led.setColor(final_color);
    }

    static uint32_t last_print = 0;
    if (millis() - last_print >= 200) {
        last_print = millis();

        Serial.print("X=");
        Serial.print(x);
        Serial.print("  Y=");
        Serial.print(y);
        Serial.print("  btn=");
        Serial.print(joy.isPressed() ? 1 : 0);

        Serial.print("  tx=");
        Serial.print(t_x);
        Serial.print("  ty=");
        Serial.print(t_y);

        Serial.print("  color_x=");
        Serial.print(color_x.r);
        Serial.print(",");
        Serial.print(color_x.g);
        Serial.print(",");
        Serial.print(color_x.b);

        Serial.print("  color_y=");
        Serial.print(color_y.r);
        Serial.print(",");
        Serial.print(color_y.g);
        Serial.print(",");
        Serial.print(color_y.b);

        Serial.print("  final=");
        Serial.print(final_color.r);
        Serial.print(",");
        Serial.print(final_color.g);
        Serial.print(",");
        Serial.println(final_color.b);
    }

    delay(20);
}