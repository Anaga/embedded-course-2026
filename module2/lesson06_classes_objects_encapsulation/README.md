# Lesson 06 — Classes, Objects, Encapsulation

Embedded Systems Course 2026 | ESP32-C3 Super Mini

---

## Overview

This lesson transitions from C-style structs and free functions to C++ classes
with encapsulation. The project provides two ready-made classes (`Led` and
`Button`) that mirror the C drivers from Lesson 4, now rewritten as proper
C++ classes with private data members, constructors, destructors, and const
methods.

---

## Project Structure

```
lesson6-classes/
  include/
    Led.h           Class declaration for the LED driver
    Button.h        Class declaration for the Button driver
  src/
    Led.cpp         LED class implementation
    Button.cpp      Button class implementation
    main.cpp        Template with exercises
  platformio.ini    Build configuration for ESP32-C3
```

---

## Wiring

### Onboard LED — GPIO 8

Built-in on the ESP32-C3 Super Mini. No external wiring needed.

### Button — GPIO 0

| Pin | Connect to          |
|-----|---------------------|
| IO0 | One leg of button   |
| GND | Other leg of button |

Internal pull-up is enabled by the `Button` constructor.

### RGB LED — GPIO 1, 3, 10 (for Exercise 3)

Common anode RGB LED. Each channel is active-low.

```
3.3V ──────────────────── common anode (longest leg)

IO1  ── 220 ohm ── Red cathode
IO3  ── 220 ohm ── Green cathode
IO10 ── 220 ohm ── Blue cathode
```

---

## Key Concepts

### Class = Data + Methods bundled together

```cpp
class Led {
private:
    uint8_t pin_;           // data hidden from outside
    bool    state_;
public:
    Led(uint8_t pin);       // constructor
    void on();              // public API
    bool isOn() const;      // const = read-only
};
```

### Constructor replaces init function

```cpp
// C style (Lesson 4):
GpioPin_t led = { .pin = 8, .active_high = true };
gpio_pin_init(&led);

// C++ style (Lesson 6):
Led led(8, true);           // constructor does everything
```

### const correctness

Mark methods `const` if they do not modify the object:

```cpp
bool Led::isOn() const { return state_; }
```

---

## Exercises

1. Read the template. Flash the code. Verify LED blinks and button prints.
2. Add a `blink(uint16_t ms)` method to the `Led` class.
3. Create an `RgbLed` class (RgbLed.h + RgbLed.cpp) holding three `Led` objects.
4. BONUS: Cycle through colors on each button press using `RgbLed` + `Button`.

---

## Expected Serial Output

```
================================================
 Lesson 06: Classes, Objects, Encapsulation
 Onboard LED blinks, button prints to Serial
================================================

LED on GPIO 8 (active-high)
Button on GPIO 0 (active-low)

Click! LED is ON
Click! LED is OFF
Click! LED is ON
...
```
