/**
 * @file    main_demo.c
 * @brief   Lesson 14 demo -- rolling counter on Nokia 5110 LCD
 *
 * This file shows the application-layer code only.
 * Paste the relevant sections into the CubeMX-generated main.c:
 *
 *   - Includes   -> USER CODE BEGIN Includes
 *   - Variables  -> USER CODE BEGIN PV
 *   - Init call  -> USER CODE BEGIN 2
 *   - Loop body  -> USER CODE BEGIN 3
 *
 * Lesson 14 - Fundamentals of C++ for Microcontrollers
 */

/* USER CODE BEGIN Includes */
#include "pcd8544.h"
#include <stdio.h>    /* sprintf */
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
static uint32_t g_counter = 0;
static char     g_buf[14];        /* "Count: 99999\0" = 14 chars  */
/* USER CODE END PV */

/*
 * Inside MX_SPI1_Init() the generated code configures:
 *   Mode            = Full-Duplex Master
 *   Data size       = 8 bit
 *   CLK polarity    = Low   (CPOL = 0)
 *   CLK phase       = 1Edge (CPHA = 0)
 *   NSS             = Software
 *   Baud rate       = APB2/16
 *   First bit       = MSB
 */

/* USER CODE BEGIN 2 */
/*
 * Initialise the display. vop=0xB8 gives good contrast on most
 * Nokia 5110 modules; adjust 0xB0-0xBF if the display is too
 * dim or too dark.
 */
lcd_init(&hspi1, 0xB8);

lcd_goto(0, 0);
lcd_print_string("Lesson 14");
lcd_goto(0, 1);
lcd_print_string("Nokia 5110");
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
/*
 * Update counter every 500 ms using HAL_Delay.
 * (The homework will replace this with a non-blocking timer.)
 */
sprintf(g_buf, "Count:%5lu", g_counter++);

lcd_goto(0, 3);               /* column 0, bank 3                */
lcd_print_string(g_buf);

HAL_Delay(500);
/* USER CODE END 3 */
