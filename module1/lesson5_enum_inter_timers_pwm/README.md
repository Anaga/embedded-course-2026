# Lesson 5: Interrupts, Timers & PWM

## Examples

### 01_interrupt_basics
Basic hardware interrupt demo. Button toggles LED using ISR with debounce.
- Shows `volatile`, `IRAM_ATTR`, `attachInterrupt()`
- Demonstrates ISR flag pattern (do heavy work in `loop()`, not ISR)

### 02_pwm_basics  
PWM fundamentals using ESP32 LEDC peripheral.
- LED fade in/out using `ledcAttach()` and `ledcWrite()`
- Discrete brightness steps demo
- Frequency and resolution concepts

### 03_rgb_pwm_controller
**Complete solution** combining all lesson concepts:
- `enum` for color state management
- Hardware interrupt for button input
- PWM output for RGB LED color mixing
- Struct array as color lookup table
- Debounced button cycling through 8 colors

### 04_homework_template
Minimal scaffolding for student homework. All logic marked with `TODO`.

## Hardware Setup

```
ESP32-C3 Super Mini

GPIO3  --[220R]-- Red LED
GPIO4  --[220R]-- Green LED  
GPIO5  --[220R]-- Blue LED
                  Common Cathode -- GND

GPIO9  -- Button -- GND  (uses internal pull-up)
```

## Key Concepts

| Concept | Why It Matters |
|---------|---------------|
| `volatile` | Compiler must re-read variable every time (ISR can change it) |
| `IRAM_ATTR` | Places ISR in internal RAM (flash may be busy during interrupt) |
| ISR flag pattern | Keep ISR short, do work in loop() |
| `ledcAttach()` | New ESP32 Arduino Core 3.x API for PWM setup |
| `enum` + struct array | Clean state machine pattern for embedded systems |

## PlatformIO

Copy `platformio.ini` into each example folder, or create a single project
and swap `main.cpp` files between examples.
