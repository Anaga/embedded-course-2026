#include <Arduino.h>
#include <stdint.h>

#include "dots.h"

// ============================================================
// Setup
// ============================================================
#define SERIAL_SPEED 115200
#define STARTUP_DELAY 1500

void setup() {
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);
    Serial.println(" ================================================= ");
    Serial.println("|  Lesson 6 Demo  |");
    Serial.println(" ================================================= ");

    delay(5000);
    point point_zero;
    point_zero.print();

    point point_one(5,10);
    point_one.print();

    uint8_t distA = point_one.distance(point_zero, point_one);

    uint8_t distB = point_zero.distance(point_one, point_zero);
    Serial.printf("distA is: %d \n", distA);
    Serial.printf("distB is: %d \n", distB);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Tick");
  delay(500);

  Serial.println("Tack");
  delay(500);
}
