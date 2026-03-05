# Homework 6 — Point on the Move

Embedded Systems Course 2026 | ESP32-C3 Super Mini

---

## Overview

During the lesson we created a basic `point` class in `dots.h`.
The code works but contains several bugs and design issues.

Your task has two parts:
1. Find and fix the bugs listed below.
2. Add a button that moves the point along the X axis.

---

## Wiring

### Button — GPIO 0

| Pin | Connect to          |
|-----|---------------------|
| IO0 | One leg of button   |
| GND | Other leg of button |

Use internal pull-up (active-low).

---

## Part 1 — Fix the Bugs

The current code has the following issues. Fix all of them.

### Bug 1 — Wrong axis in distance()

The `distance()` method has a copy-paste error. One of the delta
calculations uses the wrong member. Find it and fix it.

### Bug 2 — Uninitialized members

The default constructor `point()` does not set `x` and `y` to any value.
Calling `print()` on a default-constructed point prints garbage.

Fix: the default constructor should place the point at a **random** position.
Use `random(0, 26)` to generate a value from 0 to 25 for both `x` and `y`.
Print the generated coordinates so the user can see where the point spawned.

The parameterized constructor `point(x, y)` stays as-is (explicit coordinates).

### Bug 3 — Implementation in the header

All method bodies are currently inside `dots.h`. The file `dots.cpp`
is empty. This will cause linker errors if `dots.h` is included from
more than one source file.

Fix: move all method implementations from `dots.h` into `dots.cpp`.
Keep only the class declaration (with method prototypes) in `dots.h`.

### Bug 4 — Missing include guard

`dots.h` has no `#pragma once` or `#ifndef` guard. Add one.

---

## Part 2 — Button Moves Point on X Axis

After fixing the bugs, add the following feature:

1. Create a `point` object at position `(0, 0)`.
2. Connect a button on GPIO 0.
3. Each button press increments the X coordinate by 1.
4. After each press, print the updated position to Serial.
5. When X reaches 255, it should wrap around to 0 (natural uint8_t overflow).

### Requirements

- Add a `moveX(uint8_t delta)` method to the `point` class that increases
  X by the given amount.
- Add a `getX()` and `getY()` getter method (both `const`).
- Implement button debounce. You may use a simple delay-based approach
  or the `Button` class from the lesson template — your choice.
- Do not use `delay()` in `loop()` for debouncing.

### Expected Serial Output

```
================================================
 Homework 6: Point on the Move
================================================

Point spawned at random position: (14, 7)
[press] Position: (15, 7)
[press] Position: (16, 7)
[press] Position: (17, 7)
...
```

---

## Bonus (optional)

- Add a second button on GPIO 3 that increments Y by 1.
- Create a second point with explicit coordinates: `point origin(0, 0)`.
  After each move, print the Manhattan distance from `myPoint` to `origin`
  using a `distanceTo(const point& other) const` method.

---

## Hints

### random() on ESP32

```cpp
uint8_t val = (uint8_t)random(0, 26);  // returns 0..25
```

The ESP32 hardware RNG seeds `random()` automatically — no need to
call `randomSeed()`.

### Header vs Source — scope resolution

Inside the class declaration (`.h` file), methods are listed by name only.
The `ClassName::` prefix is used only in the `.cpp` file where you write
the implementation:

```cpp
// In the header — inside class { }
class point {
public:
    void print();                       // just the name
};

// In the source — outside the class
void point::print() {                   // ClassName::method
    Serial.printf("x=%d, y=%d\n", x, y);
}
```

---

## Grading

| Criteria                                       | Points |
|------------------------------------------------|--------|
| Bug 1 fixed — distance uses correct axes       | 1      |
| Bug 2 fixed — default ctor uses random(0,26)   | 1      |
| Bug 3 fixed — implementation moved to .cpp     | 2      |
| Bug 4 fixed — include guard added              | 1      |
| moveX() method added to point class            | 1      |
| getX() / getY() const getters added            | 1      |
| Button increments X with debounce (no delay)   | 2      |
| Code compiles without warnings                 | 1      |
| **Total**                                      | **10** |

---

## Submission

Push your code to your GitHub repository before the next lesson.
