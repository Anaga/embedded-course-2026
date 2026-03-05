/**
 * Lesson 5 - Example 2: PWM Basics with LEDC
 * 
 * Demonstrates:
 *   - ESP32 LEDC peripheral for PWM output
 *   - ledcAttach() and ledcWrite() API (Arduino Core 3.x)
 *   - Frequency and resolution concepts
 *   - LED fading effect
 * 
 * Hardware:
 *   - ESP32-C3 Super Mini
 *   - External LED on GPIO3 (with 220-330 ohm resistor)
 *   OR use built-in LED on GPIO8
 * 
 * Wiring:
 *   GPIO3 -> 220R resistor -> LED anode -> LED cathode -> GND
 */

#include <Arduino.h>

// --- Pin Definitions ---
#define LED_PIN     3     // External LED (change to 8 for built-in)

// --- PWM Configuration ---
#define PWM_FREQ    5000  // 5 kHz - good for LEDs (no visible flicker)
#define PWM_RES     8     // 8-bit resolution: duty 0..255

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== PWM Basics Demo ===");

    // Attach PWM to pin
    // New API (ESP32 Arduino Core 3.x): ledcAttach(pin, freq, resolution)
    // This replaces the old ledcSetup() + ledcAttachPin() combo
    bool ok = ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
    
    if (ok) {
        Serial.printf("PWM attached: pin=%d, freq=%d Hz, resolution=%d bits\n",
                       LED_PIN, PWM_FREQ, PWM_RES);
        Serial.printf("Duty range: 0..%d\n", (1 << PWM_RES) - 1);
    } else {
        Serial.println("ERROR: Failed to attach PWM!");
    }
}

void loop() {
    // --- Fade In ---
    Serial.println("Fading in...");
    for (int duty = 0; duty <= 255; duty++) {
        ledcWrite(LED_PIN, duty);
        delay(5);  // ~1.3 seconds total fade
    }

    delay(500);

    // --- Fade Out ---
    Serial.println("Fading out...");
    for (int duty = 255; duty >= 0; duty--) {
        ledcWrite(LED_PIN, duty);
        delay(5);
    }

    delay(500);

    // --- Discrete Brightness Steps ---
    Serial.println("Brightness steps: 0%, 25%, 50%, 75%, 100%");
    
    uint8_t steps[] = {0, 64, 128, 192, 255};
    const char* labels[] = {"0%", "25%", "50%", "75%", "100%"};
    
    for (int i = 0; i < 5; i++) {
        ledcWrite(LED_PIN, steps[i]);
        Serial.printf("  %s (duty=%d)\n", labels[i], steps[i]);
        delay(1000);
    }

    ledcWrite(LED_PIN, 0);
    delay(1000);
}
