// main.cpp
// Lesson 8: RAII, Memory Handling, Standard Libraries
//
// This demo has two parts, controlled by button presses:
//   BTN_0 (GPIO 0): RAII scope demo -- watch the LED turn on inside a scope
//                    and automatically turn off when the scope ends.
//   BTN_1 (GPIO 1): Heap fragmentation demo -- allocate and free memory
//                    blocks in a pattern that creates fragmentation,
//                    visible through Serial diagnostics.
//
// Hardware:
//   - Red LED on GPIO 3 (active high, 220 ohm resistor)
//   - Green LED on GPIO 10 (active high, 220 ohm resistor)
//   - Button 0 on GPIO 0 (active low, internal pull-up)
//   - Button 1 on GPIO 1 (active low, internal pull-up)

#include <Arduino.h>
#include <esp_heap_caps.h>
#include <new>         // for placement new
#include <stdint.h>

#include "pin_owner.h"
#include "diagnostics.h"

// -- Hardware pins --
static constexpr uint8_t PIN_RED_LED   = 3;
static constexpr uint8_t PIN_GREEN_LED = 10;
static constexpr uint8_t PIN_BTN_0     = 0;
static constexpr uint8_t PIN_BTN_1     = 1;

// -- Button debounce --
static constexpr uint32_t DEBOUNCE_MS = 250U;
static volatile uint32_t lastBtn0Press = 0;
static volatile uint32_t lastBtn1Press = 0;
static volatile bool btn0Flag = false;
static volatile bool btn1Flag = false;

// -- ISRs --
void IRAM_ATTR onBtn0() {
    uint32_t now = millis();
    if (now - lastBtn0Press > DEBOUNCE_MS) {
        lastBtn0Press = now;
        btn0Flag = true;
    }
}

void IRAM_ATTR onBtn1() {
    uint32_t now = millis();
    if (now - lastBtn1Press > DEBOUNCE_MS) {
        lastBtn1Press = now;
        btn1Flag = true;
    }
}

// -- Forward declarations --
void earlyReturnDemo();

// ====================================================================
// DEMO 1: RAII Scope Demo
//
// Creates a PinOwner for the red LED inside a { } scope.
// The LED turns on, stays on for 2 seconds, then the scope ends
// and the destructor automatically turns it off and releases the pin.
//
// Key teaching point: you never call "turn off" explicitly.
// The compiler does it for you when the object goes out of scope.
// ====================================================================

void demoRAII() {
    Serial.println();
    Serial.println("----------------------------------------");
    Serial.println("  DEMO 1: RAII Scope-Based Lifetime");
    Serial.println("----------------------------------------");
    Serial.println();

    Serial.println("Before scope: red LED pin is unconfigured.");
    printDiagnostics();
    Serial.println();

    // -- Scope begins --
    {
        // Constructor runs here: pin configured as OUTPUT, LED off
        PinOwner redLed(PIN_RED_LED);

        Serial.println("Inside scope: PinOwner created. Turning LED on...");
        redLed.on();
        delay(2000);

        Serial.println("Inside scope: LED has been on for 2 seconds.");
        Serial.println("Now leaving scope -- watch what happens...");
        Serial.println();

        // Destructor runs automatically at this closing brace.
        // LED turns off, pin goes back to INPUT.
    }
    // -- Scope ends --

    Serial.println("After scope: destructor has run.");
    Serial.println("Red LED is now OFF and pin is released (INPUT).");
    Serial.println();

    // Demonstrate early return safety with a second example
    Serial.println("--- Early return example ---");
    Serial.println("Calling a function that may return early...");
    earlyReturnDemo();
    Serial.println("Back from earlyReturnDemo(). LED is guaranteed off.");
    Serial.println();

    printDiagnostics();
    Serial.println("----------------------------------------");
    Serial.println();
}

// Simulates a function with an early return.
// The PinOwner destructor runs even though we return before the end.
void earlyReturnDemo() {
    PinOwner greenLed(PIN_GREEN_LED);
    greenLed.on();
    delay(500);

    // Simulate an error condition
    bool error = true;
    if (error) {
        Serial.println("  Error detected! Returning early...");
        return;  // <-- destructor STILL runs here!
    }

    // This code is unreachable, but that is fine:
    // cleanup happens regardless.
    Serial.println("  This line never executes.");
}

// ====================================================================
// DEMO 2: Heap Fragmentation
//
// Allocates an array of small blocks, then frees every other one.
// This creates a "swiss cheese" pattern in the heap.
// Even though there is plenty of total free memory, a large single
// allocation will fail because no contiguous block is big enough.
//
// Key teaching point: on MCUs without an MMU, fragmentation is
// permanent until reboot. This is why we avoid dynamic allocation
// in long-running embedded systems.
// ====================================================================

