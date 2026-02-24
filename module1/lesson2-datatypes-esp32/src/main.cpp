/**
 * Lesson 2: Data Types in C
 * ESP32-C3 Demonstration Project
 * 
 * This project demonstrates:
 * 1. sizeof() operator for different data types
 * 2. Integer overflow behavior
 * 3. Type casting and data loss
 * 4. Proper use of stdint.h types
 */

#include <Arduino.h>
#include <stdint.h>

// LED pin for ESP32-C3 Super Mini
#define LED_PIN 8

void setup() {
    // Initialize Serial communication
    Serial.begin(115200);
    delay(10000);
    
    // Configure LED pin
    pinMode(LED_PIN, OUTPUT);
    
    Serial.println("\n=== ESP32-C3 Data Types Demo ===\n");
    
    // ========================================
    // 1. sizeof() Demonstration
    // ========================================
    Serial.println("--- sizeof() Demonstration ---\n\r");
    Serial.printf("uint8_t:  %d byte\n\r", sizeof(uint8_t));
    Serial.printf("uint16_t: %d bytes\n\r", sizeof(uint16_t));
    Serial.printf("uint32_t: %d bytes\n\r", sizeof(uint32_t));
    Serial.printf("int8_t:   %d byte\n\r", sizeof(int8_t));
    Serial.printf("int16_t:  %d bytes\n\r", sizeof(int16_t));
    Serial.printf("int32_t:  %d bytes\n\r", sizeof(int32_t));
    Serial.printf("float:    %d bytes\n\r", sizeof(float));
    Serial.printf("double:   %d bytes\n\r", sizeof(double));
    Serial.println();
    
    // ========================================
    // 2. Overflow Demonstration
    // ========================================
    Serial.println("--- Overflow Demonstration ---");
    Serial.println("uint8_t overflow (unsigned):");
    uint8_t counter = 253;
    for(int i = 0; i < 5; i++) {
        Serial.printf("counter = %d\n", counter);
        counter++;
    }
    Serial.println("Notice: 255 -> 0 (wraps around!)\n");
    
    // ========================================
    // 3. Type Casting Demonstration
    // ========================================
    Serial.println("--- Type Casting Demonstration ---");
    
    // Example 1: Data loss when downsizing
    uint16_t big = 100;
    uint8_t small = big;  // Implicit cast - data loss!
    Serial.printf("big (uint16_t) = %d\n", big);
    Serial.printf("small (uint8_t) = %d (data loss!)\n", small);
    Serial.printf("Explanation: 1000 = 0x%04X, lower byte = 0x%02X = %d\n\n", 
                  big, small, small);
    
    // Example 2: Negative to unsigned casting
    int16_t temp = -10;
    uint16_t positive = (uint16_t)temp;  // Explicit cast
    Serial.printf("temp (int16_t) = %d\n", temp);
    Serial.printf("positive (uint16_t) = %u (becomes huge!)\n\n", positive);
    
    Serial.println("=== Demo Complete ===\n");
    Serial.println("LED will blink every second...\n");
}

void loop() {
    // Blink LED to show program is running
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    
    // Print timestamp using proper uint32_t type
    static uint8_t count = 0;
    count++;
    
    uint32_t timestamp = millis();
    Serial.printf("Count: %d, Uptime: %lu ms\n", count, timestamp);
}
