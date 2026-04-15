// =============================================================
// Lesson 16 -- Homework: WS2812 Ring Effects
// Fundamentals of C++ for Microcontrollers
//
// Hardware:
//   - TENSTAR RP2350-USB
//   - Onboard WS2812 on GP22
//   - 10-LED WS2812 ring on GP15
//   - Button on GP13 (to GND, use internal pull-up)
//
// Task:
//   Implement 3 LED ring effects. Button press cycles between them.
//     Effect 0: Chase    -- single lit LED moves around the ring
//     Effect 1: Breathe  -- all LEDs fade in and out smoothly
//     Effect 2: ColorWipe -- ring fills one LED at a time, then clears
//
//   The onboard LED (GP22) shows the current effect color.
//
// Instructions:
//   1. Fill in all TODO sections below
//   2. Search for "TODO" to find what needs to be done
//   3. The WS2812 driver and button debounce are provided
//   4. The hsv_to_rgb() function is provided from the demo
// =============================================================

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"

// ----- Pin Assignment ------------------------------------
static const uint ONBOARD_LED_PIN = 22;
static const uint RING_PIN        = 15;
static const uint BUTTON_PIN      = 13;
static const uint NUM_LEDS        = 10;
static const uint8_t MAX_BRIGHTNESS = 64;

// ----- Pixel type ----------------------------------------
struct Pixel {
    uint8_t r, g, b;
};

static Pixel ring[NUM_LEDS];

// =============================================================
//  WS2812 Driver (provided -- same as demo)
// =============================================================
static const uint32_t T0H_CYCLES = 60;
static const uint32_t T0L_CYCLES = 128;
static const uint32_t T1H_CYCLES = 120;
static const uint32_t T1L_CYCLES = 68;

