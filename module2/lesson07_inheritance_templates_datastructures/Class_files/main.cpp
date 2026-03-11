#include <Arduino.h>
#include <stdint.h>
#define BTN_X_PIN   1
#define BTN_Y_PIN   0
#include "dots.h"

// --- ISR Shared Variables (must be volatile!) ---
volatile bool     button_X_Pressed = false;
volatile bool     button_Y_Pressed = false;

// --- Debounce ---
#define DEBOUNCE_MS 500
volatile uint32_t last_X_PressTime = 0;
volatile uint32_t last_Y_PressTime = 0;

// --- ISR: Keep it SHORT! ---
// IRAM_ATTR: tells compiler to place this function in Internal RAM
// Required on ESP32 because flash may be busy during interrupt
void IRAM_ATTR onButton_X_Press() {
    uint32_t now = millis();
    if (now - last_X_PressTime > DEBOUNCE_MS) {
        last_X_PressTime = now;
        button_X_Pressed = true;
    }
}

void IRAM_ATTR onButton_Y_Press() {
    uint32_t now = millis();
    if (now - last_Y_PressTime > DEBOUNCE_MS) {
        last_Y_PressTime = now;
        button_Y_Pressed = true;
    }
}


// ============================================================
// Setup
// ============================================================
#define SERIAL_SPEED 115200
#define STARTUP_DELAY 3500


point bunny;
point central(10,10);
uint8_t const radius = 5;

void setup() {

        // Configure pins
    pinMode(BTN_X_PIN, INPUT_PULLUP);
    pinMode(BTN_Y_PIN, INPUT_PULLUP);

        // Attach interrupt
    // FALLING = trigger when signal goes HIGH -> LOW (button pressed)
    attachInterrupt(digitalPinToInterrupt(BTN_X_PIN), onButton_X_Press, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_Y_PIN), onButton_Y_Press, FALLING);

    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);
    Serial.println(" ================================================= ");
    Serial.println("| Lesson 6 Demo  |");
    Serial.println(" ================================================= ");


    delay(5000); 
    point point_zero;
    Serial.println("point_zero created");
    delay(50);

    point_zero.print();

    Serial.println("get distance A");
    uint8_t distA = point_zero.distance(point_zero, central);
    Serial.printf("distA is: %d \n", distA);
    delay(50);


}


void main_game_logic(){
    // Print out the bunny position
    Serial.print("Bunni now on");
    bunny.print();

    // Get a distance
    uint8_t dist = central.distance(bunny, central);

    // Check the hole size
    if (dist >= radius){
        Serial.println("Bunni IN A HOLE");
    } else {
        Serial.println("continue travel Bunni");
    }

    delay(50);
    
}


void loop() {
    if (button_X_Pressed) {
        button_X_Pressed = false;  // Clear the flag
        //Serial.println("X move");
        bunny.move_x();
        main_game_logic();
    }

    if (button_Y_Pressed) {
        button_Y_Pressed = false;  // Clear the flag
        bunny.move_y();
        main_game_logic();
    }
}

