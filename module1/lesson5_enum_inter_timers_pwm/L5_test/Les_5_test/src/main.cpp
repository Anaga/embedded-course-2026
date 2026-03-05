 /*
 * Hardware:
 *   - ESP32-C3 Super Mini
 *   - Common Cathode RGB LED on GPIO1 (R), GPIO3 (G), GPIO10 (B)
 *   - 220 ohm resistor on each color channel
 *   - Button on GPIO0 (active LOW, internal pull-up)
 * 
 *  * Two channels: Red and Green
 * Button press starts a slow crossfade between them
 * 
 * API: ESP32 Arduino Core 2.x (ledcSetup / ledcAttachPin)
 * 
 * 
 * Wiring:
 *   GPIO3 -> -> Red 
 *   GPIO4 -> 220R -> Green 
 *   GPIO5 -> 220R -> Blue 
 *   Common anode -> 220R -> GND
 *   Button: GPIO9 -> button -> GND
 */

#include <Arduino.h>
#include <stdint.h>


// ============================================================
// Pin Definitions
// ============================================================
#define PIN_RED     1
#define PIN_GREEN   3
#define PIN_BLUE    10
#define PIN_BUTTON  0

// --- LEDC Channels (old API uses channels, not pins!) ---
#define CH_RED      0
#define CH_GREEN    1

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
bool goingToGreen = true;

// ============================================================
// ISR - Button press handler
// ============================================================
void IRAM_ATTR onButtonPress() {
    uint32_t now = millis();
    if (now - lastPressMs > DEBOUNCE_MS) {
        lastPressMs = now;
        btnPressed  = true;
        goingToGreen = !goingToGreen;
    }
}

// ============================================================
// Set RG output (writes to channels)
// ============================================================
void setRG(uint8_t r, uint8_t g) {
    ledcWrite(CH_RED,   r);
    ledcWrite(CH_GREEN, g);
}

// ============================================================
// colorSwap - smooth crossfade between two colors
//
//   colorA:   starting color
//   colorB:   target color
//   swapTime: total transition time in milliseconds
// ============================================================
void colorSwap(const rgb_color_t* colorA,
               const rgb_color_t* colorB,
               uint32_t swapTime) {

    const uint16_t steps = 256;
    uint32_t stepDelay   = swapTime / steps;

    Serial.printf("Fade: %s -> %s (%lu ms)\n",
                   colorA->name, colorB->name, swapTime);

    for (uint16_t i = 0; i <= steps; i++) {
        // Linear interpolation: A*(1-t) + B*t
        // where t = i / steps
        uint8_t r = colorA->r + (int16_t)(colorB->r - colorA->r) * i / steps;
        uint8_t g = colorA->g + (int16_t)(colorB->g - colorA->g) * i / steps;

        setRG(r, g);
        delay(stepDelay);
    }
}


// ============================================================
// Setup
// ============================================================
#define SERIAL_SPEED 115200
#define STARTUP_DELAY 1500

void setup() {
    Serial.begin(SERIAL_SPEED);
    delay(STARTUP_DELAY);
    Serial.println(" ================================================= ");
    Serial.println("|  R-G PWM cross fade controller -  Lesson 5 Demo  |");
    Serial.println(" ================================================= ");
    Serial.println("Press button to swap colors.\n");

    // Old API: step 1 - configure channel
    ledcSetup(CH_RED,   PWM_FREQ, PWM_RES);
    ledcSetup(CH_GREEN, PWM_FREQ, PWM_RES);
  
    // Old API: step 2 - attach pin to channel
    ledcAttachPin(PIN_RED,   CH_RED);
    ledcAttachPin(PIN_GREEN, CH_GREEN);

    // Configure button with internal pull-up
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    
    // Attach interrupt - FALLING edge (button press = HIGH -> LOW)
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), onButtonPress, FALLING);

    // Set initial color
    const rgb_color_t* c = &COLOR_TABLE[currentColor];
    setRG(c->r, c->g);
    Serial.printf("Start: %s\n\n", c->name);

}

// ============================================================
// Main Loop
// ============================================================
//   2 const color for this example
//      red =  &COLOR_TABLE[COLOR_RED]
//      and
//      green = &COLOR_TABLE[COLOR_GREEN]
//

const rgb_color_t* red = &COLOR_TABLE[COLOR_RED];
const rgb_color_t* gren = &COLOR_TABLE[COLOR_GREEN];
const uint16_t swap_time = 1500; //1500ms - 1,5 sec
void loop() {
    if (btnPressed) {
        btnPressed = false;        
        Serial.printf("Fading %s...\n", goingToGreen ? "Red -> Green" : "Green -> Red");
        if (goingToGreen) {
            Serial.println("Tick");
            colorSwap(red, gren, swap_time);
        } else {
            Serial.println("Tack");
            colorSwap(gren, red, swap_time);
        }
    }
}
