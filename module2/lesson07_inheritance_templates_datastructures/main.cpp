/**
 * @file main.cpp
 * @brief Lesson 07 template — Inheritance, Templates, Data Structures.
 *
 * Embedded Systems Course 2026
 * Hardware: ESP32-C3 Super Mini
 *
 * ============================================================
 * WIRING
 * ============================================================
 *
 *   Button (active-low, uses internal pull-up):
 *     GPIO 0  --> button --> GND
 *
 * ============================================================
 * EXERCISES
 * ============================================================
 *
 * Exercise 1 — Inheritance basics
 *   Read circle.h/cpp and rectangle.h/cpp.
 *   Uncomment the circle and rectangle objects below.
 *   Call print() on each — observe the different output.
 *
 * Exercise 2 — Polymorphism
 *   Uncomment the point* array section.
 *   Call print() through base pointers — verify virtual dispatch.
 *
 * Exercise 3 — Template functions
 *   Uncomment the myMax() test section.
 *   Test with uint8_t, int16_t, and float.
 *
 * Exercise 4 — RingBuffer
 *   Uncomment the RingBuffer section.
 *   Push a new random point on each button press.
 *   Print the last 8 positions stored in the buffer.
 *
 * BONUS — Find largest area
 *   Create several circles and rectangles.
 *   Use a loop to find which shape has the largest area.
 */

#include <Arduino.h>
#include <stdint.h>

#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "RingBuffer.h"
#include "util.h"

/* ------------------------------------------------------------------ */
/* Constants                                                           */
/* ------------------------------------------------------------------ */
static const uint8_t  PIN_BUTTON     = 0;
static const uint32_t SERIAL_SPEED   = 115200u;
static const uint32_t STARTUP_DELAY  = 2000u;
static const uint16_t DEBOUNCE_MS    = 50u;

/* ------------------------------------------------------------------ */
/* Button state (simple debounce)                                      */
/* ------------------------------------------------------------------ */
static bool     lastBtnRaw     = true;   // pull-up = HIGH when released
static bool     btnStable      = true;
static uint32_t lastBtnChange  = 0;
static bool     btnEventPending = false;

static bool buttonPressed()
{
    bool raw = digitalRead(PIN_BUTTON);
    uint32_t now = millis();

    if (raw != lastBtnRaw) {
        lastBtnRaw = raw;
        lastBtnChange = now;
        return false;
    }

    if ((now - lastBtnChange) >= DEBOUNCE_MS) {
        if (raw != btnStable) {
            btnStable = raw;
            if (raw == LOW) {
                return true;    // press detected
            }
        }
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* Global objects                                                      */
/* ------------------------------------------------------------------ */
point     p1(5, 10);
// circle    c1(3, 4, 7);         // Exercise 1: uncomment
// rectangle r1(1, 1, 10, 5);     // Exercise 1: uncomment

// RingBuffer<point, 8> history;  // Exercise 4: uncomment

/* ------------------------------------------------------------------ */
/* setup()                                                             */
/* ------------------------------------------------------------------ */
void setup()
{
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);

    Serial.println("================================================");
    Serial.println(" Lesson 07: Inheritance, Templates, Data Structs");
    Serial.println("================================================");
    Serial.println();

    pinMode(PIN_BUTTON, INPUT_PULLUP);

    /* --- Exercise 1: Basic inheritance --- */
    Serial.println("--- Point ---");
    p1.print();
    Serial.println();

    // Serial.println("--- Circle ---");
    // c1.print();
    // Serial.printf("  area = %.2f\n", c1.area());
    // Serial.printf("  circumference = %.2f\n", c1.circumference());
    // Serial.println();

    // Serial.println("--- Rectangle ---");
    // r1.print();
    // Serial.printf("  area = %d\n", r1.area());
    // Serial.printf("  perimeter = %d\n", r1.perimeter());
    // Serial.println();

    /* --- Exercise 2: Polymorphism --- */
    // point* shapes[] = { &p1, &c1, &r1 };
    // Serial.println("--- Polymorphism (virtual print) ---");
    // for (uint8_t i = 0; i < 3; i++) {
    //     Serial.printf("[%d] ", i);
    //     shapes[i]->print();    // calls the correct print() for each type
    // }
    // Serial.println();

    /* --- Exercise 3: Template functions --- */
    // Serial.println("--- Template myMax() ---");
    // uint8_t  a = 42, b = 17;
    // int16_t  c = -100, d = 200;
    // float    e = 3.14f, f = 2.71f;
    //
    // Serial.printf("myMax(%d, %d)     = %d\n",   a, b, myMax(a, b));
    // Serial.printf("myMax(%d, %d) = %d\n", c, d, myMax(c, d));
    // Serial.printf("myMax(%.2f, %.2f) = %.2f\n", e, f, myMax(e, f));
    //
    // uint8_t clamped = myClamp<uint8_t>(200, 0, 100);
    // Serial.printf("myClamp(200, 0, 100) = %d\n", clamped);
    // Serial.println();

    Serial.println("Press button to add random points to history...");
    Serial.println();
}

/* ------------------------------------------------------------------ */
/* loop()                                                              */
/* ------------------------------------------------------------------ */
static uint16_t pressCount = 0;

void loop()
{
    if (buttonPressed()) {
        pressCount++;

        /* --- Exercise 4: RingBuffer --- */
        // point p;    // random position (default ctor)
        // history.push(p);
        //
        // Serial.printf("--- Press #%d | Buffer: %d/%d ---\n",
        //               pressCount, history.count(), history.capacity());
        //
        // for (uint8_t i = 0; i < history.count(); i++) {
        //     point item = history.peek(i);
        //     Serial.printf("  [age %d] ", i);
        //     item.print();
        // }
        // Serial.println();

        /* Simple feedback until exercises are uncommented */
        Serial.printf("Button press #%d\n", pressCount);
    }
}
