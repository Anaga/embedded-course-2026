/**
 * Lesson 5 - Example 1: Interrupt Basics
 * 
 * Demonstrates:
 *   - Hardware interrupt on button press
 *   - volatile keyword for shared variables
 *   - IRAM_ATTR for ESP32 ISR placement
 *   - Debouncing inside ISR using millis()
 * 
 * Hardware:
 *   - ESP32-C3 Super Mini
 *   - Button on GPIO9 (active LOW, internal pull-up)
 *   - Built-in LED on GPIO8
 * 
 * Wiring:
 *   Button: one side to GPIO9, other side to GND
 */

#include <Arduino.h>

// --- Pin Definitions ---
#define BTN_PIN   9   // Boot button on ESP32-C3 Super Mini
#define LED_PIN   8   // Built-in LED

// --- ISR Shared Variables (must be volatile!) ---
volatile bool     buttonPressed = false;
volatile uint32_t pressCount    = 0;

// --- Debounce ---
#define DEBOUNCE_MS 200
volatile uint32_t lastPressTime = 0;

// --- ISR: Keep it SHORT! ---
// IRAM_ATTR: tells compiler to place this function in Internal RAM
// Required on ESP32 because flash may be busy during interrupt
void IRAM_ATTR onButtonPress() {
    uint32_t now = millis();
    if (now - lastPressTime > DEBOUNCE_MS) {
        lastPressTime = now;
        buttonPressed = true;
        pressCount++;
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== Interrupt Basics Demo ===");

    // Configure pins
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // LED off (active LOW on most ESP32-C3 boards)

    // Attach interrupt
    // FALLING = trigger when signal goes HIGH -> LOW (button pressed)
    attachInterrupt(digitalPinToInterrupt(BTN_PIN), onButtonPress, FALLING);

    Serial.println("Press the button...");
}

void loop() {
    // Check the flag set by ISR
    // All heavy work happens here in loop(), NOT in the ISR!
    if (buttonPressed) {
        buttonPressed = false;  // Clear the flag

        // Toggle LED
        static bool ledState = false;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? LOW : HIGH);  // Active LOW

        // Safe to use Serial here (NOT inside ISR!)
        Serial.printf("Button pressed! Count: %lu, LED: %s\n",
                       pressCount, ledState ? "ON" : "OFF");
    }

    // CPU is free to do other work here!
    // Unlike polling, we don't waste cycles checking the button
}
