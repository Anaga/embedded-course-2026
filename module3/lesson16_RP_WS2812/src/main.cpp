// =============================================================
// Lesson 16 -- WS2812 Addressable LEDs: Bit-Bang Driver
// Fundamentals of C++ for Microcontrollers
//
// Board:  TENSTAR RP2350-USB (RP2350A, 16MB)
//   - Onboard WS2812 RGB LED on GP22
//   - External 10-LED WS2812 ring on GP15
//
// This demo:
//   Part 1: Cycle colors on the onboard WS2812 (GP22)
//   Part 2: Rainbow animation on the 10-LED ring (GP15)
// =============================================================

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"   // for save_and_disable_interrupts

// ----- Pin Assignment ------------------------------------
static const uint ONBOARD_LED_PIN = 22;   // WS2812 on board
static const uint RING_PIN        = 15;   // External ring DIN
static const uint NUM_RING_LEDS   = 10;

// ----- Brightness limiter (0-255) ------------------------
// USB can supply ~500 mA.  10 LEDs at full white = 600 mA.
// Cap brightness to keep total current under ~300 mA.
static const uint8_t MAX_BRIGHTNESS = 64;

// =============================================================
//  WS2812 Bit-Bang Driver
//
//  Protocol:
//    Each bit is sent as a HIGH pulse followed by LOW.
//    Bit "1":  HIGH for ~800 ns, LOW for ~450 ns
//    Bit "0":  HIGH for ~400 ns, LOW for ~850 ns
//    Reset:    LOW for >280 us  (latches data into LEDs)
//
//  Data format:  GRB order, MSB first, 24 bits per LED.
//
//  At 150 MHz, each CPU cycle = ~6.67 ns.
//  We use busy_wait_at_least_cycles() for precise timing.
//    T0H = 400 ns  ~ 60 cycles
//    T0L = 850 ns  ~ 128 cycles
//    T1H = 800 ns  ~ 120 cycles
//    T1L = 450 ns  ~ 68 cycles
// =============================================================

static const uint32_t T0H_CYCLES = 60;
static const uint32_t T0L_CYCLES = 128;
static const uint32_t T1H_CYCLES = 120;
static const uint32_t T1L_CYCLES = 68;

// Precise cycle-counting delay
// Pico SDK provides this in hardware/sync.h
// static __force_inline void busy_wait_at_least_cycles(uint32_t n);

static inline void ws2812_send_bit(uint pin, bool bit) {
    if (bit) {
        gpio_put(pin, 1);
        busy_wait_at_least_cycles(T1H_CYCLES);
        gpio_put(pin, 0);
        busy_wait_at_least_cycles(T1L_CYCLES);
    } else {
        gpio_put(pin, 1);
        busy_wait_at_least_cycles(T0H_CYCLES);
        gpio_put(pin, 0);
        busy_wait_at_least_cycles(T0L_CYCLES);
    }
}

static inline void ws2812_send_byte(uint pin, uint8_t byte) {
    for (int i = 7; i >= 0; i--) {       // MSB first
        ws2812_send_bit(pin, byte & (1 << i));
    }
}

// Send one pixel in GRB order
static void ws2812_send_pixel(uint pin, uint8_t r, uint8_t g, uint8_t b) {
    ws2812_send_byte(pin, g);   // Green first!
    ws2812_send_byte(pin, r);   // Then Red
    ws2812_send_byte(pin, b);   // Then Blue
}

// Send reset pulse (>280 us LOW to latch data)
static void ws2812_reset(uint pin) {
    gpio_put(pin, 0);
    sleep_us(300);
}

// =============================================================
//  Pixel buffer
// =============================================================
struct Pixel {
    uint8_t r, g, b;
};

static Pixel ring_buffer[NUM_RING_LEDS];

