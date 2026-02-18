# Lesson 3: Button Counter with Debounce

Practice project for Lesson 3 -- Control Flow, Functions & Pointers.

## Objective

Build a program that reads a push button, filters contact bounce,
counts the number of presses, and prints the count to Serial Monitor.

## Wiring

```
ESP32-C3 Super Mini         Push Button
------------------         -----------
     GPIO 3  <----------->  Pin 1
     GND     <----------->  Pin 2
```

No external pull-up resistor needed. We use the internal pull-up
via `INPUT_PULLUP` mode.

**Important:** With INPUT_PULLUP the logic is inverted:
- Not pressed = HIGH (1)
- Pressed = LOW (0)

## Tasks

Open `src/main.cpp` and complete all the `TODO` sections:

### 1. Setup (in `setup()`)
- Configure `BUTTON_PIN` as `INPUT_PULLUP` using `pinMode()`

### 2. Button Reading (in `isButtonPressed()`)
- Read the pin state with `digitalRead()`
- Detect a falling edge: `lastState == HIGH && reading == LOW`
- Add debounce: `delay(DEBOUNCE_MS)` then read again
- Return `true` only if still pressed after debounce

### 3. Output (in `printCounter()`)
- Use `Serial.printf()` to print a formatted message
- Use `%d` format specifier for the integer count

### 4. Main Loop (in `loop()`)
- Call `isButtonPressed()`
- If it returns true, increment counter and call `printCounter()`

## Expected Serial Output

```
=================================
  Lesson 3: Button Counter
  Press the button to count!
=================================
Button pressed! Count: 1
Button pressed! Count: 2
Button pressed! Count: 3
```

## What is Debounce?

When you press a mechanical button, the metal contacts physically
bounce for a few milliseconds. Without debounce, one press can
register as 5-10 presses. The simple fix: after detecting a press,
wait ~50ms for the contacts to settle, then read again.

## Build & Upload

1. Open the project folder in VSCode (PlatformIO should auto-detect)
2. Click the Upload button (arrow icon) in the PlatformIO toolbar
3. Open Serial Monitor (plug icon) at 115200 baud
4. Press the button and watch the counter increment

## Troubleshooting

### Button counts multiple times per press
- Increase `DEBOUNCE_MS` (try 80 or 100)
- Make sure you are updating `lastState` correctly

### Nothing happens when pressing
- Check wiring: one pin to GPIO 3, other pin to GND
- Verify `INPUT_PULLUP` is set in `pinMode()`
- Check that your condition detects LOW (pressed), not HIGH

### Serial Monitor shows garbage
- Set baud rate to 115200 in Serial Monitor
- Press the RESET button on the ESP32-C3

## License

Educational material -- Embedded Systems Course 2026
