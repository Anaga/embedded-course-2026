# Lesson 17 -- PIO: Hardware WS2812 Driver

## Overview

This lesson replaces the Lesson 16 bit-bang WS2812 driver with a
hardware PIO (Programmable I/O) driver.  PIO is a unique feature of the
RP2040/RP2350 that offloads timing-critical I/O protocols to dedicated
state machines, freeing the CPU for other work.

**Board:** TENSTAR RP2350-USB (RP2350A, 16MB flash)

**Key takeaway:** The CPU writes pixel data to a FIFO and is immediately
free.  The PIO state machine generates the WS2812 signal with
cycle-exact timing, no interrupts disabled, no CPU blocking.

---

## What is PIO?

PIO = Programmable I/O.  The RP2350 has 3 PIO blocks, each with:
- 4 independent state machines
- 32-word shared instruction memory
- Clock divider (can run at any fraction of system clock)
- TX and RX FIFOs (4 words each, can be joined to 8)

State machines execute tiny programs (up to 32 instructions) that
toggle GPIO pins with exact timing.  They run independently of the
CPU and of each other.

### The 9 PIO Instructions

| Instruction | Purpose |
|-------------|---------|
| `jmp`  | Jump (conditional or unconditional) |
| `pull` | Load 32-bit word from TX FIFO into Output Shift Register |
| `out`  | Shift N bits from OSR to pins, X, or Y register |
| `set`  | Write immediate value to pins, X, or Y |
| `nop`  | No operation (delay only) |
| `push` | Write Input Shift Register to RX FIFO |
| `in`   | Shift bits from pins into ISR |
| `mov`  | Copy between registers |
| `wait` | Stall until a pin or IRQ condition is met |

Every instruction can also:
- **Side-set**: toggle GPIO pins as a side effect
- **Delay**: wait N extra clock cycles after execution

---

## The WS2812 PIO Program

Only 4 instructions are needed:

```
.program ws2812
.side_set 1

.define T1 2    ; shared HIGH time
.define T2 5    ; extended HIGH (bit=1) or LOW (bit=0)
.define T3 3    ; end-of-cycle LOW

.wrap_target
bitloop:
    out x, 1       side 0 [T3-1]  ; Shift 1 bit into X, pin LOW
    jmp !x do_zero side 1 [T1-1]  ; Pin HIGH, branch on bit value
do_one:
    jmp bitloop    side 1 [T2-1]  ; Bit=1: stay HIGH longer
do_zero:
    nop            side 0 [T2-1]  ; Bit=0: go LOW early
.wrap
```

### How it works

Each bit takes T1 + T2 + T3 = 10 PIO cycles:
- **Bit 1:** HIGH for T1+T2 = 7 cycles, LOW for T3 = 3 cycles
- **Bit 0:** HIGH for T1 = 2 cycles, LOW for T2+T3 = 8 cycles

At 8 MHz PIO clock (150 MHz / 18.75): 1 cycle = 125 ns
- Bit period = 1.25 us (800 kbps, matches WS2812 spec)
- Bit 1 HIGH = 875 ns (spec: 800 +/- 150 ns)
- Bit 0 HIGH = 250 ns (spec: 400 +/- 150 ns)

---

## Bit-Bang vs PIO

| Aspect | Bit-Bang (L16) | PIO (L17) |
|--------|----------------|-----------|
| CPU usage during update | 100% | ~0% (FIFO write only) |
| Interrupts | Must disable | Stay enabled |
| Timing accuracy | Compiler-dependent | Cycle-exact |
| Scalability | Poor (>100 LEDs = lag) | Excellent |
| Code complexity | Simple C | PIO assembly required |
| Portability | Any MCU | RP2040/RP2350 only |

---

## Project Structure

```
lesson17-pio-ws2812/
  platformio.ini
  src/
    ws2812_pio.h    -- Pre-compiled PIO program + init function
    main.cpp        -- Demo: rainbow with CPU time measurement
  homework/
    platformio.ini
    src/
      ws2812_pio.h  -- Same PIO driver (provided)
      main.cpp      -- Homework: port L16 effects to PIO
  README.md
```

---

## Demo: `src/main.cpp`

- Initializes **two PIO state machines** on PIO0:
  SM0 for onboard LED (GP22), SM1 for ring (GP15)
