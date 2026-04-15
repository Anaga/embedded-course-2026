// =============================================================
// Lesson 17 -- PIO: Hardware WS2812 Driver
// Fundamentals of C++ for Microcontrollers
//
// Board:  TENSTAR RP2350-USB (RP2350A, 16MB)
//   - Onboard WS2812 RGB LED on GP22  (PIO0, SM0)
//   - External 10-LED WS2812 ring on GP15 (PIO0, SM1)
//   - CPU probe on GP14 (toggles HIGH during LED update)
//
// This demo:
//   1. Initialize two PIO state machines (one per LED output)
//   2. Run rainbow animation on ring + mirror to onboard LED
//   3. Measure and print CPU time spent on LED updates
//
// Compare with Lesson 16 bit-bang:
//   Bit-bang: CPU blocked ~300 us per update, interrupts disabled
//   PIO:     CPU writes FIFO in ~5 us, then is free
// =============================================================

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "ws2812_pio.h"

// ----- Pin Assignment ----------------------------------------
static const uint ONBOARD_LED_PIN = 22;
static const uint RING_PIN        = 15;
static const uint PROBE_PIN       = 14;   // CPU time measurement
static const uint NUM_RING_LEDS   = 10;

// ----- Brightness limit (USB power safety) -------------------
static const uint8_t MAX_BRIGHTNESS = 64;

// ----- PIO resources -----------------------------------------
static PIO  pio_hw = pio0;
static uint sm_onboard;
static uint sm_ring;
static uint pio_offset;

// =============================================================
//  Pixel type and color utilities
// =============================================================
struct Pixel {
    uint8_t r, g, b;
};

static Pixel ring_buffer[NUM_RING_LEDS];

static uint8_t dim(uint8_t val) {
    return (uint8_t)((uint16_t)val * MAX_BRIGHTNESS / 255);
}

static Pixel hsv_to_rgb(uint8_t hue, uint8_t sat, uint8_t val) {
    uint8_t region = hue / 43;
    uint8_t remainder = (hue - region * 43) * 6;
    uint8_t p = (uint8_t)((uint16_t)val * (255 - sat) / 255);
    uint8_t q = (uint8_t)((uint16_t)val * (255 - (uint16_t)sat * remainder / 255) / 255);
    uint8_t t = (uint8_t)((uint16_t)val * (255 - (uint16_t)sat * (255 - remainder) / 255) / 255);
    Pixel px;
    switch (region) {
        case 0:  px = { val, t, p };   break;
        case 1:  px = { q, val, p };   break;
        case 2:  px = { p, val, t };   break;
        case 3:  px = { p, q, val };   break;
        case 4:  px = { t, p, val };   break;
        default: px = { val, p, q };   break;
    }
    px.r = dim(px.r);
    px.g = dim(px.g);
    px.b = dim(px.b);
    return px;
}

// =============================================================
//  PIO pixel output
//
//  Pack RGB into GRB 32-bit word and write to FIFO.
//  The PIO state machine handles all timing from here.
//  CPU is free immediately after the FIFO write returns.
// =============================================================
static inline uint32_t pixel_to_grb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)g << 24) | ((uint32_t)r << 16) | ((uint32_t)b << 8);
}

static void pio_put_pixel(uint sm, uint8_t r, uint8_t g, uint8_t b) {
    pio_sm_put_blocking(pio_hw, sm, pixel_to_grb(r, g, b));
}

static void pio_show_ring(uint sm, const Pixel* px, uint count) {
    for (uint i = 0; i < count; i++) {
        pio_sm_put_blocking(pio_hw, sm, pixel_to_grb(px[i].r, px[i].g, px[i].b));
    }
}

// =============================================================
//  setup()
// =============================================================
void setup() {
    Serial.begin(115200);
    sleep_ms(1000);

    // --- CPU measurement probe ---
    gpio_init(PROBE_PIN);
    gpio_set_dir(PROBE_PIN, GPIO_OUT);
    gpio_put(PROBE_PIN, 0);

    // --- Initialize PIO ---
    // Both state machines share the same PIO program (loaded once)
    // but run independently on different GPIO pins.

    // Claim two state machines
    sm_onboard = pio_claim_unused_sm(pio_hw, true);
    sm_ring    = pio_claim_unused_sm(pio_hw, true);

    // Load the program once into PIO instruction memory
    pio_offset = pio_add_program(pio_hw, &ws2812_program);

    // Initialize each SM for its respective GPIO pin
    ws2812_pio_init(pio_hw, sm_onboard, pio_offset, ONBOARD_LED_PIN);
    ws2812_pio_init(pio_hw, sm_ring,    pio_offset, RING_PIN);

    // Clear all LEDs
    pio_put_pixel(sm_onboard, 0, 0, 0);
    memset(ring_buffer, 0, sizeof(ring_buffer));
    pio_show_ring(sm_ring, ring_buffer, NUM_RING_LEDS);
    sleep_ms(100);   // Allow reset pulse

    Serial.println("=== Lesson 17: PIO WS2812 Driver ===");
    Serial.print("PIO block      : pio0");
    Serial.println();
    Serial.print("SM onboard LED : ");
    Serial.print(sm_onboard);
    Serial.print(" (GP");
    Serial.print(ONBOARD_LED_PIN);
    Serial.println(")");
    Serial.print("SM ring        : ");
    Serial.print(sm_ring);
    Serial.print(" (GP");
    Serial.print(RING_PIN);
    Serial.println(")");
    Serial.print("Probe pin      : GP");
    Serial.println(PROBE_PIN);
    Serial.print("Brightness     : ");
    Serial.print(MAX_BRIGHTNESS);
    Serial.println(" / 255");
    Serial.println("------------------------------------");
    Serial.println("Running rainbow... CPU time printed every 100 frames.");
    Serial.println();
}

// =============================================================
//  loop() -- Rainbow animation with CPU time measurement
// =============================================================
void loop() {
    static uint16_t hue_offset = 0;
    static uint32_t frame_count = 0;
    static uint32_t total_update_us = 0;

    // ---- Measure CPU time for the LED update ----
    gpio_put(PROBE_PIN, 1);                       // Probe HIGH
    uint32_t t_start = time_us_32();

    // Fill ring buffer with rainbow
    for (uint i = 0; i < NUM_RING_LEDS; i++) {
        uint8_t hue = (uint8_t)(hue_offset + i * 256 / NUM_RING_LEDS);
        ring_buffer[i] = hsv_to_rgb(hue, 255, 255);
    }

    // Push to ring via PIO FIFO
    pio_show_ring(sm_ring, ring_buffer, NUM_RING_LEDS);

    // Mirror first LED to onboard
    pio_put_pixel(sm_onboard,
                  ring_buffer[0].r,
                  ring_buffer[0].g,
                  ring_buffer[0].b);

    uint32_t t_end = time_us_32();
    gpio_put(PROBE_PIN, 0);                       // Probe LOW

    total_update_us += (t_end - t_start);
    frame_count++;

    // Print average CPU time every 100 frames
    if (frame_count % 100 == 0) {
        uint32_t avg_us = total_update_us / 100;
        Serial.print("Frame ");
        Serial.print(frame_count);
        Serial.print("  Avg CPU time: ");
        Serial.print(avg_us);
        Serial.print(" us  (compare: bit-bang ~300 us)");
        Serial.println();
        total_update_us = 0;
    }

    hue_offset += 2;
    sleep_ms(30);   // ~33 FPS
}
