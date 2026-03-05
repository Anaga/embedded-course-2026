/**
 * Lesson 5 - Homework: RGB PWM Controller
 * 
 * YOUR TASK:
 *   Build an RGB LED controller that cycles through colors
 *   using a button interrupt and PWM output.
 * 
 * Requirements:
 *   1. Define a color enum with at least 6 colors
 *   2. Use a hardware interrupt for button press (NOT polling!)
 *   3. Output PWM to RGB LED using ledcAttach() / ledcWrite()
 *   4. Implement debounce for the button interrupt
 *   5. Print the current color name to Serial on each change
 * 
 * Bonus:
 *   - Smooth fade transition between colors
 *   - Second button for brightness control
 *   - Auto-cycle mode using a timer
 * 
 * Hardware:
 *   - ESP32-C3 Super Mini
 *   - Common Cathode RGB LED (or 3 separate LEDs)
 *   - 220 ohm resistors (one per LED channel)
 *   - Push button
 * 
 * Hints:
 *   - Use millis() for debounce timing inside ISR
 *   - Store color RGB values in a struct array indexed by enum
 *   - Use COLOR_COUNT as the last enum value for modulo wrap
 *   - Remember: ISR must be IRAM_ATTR and SHORT!
 *   - Remember: shared variables must be volatile!
 */

#include <Arduino.h>
#include <stdint.h>

// ============================================================
// TODO: Define your pin numbers
// ============================================================
#define PIN_RED     0   // Change to your actual GPIO
#define PIN_GREEN   0   // Change to your actual GPIO
#define PIN_BLUE    0   // Change to your actual GPIO
#define PIN_BUTTON  0   // Change to your actual GPIO

// ============================================================
// TODO: Define PWM parameters
// ============================================================
#define PWM_FREQ    0   // Choose a good frequency for LEDs
#define PWM_RES     0   // Choose resolution (8-bit is a good start)

// ============================================================
// TODO: Define debounce time
// ============================================================
#define DEBOUNCE_MS 0

// ============================================================
// TODO: Create your color enum
// Hint: end with a _COUNT entry for easy modulo wrap
// ============================================================
typedef enum {
    // Define at least 6 colors here
    
    COLOR_COUNT     // Keep this last!
} color_t;

// ============================================================
// TODO: Create a struct to hold RGB values + color name
// ============================================================


// ============================================================
// TODO: Create a color lookup table (array of structs)
// Hint: use designated initializers like [COLOR_RED] = { ... }
// ============================================================


// ============================================================
// TODO: Declare ISR shared variables (volatile!)
// ============================================================


// ============================================================
// TODO: Write the ISR function
// Remember: IRAM_ATTR, keep it SHORT, debounce with millis()
// ============================================================


// ============================================================
// TODO: Write a function to apply a color to the RGB LED
// ============================================================


// ============================================================
// Setup
// ============================================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("RGB PWM Controller - Homework");

    // TODO: Initialize PWM channels with ledcAttach()

    // TODO: Configure button pin with pull-up

    // TODO: Attach interrupt

    // TODO: Set initial color
}

// ============================================================
// Main Loop
// ============================================================
void loop() {
    // TODO: Check button flag, advance color, apply it
}
