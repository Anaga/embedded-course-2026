# Homework 5: Color Wheel

## Task

Create a smooth, continuously running color wheel using PWM on an RGB LED.

The LED should cycle through colors in a loop, never stopping:

```
Red -> Green -> Blue -> Red -> Green -> Blue -> ...
```

During each transition, one color fades out while the next fades in.
This produces all intermediate colors along the way:

```
Red -> [Yellow] -> Green -> [Cyan] -> Blue -> [Magenta] -> Red -> ...
```

## Requirements

- Use 3 PWM channels for R, G, B (old LEDC API: `ledcSetup` / `ledcAttachPin` / `ledcWrite`)
- Smooth fade between colors (no abrupt jumps)
- Full cycle should take about 3-6 seconds (your choice)
- Print the current phase to Serial (e.g. "Phase: R -> G")
- Use `#define` for pin numbers and timing constants
- No button needed -- the wheel runs automatically in `loop()`

## Hints

- Each phase has 256 steps (0..255)
- In each phase, one channel goes DOWN (255 -> 0) and another goes UP (0 -> 255)
- The third channel stays at 0

| Phase     | Red   | Green | Blue  |
|-----------|-------|-------|-------|
| R -> G    | DOWN  | UP    | 0     |
| G -> B    | 0     | DOWN  | UP    |
| B -> R    | UP    | 0     | DOWN  |

- Think about how to organize this with a loop or a function

## Hardware

```
ESP32-C3 Super Mini

GPIO3 --[220R]-- Red LED   --|
GPIO4 --[220R]-- Green LED --+--> GND (common cathode)
GPIO5 --[220R]-- Blue LED  --|

```

## Bonus (optional)

- Use a struct or array to define the three phases instead of copy-pasting code
- Add a button to pause/resume the wheel
- Add a potentiometer (ADC) to control speed

## Submission

Push your code to your GitHub repository before the next lesson.
