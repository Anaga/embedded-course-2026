/**
 * @file main.cpp
 * @brief Lesson 4 template — Structs and Pointers to Structs.
 *
 * Embedded Systems Course 2026
 * Hardware: ESP32-C3 Super Mini
 *
 * ============================================================
 * WIRING
 * ============================================================
 *
 *   LED (active-high):
 *     GPIO 8  --> 220 ohm resistor --> LED anode
 *     LED cathode --> GND
 *
 *   Button (active-low, uses internal pull-up):
 *     GPIO 9  --> button --> GND
 *
 * ============================================================
 * EXERCISES
 * ============================================================
 *
 * The file compiles and runs as-is. Work through the exercises
 * in order — each one builds on the previous.
 *
 * Exercise 1 — Struct basics
 *   The led and button structs below are already declared.
 *   a) Add a second LED on GPIO 10 (active-low this time).
 *   b) Initialise it and toggle it in loop() at a different rate.
 *
 * Exercise 2 — Pointer syntax
 *   a) Declare a GpioPin_t pointer that points to 'led'.
 *   b) Use the pointer and the -> operator to read led.pin.
 *   c) Print the value over Serial. Confirm it matches.
 *
 * Exercise 3 — Passing structs to a function
 *   Implement the blink() function at the bottom of this file.
 *   Signature: void blink(GpioPin_t *p, uint16_t on_ms, uint16_t off_ms)
 *   It should set the pin HIGH for on_ms, then LOW for off_ms.
 *   Call it from loop() for your second LED.
 *
 * Exercise 4 — Array of structs (BONUS)
 *   Replace the individual LED declarations with a GpioPin_t array.
 *   Use gpio_pin_init_array() to initialise them all in one call.
 *   Loop through the array and toggle each LED in sequence.
 *
 * ============================================================
 */

#include <Arduino.h>
#include "gpio_driver.h"
#include "button_driver.h"

/* ------------------------------------------------------------------
 * Pin assignments
 * Change these to match your actual wiring.
 * ------------------------------------------------------------------ */
static const uint8_t PIN_LED    = 8;
static const uint8_t PIN_BUTTON = 9;

/* ------------------------------------------------------------------
 * Peripheral descriptors
 *
 * Designated initialiser syntax: .field = value
 * Fields not listed are zero-initialised (false / 0).
 * ------------------------------------------------------------------ */
static GpioPin_t led = {
    .pin         = PIN_LED,
    .output      = true,
    .active_high = true,
    .pull_up     = false,
};

static Button_t button = {
    .pin         = PIN_BUTTON,
    .active_high = false,   /* active-low: pressed = GND */
    .debounce_ms = 50,
};

/* ------------------------------------------------------------------
 * Exercise 3 — implement this function
 * ------------------------------------------------------------------ */
// void blink(GpioPin_t *p, uint16_t on_ms, uint16_t off_ms)
// {
//     /* TODO */
// }

/* ------------------------------------------------------------------
 * setup()
 * ------------------------------------------------------------------ */
void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println("Lesson 4 - Structs and Pointers to Structs");
    Serial.println("-------------------------------------------");

    /* Initialise peripherals by passing pointers to their structs */
    gpio_pin_init(&led);
    button_init(&button);

    /* Print struct sizes — observe padding on ESP32-C3 */
    Serial.printf("sizeof(GpioPin_t) = %u bytes\n", sizeof(GpioPin_t));
    Serial.printf("sizeof(Button_t)  = %u bytes\n", sizeof(Button_t));
    Serial.printf("LED pin: %u  (active-%s)\n",
                  led.pin, led.active_high ? "high" : "low");
    Serial.printf("Button pin: %u  (active-%s, debounce: %u ms)\n",
                  button.pin, button.active_high ? "high" : "low",
                  button.debounce_ms);

    Serial.println("Setup complete. Press the button to toggle the LED.");
}

/* ------------------------------------------------------------------
 * loop()
 * ------------------------------------------------------------------ */
void loop()
{
    /* button_pressed() returns true once per confirmed press */
    if (button_pressed(&button)) {
        gpio_pin_toggle(&led);
        Serial.printf("Button pressed! LED is now %s\n",
                      gpio_pin_read(&led) ? "ON" : "OFF");

        /* Exercise 2: use a pointer to access led.pin via -> */
        /* GpioPin_t *p = &led; */
        /* Serial.printf("LED pin via pointer: %u\n", p->pin); */
    }
}
