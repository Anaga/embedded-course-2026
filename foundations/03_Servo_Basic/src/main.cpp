#include <Arduino.h>
#include <ESP32Servo.h>

// ============================================================
// Project: 03_Servo_Basic (ESP32 + PlatformIO)
// Goal   : Drive a hobby servo using PWM (via ESP32Servo library)
// Notes  :
// - A hobby servo expects a ~50 Hz PWM signal (period ~20 ms).
// - Position is encoded mainly by the pulse width (e.g. ~500..2400 us).
// - On ESP32 it is recommended to use ESP32Servo (not the classic Servo.h).
// ============================================================

// Choose a "safe" GPIO for servo signal. GPIO18 is commonly safe on ESP32.
static const int SERVO_PIN = 18;

// Typical pulse width range for many hobby servos.
// Some servos may need slightly different values (e.g. 544..2400).
static const int SERVO_MIN_US = 500;
static const int SERVO_MAX_US = 2400;

// Create a Servo object (provided by ESP32Servo library)
Servo servo;

void setup() {
  // Serial is used for debug output (very useful while testing on real hardware)
  Serial.begin(115200);
  delay(300); // small delay to allow the serial monitor to connect

  Serial.println("ESP32 Servo basic test");

  // Attach the servo object to a GPIO pin.
  // The library will configure the ESP32 PWM generation for the servo.
  // We also provide the min/max pulse width (microseconds) for correct mapping.
  servo.attach(SERVO_PIN, SERVO_MIN_US, SERVO_MAX_US);

  // Move to a known start position so we know the initial state.
  servo.write(90); // degrees: 0..180
  Serial.println("Servo -> 90 deg");
  delay(800); // give time for the servo to reach the position
}

void loop() {
  // Simple position sequence (slow enough to see movement clearly).
  // This is intentionally not "professional timing" (uses delay),
  // because the goal is a clear and reliable first test.

  servo.write(0);
  Serial.println("Servo -> 0 deg");
  delay(800);

  servo.write(90);
  Serial.println("Servo -> 90 deg");
  delay(800);

  servo.write(180);
  Serial.println("Servo -> 180 deg");
  delay(800);
}
