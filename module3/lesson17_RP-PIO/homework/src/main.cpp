// =============================================================
// Lesson 17 -- Homework: PIO WS2812 Effects + Measurement
// Fundamentals of C++ for Microcontrollers
//
// Hardware:
//   - TENSTAR RP2350-USB
//   - Onboard WS2812 on GP22  (PIO0, SM0)
//   - 10-LED WS2812 ring on GP15 (PIO0, SM1)
//   - Button on GP13 (to GND, internal pull-up)
//   - CPU probe on GP14 (for logic analyzer / oscilloscope)
//
// Task:
//   1. Port your Lesson 16 ring effects (chase, breathe, wipe)
//      to use the PIO driver instead of bit-bang
//   2. Measure CPU time per frame and print to serial
//   3. Bonus: drive onboard LED independently as a status indicator
//   4. Bonus: add a new animation effect of your own design
//
// The PIO driver and measurement framework are provided.
// Your job: implement the effects using the PIO API.
// =============================================================

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"

#include "ws2812_pio.h"

// ----- Pin Assignment ----------------------------------------
static const uint ONBOARD_LED_PIN = 22;
static const uint RING_PIN        = 15;
static const uint BUTTON_PIN      = 13;
static const uint PROBE_PIN       = 14;
static const uint NUM_LEDS        = 10;
static const uint8_t MAX_BRIGHTNESS = 64;

// ----- Pixel type --------------------------------------------
struct Pixel {
    uint8_t r, g, b;
};

static Pixel ring[NUM_LEDS];

// ----- PIO resources (provided) ------------------------------
static PIO  pio_hw = pio0;
static uint sm_onboard;
static uint sm_ring;
static uint pio_offset;

// =============================================================
//  PIO output functions (provided)
// =============================================================
static inline uint32_t pixel_to_grb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)g << 24) | ((uint32_t)r << 16) | ((uint32_t)b << 8);
}

static void pio_put_pixel(uint sm, uint8_t r, uint8_t g, uint8_t b) {
    pio_sm_put_blocking(pio_hw, sm, pixel_to_grb(r, g, b));
}

// Send an entire pixel buffer to a PIO state machine
static void pio_show(uint sm, const Pixel* px, uint count) {
    for (uint i = 0; i < count; i++) {
        pio_sm_put_blocking(pio_hw, sm, pixel_to_grb(px[i].r, px[i].g, px[i].b));
    }
}

// =============================================================
//  Color utilities (provided -- same as L16)
// =============================================================
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

static Pixel make_pixel(uint8_t r, uint8_t g, uint8_t b) {
    return { dim(r), dim(g), dim(b) };
}

// =============================================================
//  Button debounce (provided)
// =============================================================
struct ButtonState {
    bool last_raw, stable;
    uint32_t last_change_ms;
    static const uint32_t DEBOUNCE_MS = 50;
    ButtonState() : last_raw(true), stable(true), last_change_ms(0) {}
    bool pressed() {
        bool raw = gpio_get(BUTTON_PIN);
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (raw != last_raw) { last_change_ms = now; last_raw = raw; }
        if ((now - last_change_ms) >= DEBOUNCE_MS) {
            bool prev = stable;
            stable = raw;
            if (prev && !stable) return true;
        }
        return false;
    }
};

// =============================================================
//  CPU time measurement (provided)
//
//  Usage:
//    uint32_t t = start_measure();
//    ... do LED update work ...
//    uint32_t elapsed = end_measure(t);
//
//  Also toggles GP14 so you can see the pulse on a logic analyzer.
// =============================================================
static uint32_t start_measure() {
    gpio_put(PROBE_PIN, 1);
    return time_us_32();
}

static uint32_t end_measure(uint32_t t_start) {
    uint32_t elapsed = time_us_32() - t_start;
    gpio_put(PROBE_PIN, 0);
    return elapsed;
}

// =============================================================
//  Global state
// =============================================================
static ButtonState button;
static const int NUM_EFFECTS = 3;
static int current_effect = 0;
static uint32_t frame_count = 0;
static uint32_t total_us = 0;

static const char* EFFECT_NAMES[] = {
    "Chase",
    "Breathe",
    "Color Wipe"
};

