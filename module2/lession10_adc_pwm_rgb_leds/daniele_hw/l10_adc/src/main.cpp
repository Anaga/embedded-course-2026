#include <Arduino.h>
#include "Potentiometer.h"
#include "rgbLed.h"

using namespace drivers;

// Potenziometro su GPIO 2
static Potentiometer pot(2);

// RGB LED:
// R = GPIO10
// G = GPIO0
// B = GPIO1
static RgbLed rgb(10, 0, 1);

void setup() {
    Serial.begin(115200);
}

void loop() {
    uint8_t pct = pot.readPercent();

    if (pct <= 33) {
        rgb.setColor(255, 0, 0); // RED
        Serial.println("Zone: RED");
    } 
    else if (pct <= 66) {
        rgb.setColor(0, 255, 0); // GREEN
        Serial.println("Zone: GREEN");
    } 
    else {
        rgb.setColor(0, 0, 255); // BLUE
        Serial.println("Zone: BLUE");
    }

    delay(50);
}