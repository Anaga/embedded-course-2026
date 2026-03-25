#include <Arduino.h>

// GPIO 2 = ADC-capable pin on ESP32-C3
// static Potentiometer pot(2);
#define POT_PIN_X 4
#define POT_PIN_Y 0

hw_timer_t *timer = NULL;
boolean time_to_read = false;

void IRAM_ATTR on5MsTick(){ time_to_read = true; }

void setup()
{
    Serial.begin(115200);
    Serial.println("Lesson 10: ADC demo");
    
    // Create hardware timer (1 MHz clock)
    timer = timerBegin(0, 80, true);   // Timer 0, prescaler=80 → 1µs per tick

    // Attach interrupt handler
    timerAttachInterrupt(timer, &on5MsTick, true);

    // Set alarm to fire every 50,000µs (50ms)
    timerAlarmWrite(timer, 50000, true);

    // Start timer
    timerAlarmEnable(timer);
}

void loop()
{
  u16_t adc_val_x = 0;
  u16_t adc_val_y = 0;
  if (time_to_read) {
      adc_val_x = analogRead(POT_PIN_X);
      adc_val_y = analogRead(POT_PIN_Y);
      timerStart(timer);
      time_to_read = false;
  }
  //  Serial.printf("ADC value ");
  Serial.printf("ADC value X %d, Y %d  \n",adc_val_x, adc_val_y);
  delay(1000);
}
