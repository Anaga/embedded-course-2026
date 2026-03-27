# Lesson 13 -- Pin Reference
# NUCLEO-F334R8 + OPT4001 Eval Board

---

## I2C1 -- OPT4001 Light Sensor

| Signal      | MCU Pin | Alternate Function | Arduino Header | OPT4001 Pin |
|-------------|---------|--------------------|----------------|-------------|
| I2C1_SCL    | PB6     | AF4                | D15 (CN5)      | SCL         |
| I2C1_SDA    | PB7     | AF4                | D14 (CN5)      | SDA         |
| 3.3 V power | --      | --                 | 3V3 (CN6 p.4)  | VDD         |
| Ground      | --      | --                 | GND (CN6 p.6)  | GND         |
| Address sel | --      | --                 | GND (CN6 p.6)  | ADDR        |
| Interrupt   | --      | --                 | not connected  | INT         |

GPIO mode (set by CubeMX): Alternate Function Open Drain, Pull-up, Very High Speed.

OPT4001 I2C address: 0x44 when ADDR pin is tied to GND.
Eval board pull-up resistors: 10 kOhm on SCL and SDA (already fitted).
No external pull-ups needed for 100 kHz operation.

---

## USART2 -- ST-Link Virtual COM Port (VCP)

| Signal     | MCU Pin | Alternate Function | Connector      | Direction          |
|------------|---------|--------------------|----------------|--------------------|
| USART2_TX  | PA2     | AF7                | ST-Link (internal) | MCU -> PC      |
| USART2_RX  | PA3     | AF7                | ST-Link (internal) | PC -> MCU      |

Baud rate: 115200, 8N1.
No external wiring needed. The ST-Link exposes this as a COM port over the USB cable.
Use this port for printf() debug output.

---

## USART3 -- External UART (Flying Wires to USB-UART Adapter)

| Signal     | MCU Pin | Alternate Function | Morpho Header | USB-UART Adapter |
|------------|---------|--------------------|---------------|------------------|
| USART3_TX  | PC10    | AF7                | CN7 pin 1     | RX               |
| USART3_RX  | PC11    | AF7                | CN7 pin 2     | TX               |
| Ground     | --      | --                 | CN7 GND pin   | GND              |

Baud rate: 115200, 8N1.
The F334R8 I/O is 3.3 V. Do not connect directly to a 5 V UART adapter.
Pin 1 on CN7 is marked with an arrow on the board silkscreen.

---

## On-Board LED and Button

| Function | MCU Pin | Connector  | Active Level | Notes                  |
|----------|---------|------------|--------------|------------------------|
| LD2 LED  | PA5     | CN10 p.11  | High         | Green LED, push-pull   |
| B1 button| PC13    | CN7 p.23   | Low          | Internal pull-up fitted|

CubeMX generates LD2_GPIO_Port / LD2_Pin and B1_GPIO_Port / B1_Pin macros
when the board is initialized with "Initialize all peripherals" set to Yes.

---

## CubeMX Peripheral Summary

| Peripheral | Mode             | Speed       | Pins        |
|------------|------------------|-------------|-------------|
| I2C1       | I2C              | 400 kHz     | PB6, PB7    |
| USART2     | Asynchronous     | 115200 baud | PA2, PA3    |
| USART3     | Asynchronous     | 115200 baud | PC10, PC11  |
| SYS        | SysTick timebase | --          | --          |
| RCC        | HSI, PLL x16     | 64 MHz      | --          |
