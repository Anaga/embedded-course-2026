/**
 * Lesson 5 - Example 3: RGB PWM Controller (Instructor Solution)
 * 
 * Combines ALL lesson concepts:
 *   - enum for color state management
 *   - Hardware interrupt for button input
 *   - PWM (LEDC) for RGB LED color mixing
 *   - Debouncing via millis() in ISR
 *   - Struct array for color lookup table
 * 
 * Hardware:
 *   - ESP32-C3 Super Mini
 *   - Common Cathode RGB LED on GPIO3 (R), GPIO4 (G), GPIO5 (B)
 *   - 220 ohm resistor on each color channel
 *   - Button on GPIO9 (active LOW, internal pull-up)
 * 
 * Wiring:
 *   GPIO3 -> 220R -> Red anode
 *   GPIO4 -> 220R -> Green anode
 *   GPIO5 -> 220R -> Blue anode
 *   Common cathode -> GND
 *   Button: GPIO9 -> button -> GND
 */

#include <Arduino.h>
#include <stdint.h>

// ============================================================
// Pin Definitions
// ============================================================
#define PIN_RED     3
#define PIN_GREEN   4
#define PIN_BLUE    5
#define PIN_BUTTON  9

// ============================================================
// PWM Configuration
// ============================================================
#define PWM_FREQ    5000    // 5 kHz
#define PWM_RES     8       // 8-bit: 0..255

// ============================================================
// Debounce
// ============================================================
#define DEBOUNCE_MS 250

// ============================================================
// Color Enum - clean, readable state management
// ============================================================
typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_WHITE,
    COLOR_ORANGE,
    COLOR_COUNT         // Always last! Used for modulo wrap-around
} color_t;

// ============================================================
// Color Data Structure - maps enum to RGB values
// ============================================================
typedef struct {
    uint8_t     r;
    uint8_t     g;
    uint8_t     b;
    const char* name;   // For serial output
} rgb_color_t;

// Color lookup table - indexed by color_t enum
// This pattern (enum + struct array) is very common in embedded!
static const rgb_color_t COLOR_TABLE[COLOR_COUNT] = {
    [COLOR_RED]     = { .r = 255, .g =   0, .b =   0, .name = "Red"     },
    [COLOR_GREEN]   = { .r =   0, .g = 255, .b =   0, .name = "Green"   },
    [COLOR_BLUE]    = { .r =   0, .g =   0, .b = 255, .name = "Blue"    },
    [COLOR_YELLOW]  = { .r = 255, .g = 255, .b =   0, .name = "Yellow"  },
    [COLOR_CYAN]    = { .r =   0, .g = 255, .b = 255, .name = "Cyan"    },
    [COLOR_MAGENTA] = { .r = 255, .g =   0, .b = 255, .name = "Magenta" },
    [COLOR_WHITE]   = { .r = 255, .g = 255, .b = 255, .name = "White"   },
    [COLOR_ORANGE]  = { .r = 255, .g = 128, .b =   0, .name = "Orange"  },
};

// ============================================================
// ISR Shared Variables
// ============================================================
volatile bool     btnPressed   = false;
volatile uint32_t lastPressMs  = 0;

// ============================================================
// State
// ============================================================
color_t currentColor = COLOR_RED;

// ============================================================
// ISR - Button press handler
// ============================================================
void IRAM_ATTR onButtonPress() {
    uint32_t now = millis();
    if (now - lastPressMs > DEBOUNCE_MS) {
        lastPressMs = now;
        btnPressed  = true;
    }
}

// ============================================================
// Apply Color - set PWM duty for each channel
// ============================================================
void applyColor(color_t color) {
    const rgb_color_t* c = &COLOR_TABLE[color];
    
    ledcWrite(PIN_RED,   c->r);
    ledcWrite(PIN_GREEN, c->g);
    ledcWrite(PIN_BLUE,  c->b);
    
    Serial.printf("Color: %-8s  (R=%3d, G=%3d, B=%3d)\n",
                   c->name, c->r, c->g, c->b);
}

// ============================================================
// Setup
// ============================================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("========================================");
    Serial.println("  RGB PWM Controller - Lesson 5 Demo");
    Serial.println("========================================");
    Serial.printf("Colors available: %d\n", COLOR_COUNT);
    Serial.println("Press button to cycle colors.\n");

    // Initialize PWM on all three channels
    ledcAttach(PIN_RED,   PWM_FREQ, PWM_RES);
    ledcAttach(PIN_GREEN, PWM_FREQ, PWM_RES);
    ledcAttach(PIN_BLUE,  PWM_FREQ, PWM_RES);

    // Configure button with internal pull-up
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    
    // Attach interrupt - FALLING edge (button press = HIGH -> LOW)
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), onButtonPress, FALLING);

    // Set initial color
    applyColor(currentColor);
}

// ============================================================
// Main Loop
// ============================================================
void loop() {
    if (btnPressed) {
        btnPressed = false;

        // Advance to next color using modulo wrap
        currentColor = (color_t)((currentColor + 1) % COLOR_COUNT);
        applyColor(currentColor);
    }

    // CPU is free for other tasks!
    // In a real project you might:
    //   - Read sensors
    //   - Update a display
    //   - Communicate over UART/I2C/SPI
    //   - Enter light sleep for power saving
}
