/**
 * @file    pcd8544.h
 * @brief   PCD8544 (Nokia 5110) LCD driver for STM32 HAL
 *
 * Display specs : 84 x 48 pixels, monochrome
 * Interface     : SPI (write-only, no MISO)
 * Controller    : Philips PCD8544
 *
 * Pin mapping (configured in STM32CubeMX):
 *   Nokia CLK   -> PA5  SPI1_SCK
 *   Nokia DIN   -> PA7  SPI1_MOSI
 *   Nokia CE    -> PB6  GPIO output  (LCD_CE)
 *   Nokia DC    -> PA9  GPIO output  (LCD_DC)
 *   Nokia RST   -> PA8  GPIO output  (LCD_RST)
 *   Nokia VCC   -> 3.3V
 *   Nokia LIGHT -> GND
 *   Nokia GND   -> GND
 *
 * Lesson 14 - Fundamentals of C++ for Microcontrollers
 */

#ifndef PCD8544_H
#define PCD8544_H

#include "main.h"          /* HAL types, GPIO/SPI handles */
#include <stdint.h>

/* -- Display geometry ------------------------------------------- */
#define LCD_COLS      84
#define LCD_ROWS      48
#define LCD_BANKS     6    /* 48 / 8 = 6 horizontal banks        */
#define LCD_BUF_SIZE  (LCD_COLS * LCD_BANKS)  /* 504 bytes       */

/* -- GPIO aliases - must match CubeMX pin labels --------------- */
#define LCD_CE_PORT   LCD_CE_GPIO_Port
#define LCD_CE_PIN    LCD_CE_Pin
#define LCD_DC_PORT   LCD_DC_GPIO_Port
#define LCD_DC_PIN    LCD_DC_Pin
#define LCD_RST_PORT  LCD_RST_GPIO_Port
#define LCD_RST_PIN   LCD_RST_Pin

/* -- Public API ------------------------------------------------- */

/**
 * @brief  Initialise the PCD8544 controller.
 *         Must be called once after HAL_Init() and clock setup.
 * @param  hspi  Pointer to the SPI handle (e.g. &hspi1)
 * @param  vop   Contrast byte, typically 0xB0..0xBF (default 0xB8)
 */
void lcd_init(SPI_HandleTypeDef *hspi, uint8_t vop);

/**
 * @brief  Fill the entire display with 0x00 (all pixels off).
 */
void lcd_clear(void);

/**
 * @brief  Set the DDRAM cursor position.
 * @param  col   Column  0..83
 * @param  bank  Bank    0..5  (each bank = 8 pixel rows)
 */
void lcd_goto(uint8_t col, uint8_t bank);

/**
 * @brief  Write a single ASCII character at the current cursor position.
 *         Advances the cursor by 6 pixels (5 data + 1 spacer).
 * @param  c  ASCII character (0x20..0x7E supported)
 */
void lcd_print_char(char c);

/**
 * @brief  Write a null-terminated ASCII string at the current cursor.
 * @param  str  Pointer to the string
 */
void lcd_print_string(const char *str);

/**
 * @brief  Send one raw byte to the controller.
 * @param  data     Byte to send
 * @param  is_data  1 = pixel data (DC high), 0 = command (DC low)
 */
void lcd_send_byte(uint8_t data, uint8_t is_data);

#endif /* PCD8544_H */
