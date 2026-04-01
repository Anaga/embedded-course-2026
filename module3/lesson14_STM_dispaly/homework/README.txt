Lesson 14 -- Homework: Simple LCD UI
=====================================

Wiring and CubeMX setup are identical to the demo project.
See demo/README.txt for the full wiring table and CubeMX steps.


TASK
----

Implement a 3-line dashboard on the Nokia 5110 that updates every
1 second without blocking the main loop.

Required display layout (banks are horizontal 8-pixel rows):

  Bank 0:  <your static label>      (written once at startup)
  Bank 2:  uptime in seconds        (updated every second)
  Bank 4:  event counter            (increments every second)

Example after 42 seconds:

  STM32 F446RE
  
  Up:    42s
  
  Events:   42


RULES
-----

1. No HAL_Delay() calls anywhere inside while(1).
2. The static label must be written before the loop, not inside it.
3. Use HAL_GetTick() for timing.
4. Numbers must be right-aligned in a fixed-width field so that
   shorter numbers erase the digits of longer ones.
   Example: "%5lu" in sprintf produces "   42" (5 chars total).


HINTS
-----

Non-blocking timer skeleton:

    static uint32_t last_tick = 0;

    if (HAL_GetTick() - last_tick >= 1000U) {
        last_tick = HAL_GetTick();
        // update display
    }

Cursor placement:

    lcd_goto(0, 2);              -- column 0, bank 2
    lcd_print_string(buf);

lcd_goto() resets the cursor; you must call it before each line
you want to update.


DELIVERABLE
-----------

Paste your completed USER CODE blocks into main.c, build, and flash.
Demonstrate the running dashboard to the instructor.
