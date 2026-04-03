// =============================================================
// Lesson 15 -- RP2350 USB Blink Demo
// Fundamentals of C++ for Microcontrollers
//
// Hardware:  RP2350 USB dongle  (no onboard LED)
//            External LED on GPIO 15 via 330 Ohm to GND
//
// SDK style: Native Pico SDK API calls (gpio_init, gpio_put)
//            inside Arduino setup()/loop() entry point.
//
// Why setup()/loop()?
//   PlatformIO's Arduino framework provides the build system
//   and USB CDC serial.  The earlephilhower core links the
//   full Pico SDK underneath, so all SDK functions work as-is.
// =============================================================

#include <Arduino.h>          // Arduino wrapper (provides setup/loop)
#include "pico/stdlib.h"      // Pico SDK core: gpio, sleep, stdio
#include "hardware/gpio.h"    // Pico SDK GPIO API (explicit include)

// ----- Pin Assignment ------------------------------------
static const uint LED_PIN = 15;   // External LED, no onboard LED on this board

// ----- Blink timing --------------------------------------
static const uint32_t BLINK_ON_MS  = 500;
static const uint32_t BLINK_OFF_MS = 500;

// =============================================================
//  setup() -- runs once after boot
// =============================================================
void setup() {
    // Initialize USB CDC serial (provided by Arduino core)
    Serial.begin(115200);

    // Wait a moment for USB enumeration on host
    sleep_ms(1000);

    // --- Pico SDK GPIO setup ---
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);   // Start with LED off

    // Announce ourselves
    Serial.println("=== Lesson 15: RP2350 Blink Demo ===");
    Serial.print("LED pin : GPIO ");
    Serial.println(LED_PIN);
    Serial.print("CPU     : ");
    Serial.print(rp2040.f_cpu() / 1000000);
    Serial.println(" MHz");
    Serial.println("------------------------------------");
}

// =============================================================
//  loop() -- runs repeatedly
// =============================================================
void loop() {
    static uint32_t cycle = 0;

    // LED ON
    gpio_put(LED_PIN, 1);
    Serial.print("Blink #");
    Serial.print(cycle);
    Serial.println("  ON");
    sleep_ms(BLINK_ON_MS);

    // LED OFF
    gpio_put(LED_PIN, 0);
    Serial.print("Blink #");
    Serial.print(cycle);
    Serial.println("  OFF");
    sleep_ms(BLINK_OFF_MS);

    cycle++;
}
