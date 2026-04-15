#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  12
#define LEDS_PIN	2
#define CHANNEL		0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
  strip.begin();
  strip.setBrightness(0);  
}

void loop() {
  // Chase
  /* for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, 255, 255, 0);
	  strip.show();
    delay(100);
    strip.setLedColorData(i, 0, 0, 0);
  } */

  // Breathe
  for (int b = 0; b <= 255; b++) {
    strip.setBrightness(b);
    strip.setAllLedsColorData(255, 255, 0);
	  strip.show();
    delay(10);
  }
    for (int b = 255; b <= 0; b--) {
    //strip.setBrightness(b);
    strip.setAllLedsColorData(0, 0, 0);
	  strip.show();
    delay(10);
  } 

  // ColorWipe
  // Fill ring one LED at a time 
  /* for (int i = 0; i < LEDS_COUNT; i++) {
   strip.setLedColorData(i, 0, 200, 80); 
   strip.show(); 
   delay(80); 
   } 
   // Clear ring one LED at a time 
   for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, 0, 0, 0); 
    strip.show(); 
    delay(80); 
    } */

  // Rainbow spin
  /* for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  }  */



  // Accident - chase reversed
  /* for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorAndBrightnessData(i, 255, 0);
	  strip.show();
    delay(1000);
    strip.setLedColorAndBrightnessData(i, 255, 1);
  } */
}
