# Lesson 2: Data Types in C - ESP32-C3 Demo

This project demonstrates fundamental C data types and their behavior on the ESP32-C3 microcontroller.

## Hardware Requirements

- **ESP32-C3 Super Mini** (Lolin C3 Mini compatible)
- USB-C cable
- Computer with Windows/Linux/Mac

## Software Requirements

- **Visual Studio Code** with PlatformIO extension
- **CH343 USB driver** (usually auto-installed on Windows)

## Project Overview

This demonstration covers:

1. **sizeof() operator** - Verify type sizes on ESP32-C3
2. **Integer overflow** - See wrap-around behavior
3. **Type casting** - Understand data loss risks
4. **stdint.h types** - Use fixed-width types for portability

## Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
cd lesson2-datatypes-esp32
```

### 2. Open in VSCode

```bash
code .
```

Or: `File -> Open Folder` in VSCode

### 3. Connect ESP32-C3

- Connect ESP32-C3 Super Mini via USB-C cable
- Check Device Manager (Windows) for COM port
- Note your COM port number (e.g., COM19)

### 4. Upload the Code

**Method 1 - VSCode Button:**
- Click the arrow button (→) in the bottom toolbar

**Method 2 - Command Palette:**
- Press `Ctrl+Shift+P` (Windows) or `Cmd+Shift+P` (Mac)
- Type: `PlatformIO: Upload`

### 5. Open Serial Monitor

**Method 1 - VSCode Button:**
- Click the plug icon (🔌) in the bottom toolbar

**Method 2 - Command Palette:**
- Press `Ctrl+Shift+P` / `Cmd+Shift+P`
- Type: `PlatformIO: Serial Monitor`

## Expected Output

```
=== ESP32-C3 Data Types Demo ===

--- sizeof() Demonstration ---
uint8_t:  1 byte
uint16_t: 2 bytes
uint32_t: 4 bytes
int8_t:   1 byte
int16_t:  2 bytes
int32_t:  4 bytes
float:    4 bytes
double:   8 bytes

--- Overflow Demonstration ---
uint8_t overflow (unsigned):
counter = 253
counter = 254
counter = 255
counter = 0
counter = 1
Notice: 255 -> 0 (wraps around!)

--- Type Casting Demonstration ---
big (uint16_t) = 1000
small (uint8_t) = 232 (data loss!)
Explanation: 1000 = 0x03E8, lower byte = 0xE8 = 232

temp (int16_t) = -10
positive (uint16_t) = 65526 (becomes huge!)

=== Demo Complete ===

LED will blink every second...

Count: 1, Uptime: 3079 ms
Count: 2, Uptime: 5084 ms
...
```

The onboard LED should blink every second.

## Code Explanation

### sizeof() Demonstration

```cpp
Serial.printf("uint8_t:  %d byte\n", sizeof(uint8_t));   // Always 1 byte
Serial.printf("uint32_t: %d bytes\n", sizeof(uint32_t)); // Always 4 bytes
```

This confirms that `stdint.h` types have guaranteed sizes across platforms.

### Overflow Example

```cpp
uint8_t counter = 253;
counter++;  // 254
counter++;  // 255
counter++;  // 0  <-- Wraps around!
```

Unsigned types wrap around when they exceed their maximum value.

### Type Casting

```cpp
uint16_t big = 1000;
uint8_t small = big;  // Data loss: only keeps lower byte (232)
```

When casting to a smaller type, only the lower bits are kept.

## Tasks for Students

### Task 1: Add Signed Overflow Demo

Add code to demonstrate signed integer overflow:

```cpp
int8_t signed_counter = 125;
for(int i = 0; i < 5; i++) {
    Serial.printf("signed_counter = %d\n", signed_counter);
    signed_counter++;
}
// Expected: 125 -> 126 -> 127 -> -128 -> -127
```

Where should this code go? (Hint: in `setup()` after the unsigned overflow demo)

### Task 2: Add Boolean Type

Demonstrate the `bool` type:

```cpp
bool is_running = true;
Serial.printf("bool size: %d byte\n", sizeof(bool));
Serial.printf("is_running = %d\n", is_running);
```

### Task 3: Variable Blink Speed

Modify the LED blink speed using a variable:

```cpp
uint16_t delay_ms = 200;  // Change from hardcoded 1000

// In loop():
digitalWrite(LED_PIN, HIGH);
delay(delay_ms);
digitalWrite(LED_PIN, LOW);
delay(delay_ms);
```

## Troubleshooting

### Upload Failed - Device Not Found

**Solution:**
1. Check USB cable (must support data, not just charging)
2. Verify COM port in Device Manager
3. Install CH343 driver if needed
4. Try different USB port

### Upload Failed - Access Denied

**Solution:**
- Close Serial Monitor before uploading
- Click the trash can icon in PlatformIO terminal

### No Output in Serial Monitor

**Solution:**
1. Check baud rate is 115200
2. Press RESET button on ESP32-C3
3. Reconnect Serial Monitor

### LED Not Blinking

**Solution:**
- Verify GPIO8 is correct for your board
- Check LED with multimeter
- Try a different board

## Homework Assignment

Create a new program that:

1. **Counts from 0 to 300** using the appropriate data type
2. **Prints every 10th number** to Serial Monitor
3. **Blinks LED faster** when counter exceeds 255
4. **Demonstrates overflow** when counter reaches maximum
5. **Uses sizeof()** to verify your type choice is correct

**Bonus Challenge:**
Add a second counter that counts down from 100 to 0.

### Submission

- Push your code to your personal Git repository
- Name the branch: `lesson2-homework`
- File should be in: `src/main.cpp`

## Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32-C3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
- [C stdint.h Reference](https://en.cppreference.com/w/c/types/integer)

## License

This project is for educational purposes - Embedded Systems Course 2026
