// =============================================================
// Lesson 15 -- Homework: Multi-LED Button Controller
// Fundamentals of C++ for Microcontrollers
//
// Hardware:
//   - RP2350 USB dongle
//   - LED A on GPIO 15  (330 Ohm to GND)  -- from demo
//   - LED B on GPIO 14  (330 Ohm to GND)  -- add this one
//   - Button on GPIO 13 (to GND, use internal pull-up)
//
// Task:
//   Pressing the button cycles through 3 blink patterns:
//     Pattern 0: Both LEDs blink together
//     Pattern 1: LEDs alternate  (A on -> B on -> repeat)
//     Pattern 2: LED A fast (100ms), LED B slow (500ms)
//
//   Print the current pattern name to USB serial on change.
//
// Instructions:
//   1. Fill in all TODO sections below
//   2. Search for "TODO" to find what needs to be done
//   3. The debounce helper is provided -- study how it works
//   4. Build, flash via BOOTSEL, test with serial monitor
// =============================================================

#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// ----- Pin Assignment ------------------------------------
static const uint LED_A_PIN  = 15;
static const uint LED_B_PIN  = 14;
static const uint BUTTON_PIN = 13;   // Active LOW (pulled up internally)

// ----- Blink timing --------------------------------------
static const uint32_t BLINK_ON_MS  = 500;
static const uint32_t BLINK_OFF_MS = 500;

// ----- Pattern definitions -------------------------------
static const int NUM_PATTERNS = 3;
static const char* PATTERN_NAMES[] = {
    "Both together",
    "Alternating",
    "Fast A / Slow B"
};

// ----- Debounce state (provided) -------------------------
struct ButtonState {
    bool     last_raw;
    bool     stable;
    uint32_t last_change_ms;
    static const uint32_t DEBOUNCE_MS = 50;

    ButtonState() : last_raw(true), stable(true), last_change_ms(0) {}

    // Returns true on a falling edge (button just pressed).
    // Call this every loop iteration.
    bool update() {
        bool raw = gpio_get(BUTTON_PIN);
        uint32_t now = to_ms_since_boot(get_absolute_time());

        if (raw != last_raw) {
            last_change_ms = now;
            last_raw = raw;
        }

        if ((now - last_change_ms) >= DEBOUNCE_MS) {
            bool prev_stable = stable;
            stable = raw;
            // Detect falling edge: was HIGH, now LOW
            if (prev_stable && !stable) {
                return true;
            }
        }
        return false;
    }
};

// ----- Global state --------------------------------------
static ButtonState button;
static int current_pattern = 0;

// =============================================================
//  TODO 1: Initialize all GPIO pins
//
//  Hints:
//    - LED pins: gpio_init(), gpio_set_dir() with GPIO_OUT
//    - Button pin: gpio_init(), gpio_set_dir() with GPIO_IN,
//      then enable internal pull-up with gpio_pull_up()
//    - Start both LEDs in OFF state
// =============================================================
void init_pins() {
    // --- LED A (GPIO 15) ---
    // TODO: initialize LED A pin as output, set to LOW
    gpio_init(LED_A_PIN);
    gpio_set_dir(LED_A_PIN, GPIO_OUT);
    gpio_put(LED_A_PIN, 0); 
    // --- LED B (GPIO 14) ---
    // TODO: initialize LED B pin as output, set to LOW
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_put(LED_B_PIN, 0); 
    // --- Button (GPIO 13) ---
    // TODO: initialize button pin as input with pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_put(BUTTON_PIN, 0); 
}

// =============================================================
//  TODO 2: Implement the three blink patterns
//
//  Each function runs one "frame" of the pattern.
//  Use gpio_put() and sleep_ms() as in the demo.
//
//  Pattern 0: Both LEDs on 500ms, both off 500ms
//  Pattern 1: LED A on 500ms (B off), then B on 500ms (A off)
//  Pattern 2: LED A toggles every 100ms, LED B every 500ms
//             Hint: use a static counter to track B's timing
// =============================================================
void pattern_both() {
    // TODO: both LEDs on, delay, both off, delay
    // CONTINUE FROM HERE
    static uint32_t cycle = 0;
    
    gpio_put(LED_A_PIN, LED_B_PIN, 1);
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

void pattern_alternate() {
    // TODO: LED A on + LED B off, delay,
    //       LED A off + LED B on, delay
}

void pattern_fast_slow() {
    // Hint: LED A toggles every 100ms.
    //       Use a static variable to count iterations.
    //       Every 5th toggle (5 * 100ms = 500ms), also toggle LED B.
    //
    // TODO: implement fast/slow pattern
    static bool led_a_state = false;
    static uint8_t a_count  = 0;
    static bool led_b_state = false;

    // TODO: toggle LED A every call
    // TODO: increment a_count
    // TODO: every 5th call, toggle LED B
    // TODO: sleep_ms(100)
}

// =============================================================
//  setup()
// =============================================================
void setup() {
    Serial.begin(115200);
    sleep_ms(1000);

    init_pins();

    Serial.println("=== Lesson 15 Homework: Multi-LED Controller ===");
    Serial.print("Pattern: ");
    Serial.println(PATTERN_NAMES[current_pattern]);
}

// =============================================================
//  loop()
// =============================================================
void loop() {
    // --- Check button ---
    if (button.update()) {
        // TODO 3: Advance to the next pattern.
        //         Wrap around using modulo (%).
        //         Print the new pattern name to Serial.
        //
        // Hint:
        //   current_pattern = ???
        //   Serial.print("Pattern: ");
        //   Serial.println(PATTERN_NAMES[current_pattern]);
    }

    // --- Run the current pattern ---
    // TODO 4: Call the correct pattern function based on
    //         current_pattern (0, 1, or 2).
    //         Use a switch statement or if/else.
}
