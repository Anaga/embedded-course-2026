# Homework 4 — RGB LED Color Cycle

Embedded Systems Course 2026 | ESP32-C3 Super Mini

---

## Task

Connect a button and an RGB LED to the ESP32-C3.
Each button press cycles to the next color: **Red → Green → Blue → Red → ...**

Use the `GpioPin_t` and `Button_t` drivers from Lesson 4. Do not copy-paste raw `digitalWrite()` calls — the whole point is to use your structs.

---

## Wiring

### Button — GPIO 0

| Pin | Connect to |
|-----|-----------|
| IO0 | One leg of the button |
| GND | Other leg of the button |

Use the internal pull-up (`active_high = false`).

### RGB LED — GPIO 1, 3, 10

This LED has a **common anode** (the longest leg connects to 3.3V).
Each color channel is active-low: the LED lights up when the pin is driven LOW.

```
3.3V ────────220 ohm ─────────────────── common anode (longest leg)

IO1  ──── Red cathode
IO3  ──── Green cathode
IO10 ──── Blue cathode
```

> Put a 220 ohm resistor on  common anode. Without resistors you will exceed
> the LED's current rating and may damage the ESP32-C3 output.

---

## Expected Behavior

```
[boot]  all LEDs off

[press] RED on,   Green off, Blue off
[press] RED off,  Green on,  Blue off
[press] RED off,  Green off, Blue on
[press] RED on,   Green off, Blue off   <- wraps around
...
```

Print the current color name to Serial on each press.

---

## Requirements

1. Use `GpioPin_t` for each of the three LED channels and for the button.
2. Use `Button_t` with debounce for the button — no `delay()` for debouncing.
3. Set `active_high = false` for all three LED channels (common anode = active-low).
4. Cycle through colors using an index variable and a switch or array — no long if/else chains.
5. Serial output on each press: print which color is now active.

---

## Hints

- Copy `gpio_driver.h`, `gpio_driver.cpp`, `button_driver.h`, `button_driver.cpp` from the Lesson 4 template into your new project.
- Declare all three LED pins as a `GpioPin_t` array and initialise them with `gpio_pin_init_array()`.
- A `uint8_t color_index` that increments and wraps with `% 3` is all you need for the cycle logic.
- `gpio_pin_set(&leds[color_index], true)` turns one channel on — remember to turn the previous one off first.

---

## Grading

| Criteria | Points |
|----------|--------|
| Correct wiring (resistors, common anode) | 2 |
| GpioPin_t used for all three channels | 2 |
| Button_t with debounce, no delay() | 2 |
| Color cycles correctly on each press | 2 |
| Serial output with color name | 1 |
| Code compiles and runs without warnings | 1 |
| **Total** | **10** |
