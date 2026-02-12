#include <Arduino.h>

#define LED1 21
#define LED2 22
#define LED3 23
#define BTN  19   // Safe GPIO for button (using internal pull-up)

int currentLed = 0;
bool lastButtonState = HIGH;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Button wired to GND when pressed (INPUT_PULLUP keeps it HIGH when released)
  pinMode(BTN, INPUT_PULLUP);

  // All LEDs OFF at startup
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() {
  bool buttonState = digitalRead(BTN);

  // Detect button PRESS (falling edge: HIGH -> LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {

    // Turn all LEDs OFF
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

    // Turn ON current LED
    if (currentLed == 0) digitalWrite(LED1, HIGH);
    if (currentLed == 1) digitalWrite(LED2, HIGH);
    if (currentLed == 2) digitalWrite(LED3, HIGH);

    // Move to next LED in the sequence
    currentLed++;
    if (currentLed > 2) currentLed = 0;

    delay(200); // Simple debounce
  }

  lastButtonState = buttonState;
}
