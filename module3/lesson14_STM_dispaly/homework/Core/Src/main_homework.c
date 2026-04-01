/**
 * @file    main_homework.c
 * @brief   Lesson 14 homework scaffold -- Simple LCD UI
 *
 * Task: Display a 3-line dashboard on the Nokia 5110 that updates
 *       every 1 second WITHOUT using HAL_Delay inside the loop.
 *
 * Requirements:
 *   Line 0 (bank 0): Static label -- your choice of text
 *   Line 1 (bank 2): Uptime in seconds (use HAL_GetTick() / 1000)
 *   Line 2 (bank 4): A counter that increments each update
 *
 *   - Update period: exactly 1000 ms
 *   - Use the non-blocking timer pattern (compare HAL_GetTick())
 *   - Only redraw lines that change (static label written once)
 *   - No HAL_Delay() calls inside while(1)
 *
 * Paste the relevant sections into CubeMX-generated main.c as shown
 * in the demo project (see demo/README.txt for CubeMX setup).
 *
 * Lesson 14 - Fundamentals of C++ for Microcontrollers
 */

/* USER CODE BEGIN Includes */
#include "pcd8544.h"
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PV */

/*
 * TODO: Declare variables you will need.
 *
 * Hints:
 *   - A uint32_t to remember when the last update happened
 *   - A uint32_t for the uptime counter
 *   - A uint32_t for the event counter
 *   - A char array large enough for a formatted line
 *     (14 chars fits "Uptime:  9999s")
 */

/* USER CODE END PV */

/* USER CODE BEGIN 2 */

/*
 * TODO: Initialise the LCD and write the static label on line 0.
 *
 * Hints:
 *   lcd_init(&hspi1, 0xB8);   -- contrast 0xB0..0xBF
 *   lcd_goto(col, bank);      -- bank 0 = top row
 *   lcd_print_string("...");
 *
 * Write the static label HERE (before the loop), not inside while(1).
 */

/* USER CODE END 2 */

/* USER CODE BEGIN 3 */

/*
 * Non-blocking timer pattern:
 *
 *   if (HAL_GetTick() - last_tick >= 1000U) {
 *       last_tick = HAL_GetTick();
 *       // ... update display here ...
 *   }
 *
 * TODO: Implement the complete timer body:
 *   1. Compute uptime_s = HAL_GetTick() / 1000
 *   2. Format uptime_s into a string with sprintf
 *   3. Move cursor to bank 2 and print the uptime string
 *   4. Increment your event counter
 *   5. Format and print the event counter on bank 4
 *
 * Hints:
 *   - sprintf(buf, "Up: %5lus", uptime_s);
 *   - lcd_goto(0, 2);   -- column 0, bank 2
 *   - lcd_print_string(buf);
 *   - Pad numbers with spaces to overwrite leftover digits:
 *       "%5lu" prints right-aligned in a 5-char field.
 */

/* USER CODE END 3 */
