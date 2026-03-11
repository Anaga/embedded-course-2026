# Homework 6 — Bunny Escape Game

Embedded Systems Course 2026 | ESP32-C3 Super Mini

---

## The Story

A bunny has spawned at a random location on a 25x25 field.
A hungry hawk is circling above. The bunny has exactly **25 moves**
to reach its hole in the center of the field — or the hawk catches it.

Your job: guide the bunny to safety using two buttons.

---

## Wiring

### Buttons

| Button   | Pin  | Connect to          |
|----------|------|---------------------|
| BTN_X    | IO1  | One leg of button   |
| BTN_Y    | IO0  | One leg of button   |
| Both GND | GND  | Other leg of both   |

Internal pull-ups are used. Interrupts with FALLING edge.

### RGB LED (common anode)

```
3.3V ──────────────────── common anode (longest leg)

IO3  ── 220 ohm ── Red cathode     (bunny in danger)
IO10 ── 220 ohm ── Green cathode   (bunny is safe)
```

Remember: common anode = active-low. `LOW` turns the LED ON.

---

## Game Rules

1. The field is 25x25 (coordinates 0..25 for both X and Y).
2. The **hole** is at the center of the field: position **(12, 12)**.
3. The hole has a **radius of 5** — the bunny is safe if its
   Manhattan distance to the center is less than or equal to 5.
4. The bunny spawns at a **random position** (default constructor).
5. BTN_X moves the bunny +1 on the X axis. BTN_Y moves +1 on Y.
   When X or Y exceeds 25, it wraps to 0.
6. The player has **25 moves** total (X and Y moves combined).
7. If the bunny reaches the hole within 25 moves — **green LED**
   turns on, red turns off. Print a victory message.
8. If 25 moves are used and the bunny is still outside — **red LED**
   stays on. Print a game over message. Buttons stop working.
9. On startup, the **red LED** is on (bunny is in danger).

---

## Requirements

### Part 1 — Fix the Bug

The `distance()` method has an unsigned subtraction bug.
If `A.x` is smaller than `B.x`, the result wraps around to a large
number instead of giving the correct distance.

Fix this so the distance is always correct regardless of which
point has larger coordinates.

Hint: compare before subtracting, or use a ternary operator.

### Part 2 — Game Logic

1. Use the `point` class from the lesson (with the bug fix above).
2. Create a `point bunny` (random spawn) and `point hole(12, 12)`.
3. Use ISR-based button handling with debounce (from the lesson).
4. Count total moves. After each move, print:
   - Current bunny position
   - Distance to hole
   - Moves remaining
5. Check win/lose conditions after each move.

### Part 3 — LED Feedback

1. Red LED on GPIO 3 — ON at startup (bunny in danger).
2. Green LED on GPIO 10 — OFF at startup.
3. When the bunny enters the hole zone (distance <= 5):
   - Turn OFF red, turn ON green.
   - Print victory message.
   - Stop accepting button presses.
4. When 25 moves are exhausted without reaching the hole:
   - Red stays on.
   - Print game over message.
   - Stop accepting button presses.

### Part 4 — Serial Output

Print a status display after each move. Example:

```
================================================
 Bunny Escape Game
================================================
Bunny spawned at (21, 3)
Hole is at (12, 12). Radius: 5
Moves allowed: 25
---

[Move 1] BTN_X -> Bunny at (22, 3) | Distance: 19 | Moves left: 24
[Move 2] BTN_X -> Bunny at (23, 3) | Distance: 20 | Moves left: 23
[Move 3] BTN_Y -> Bunny at (23, 4) | Distance: 19 | Moves left: 22
...
[Move 18] BTN_Y -> Bunny at (14, 11) | Distance: 3 | Moves left: 7

*** BUNNY IS SAFE! Reached the hole in 18 moves! ***
```

Game over example:

```
[Move 25] BTN_X -> Bunny at (5, 20) | Distance: 15 | Moves left: 0

*** GAME OVER! The hawk caught the bunny! ***
```

---

## File Structure

```
homework6-bunny/
  include/
    dots.h          (from lesson, fix the distance bug)
  src/
    dots.cpp        (from lesson, fix the distance bug)
    main.cpp        (game logic — you write this)
  platformio.ini
```

---

## Hints

### Fixing the distance bug

```cpp
// WRONG: unsigned subtraction wraps around
uint8_t delta_x = A.x - B.x;    // 3 - 12 = 247 (not -9)

// CORRECT: check which is larger first
uint8_t delta_x = (A.x > B.x) ? (A.x - B.x) : (B.x - A.x);
```

### LED active-low (common anode)

```cpp
// Turn RED on:
digitalWrite(RED_PIN, LOW);     // active-low!

// Turn RED off:
digitalWrite(RED_PIN, HIGH);
```

### Stopping the game

Use a `bool gameOver` flag. In `loop()`, only process button
presses when `gameOver == false`.

### Manhattan distance

The distance from (x1, y1) to (x2, y2) is:
`|x1 - x2| + |y1 - y2|`

This is what your fixed `distance()` method should calculate.

---

## Grading

| Criteria                                        | Points |
|-------------------------------------------------|--------|
| distance() bug fixed (correct for all cases)    | 2      |
| Bunny spawns randomly, hole at (12,12)          | 1      |
| Buttons move bunny with ISR + debounce          | 2      |
| Move counter works, game stops at 25            | 1      |
| Win condition: distance <= 5, green LED         | 1      |
| Lose condition: 25 moves, red LED stays         | 1      |
| Serial output shows position, distance, moves   | 1      |
| Code compiles without warnings                  | 1      |
| **Total**                                       | **10** |

---

## Submission

Push your code to your GitHub repository before the next lesson.
