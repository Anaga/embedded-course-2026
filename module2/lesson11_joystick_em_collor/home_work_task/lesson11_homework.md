# Lesson 11 — Homework: 2D Color Mapping

## Background

In the demo we mapped the joystick **X axis** to a color blend:

```cpp
// X axis: RED -> BLUE
uint8_t t_x = static_cast<uint8_t>(x + 100); // 0..200
em_color c = lerp(em_color::RED, em_color::BLUE, t_x);
led.setColor(c);
```

Moving the stick left showed red, moving right showed blue.

---

## Your Task

Extend the demo so that the **Y axis** controls a second color blend independently:

```cpp
// Y axis: GREEN -> YELLOW
lerp(em_color::GREEN, em_color::YELLOW, t_y)
```

### Requirements

1. Compute `t_y` from `joy.getY()` the same way `t_x` is computed from `joy.getX()`.

2. Blend the two results together using a second `lerp()` call:
   - Use `t_x` as the mix parameter between the X-color and Y-color.
   - In other words: `final_color = lerp(color_x, color_y, t_x)`

3. Send `final_color` to the LED.

4. The button behavior stays the same: flash WHITE on press.

5. Serial debug output must print both axes:
   ```
   X=42  Y=-17  btn=0
   ```

---

## Expected Behavior

| Joystick position      | LED color (approximate) |
|------------------------|-------------------------|
| Center                 | Mix of all four colors  |
| Full left              | GREEN or YELLOW (Y-driven) |
| Full right             | RED or BLUE (Y-driven)  |
| Full up                | YELLOW-ish              |
| Full down              | GREEN-ish               |
| Top-right corner       | BLUE blended with YELLOW |
| Button press           | WHITE flash             |

---

## Hints

- `joy.getY()` returns `int8_t` in range `-100..+100`, same as `getX()`.
- `t_y` computation is identical to `t_x` -- just replace `x` with `y`.
- `lerp()` signature: `em_color lerp(em_color a, em_color b, uint8_t t)`
  where `t = 0` returns `a` and `t = 200` returns `b` (your range is 0..200).
- You need exactly **three** `lerp()` calls total.

---

## Submission

Push your changes to your personal branch on GitHub repository before the next class.