// =============================================================
//  TODO 1: Effect -- Chase
//
//  Same logic as Lesson 16, but now use PIO to send data:
//    - Fill the ring[] buffer (one LED lit, rest off)
//    - Call pio_show(sm_ring, ring, NUM_LEDS) to send
//
//  The key difference from L16:
//    - No interrupts disabled
//    - No manual bit timing
//    - Just write to the FIFO and PIO handles the rest
// =============================================================
void effect_chase() {
    static uint8_t pos = 0;
    static uint8_t hue = 0;

    // TODO: clear ring buffer (memset to 0)

    // TODO: set ring[pos] to hsv_to_rgb(hue, 255, 255)

    // TODO: send ring to PIO using pio_show(sm_ring, ring, NUM_LEDS)

    // TODO: advance pos (wrap with %), advance hue

    sleep_ms(80);
}

// =============================================================
//  TODO 2: Effect -- Breathe
//
//  All LEDs fade in/out. Same logic as L16.
//    - Compute brightness, create pixel with hsv_to_rgb
//    - Fill entire ring[] with that pixel
//    - Send via pio_show()
// =============================================================
void effect_breathe() {
    static uint8_t brightness = 0;
    static bool    fading_in  = true;
    static uint8_t hue        = 160;

    // TODO: update brightness (increment/decrement by 3)
    //       reverse direction at 0 and 255

    // TODO: create pixel using hsv_to_rgb(hue, 255, brightness)

    // TODO: fill entire ring[] with that pixel

    // TODO: send to PIO

    // TODO: slowly advance hue

    sleep_ms(15);
}

// =============================================================
//  TODO 3: Effect -- Color Wipe
//
//  Ring fills up one LED at a time, then clears.
//    - ring[0..fill-1] = wipe color
//    - ring[fill..NUM_LEDS-1] = black
//    - Send via pio_show()
// =============================================================
void effect_color_wipe() {
    static uint8_t fill_count = 0;
    static uint8_t hue = 0;

    // TODO: create wipe color with hsv_to_rgb(hue, 255, 255)

    // TODO: fill ring[0..fill_count-1] with wipe color

    // TODO: fill ring[fill_count..NUM_LEDS-1] with {0, 0, 0}

    // TODO: send to PIO

    // TODO: increment fill_count
    //       if > NUM_LEDS, pause 500ms, reset, advance hue by 40

    sleep_ms(100);
}

// =============================================================
//  setup()
// =============================================================
void setup() {
    Serial.begin(115200);
    sleep_ms(1000);

    // Probe pin
    gpio_init(PROBE_PIN);
    gpio_set_dir(PROBE_PIN, GPIO_OUT);
    gpio_put(PROBE_PIN, 0);

    // Button
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // --- Initialize PIO ---
    sm_onboard = pio_claim_unused_sm(pio_hw, true);
    sm_ring    = pio_claim_unused_sm(pio_hw, true);
    pio_offset = pio_add_program(pio_hw, &ws2812_program);
    ws2812_pio_init(pio_hw, sm_onboard, pio_offset, ONBOARD_LED_PIN);
    ws2812_pio_init(pio_hw, sm_ring,    pio_offset, RING_PIN);

    // Clear
    pio_put_pixel(sm_onboard, 0, 0, 0);
    memset(ring, 0, sizeof(ring));
    pio_show(sm_ring, ring, NUM_LEDS);
    sleep_ms(100);

    Serial.println("=== Lesson 17 Homework: PIO Effects ===");
    Serial.print("Effect: ");
    Serial.println(EFFECT_NAMES[current_effect]);
    Serial.println("CPU time printed every 50 frames.");
    Serial.println();
}

// =============================================================
//  loop()
// =============================================================
void loop() {
    // --- Button: cycle effects ---
    if (button.pressed()) {
        // TODO 4: Advance current_effect (wrap with %)
        //         Print new effect name to Serial
        //         Update onboard LED to an indicator color:
        //           Chase=blue, Breathe=green, Wipe=red
        //
        // Example:
        //   current_effect = (current_effect + 1) % NUM_EFFECTS;
        //   Serial.print("Effect: ");
        //   Serial.println(EFFECT_NAMES[current_effect]);
        //   pio_put_pixel(sm_onboard, r, g, b);
    }

    // --- Measure CPU time ---
    uint32_t t = start_measure();

    // --- Run the current effect ---
    // TODO 5: Call the correct effect function (switch or if/else)

    // --- End measurement ---
    uint32_t elapsed = end_measure(t);
    total_us += elapsed;
    frame_count++;

    if (frame_count % 50 == 0) {
        Serial.print("[");
        Serial.print(EFFECT_NAMES[current_effect]);
        Serial.print("]  Avg CPU: ");
        Serial.print(total_us / 50);
        Serial.println(" us");
        total_us = 0;
    }
}
