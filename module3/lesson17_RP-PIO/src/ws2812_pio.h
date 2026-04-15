// =============================================================
// ws2812_pio.h -- Pre-compiled WS2812 PIO program
//
// Based on the official Raspberry Pi pico-examples ws2812.pio
// Pre-assembled so no pioasm toolchain dependency is needed.
//
// PIO program: 4 instructions, uses side-set for pin control.
//
//   .program ws2812
//   .side_set 1
//   .define public T1 2    ; HIGH time shared by both bit types
//   .define public T2 5    ; extra HIGH (bit 1) or LOW (bit 0)
//   .define public T3 3    ; LOW (bit 1) or start-of-next (bit 0)
//
//   .wrap_target
//   bitloop:
//       out x, 1       side 0 [T3-1]  ; Shift 1 bit, pin LOW
//       jmp !x do_zero side 1 [T1-1]  ; Pin HIGH, branch on bit
//   do_one:
//       jmp bitloop    side 1 [T2-1]  ; Stay HIGH longer (bit=1)
//   do_zero:
//       nop            side 0 [T2-1]  ; Go LOW early (bit=0)
//   .wrap
//
// Timing per bit: T1 + T2 + T3 = 10 PIO cycles
//   Bit 1: HIGH for T1+T2 = 7 cycles, LOW for T3 = 3 cycles
//   Bit 0: HIGH for T1    = 2 cycles, LOW for T2+T3 = 8 cycles
//
// At 8 MHz PIO clock (150 MHz / 18.75):
//   Bit period  = 10 / 8 MHz = 1.25 us  (800 kbps)
//   Bit 1 HIGH  = 7 / 8 MHz  = 875 ns   (spec: 800 ns +/- 150)
//   Bit 0 HIGH  = 2 / 8 MHz  = 250 ns   (spec: 400 ns +/- 150)
// =============================================================

#pragma once

#include "hardware/pio.h"
#include "hardware/clocks.h"

// ----- Assembled PIO program (4 instructions) ----------------
static const uint16_t ws2812_program_instructions[] = {
    0x6221, //  0: out    x, 1            side 0 [2]
    0x1123, //  1: jmp    !x, 3           side 1 [1]
    0x1400, //  2: jmp    0               side 1 [4]
    0xA442, //  3: nop                    side 0 [4]
};

static const struct pio_program ws2812_program = {
    .instructions = ws2812_program_instructions,
    .length       = 4,
    .origin       = -1,   // Let PIO allocate instruction space
};

// ----- Timing constants (matching the program above) ---------
static const uint WS2812_T1 = 2;
static const uint WS2812_T2 = 5;
static const uint WS2812_T3 = 3;
static const uint WS2812_CYCLES_PER_BIT = WS2812_T1 + WS2812_T2 + WS2812_T3;

// ----- Target bit rate: 800 kHz ------------------------------
static const float WS2812_FREQ_HZ = 800000.0f;

// =============================================================
//  ws2812_pio_init()
//
//  Loads the PIO program and configures a state machine to
//  drive WS2812 LEDs on the specified GPIO pin.
//
//  Parameters:
//    pio    -- PIO block (pio0 or pio1)
//    sm     -- State machine index (0-3)
//    offset -- Program offset (from pio_add_program)
//    pin    -- GPIO pin connected to WS2812 DIN
//
//  After init, write GRB pixel data to the FIFO:
//    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
// =============================================================
static inline void ws2812_pio_init(PIO pio, uint sm, uint offset, uint pin) {
    // Configure the GPIO for PIO output
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);  // 1 pin, output

    // Build the state machine configuration
    pio_sm_config c = pio_get_default_sm_config();

    // Set the program origin
    sm_config_set_wrap(&c,
        offset + 0,   // wrap_target = first instruction
        offset + 3    // wrap = last instruction
    );

    // Side-set: 1 pin, starting at 'pin'
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_sideset(&c, 1, false, false);
    //   1 bit for side-set, not optional, no pindirs

    // Output shift: shift left (MSB first), autopull at 24 bits
    sm_config_set_out_shift(&c, false, true, 24);
    //   shift_right=false (shift left, MSB first)
    //   autopull=true
    //   pull_threshold=24 (one full GRB pixel)

    // FIFO: join TX+RX into one 8-deep TX FIFO (we only send)
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // Clock divider: system_clock / (WS2812_FREQ * cycles_per_bit)
    float div = (float)clock_get_hz(clk_sys) /
                (WS2812_FREQ_HZ * WS2812_CYCLES_PER_BIT);
    sm_config_set_clkdiv(&c, div);

    // Initialize and start the state machine
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}