static constexpr uint8_t  FRAG_BLOCKS    = 20;
static constexpr uint16_t FRAG_BLOCK_SIZE = 1024;  // 1 KB each

void demoFragmentation() {
    Serial.println();
    Serial.println("----------------------------------------");
    Serial.println("  DEMO 2: Heap Fragmentation");
    Serial.println("----------------------------------------");
    Serial.println();

    Serial.println("Step 0: Initial heap state");
    printDiagnostics();
    Serial.println();

    // Step 1: Allocate 20 blocks of 1 KB each
    uint8_t* blocks[FRAG_BLOCKS] = {};
    Serial.printf("Step 1: Allocating %u blocks of %u bytes...\n",
                  FRAG_BLOCKS, FRAG_BLOCK_SIZE);

    for (uint8_t i = 0; i < FRAG_BLOCKS; ++i) {
        blocks[i] = new (std::nothrow) uint8_t[FRAG_BLOCK_SIZE];
        if (!blocks[i]) {
            Serial.printf("  Block %u: allocation FAILED\n", i);
        }
    }
    Serial.println("  All blocks allocated.");
    printDiagnostics();
    Serial.println();

    // Step 2: Free every OTHER block (creates holes)
    Serial.println("Step 2: Freeing every other block (swiss cheese)...");
    for (uint8_t i = 0; i < FRAG_BLOCKS; i += 2) {
        delete[] blocks[i];
        blocks[i] = nullptr;
    }

    uint16_t freedBytes = (FRAG_BLOCKS / 2) * FRAG_BLOCK_SIZE;
    Serial.printf("  Freed %u bytes in %u scattered holes.\n",
                  freedBytes, FRAG_BLOCKS / 2);
    printDiagnostics();
    Serial.println();

    // Step 3: Try to allocate a block larger than any single hole
    uint16_t bigSize = FRAG_BLOCK_SIZE * 3;  // 3 KB -- bigger than any hole
    Serial.printf("Step 3: Attempting to allocate %u bytes (3x block size)...\n",
                  bigSize);

    uint8_t* bigBlock = new (std::nothrow) uint8_t[bigSize];
    if (bigBlock) {
        Serial.println("  Allocation SUCCEEDED (heap was not fragmented enough).");
        delete[] bigBlock;
    } else {
        Serial.println("  Allocation FAILED -- not enough contiguous memory!");
        Serial.println("  This is fragmentation in action.");
    }
    Serial.println();

    // Step 4: Cleanup -- free the remaining blocks
    Serial.println("Step 4: Cleaning up remaining blocks...");
    for (uint8_t i = 0; i < FRAG_BLOCKS; ++i) {
        if (blocks[i]) {
            delete[] blocks[i];
            blocks[i] = nullptr;
        }
    }

    Serial.println("  All blocks freed.");
    printDiagnostics();

    Serial.println();
    Serial.println("Note: even after freeing everything, the heap may show");
    Serial.println("a smaller largest_block than before due to allocator");
    Serial.println("metadata overhead. On real systems, fragmentation");
    Serial.println("accumulates over time and never fully recovers.");
    Serial.println();
    Serial.println("----------------------------------------");
    Serial.println();
}

// ====================================================================
// Setup and Loop
// ====================================================================

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("+==========================================+");
    Serial.println("|  Lesson 8: RAII & Memory Handling Demo   |");
    Serial.println("+------------------------------------------+");
    Serial.println("|  BTN_0 (GPIO 0): RAII scope demo         |");
    Serial.println("|  BTN_1 (GPIO 1): Heap fragmentation demo |");
    Serial.println("+==========================================+");
    Serial.println();

    // Configure buttons with internal pull-ups
    pinMode(PIN_BTN_0, INPUT_PULLUP);
    pinMode(PIN_BTN_1, INPUT_PULLUP);

    // Attach interrupts (falling edge = button pressed)
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_0), onBtn0, FALLING);
    attachInterrupt(digitalPinToInterrupt(PIN_BTN_1), onBtn1, FALLING);

    // Print initial memory state
    Serial.println("Initial memory state:");
    printMemoryReport();
    Serial.println();
    Serial.println("Press BTN_0 or BTN_1 to start a demo...");
}

void loop() {
    if (btn0Flag) {
        btn0Flag = false;
        demoRAII();
    }

    if (btn1Flag) {
        btn1Flag = false;
        demoFragmentation();
    }

    delay(10);
}
