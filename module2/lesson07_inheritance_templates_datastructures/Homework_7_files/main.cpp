/**
 * Homework 6: Bunny Escape Game
 *
 * A bunny spawns at a random location on a 25x25 field.
 * Guide it to the hole at (12,12) within 25 moves using two buttons.
 * Red LED = danger, Green LED = safe in the hole.
 *
 * See README.md for full requirements.
 *
 * Wiring:
 *   BTN_X: GPIO 1 --> button --> GND (internal pull-up, ISR FALLING)
 *   BTN_Y: GPIO 0 --> button --> GND (internal pull-up, ISR FALLING)
 *   Red:   GPIO 3 --> 220 ohm --> LED --> 3.3V (common anode, active-low)
 *   Green: GPIO 10 --> 220 ohm --> LED --> 3.3V (common anode, active-low)
 */

#include <Arduino.h>
#include <stdint.h>

#include "dots.h"

/* ------------------------------------------------------------------ */
/* Pin assignments                                                     */
/* ------------------------------------------------------------------ */
#define BTN_X_PIN    1
#define BTN_Y_PIN    0
#define RED_LED_PIN  3
#define GREEN_LED_PIN 10

/* ------------------------------------------------------------------ */
/* Constants                                                           */
/* ------------------------------------------------------------------ */
#define SERIAL_SPEED  115200u
#define STARTUP_DELAY 3500u
#define DEBOUNCE_MS   500u
#define MAX_MOVES     25
#define HOLE_X        12
#define HOLE_Y        12
#define HOLE_RADIUS   5

/* ------------------------------------------------------------------ */
/* ISR shared variables (must be volatile!)                            */
/* ------------------------------------------------------------------ */
volatile bool     button_X_Pressed  = false;
volatile bool     button_Y_Pressed  = false;
volatile uint32_t last_X_PressTime  = 0;
volatile uint32_t last_Y_PressTime  = 0;

/* ------------------------------------------------------------------ */
/* ISRs — keep them SHORT!                                             */
/* ------------------------------------------------------------------ */
void IRAM_ATTR onButton_X_Press()
{
    uint32_t now = millis();
    if (now - last_X_PressTime > DEBOUNCE_MS) {
        last_X_PressTime = now;
        button_X_Pressed = true;
    }
}

void IRAM_ATTR onButton_Y_Press()
{
    uint32_t now = millis();
    if (now - last_Y_PressTime > DEBOUNCE_MS) {
        last_Y_PressTime = now;
        button_Y_Pressed = true;
    }
}

/* ------------------------------------------------------------------ */
/* Game state                                                          */
/* ------------------------------------------------------------------ */
point bunny;                    // random spawn (default ctor)
point hole(HOLE_X, HOLE_Y);    // center of the field

// TODO: Add a move counter
// TODO: Add a gameOver flag

/* ------------------------------------------------------------------ */
/* setup()                                                             */
/* ------------------------------------------------------------------ */
void setup()
{
    Serial.begin(SERIAL_SPEED);

    // Configure button pins
    pinMode(BTN_X_PIN, INPUT_PULLUP);
    pinMode(BTN_Y_PIN, INPUT_PULLUP);

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(BTN_X_PIN), onButton_X_Press, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_Y_PIN), onButton_Y_Press, FALLING);

    // TODO: Configure LED pins as OUTPUT
    // TODO: Turn red LED ON, green LED OFF (remember: active-low!)

    delay(STARTUP_DELAY);

    Serial.println("================================================");
    Serial.println(" Bunny Escape Game");
    Serial.println("================================================");
    Serial.printf("Bunny spawned at ");
    bunny.print();
    Serial.printf("Hole is at (%d, %d). Radius: %d\n", HOLE_X, HOLE_Y, HOLE_RADIUS);
    Serial.printf("Moves allowed: %d\n", MAX_MOVES);
    Serial.println("---");
    Serial.println();
}

/* ------------------------------------------------------------------ */
/* loop()                                                              */
/* ------------------------------------------------------------------ */
void loop()
{
    // TODO: Only process buttons if gameOver == false

    if (button_X_Pressed) {
        button_X_Pressed = false;
        bunny.move_x();
        // TODO: Increment move counter
        // TODO: Print status: position, distance, moves left
        // TODO: Check win/lose conditions
    }

    if (button_Y_Pressed) {
        button_Y_Pressed = false;
        bunny.move_y();
        // TODO: Increment move counter
        // TODO: Print status: position, distance, moves left
        // TODO: Check win/lose conditions
    }
}
