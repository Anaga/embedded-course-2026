#include <Arduino.h>
#include "button.h"
#include "led.h"

// ------------------------------------------------------------
// Lesson 9 demo — peripheral control library in action
//
// Hardware:
//   BTN0 : GPIO0 (active-low, internal pull-up)
//   BTN1 : GPIO1 (active-low, internal pull-up)
//   RED  : GPIO3  -> LEDC channel 0
//   GRN  : GPIO10 -> LEDC channel 1
//
// Behaviour:
//   BTN0 held    -> red LED fades in  (1 s)
//   BTN0 released-> red LED fades out (1 s)
//   BTN1 press   -> green LED toggles
// ------------------------------------------------------------

// Each object owns its GPIO pin (RAII).
// Constructors call pinMode() / ledcSetup() / ledcAttachPin()
// before setup() even runs.
drivers::Button btn0(0);
drivers::Button btn1(1);
drivers::Led    red(3,  0);   // GPIO3,  LEDC channel 0
drivers::Led    grn(10, 1);   // GPIO10, LEDC channel 1

// ISR wrappers - must be free functions; they delegate to the
// Button object so all debounce logic stays inside the class.
void IRAM_ATTR isr_btn0() { btn0.onISR(); }
void IRAM_ATTR isr_btn1() { btn1.onISR(); }


// Track previous button state to detect the press edge for BTN1.
bool prevBtn1 = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Lesson 9: peripheral control library demo");

    attachInterrupt(digitalPinToInterrupt(0), isr_btn0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(1), isr_btn1, CHANGE);
}

void loop()
{
    // --- BTN0: hold-to-fade -----------------------------------
    // fadeTo() is safe to call repeatedly with the same target;
    // it returns immediately if the target is already set.
    if (btn0.isPressed()) {
        red.fadeTo(255, 1000);
    } else {
        red.fadeTo(0, 1000);
    }

    // --- BTN1: toggle on press edge ---------------------------
    // isPressed() reflects the current held state. We detect
    // the rising edge (false -> true) to toggle once per press.
    bool currBtn1 = btn1.isPressed();
    if (currBtn1 && !prevBtn1) {
        grn.toggle();
        Serial.println("BTN1 pressed - green toggled");
    }
    prevBtn1 = currBtn1;

    // --- Drive the non-blocking fade state machine -----------
    // update() checks its internal millis() timer and advances
    // the duty cycle by one step if the interval has elapsed.
    // No blocking delay anywhere in this file.
    red.update();

    // Serial feedback for BTN0 state (printed once on change)
    static bool prevBtn0 = false;
    bool currBtn0 = btn0.isPressed();
    if (currBtn0 != prevBtn0) {
        Serial.print("BTN0 ");
        Serial.println(currBtn0 ? "pressed  -> fading in"
                                : "released -> fading out");
        prevBtn0 = currBtn0;
    }
}
