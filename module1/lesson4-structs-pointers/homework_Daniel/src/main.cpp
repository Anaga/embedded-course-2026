#include <Arduino.h>
#include "gpio_driver.h"

/* ---------------- RGB PINS (common cathode, 3 resistors) ---------------- */
static const uint8_t PIN_R = 4;
static const uint8_t PIN_G = 3;
static const uint8_t PIN_B = 10;

/* ---------------- SWITCH PINS (3 positions using 2 GPIO) ----------------
 * Your measured states:
 * pos 1 -> GPIO0=1 GPIO2=0
 * pos 0 -> GPIO0=1 GPIO2=1
 * pos 2 -> GPIO0=0 GPIO2=1
 */
static const uint8_t PIN_SW0 = 0;
static const uint8_t PIN_SW2 = 2;

/* ---------------- GPIO descriptors ---------------- */
static GpioPin_t rgb[3] = {
    { .pin = PIN_R, .output = true, .active_high = true, .pull_up = false }, // RED
    { .pin = PIN_G, .output = true, .active_high = true, .pull_up = false }, // GREEN
    { .pin = PIN_B, .output = true, .active_high = true, .pull_up = false }, // BLUE
};

static const char *color_names[3] = { "RED", "GREEN", "BLUE" };

static void rgb_all_off()
{
    for (uint8_t i = 0; i < 3; i++) {
        gpio_pin_set(&rgb[i], false); // OFF
    }
}

static void rgb_set_color(uint8_t idx)
{
    rgb_all_off();
    gpio_pin_set(&rgb[idx], true);   // ON
}

/* Map switch electrical state -> color index (0=RED,1=GREEN,2=BLUE)
 *
 * Measured:
 *  (GPIO0=0, GPIO2=1) => switch pos 2
 *  (GPIO0=1, GPIO2=1) => switch pos 0
 *  (GPIO0=1, GPIO2=0) => switch pos 1
 */
static uint8_t read_color_from_switch()
{
    int a = digitalRead(PIN_SW0); // 1=open, 0=to GND
    int b = digitalRead(PIN_SW2);

    if (a == LOW  && b == HIGH) return 0; // RED  (pos 2)
    if (a == HIGH && b == HIGH) return 1; // GREEN(pos 0)
    if (a == HIGH && b == LOW ) return 2; // BLUE (pos 1)

    return 255; // invalid (should not happen)
}

void setup()
{
    Serial.begin(115200);
    delay(200);

    gpio_pin_init_array(rgb, 3);

    pinMode(PIN_SW0, INPUT_PULLUP);
    pinMode(PIN_SW2, INPUT_PULLUP);

    uint8_t c = read_color_from_switch();
    if (c != 255) {
        rgb_set_color(c);
        Serial.printf("Start -> %s\n", color_names[c]);
    } else {
        rgb_all_off();
        Serial.println("Invalid switch state (check wiring).");
    }
}

void loop()
{
    static uint8_t last = 255;

    uint8_t c = read_color_from_switch();
    if (c != 255 && c != last) {
        last = c;
        rgb_set_color(c);
        Serial.printf("Color -> %s\n", color_names[c]);
    }

    delay(10);
}