/**
 * Lesson 3 Homework: 16x16 Multiplication Table
 *
 * Button cycles display mode: OCT -> DEC -> HEX -> OCT -> ...
 * See home_task.md for full requirements.
 */
#include <Arduino.h>
#include <stdint.h>

#define BUTTON_PIN    3
#define DEBOUNCE_MS   50
#define TABLE_SIZE    16
#define SERIAL_SPEED   (115200u)
#define ONE_SEC_DELAY  (1000u)

void setup() {
  Serial.begin(SERIAL_SPEED);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(ONE_SEC_DELAY);

  Serial.printf("================================================\n");
  Serial.printf(" Lesson 3: Homework 16x16 Multiplication Table  \n");
  Serial.printf(" Press the button to display different view!     \n");
  Serial.printf("================================================\n");

  // TODO: Print the table on startup
}

void loop() {
  // TODO: Check button, switch mode, reprint table
}