static inline void ws_send_bit(uint pin, bool bit) {
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

static inline void ws_send_byte(uint pin, uint8_t b) {
    for (int i = 7; i >= 0; i--) {
        ws_send_bit(pin, b & (1 << i));
    }
}

static void ws_send_pixel(uint pin, uint8_t r, uint8_t g, uint8_t b) {
    ws_send_byte(pin, g);
    ws_send_byte(pin, r);
    ws_send_byte(pin, b);
}

static void ws_show(uint pin, const Pixel* px, uint count) {
    uint32_t st = save_and_disable_interrupts();
    for (uint i = 0; i < count; i++) {
        ws_send_pixel(pin, px[i].r, px[i].g, px[i].b);
    }
    restore_interrupts(st);
    gpio_put(pin, 0);
    sleep_us(300);
}

static void ws_show_single(uint pin, uint8_t r, uint8_t g, uint8_t b) {
    Pixel p = { r, g, b };
    ws_show(pin, &p, 1);
}

// =============================================================
//  Color utilities (provided)
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

// Make a solid-color pixel with brightness applied
static Pixel make_pixel(uint8_t r, uint8_t g, uint8_t b) {
    return { dim(r), dim(g), dim(b) };
}

// =============================================================
//  Button debounce (provided -- same as Lesson 15)
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
//  Global state
// =============================================================
static ButtonState button;
static const int NUM_EFFECTS = 3;
static int current_effect = 0;

static const char* EFFECT_NAMES[] = {
    "Chase",
    "Breathe",
    "Color Wipe"
};

// Indicator colors for onboard LED per effect
static const Pixel EFFECT_COLORS[] = {
    { 0, 0, MAX_BRIGHTNESS },   // Chase = blue
    { 0, MAX_BRIGHTNESS, 0 },   // Breathe = green
    { MAX_BRIGHTNESS, 0, 0 },   // Wipe = red
};

// =============================================================
//  TODO 1: Effect -- Chase
//
//  A single bright LED moves around the ring.
//  All other LEDs are off (or dim).
//
//  Hints:
//    - Use a static variable to track position (0 to NUM_LEDS-1)
//    - Clear the entire ring buffer (set all to {0,0,0})
//    - Set ring[position] to a bright color
//    - Increment position, wrap with modulo
//    - Call ws_show() and sleep_ms() for timing
// =============================================================
void effect_chase() {
    static uint8_t pos = 0;
    static uint8_t hue = 0;

    // TODO: clear ring buffer

    // TODO: set ring[pos] to a color (try hsv_to_rgb(hue, 255, 255))

    // TODO: show the ring

    // TODO: advance position (wrap around)
    // TODO: advance hue for color variation

    sleep_ms(80);  // Speed of chase
}

// =============================================================
//  TODO 2: Effect -- Breathe
//
//  All LEDs fade in and out smoothly (same color).
//
//  Hints:
//    - Use a static variable for brightness (0-255)
//    - Use a static bool for direction (fading in or out)
//    - When brightness reaches 255, reverse to fading out
//    - When brightness reaches 0, reverse to fading in
//    - Use hsv_to_rgb(hue, 255, brightness) for the color
//    - Fill ALL LEDs in the ring with the same color
//    - Slowly cycle the hue for visual interest
// =============================================================
void effect_breathe() {
    static uint8_t brightness = 0;
    static bool    fading_in  = true;
    static uint8_t hue        = 160;  // Start with a blue-ish hue

    // TODO: update brightness based on direction
    //   if fading_in:  brightness += 3 (clamp at 255, then reverse)
    //   if fading_out: brightness -= 3 (clamp at 0, then reverse)

    /* for (int i = 0; i < LEDS_COUNT; i) {
        strip.setLedColorData(i, 255, 255, 0);
	    strip.show();
        delay(1000);
        strip.setLedColorData(i, 0, 0, 0);
    } */


    // TODO: create a pixel using hsv_to_rgb(hue, 255, brightness)

    // TODO: fill entire ring buffer with that pixel

    // TODO: show the ring

    // TODO: slowly advance hue (e.g., increment by 1 every few frames)

    sleep_ms(15);
}

// =============================================================
//  TODO 3: Effect -- Color Wipe
//
//  The ring fills up one LED at a time (like a progress bar),
//  then clears and starts over with a new color.
//
//  Hints:
//    - Use a static variable for fill_count (0 to NUM_LEDS)
//    - Use a static hue variable for the current wipe color
//    - Set ring[0..fill_count-1] to the wipe color
//    - Set ring[fill_count..NUM_LEDS-1] to off ({0,0,0})
//    - When fill_count reaches NUM_LEDS, hold briefly, then
//      reset fill_count to 0 and change the hue
// =============================================================
void effect_color_wipe() {
    static uint8_t fill_count = 0;
    static uint8_t hue = 0;

    // TODO: create the wipe color using hsv_to_rgb(hue, 255, 255)

    // TODO: fill ring[0..fill_count-1] with the wipe color

    // TODO: fill ring[fill_count..NUM_LEDS-1] with {0, 0, 0}

    // TODO: show the ring

    // TODO: increment fill_count
    // TODO: if fill_count > NUM_LEDS, hold for 500ms, then
    //       reset to 0 and advance hue by ~40

    sleep_ms(100);
}

// =============================================================
//  setup()
// =============================================================
void setup() {
    Serial.begin(115200);
    sleep_ms(1000);

    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_put(ONBOARD_LED_PIN, 0);

    gpio_init(RING_PIN);
    gpio_set_dir(RING_PIN, GPIO_OUT);
    gpio_put(RING_PIN, 0);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Clear all LEDs
    memset(ring, 0, sizeof(ring));
    ws_show(RING_PIN, ring, NUM_LEDS);
    ws_show_single(ONBOARD_LED_PIN, 0, 0, 0);

    Serial.println("=== Lesson 16 Homework: Ring Effects ===");
    Serial.print("Effect: ");
    Serial.println(EFFECT_NAMES[current_effect]);

    // Show effect indicator on onboard LED
    ws_show_single(ONBOARD_LED_PIN,
                   EFFECT_COLORS[current_effect].r,
                   EFFECT_COLORS[current_effect].g,
                   EFFECT_COLORS[current_effect].b);
}

// =============================================================
//  loop()
// =============================================================
void loop() {
    // --- Check button for effect change ---
    if (button.pressed()) {
        // TODO 4: Advance to the next effect.
        //         Wrap around using modulo (%).
        //         Print the new effect name to Serial.
        //         Update the onboard LED indicator color.
        //
        // current_effect = ???
        // Serial.print("Effect: ");
        // Serial.println(EFFECT_NAMES[current_effect]);
        // ws_show_single(ONBOARD_LED_PIN, ...);
    }

    // --- Run the current effect ---
    // TODO 5: Call the correct effect function based on
    //         current_effect (0, 1, or 2).
    //         Use a switch statement or if/else chain.
}
