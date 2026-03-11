#include <Arduino.h>
#include <stdint.h>

#include "dots.cpp"

// ============================================================
// Setup
// ============================================================
#define SERIAL_SPEED 115200
#define STARTUP_DELAY 3500

void setup() {
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);
    Serial.println(" ================================================= ");
    Serial.println("| Lesson 6 Demo  |");
    Serial.println(" ================================================= ");


    delay(5000); 
    point point_zero;
    Serial.println("point_zero created");
    delay(50);

    point bunny;
    point centre;

    point_zero.print();

    point point_one(5,10);

    Serial.println("point_one created");
    delay(50);
    point_one.print();

    Serial.println("get distance A");
    uint8_t distA = point_one.distance(point_zero, point_one);
    Serial.printf("distA is: %d \n", distA);
    delay(50);

    Serial.println("get distance B");
    uint8_t distB = point_zero.distance(point_one, point_zero);
    Serial.printf("distB is: %d \n", distB);
    delay(50);

}

void loop() {
            Serial.println("Tick");
            delay(5000); 

            Serial.println("Tack");
            delay(5000); 
        }

