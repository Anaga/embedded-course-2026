/**
 * Lesson 3: Button Counter with Debounce
 * 
 * Practice exercise: Read a push button, debounce it,
 * count presses, and print the counter to Serial Monitor.
 *
 * Wiring:
 *   Button Pin 1 --> GPIO 3
 *   Button Pin 2 --> GND
 *   (No external resistor needed -- we use INPUT_PULLUP)
 *
 * Topics covered:
 *   - if/else (button state check)
 *   - while(1) via loop() (main loop)
 *   - Functions (debounce logic)
 *   - Serial.printf() (formatted output)
 */

#include <Arduino.h>

// ---------------------------------------------------------
// Constants
// ---------------------------------------------------------
#define BUTTON_PIN    3
#define DEBOUNCE_MS   50

// ---------------------------------------------------------
// Global variables
// ---------------------------------------------------------
int counter   = 0;
int lastState = HIGH;  // INPUT_PULLUP: HIGH when not pressed

// ---------------------------------------------------------
// Functions
// ---------------------------------------------------------

/**
 * isButtonPressed()
 * 
 * Reads the button with simple delay-based debounce.
 * Returns true on a falling edge (button was just pressed).
 *
 * How it works:
 *   1. Read the current pin state
 *   2. If we detect a HIGH -> LOW transition (press):
 *      a. Wait DEBOUNCE_MS to let the contacts settle
 *      b. Read again to confirm it is still LOW
 *      c. Update lastState
 *      d. Return true if confirmed
 *   3. Otherwise update lastState and return false
 */
bool isButtonPressed() {
  // TODO: Read the current button state using digitalRead()
  int reading = 0;  // <-- fix this line

  // TODO: Check for falling edge (HIGH -> LOW transition)
  //       Remember: INPUT_PULLUP means LOW = pressed
  if (false) {  // <-- fix this condition

    // TODO: Wait for debounce period
    // ...

    // TODO: Read the button state again to confirm
    // ...

    // TODO: Update lastState and return true if still pressed
    lastState = reading;
    return false;  // <-- fix this return
  }

  lastState = reading;
  return false;
}

/**
 * printCounter()
 *
 * Prints the current counter value to Serial using printf format.
 * Shows the count in decimal with a message.
 */
void printCounter(int count) {
  // TODO: Use Serial.printf() to print a formatted message
  //       Example output: "Button pressed! Count: 5"
  //       Hint: %d is the format specifier for integers
}

// ---------------------------------------------------------
// Arduino setup & loop
// ---------------------------------------------------------

void setup() {
  Serial.begin(115200);
  delay(1000);  // Wait for Serial Monitor to connect

  // TODO: Configure BUTTON_PIN as INPUT_PULLUP
  // ...

  Serial.printf("=================================\n");
  Serial.printf("  Lesson 3: Button Counter\n");
  Serial.printf("  Press the button to count!\n");
  Serial.printf("=================================\n");
}

void loop() {
  // TODO: Call isButtonPressed() and if true:
  //       1. Increment counter
  //       2. Call printCounter()

}