- Both share the same 4-instruction program (loaded once)
- Runs rainbow animation, mirrors first LED to onboard
- Measures CPU time per frame (prints every 100 frames)
- Toggles GP14 during updates (visible on logic analyzer)

### Expected output

```
=== Lesson 17: PIO WS2812 Driver ===
PIO block      : pio0
SM onboard LED : 0 (GP22)
SM ring        : 1 (GP15)
Probe pin      : GP14
Brightness     : 64 / 255
------------------------------------
Running rainbow... CPU time printed every 100 frames.

Frame 100  Avg CPU time: 12 us  (compare: bit-bang ~300 us)
Frame 200  Avg CPU time: 11 us  (compare: bit-bang ~300 us)
```

The CPU time should be ~10-15 us per frame (vs ~300 us for bit-bang).
That is a ~25x improvement in CPU availability.

---

## Hardware Wiring

Same as Lesson 16 -- no changes needed:

```
Ring VDD  -->  5V (VBUS pin)
Ring GND  -->  GND
Ring DIN  -->  GP15
```

Optional: connect GP14 to a logic analyzer or oscilloscope channel
to visualize the CPU time pulse during updates.

---

## Homework: `homework/src/main.cpp`

### Task

Port your Lesson 16 ring effects (Chase, Breathe, Color Wipe) to use
the PIO driver.  The PIO driver, color utilities, and measurement
framework are all provided.

### What is pre-written for you

- Complete PIO setup (ws2812_pio.h + initialization in setup())
- `pio_show()` and `pio_put_pixel()` output functions
- `hsv_to_rgb()`, `make_pixel()`, `dim()` color utilities
- `ButtonState` debounce
- CPU time measurement: `start_measure()` / `end_measure()`
- Frame counter with periodic Serial output

### What you need to implement (search for TODO)

1. **`effect_chase()`** -- single LED chasing around the ring
2. **`effect_breathe()`** -- all LEDs fade in/out
3. **`effect_color_wipe()`** -- fill ring one LED at a time
4. **Button handler** -- cycle effects, update onboard LED indicator
5. **Effect dispatcher** -- call the right function in loop()

### Key API change from Lesson 16

Replace this (bit-bang):
```cpp
// L16: manually disable interrupts, toggle GPIO
uint32_t st = save_and_disable_interrupts();
for (uint i = 0; i < count; i++) {
    ws_send_pixel(pin, px[i].r, px[i].g, px[i].b);
}
restore_interrupts(st);
sleep_us(300);  // reset pulse
```

With this (PIO):
```cpp
// L17: just write to the FIFO
pio_show(sm_ring, ring, NUM_LEDS);
```

That is the entire difference. PIO handles timing and reset internally.

### Bonus tasks

- **Dual-strip:** Connect a second LED strip to another GPIO, claim
  a 3rd state machine, and run independent animations simultaneously
- **New effect:** design your own animation (comet tail, sparkle,
  fire, theater chase, etc.)
- **Measure comparison:** run the same animation with bit-bang (L16)
  and PIO (L17), compare the GP14 probe pulse widths

---

## How ws2812_pio.h Works

The header contains:

1. **Pre-assembled PIO program** (4 uint16_t values) -- avoids
   needing the pioasm tool in the build chain

2. **`ws2812_pio_init()`** function that:
   - Configures the GPIO pin for PIO side-set output
   - Sets output shift: left (MSB first), autopull at 24 bits
   - Joins TX+RX FIFOs into one 8-deep TX FIFO
   - Sets clock divider to achieve 800 kbps bit rate
   - Starts the state machine

3. **Data format:** write `(grb << 8)` as a 32-bit word to the FIFO.
   The autopull triggers every 24 bits, and the top 8 bits are ignored.

---

## Troubleshooting

**PIO program fails to load ("no space")**
- Each PIO block has 32 instruction words shared by all 4 SMs
- Our program is only 4 words, so this is unlikely
- If other libraries use PIO (USB, etc.), try pio1 instead of pio0

**No state machine available**
- Each PIO block has 4 SMs; we use 2 (onboard + ring)
- If something else claimed SMs, you will get a panic

**LEDs work but colors are wrong**
- Check GRB order in pixel_to_grb()
- Some LED variants (SK6812) use different color order

**Serial output but no LEDs**
- Check wiring (same as L16)
- Verify the PIO init completed without error in Serial output
