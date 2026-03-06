/**
 * Homework 6: Point on the Move
 *
 * Part 1: Fix the bugs in dots.h / dots.cpp (see README.md)
 * Part 2: Button press moves point along the X axis
 *
 * Wiring:
 *   Button: GPIO 0 --> button --> GND (internal pull-up)
 *
 * See README.md for full requirements.
 */

#include <Arduino.h>
#include <stdint.h>

#include "dots.h"

/* ------------------------------------------------------------------ */
/* Constants                                                           */
/* ------------------------------------------------------------------ */
#define SERIAL_SPEED  115200u
#define STARTUP_DELAY 3500u
#define BUTTON_PIN    0
#define DEBOUNCE_MS   50

/* ------------------------------------------------------------------ */
/* Global objects                                                      */
/* ------------------------------------------------------------------ */
point myPoint;    // default constructor — spawns at random position

// TODO: Add button handling variables or a Button object

/* ------------------------------------------------------------------ */
/* setup()                                                             */
/* ------------------------------------------------------------------ */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);

    Serial.println("================================================");
    Serial.println(" Homework 6: Point on the Move");
    Serial.println("================================================");
    Serial.println();

    myPoint.print();

    // TODO: Configure button pin
}

/* ------------------------------------------------------------------ */
/* loop()                                                              */
/* ------------------------------------------------------------------ */
void loop()
{
    // TODO: Check button press (with debounce, no delay())
    // TODO: On press — call myPoint.moveX(1)
    // TODO: Print updated position
}
