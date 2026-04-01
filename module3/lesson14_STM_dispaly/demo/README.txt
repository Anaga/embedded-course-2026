Lesson 14 -- Nokia 5110 LCD via SPI on NUCLEO-F446RE
=====================================================

Demo project: rolling counter displayed on the Nokia 5110 LCD.


WIRING
------

Nokia 5110   F446RE Pin   Signal           Notes
-----------  -----------  ---------------  ----------------------------
VCC          3.3V         Power            Do NOT connect to 5V
GND          GND          Ground
CLK          PA5 (D13)    SPI1_SCK         Hardware SPI, AF5
DIN          PA7 (D11)    SPI1_MOSI        Hardware SPI, AF5
CE           PB6 (D10)    GPIO out         Label: LCD_CE
DC           PA9 (D8)     GPIO out         Label: LCD_DC
RST          PA8 (D7)     GPIO out         Label: LCD_RST
LIGHT        GND          Backlight        Module has on-board resistor


CUBEMX CONFIGURATION
--------------------

SPI1:
  Mode                 Full-Duplex Master
  Data size            8 Bits
  First Bit            MSB First
  CPOL                 Low   (CPOL = 0)
  CPHA                 1 Edge (CPHA = 0)
  NSS                  Software
  Baud Rate prescaler  APB2 / 16  (approx 5.6 MHz)

GPIO outputs (Push-Pull, No Pull, High speed):
  PB6   label LCD_CE
  PA9   label LCD_DC
  PA8   label LCD_RST

USART2 (PA2/PA3 AF7): keep enabled for ST-Link VCP / printf.


HOW TO INTEGRATE
----------------

1. Generate code from the .ioc file in STM32CubeIDE.
2. Copy pcd8544.h into Core/Inc/
3. Copy pcd8544.c into Core/Src/
4. Add pcd8544.c to the build (right-click -> Resource Configurations
   -> Exclude from build: make sure it is NOT excluded).
5. Open main.c and paste the snippets from main_demo.c into the
   matching USER CODE regions.
6. Build and flash.


EXPECTED RESULT
---------------

Line 0:  "Lesson 14"
Line 1:  "Nokia 5110"
Line 3:  "Count:    0"  ->  "Count:    1"  ->  ... (every 500 ms)


KNOWN ISSUE FOR STUDENTS
-------------------------

If IntelliSense shows a red underline under LCD_CE_GPIO_Port or
similar symbols, add Core/Inc to your include path:
  Project -> Properties -> C/C++ General -> Paths and Symbols
  -> Includes -> Add -> "Core/Inc"
The build will still succeed even without this step.
