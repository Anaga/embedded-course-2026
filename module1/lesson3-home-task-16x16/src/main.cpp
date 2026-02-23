/**
 * Lesson 3 - Home Task
 * 16x16 Multiplication Table with Button Mode Switch (OCT / DEC / HEX)
 *
 * Wiring (ESP32-C3):
 * - Button pin 1 -> GPIO 3
 * - Button pin 2 -> GND
 * - We use INPUT_PULLUP, so:
 *     Not pressed = HIGH (1)
 *     Pressed     = LOW  (0)
 *
 * Behavior:
 * - Each valid button press changes mode:
 *     OCT -> DEC -> HEX -> OCT ...
 * - After changing mode, the program prints the 16x16 table in that mode.
 */

#include <Arduino.h>

// ----------------------------
// Constants
// ----------------------------
#define BUTTON_PIN   3
#define DEBOUNCE_MS  50

// Mode numbers (no typedef/enum, only integers)
#define MODE_OCT     0
#define MODE_DEC     1
#define MODE_HEX     2
#define MODE_COUNT   3

// ----------------------------
// Global variables
// ----------------------------
int mode = MODE_OCT;

// For edge detection (INPUT_PULLUP: HIGH when not pressed)
int lastState = HIGH;

// ----------------------------
// Function: read button with debounce and detect press event
// Returns true only when a press is confirmed (falling edge)
// ----------------------------
bool isButtonPressed() {

  // Read current pin level
  int reading = digitalRead(BUTTON_PIN);

  // Detect falling edge: HIGH -> LOW means "just pressed"
  if (lastState == HIGH && reading == LOW) {

    // Wait for contacts to settle (debounce)
    delay(DEBOUNCE_MS);

    // Read again to confirm it is still pressed
    reading = digitalRead(BUTTON_PIN);

    // Update lastState with the confirmed reading
    lastState = reading;

    // Return true only if still LOW after debounce
    return (reading == LOW);
  }

  // No press event, just update lastState
  lastState = reading;
  return false;
}

// ----------------------------
// Print a small header showing the current mode
// ----------------------------
void printModeHeader(int currentMode) {

  Serial.println();
  Serial.println("=================================");
  Serial.println("  16x16 Multiplication Table");
  Serial.print  ("  Mode: ");

  switch (currentMode) {
    case MODE_OCT:
      Serial.println("OCT (base 8)");
      break;

    case MODE_DEC:
      Serial.println("DEC (base 10)");
      break;

    case MODE_HEX:
      Serial.println("HEX (base 16)");
      break;

    default:
      Serial.println("UNKNOWN");
      break;
  }

  Serial.println("  Press button to change mode");
  Serial.println("=================================");
}

// ----------------------------
// Print one table cell in the selected mode
// We use fixed width so columns stay aligned.
// ----------------------------
void printCell(int currentMode, int value) {

  switch (currentMode) {

    case MODE_OCT:
      // %o = octal, wider spacing for readability
      Serial.printf("%6o", value);
      break;

    case MODE_DEC:
      // %d = decimal
      Serial.printf("%4d", value);
      break;

    case MODE_HEX:
      // %X = hex uppercase
      Serial.printf("%4X", value);
      break;

    default:
      Serial.printf("%4d", value);
      break;
  }
}

// ----------------------------
// Print the full 16x16 multiplication table
// ----------------------------
void printTable16x16(int currentMode) {

  // Optional: print column headers (1..16) in the same mode
  Serial.print("     "); // left margin for row labels
  for (int col = 1; col <= 16; col++) {
    printCell(currentMode, col);
  }
  Serial.println();

  // Print rows
  for (int row = 1; row <= 16; row++) {

    // Row label on the left (I keep it decimal to be clear)
    Serial.printf("%3d |", row);

    for (int col = 1; col <= 16; col++) {
      int result = row * col;
      printCell(currentMode, result);
    }

    Serial.println();
  }
}

// ----------------------------
// Arduino setup & loop
// ----------------------------
void setup() {

  Serial.begin(115200);
  delay(1000); // Wait for Serial Monitor

  // Configure button input with internal pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Print first table at startup
  printModeHeader(mode);
  printTable16x16(mode);
}

void loop() {

  // If button press is detected, change mode and print table again
  if (isButtonPressed()) {

    // Cycle mode: 0 -> 1 -> 2 -> 0 ...
    mode = (mode + 1) % MODE_COUNT;

    printModeHeader(mode);
    printTable16x16(mode);

    // Optional: wait until button is released
    // This avoids multiple triggers if the user keeps it pressed.
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(5);
    }
  }
}