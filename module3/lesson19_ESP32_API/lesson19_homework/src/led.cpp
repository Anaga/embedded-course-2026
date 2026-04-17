#include "led.h"
#include "config.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

static Adafruit_NeoPixel strip(
    ONBOARD_LED_CNT,
    ONBOARD_LED_PIN,
    NEO_GRB + NEO_KHZ800);

void initLed() {
    strip.begin();
    strip.setBrightness(MAX_BRIGHTNESS);
    strip.show();  // All pixels off
}

void showPrice(float curPrice, float minPrice, float maxPrice) {
    float ratio = (curPrice - minPrice) / (maxPrice - minPrice);
    ratio = constrain(ratio, 0.0f, 1.0f);

    // Green (cheap) -> Red (expensive)
    uint8_t r = (uint8_t)(ratio * 255.0f);
    uint8_t g = (uint8_t)((1.0f - ratio) * 255.0f);

    strip.setPixelColor(0, strip.Color(r, g, 0u));
    strip.show();
}

void ledOff() {
    strip.setPixelColor(0, strip.Color(0u, 0u, 0u));
    strip.show();
}
