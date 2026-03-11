#include <Arduino.h>
#include "pin_owner.h"


// -- Hardware pins --
static constexpr uint8_t PIN_RED_LED   = 3;
static constexpr uint8_t PIN_GREEN_LED = 10;
static constexpr uint8_t PIN_BTN_0     = 0;
static constexpr uint8_t PIN_BTN_1     = 1;

// -- Button debounce --
static constexpr uint32_t DEBOUNCE_MS = 250U;
static volatile uint32_t lastBtn0Press = 0;
static volatile uint32_t lastBtn1Press = 0;
static volatile bool btn0Flag = false;
static volatile bool btn1Flag = false;

// -- ISRs --
void IRAM_ATTR onBtn0() {
    uint32_t now = millis();
    if (now - lastBtn0Press > DEBOUNCE_MS) {
        lastBtn0Press = now;
        btn0Flag = true;
    }
}

void IRAM_ATTR onBtn1() {
    uint32_t now = millis();
    if (now - lastBtn1Press > DEBOUNCE_MS) {
        lastBtn1Press = now;
        btn1Flag = true;
    }
}

// Simulates a function with an early return.
// The PinOwner destructor runs even though we return before the end.
void earlyReturnDemo() {
    PinOwner greenLed(PIN_GREEN_LED, true);
    greenLed.on();
    delay(2500);

    // Simulate an error condition
    bool error = true;
    if (error) {
        Serial.println("  Error detected! Returning early...");
        return;  // <-- destructor STILL runs here!
    }

    // This code is unreachable, but that is fine:
    // cleanup happens regardless.
    Serial.println("  This line never executes.");
}



// ====================================================================
// Setup and Loop
// ====================================================================

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("+==========================================+");
    Serial.println("|  Lesson 8: RAII & Memory Handling Demo   |");
    Serial.println("+------------------------------------------+");
    Serial.println("|  BTN_0 (GPIO 0): RAII scope demo         |");
    Serial.println("|  BTN_1 (GPIO 1): Heap fragmentation demo |");
    Serial.println("+==========================================+");
    Serial.println();

        // Configure buttons with internal pull-ups
    pinMode(PIN_BTN_0, INPUT_PULLUP);
    pinMode(PIN_BTN_1, INPUT_PULLUP);

    // Attach interrupts (falling edge = button pressed)
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_0), onBtn0, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_1), onBtn1, FALLING);

    Serial.println();
    Serial.println("Press BTN_0 or BTN_1 to start a demo...");
}

void loop() {

    if (btn0Flag) {
      Serial.println("Tick");
      btn0Flag = false;
      earlyReturnDemo();
      delay(1000);
    }

    Serial.println("Tack");
    delay(1000);
}