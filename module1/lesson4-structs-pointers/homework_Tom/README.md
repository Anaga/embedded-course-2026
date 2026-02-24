# Lesson 4 — Structs and Pointers to Structs

Embedded Systems Course 2026 | ESP32-C3 / PlatformIO

---

## Project Structure

```
lesson4_structs/
├── platformio.ini          -- board and build configuration
├── include/
│   ├── gpio_driver.h       -- GpioPin_t type + API declarations
│   └── button_driver.h     -- Button_t type + API declarations
└── src/
    ├── gpio_driver.cpp     -- GPIO driver implementation
    ├── button_driver.cpp   -- debounced button implementation
    └── main.cpp            -- exercise template (start here)
```

---

## Wiring

| Signal | GPIO | Notes |
|--------|------|-------|
| LED    | 8    | 220 ohm resistor to GND, active-high |
| Button | 9    | one leg to GPIO, other to GND; internal pull-up enabled |

You can change the pin numbers at the top of `src/main.cpp`.

---

## Key Concepts

### struct — grouping related data

```c
typedef struct {
    uint8_t  pin;
    bool     output;
    bool     active_high;
    bool     pull_up;
} GpioPin_t;
```

One struct instance represents one physical pin and all its configuration. No magic numbers scattered across the code.

### Pointer to struct — arrow operator

```c
GpioPin_t led = { .pin = 8, .output = true, .active_high = true };
GpioPin_t *p  = &led;

// Three equivalent accesses:
uint8_t a = led.pin;      // dot     — direct variable
uint8_t b = (*p).pin;     // deref + dot
uint8_t c = p->pin;       // arrow   — preferred for pointers
```

### Passing by pointer — the standard embedded C pattern

```c
// Correct: passes 4-byte pointer, driver can modify the struct
void gpio_pin_init(GpioPin_t *p) { ... }
gpio_pin_init(&led);

// Avoid: copies all bytes of the struct, changes do not affect caller
void gpio_pin_init_val(GpioPin_t p) { ... }
```

### Designated initialisers (C99)

```c
GpioPin_t led = {
    .pin         = 8,
    .output      = true,
    .active_high = true,
    .pull_up     = false,
};
```

Fields listed by name, order does not matter, unlisted fields default to zero. Safer and more readable than positional initialisation.

### struct with internal state — Button_t

`Button_t` stores both configuration and runtime state inside the same struct. This eliminates global variables for debounce timing and makes each button fully self-contained.

```c
Button_t btn = { .pin = 9, .active_high = false, .debounce_ms = 50 };
button_init(&btn);

// In loop():
if (button_pressed(&btn)) {
    // fires once per confirmed press
}
```

---

## Exercises

Work through these in `src/main.cpp`.

**Exercise 1 — Struct basics**
Add a second LED on GPIO 10 with `active_high = false`. Initialise it and toggle it at a different rate.

**Exercise 2 — Pointer syntax**
Declare a `GpioPin_t *` pointing to `led`. Use `->` to read `led.pin` and print it over Serial.

**Exercise 3 — Function with pointer parameter**
Implement the `blink(GpioPin_t *p, uint16_t on_ms, uint16_t off_ms)` function. Use it for the second LED.

**Exercise 4 (BONUS) — Array of structs**
Replace individual LED declarations with a `GpioPin_t` array. Use `gpio_pin_init_array()` and loop through the array to toggle LEDs in sequence.

---

## Build and Flash

```bash
# Build
pio run

# Upload
pio run --target upload

# Monitor
pio device monitor
```

---

## Expected Serial Output

```
Lesson 4 - Structs and Pointers to Structs
-------------------------------------------
sizeof(GpioPin_t) = 4 bytes
sizeof(Button_t)  = 16 bytes
LED pin: 8  (active-high)
Button pin: 9  (active-low, debounce: 50 ms)
Setup complete. Press the button to toggle the LED.
Button pressed! LED is now ON
Button pressed! LED is now OFF
```
