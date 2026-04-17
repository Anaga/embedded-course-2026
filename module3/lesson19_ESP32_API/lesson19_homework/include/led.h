#pragma once

#include <stdint.h>

// Initialize the onboard WS2812 LED (GPIO 8).
void initLed();

// Set the LED color based on the current price relative to
// today's min and max.
// ratio 0.0 -> green (cheap)
// ratio 1.0 -> red   (expensive)
void showPrice(float curPrice, float minPrice, float maxPrice);

// Turn off the LED.
void ledOff();
