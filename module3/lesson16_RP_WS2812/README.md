# Lesson 16 -- WS2812 Addressable LEDs

## Overview

This lesson covers the WS2812 (NeoPixel) addressable LED protocol and
implements a bit-bang driver from scratch on the RP2350.

**Board:** TENSTAR RP2350-USB (RP2350A, 16MB flash, onboard WS2812 on GP22)

---

## WS2812 Protocol Summary

### What Makes Them "Addressable"

Each WS2812 LED contains a tiny controller chip.  It has 4 pins:
VDD (5V), GND, DIN (data in), DOUT (data out).

The controller:
- Reads the first 24 bits from DIN and uses them as its color
- Passes all remaining bits to DOUT for the next LED in the chain
- When a RESET pulse arrives (>50 us LOW), it latches the color

This means you can control any number of LEDs from a single GPIO pin.

### Data Format

Each LED needs 24 bits in **GRB order** (not RGB!):

```
[G7 G6 G5 G4 G3 G2 G1 G0] [R7 R6 R5 R4 R3 R2 R1 R0] [B7 B6 B5 B4 B3 B2 B1 B0]
         Green                       Red                        Blue
```

Bits are sent MSB first.  For N LEDs, send N x 24 bits without pause.

### Bit Encoding (Timing)

Each bit is a HIGH pulse followed by a LOW pulse.  The duration of the
HIGH portion determines whether it is a 0 or 1:

| Bit | HIGH time | LOW time | Total  |
|-----|-----------|----------|--------|
| 0   | ~400 ns   | ~850 ns  | ~1250 ns |
| 1   | ~800 ns   | ~450 ns  | ~1250 ns |

After the last bit, hold LOW for >280 us to latch (RESET pulse).

### Why Bit-Banging?

Bit-banging means toggling the GPIO pin manually with precise timing.
This is educational and shows exactly how the protocol works.

The downside: interrupts must be disabled during transmission, which
blocks other code for ~300 us per 10 LEDs.

A better approach (for later): use PIO state machines, which handle
the timing in hardware while the CPU does other work.

---

## Hardware Wiring

### Onboard WS2812 (already soldered)

The TENSTAR RP2350-USB has a WS2812 on GP22.  No wiring needed.

### External 10-LED Ring

```
Ring VDD  -->  5V   (VBUS pin on the board)
Ring GND  -->  GND
Ring DIN  -->  GP15 (optionally through a 330 Ohm resistor)
```

### Power Notes

- Each LED draws up to 60 mA at full white (20 mA per channel)
- 10 LEDs at full white = 600 mA (exceeds USB 500 mA limit!)
- The code caps brightness to MAX_BRIGHTNESS = 64 (out of 255)
  which keeps total current well under 300 mA

### 3.3V Signal Level

The WS2812 spec says VIH = 0.7 x VDD = 3.5V at 5V power.
RP2350 GPIO outputs 3.3V, which is technically below spec.

In practice this works fine for short wires and small LED counts.
For production or longer runs, use a level shifter (74AHCT125).

---

## Project Structure

```
lesson16-ws2812/
  platformio.ini          -- PlatformIO configuration
  src/main.cpp            -- Demo: onboard LED + ring rainbow
  homework/
    platformio.ini        -- Same PlatformIO configuration
    src/main.cpp          -- Homework scaffold: 3 ring effects
  README.md               -- This file
```

---

## Demo: `src/main.cpp`

### Part 1: Onboard LED Color Cycle

Cycles through 7 basic colors (red, green, blue, yellow, cyan,
magenta, white) on the onboard WS2812 (GP22), one per second.

### Part 2: Ring Rainbow Animation

A continuously rotating rainbow across all 10 ring LEDs.
Uses HSV-to-RGB conversion with the hue spread evenly across the ring.

### Key Driver Functions

| Function | Purpose |
|----------|---------|
| `ws2812_send_bit()` | Send one bit with precise timing |
| `ws2812_send_byte()` | Send 8 bits MSB first |
| `ws2812_send_pixel()` | Send one pixel in GRB order |
| `ws2812_show()` | Send entire buffer with interrupts disabled |
| `ws2812_reset()` | Send reset pulse to latch data |
| `hsv_to_rgb()` | Convert HSV color to RGB pixel |

---

## Homework: `homework/src/main.cpp`

### Task

Implement 3 LED ring effects with a button to cycle between them.

| Effect | Behavior |
|--------|----------|
| Chase | Single lit LED moves around the ring |
| Breathe | All LEDs fade in and out smoothly |
| Color Wipe | Ring fills one LED at a time, then clears |

### What is pre-written for you

- Complete WS2812 driver (`ws_show`, `ws_send_pixel`, etc.)
- `hsv_to_rgb()` and `make_pixel()` color utilities
- `ButtonState` debounce from Lesson 15
- Effect names, indicator colors, and `setup()` / `loop()` structure

### What you need to implement (search for TODO)

1. **`effect_chase()`** -- Move a single bright LED around the ring
2. **`effect_breathe()`** -- Fade all LEDs in and out
3. **`effect_color_wipe()`** -- Fill ring one LED at a time
4. **Button handler in `loop()`** -- Cycle effect on press
5. **Effect dispatcher in `loop()`** -- Call the right function

### Hints

- Use `static` variables to maintain state between loop() calls
- `memset(ring, 0, sizeof(ring))` clears the entire ring to black
- `hsv_to_rgb(hue, 255, brightness)` gives smooth color with
  adjustable brightness (0-255)
- For breathing: increment/decrement brightness by 3 per frame,
  reverse direction at 0 and 255
- For color wipe: fill ring[0..n-1] with color, ring[n..9] with black,
  advance n each frame

---

## Troubleshooting

**LEDs flicker or show wrong colors**
- Check wiring: VDD=5V, GND=GND, DIN=GP15
- Make sure data goes to DIN, not DOUT
- Try a 330 Ohm resistor between GP15 and DIN

**Only the first LED works**
- Check that DOUT of each LED connects to DIN of the next
- On a ring, this should already be wired correctly

**Colors are wrong (red/green swapped)**
- WS2812 uses GRB order -- the driver handles this
- Some SK6812 clones use RGB -- adjust sendPixel() order if needed

**No LEDs light up at all**
- Verify 5V power is connected (VBUS pin)
- Try the onboard LED first (GP22) to confirm driver works
- Check that MAX_BRIGHTNESS is not 0

**USB serial shows nothing**
- Reopen serial monitor after flashing
- Verify monitor_speed = 115200
