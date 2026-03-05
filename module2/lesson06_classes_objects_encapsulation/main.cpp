/**
 * @file main.cpp
 * @brief Lesson 06 template — Classes, Objects, Encapsulation.
 *
 * Embedded Systems Course 2026
 * Hardware: ESP32-C3 Super Mini
 *
 * ============================================================
 * WIRING
 * ============================================================
 *
 *   Onboard LED (active-high):
 *     GPIO 8  (built-in on ESP32-C3 Super Mini)
 *
 *   Button (active-low, uses internal pull-up):
 *     GPIO 0  --> button --> GND
 *
 *   RGB LED (common anode, active-low):
 *     3.3V    --> common anode (longest leg)
 *     GPIO 1  --> 220 ohm --> Red cathode
 *     GPIO 3  --> 220 ohm --> Green cathode
 *     GPIO 10 --> 220 ohm --> Blue cathode
 *
 * ============================================================
 * EXERCISES
 * ============================================================
 *
 * The file compiles and runs as-is. Work through the exercises
 * in order — each one builds on the previous.
 *
 * Exercise 1 — Read and understand
 *   Read Led.h, Led.cpp, Button.h, Button.cpp.
 *   Flash the code. Verify the onboard LED blinks and the
 *   button prints "Click!" to Serial.
 *
 * Exercise 2 — Add a blink() method
 *   Add a blink(uint16_t ms) method to the Led class.
 *   It should turn the LED on, wait ms milliseconds,
 *   then turn it off.
 *   Declare in Led.h, implement in Led.cpp, call from loop().
 *
 * Exercise 3 — Create an RgbLed class
 *   Create RgbLed.h and RgbLed.cpp.
 *   The class should hold three Led objects (red, green, blue).
 *   Provide methods: setColor(bool r, bool g, bool b) and off().
 *   Remember: these LEDs are active-low (common anode).
 *
 * BONUS — Cycle colors with Button
 *   Use your RgbLed + Button to cycle through:
 *   Red -> Green -> Blue -> Yellow -> Cyan -> Magenta -> White -> Off
 *   on each button press.
 */

#include <Arduino.h>
#include <stdint.h>

#include "Led.h"
#include "Button.h"

/* ------------------------------------------------------------------ */
/* Pin assignments                                                     */
/* ------------------------------------------------------------------ */
static const uint8_t  PIN_ONBOARD_LED = 8;
static const uint8_t  PIN_BUTTON      = 0;

static const uint32_t SERIAL_SPEED    = 115200u;
static const uint32_t BLINK_INTERVAL  = 500u;

/* ------------------------------------------------------------------ */
/* Global objects                                                      */
/* ------------------------------------------------------------------ */
Led    onboardLed(PIN_ONBOARD_LED, true);   // active-high
Button btn(PIN_BUTTON, false, 50);          // active-low, 50ms debounce

/* ------------------------------------------------------------------ */
/* Timing                                                              */
/* ------------------------------------------------------------------ */
static uint32_t lastBlink = 0;

/* ------------------------------------------------------------------ */
/* setup()                                                             */
/* ------------------------------------------------------------------ */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    delay(1000);

    Serial.println("================================================");
    Serial.println(" Lesson 06: Classes, Objects, Encapsulation");
    Serial.println(" Onboard LED blinks, button prints to Serial");
    Serial.println("================================================");
    Serial.println();
    Serial.printf("LED on GPIO %u (active-high)\n", onboardLed.pin());
    Serial.printf("Button on GPIO %u (active-low)\n", btn.pin());
    Serial.println();
}

/* ------------------------------------------------------------------ */
/* loop()                                                              */
/* ------------------------------------------------------------------ */
void loop()
{
    /* Blink the onboard LED without delay() */
    uint32_t now = millis();
    if (now - lastBlink >= BLINK_INTERVAL) {
        lastBlink = now;
        onboardLed.toggle();
    }

    /* Check for button press */
    if (btn.pressed()) {
        Serial.printf("Click! LED is %s\n", onboardLed.isOn() ? "ON" : "OFF");
    }
}
