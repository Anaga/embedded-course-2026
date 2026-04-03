# Lesson 15 -- RP2350: Meet the New Platform

## Overview

First hands-on lesson with the RP2350 platform.  We set up a PlatformIO
project, wire an external LED, and flash a blink demo using the Pico SDK
GPIO API.

**Board:** RP2350 USB dongle (RP2350A, USB-A form factor, no onboard LED)

**Toolchain:** PlatformIO + Arduino framework (earlephilhower core).
The Arduino framework is used purely as a build wrapper; all application
code uses native Pico SDK API calls (`gpio_init`, `gpio_put`, `sleep_ms`).

---

## Why Arduino Framework + Pico SDK Calls?

PlatformIO does not yet have stable `framework = pico-sdk` support for
RP2350.  The earlephilhower Arduino-Pico core links the full Pico SDK
under the hood, giving us access to every SDK function while PlatformIO
handles the build toolchain, USB CDC serial, and .uf2 generation.

Entry point is `setup()` / `loop()` (Arduino convention), but inside we
write pure Pico SDK code -- no `digitalWrite()`, no `pinMode()`.

**Fallback:** If PlatformIO setup fails, install the official Raspberry Pi
Pico VS Code Extension and use CMake + Pico SDK directly.

---

## Hardware Wiring

No onboard LED on this board -- wire an external one:

```
GPIO 15 ---[ 330 Ohm ]---[LED anode]---[LED cathode]--- GND
```

For the homework, add:

```
GPIO 14 ---[ 330 Ohm ]---[LED B anode]---[LED B cathode]--- GND
GPIO 13 ---[Button]--- GND    (internal pull-up enabled in software)
```

Current calculation (red LED):
- Forward voltage ~2.0 V
- I = (3.3 V - 2.0 V) / 330 Ohm = ~4 mA (safe for RP2350 GPIO)

---

## First-Time Setup

### 1. Windows Long Path Fix (Windows only)

The Pico SDK's tinyusb submodule has deep paths.  Before your first build:

```
git config --system core.longpaths true
```

Then enable Win32 Long Paths:
- Win+R -> `gpedit.msc`
- Computer Configuration -> Administrative Templates -> System -> Filesystem
- Enable "Enable Win32 long paths"
- Reboot

### 2. Create the Project

Copy this folder into your workspace, or create a new PlatformIO project
and paste the `platformio.ini` and `src/main.cpp` files.

### 3. Build

Click the PlatformIO Build button (checkmark icon) or press `Ctrl+Alt+B`.
The first build downloads the toolchain and SDK -- this takes a few minutes.

Output: `.pio/build/rp2350_usb/firmware.uf2`

### 4. Flash via BOOTSEL

1. Hold the **BOOT** button on the dongle
2. Plug the dongle into a USB port
3. Release BOOT -- a drive called **RPI-RP2** appears
4. Drag `firmware.uf2` onto that drive
5. The dongle reboots and runs your code

### 5. Serial Monitor

Open PlatformIO Serial Monitor (plug icon) at **115200 baud**.
The RP2350 USB dongle uses USB CDC serial -- no extra UART wiring needed.

---

## Demo: `src/main.cpp`

Blinks an external LED on GPIO 15 at 500 ms intervals.  Prints each
toggle to USB serial.

Key Pico SDK functions used:
- `gpio_init(pin)` -- enable the GPIO pad
- `gpio_set_dir(pin, GPIO_OUT)` -- configure as output
- `gpio_put(pin, value)` -- set pin high (1) or low (0)
- `sleep_ms(ms)` -- blocking delay

---

## Homework: `homework/src/main.cpp`

**Multi-LED Button Controller**

Add a second LED (GPIO 14) and a button (GPIO 13).  Pressing the button
cycles through three blink patterns:

| Pattern | Behavior |
|---------|----------|
| 0 | Both LEDs blink together (500 ms) |
| 1 | LEDs alternate (A on, B off, then swap) |
| 2 | LED A fast (100 ms), LED B slow (500 ms) |

### What is pre-written for you

- `ButtonState` struct with debounce logic -- study how `update()` works
- Pattern name array and serial output skeleton
- `setup()` and `loop()` structure

### What you need to implement (search for TODO)

1. **`init_pins()`** -- Initialize GPIO for both LEDs and the button
2. **`pattern_both()`** -- Blink both LEDs together
3. **`pattern_alternate()`** -- Alternate between LED A and LED B
4. **`pattern_fast_slow()`** -- LED A fast, LED B slow (use a counter)
5. **Button handler in `loop()`** -- Advance pattern on press
6. **Pattern dispatcher in `loop()`** -- Call the right function

### Hints

- `gpio_pull_up(pin)` enables the internal pull-up resistor
- `gpio_get(pin)` reads the current pin state (returns `bool`)
- Button is active LOW: pressed = `false`, released = `true`
- For pattern 2, use a `static` counter to track when to toggle LED B

---

## RP2350 Quick Reference

| Feature | Value |
|---------|-------|
| CPU | 2x ARM Cortex-M33 @ 150 MHz (or 2x RISC-V Hazard3) |
| SRAM | 520 KB |
| Flash | External QSPI (4-16 MB, board-dependent) |
| GPIO | 30 (RP2350A) / 48 (RP2350B) |
| ADC | 12-bit, 4 channels (A) / 8 channels (B) |
| PIO | 3 blocks, 12 state machines |
| USB | 1.1 Host/Device |
| FPU | Single + Double precision |

### Architecture Selection

Default: ARM Cortex-M33.  To switch to RISC-V, add to `platformio.ini`:

```ini
board_build.mcu = rp2350-riscv
```

---

## Troubleshooting

**Build fails with "Filename too long"**
- See "Windows Long Path Fix" above

**RPI-RP2 drive does not appear**
- Make sure you hold BOOT *before* plugging in
- Try a different USB port (some hubs don't support it)

**Serial monitor shows nothing**
- Verify `monitor_speed = 115200` in `platformio.ini`
- The USB CDC serial needs a moment after reboot -- reopen the monitor

**IntelliSense red squiggles on Pico SDK headers**
- This is normal on the first build.  After building once, PlatformIO
  generates the compile_commands.json and IntelliSense resolves.
- If squiggles persist, try: `Ctrl+Shift+P` -> "PlatformIO: Rebuild
  IntelliSense Index"
