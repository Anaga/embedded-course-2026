#include <Arduino.h>
#include "potentiometer.h"
#include "led.h"

// GPIO 2 = ADC-capable pin on ESP32-C3
// static Potentiometer pot(2);
#define POT_PIN 2

hw_timer_t *timer = NULL;
boolean time_to_read = false;

void IRAM_ATTR on5MsTick() {

  time_to_read = false;
}

void setup() {
  Serial.begin(115200);
  // lesson 10 print

  timer = timerBegin(0, 80, true);

  timerAttachInterrupt(timer, &on5MsTick, true);

  timerAlarmWrite (timer, 50000, true);

  timerAlarmEnable(timer);

  timerStart(timer);
}

void loop() {
  u16_t adc_val = 0;
  if (time_to_read) {
    adc_val = analogRead(POT_PIN);
    timerStart(timer);
    time_to_read = false;
  }
  // adc_val = analogRead(POT_PIN);
  Serial.printf("ADC value %d \n", adc_val);
  delay(1000);
}