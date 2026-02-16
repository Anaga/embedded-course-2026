#include <Arduino.h>
#include <stdint.h>

#define LED_PIN 8  // Confirmed: LED on GPIO8

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    pinMode(LED_PIN, OUTPUT);
    
    Serial.println("\n=== ESP32-C3 Data Types Demo ===\n");
    
    // 1. sizeof() demonstration
    Serial.println("--- sizeof() Demonstration ---");
    Serial.printf("uint8_t:  %d byte\n", sizeof(uint8_t));
    Serial.printf("uint16_t: %d bytes\n", sizeof(uint16_t));
    Serial.printf("uint32_t: %d bytes\n", sizeof(uint32_t));
    Serial.printf("int8_t:   %d byte\n", sizeof(int8_t));
    Serial.printf("int16_t:  %d bytes\n", sizeof(int16_t));
    Serial.printf("int32_t:  %d bytes\n", sizeof(int32_t));
    Serial.printf("float:    %d bytes\n", sizeof(float));
    Serial.printf("double:   %d bytes\n", sizeof(double));
    Serial.println();
    
    // 2. Overflow demonstration
    Serial.println("--- Overflow Demonstration ---");
    uint8_t counter = 253;
    for(int i = 0; i < 5; i++) {
        Serial.printf("counter = %d\n", counter);
        counter++;
    }
    Serial.println("Notice: 255 -> 0 (overflow!)\n");
    
    // 3. Type casting demonstration
    Serial.println("--- Type Casting Demonstration ---");
    uint16_t big = 1000;
    uint8_t small = big;  // Data loss!
    Serial.printf("big (uint16_t) = %d\n", big);
    Serial.printf("small (uint8_t) = %d (data loss!)\n", small);
    Serial.printf("1000 = 0x%04X, lower byte = 0x%02X = %d\n\n", big, small, small);
    
    // 4. Negative to unsigned casting
    int16_t temp = -10;
    uint16_t positive = (uint16_t)temp;
    Serial.printf("temp (int16_t) = %d\n", temp);
    Serial.printf("positive (uint16_t) = %u (wrong!)\n\n", positive);
    
    Serial.println("=== Demo Complete ===\n");
    Serial.println("LED will blink every second...\n");
}

void loop() {
    // Blink LED
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    
    // Print timestamp using uint32_t
    static uint8_t count = 0;
    count++;
    
    uint32_t timestamp = millis();
    Serial.printf("Count: %d, Uptime: %lu ms\n", count, timestamp);
}