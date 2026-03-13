# Lesson 9 — Creating Peripheral Control Libraries

## Hardware

| Pin   | Role              |
|-------|-------------------|
| GPIO0 | BTN0 (active-low) |
| GPIO1 | BTN1 (active-low) |
| GPIO3 | Red LED (PWM)     |
| GPIO10| Green LED (PWM)   |

RGB LED is common-anode. All LED pins are active-low.
220-ohm resistors on each LED pin.

---

## Project structure

```
include/
    digital_pin.h   Base class — owns one GPIO pin (RAII)
    analog_pin.h    analogRead wrapper
    pwm_pin.h       LEDC wrapper (Arduino Core 2.x API)
    button.h        Derived from DigitalPin, ISR + debounce
    led.h           Derived from DigitalPin + PwmPin, fade engine
src/
    digital_pin.cpp
    analog_pin.cpp
    pwm_pin.cpp
    button.cpp
    led.cpp
    main.cpp
```

All classes live in the `drivers::` namespace.

---

## Expected behaviour

| Action          | Result                          |
|-----------------|---------------------------------|
| Hold BTN0       | Red LED fades in over 1 s       |
| Release BTN0    | Red LED fades out over 1 s      |
| Press BTN1      | Green LED toggles on/off        |
| Serial monitor  | State changes printed at 115200 |

---

## Key concepts

**RAII** — `DigitalPin` constructor calls `pinMode()`.
`PwmPin` constructor calls `ledcSetup()` and `ledcAttachPin()`.
The pin is ready the moment the object is constructed.

**Inheritance** — `Button` extends `DigitalPin` (INPUT_PULLUP).
`Led` extends both `DigitalPin` (OUTPUT) and `PwmPin` (LEDC).

**ISR + debounce** — `Button::onISR()` runs in interrupt context
(`IRAM_ATTR`). It ignores edges within 50 ms of the previous one
and stores the result in a `volatile bool`. `isPressed()` simply
returns that value — no GPIO read in the main loop.

**Non-blocking fade** — `Led::fadeTo()` records the target and
computes the step interval. `Led::update()` checks `millis()` and
advances the duty cycle by one step if enough time has passed.
`delay()` is never used inside library code.

**Copy disabled** — Each class deletes its copy constructor and
copy assignment operator. Two objects must not own the same pin.

---

## Homework notes

### Files to edit

- `src/button.cpp` — implement constructor and `isPressed()`
- `src/led.cpp` — implement constructor, `on()`, `off()`,
  `toggle()`, `setDutyCycle()`

### Files to leave untouched

- All `.h` files
- `src/digital_pin.cpp`, `src/analog_pin.cpp`, `src/pwm_pin.cpp`
- `src/main.cpp`

### Hints

**Button constructor** — The base class `DigitalPin` needs a pin
number and a mode. Buttons are wired active-low with internal
pull-ups. Look at the `DigitalPin` constructor signature in
`digital_pin.h`.

**Led constructor** — `Led` inherits from two base classes.
Both need to be initialised in the member initialiser list.
`DigitalPin` needs `OUTPUT` mode. `PwmPin` needs the pin and
channel numbers.

**setDutyCycle** — Store the value in `_duty` AND in
`_fadeTarget`. If you only update one of them, the fade engine
will immediately undo your change on the next `update()` call.

**toggle** — Use `setDutyCycle()` rather than writing `_duty`
directly. That way both `_duty` and `_fadeTarget` stay in sync
and the PWM output is updated.

**IntelliSense error 392** — If you see "member function may not
be redeclared outside its class", you have accidentally written
`Button::onISR()` inside the class body in the header file.
Method bodies belong in `.cpp` files only.