// Send entire buffer to the ring with interrupts disabled
static void ws2812_show(uint pin, const Pixel* pixels, uint count) {
    uint32_t irq_state = save_and_disable_interrupts();
    for (uint i = 0; i < count; i++) {
        ws2812_send_pixel(pin, pixels[i].r, pixels[i].g, pixels[i].b);
    }
    restore_interrupts(irq_state);
    ws2812_reset(pin);
}

// Send a single pixel (for onboard LED)
static void ws2812_show_single(uint pin, uint8_t r, uint8_t g, uint8_t b) {
    Pixel p = { r, g, b };
    ws2812_show(pin, &p, 1);
}

// =============================================================
//  Color utilities
// =============================================================

// Apply brightness limit
static uint8_t dim(uint8_t val) {
    return (uint8_t)((uint16_t)val * MAX_BRIGHTNESS / 255);
}

// HSV to RGB (hue: 0-255, sat: 0-255, val: 0-255)
// Returns dimmed RGB values
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
//  setup()
// =============================================================
void setup() {
    Serial.begin(115200);
    sleep_ms(1000);

    // Initialize GPIO for both WS2812 outputs
    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_put(ONBOARD_LED_PIN, 0);

    gpio_init(RING_PIN);
    gpio_set_dir(RING_PIN, GPIO_OUT);
    gpio_put(RING_PIN, 0);

    // Clear LEDs on startup
    ws2812_show_single(ONBOARD_LED_PIN, 0, 0, 0);
    memset(ring_buffer, 0, sizeof(ring_buffer));
    ws2812_show(RING_PIN, ring_buffer, NUM_RING_LEDS);

    Serial.println("=== Lesson 16: WS2812 Addressable LEDs ===");
    Serial.print("Onboard LED : GP");
    Serial.println(ONBOARD_LED_PIN);
    Serial.print("Ring        : GP");
    Serial.print(RING_PIN);
    Serial.print(", ");
    Serial.print(NUM_RING_LEDS);
    Serial.println(" LEDs");
    Serial.print("Brightness  : ");
    Serial.print(MAX_BRIGHTNESS);
    Serial.println(" / 255");
    Serial.println("------------------------------------------");

    // --- Part 1: Cycle through basic colors on onboard LED ---
    Serial.println("Part 1: Onboard LED color cycle");

    const uint8_t bright = MAX_BRIGHTNESS;
    struct { const char* name; uint8_t r, g, b; } colors[] = {
        { "Red",     bright, 0,      0      },
        { "Green",   0,      bright, 0      },
        { "Blue",    0,      0,      bright },
        { "Yellow",  bright, bright, 0      },
        { "Cyan",    0,      bright, bright },
        { "Magenta", bright, 0,      bright },
        { "White",   bright, bright, bright },
    };

    for (auto& c : colors) {
        Serial.print("  ");
        Serial.println(c.name);
        ws2812_show_single(ONBOARD_LED_PIN, c.r, c.g, c.b);
        sleep_ms(800);
    }
    ws2812_show_single(ONBOARD_LED_PIN, 0, 0, 0);   // Off

    Serial.println("Part 2: Ring rainbow animation (running...)");
}

// =============================================================
//  loop() -- Rainbow animation on the ring
// =============================================================
void loop() {
    static uint16_t hue_offset = 0;

    // Fill ring buffer with evenly-spaced hues
    for (uint i = 0; i < NUM_RING_LEDS; i++) {
        uint8_t hue = (uint8_t)(hue_offset + i * 256 / NUM_RING_LEDS);
        ring_buffer[i] = hsv_to_rgb(hue, 255, 255);
    }

    // Push to ring
    ws2812_show(RING_PIN, ring_buffer, NUM_RING_LEDS);

    // Also mirror first LED color to onboard LED
    ws2812_show_single(ONBOARD_LED_PIN,
                       ring_buffer[0].r,
                       ring_buffer[0].g,
                       ring_buffer[0].b);

    hue_offset += 2;   // Speed of rotation
    sleep_ms(30);       // ~33 FPS
}
