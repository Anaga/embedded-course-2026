#include <Arduino.h>
#include <stdint.h>

/*
 * Lesson 5 - HOMEWORK5
 * RGB Color Wheel using PWM (LEDC old API)
 *
 * Target behavior:
 *   Smooth color wheel:
 *     Red -> Green -> Blue -> Red (continuous loop)
 *   Total cycle time: about 3..6 seconds (here ~5.8s)
 *   Print current phase on Serial
 *
 * Hardware (ESP32-C3):
 *   - RGB LED common cathode (common pin -> GND)
 *   - R -> GPIO3 (with 220R)
 *   - G -> GPIO4 (with 220R)
 *   - B -> GPIO5 (with 220R)
 *
 * Notes:
 *   - We use 8-bit PWM (0..255)
 *   - HOLD_MS is used to keep pure colors visible for human eye
 */

// ============================================================
// Pin Definitions (HOMEWORK5)
// ============================================================
#define PIN_RED     3
#define PIN_GREEN   4
#define PIN_BLUE    5

// ============================================================
// LEDC Channels (old API)
// ============================================================
#define CH_RED      0
#define CH_GREEN    1
#define CH_BLUE     2

// ============================================================
// PWM Configuration
// ============================================================
#define PWM_FREQ    5000    // 5 kHz
#define PWM_RES     8       // 8-bit resolution: duty 0..255
#define PWM_MAX     255

// ============================================================
// Timing
// Cycle time ≈ 3 phases * 256 steps * STEP_DELAY_MS + 3 * HOLD_MS
// STEP_DELAY_MS=7 and HOLD_MS=150 => about 5.8 seconds total
// ============================================================
#define STEP_DELAY_MS  7
#define HOLD_MS        150

// ============================================================
// BONUS: phase table (embedded pattern)
// Each phase crossfades between two channels:
//   - one channel goes down (255 -> 0)
//   - the other channel goes up   (0 -> 255)
// ============================================================
typedef struct {
    uint8_t ch_down;
    uint8_t ch_up;
    const char *name;    // printed on Serial
} phase_t;

static const phase_t PHASES[] = {
    { CH_RED,   CH_GREEN, "Phase: R -> G" },
    { CH_GREEN, CH_BLUE,  "Phase: G -> B" },
    { CH_BLUE,  CH_RED,   "Phase: B -> R" },
};

// Write only two active channels (third one forced to 0)
static void setOnlyTwoChannels(uint8_t ch1, uint8_t v1, uint8_t ch2, uint8_t v2)
{
    ledcWrite(CH_RED,   0);
    ledcWrite(CH_GREEN, 0);
    ledcWrite(CH_BLUE,  0);

    ledcWrite(ch1, v1);
    ledcWrite(ch2, v2);
}

void setup()
{
    Serial.begin(115200);
    delay(200);
    Serial.println("RGB Color Wheel - Homework 5");

    // Old LEDC API: configure channels
    ledcSetup(CH_RED,   PWM_FREQ, PWM_RES);
    ledcSetup(CH_GREEN, PWM_FREQ, PWM_RES);
    ledcSetup(CH_BLUE,  PWM_FREQ, PWM_RES);

    // Old LEDC API: attach pins to channels
    ledcAttachPin(PIN_RED,   CH_RED);
    ledcAttachPin(PIN_GREEN, CH_GREEN);
    ledcAttachPin(PIN_BLUE,  CH_BLUE);

    // Start from pure Red
    setOnlyTwoChannels(CH_RED, PWM_MAX, CH_GREEN, 0);
    delay(HOLD_MS);
}

void loop()
{
    // Repeat forever through all phases
    for (size_t p = 0; p < (sizeof(PHASES) / sizeof(PHASES[0])); ++p)
    {
        Serial.println(PHASES[p].name);

        // 256 steps linear interpolation
        for (uint16_t t = 0; t <= PWM_MAX; ++t)
        {
            uint8_t down = (uint8_t)(PWM_MAX - t); // 255 -> 0
            uint8_t up   = (uint8_t)t;             // 0 -> 255

            setOnlyTwoChannels(PHASES[p].ch_down, down,
                               PHASES[p].ch_up,   up);

            delay(STEP_DELAY_MS);

            // Hold the pure target color at the end of each phase
            if (t == PWM_MAX) {
                delay(HOLD_MS);
            }
        }
    }
}