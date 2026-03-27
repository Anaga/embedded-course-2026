#include "opt4001_ping.h"
#include <stdio.h>

/*
 * opt4001_ping.c
 *
 * Lesson 13 demo: probe the OPT4001 ambient light sensor over I2C1,
 * report the result over USART2, and toggle LD2 on each successful ACK.
 *
 * Board:    NUCLEO-F334R8
 * Sensor:   Texas Instruments OPT4001 (SOT-5X3 eval board, ADDR = GND)
 * I2C bus:  I2C1  -- PB6 SCL (AF4), PB7 SDA (AF4), Arduino D15/D14
 * UART:     USART2 -- PA2 TX (AF7), PA3 RX (AF7), ST-Link VCP
 *
 * Configure in CubeMX before building:
 *   Connectivity > I2C1   : I2C, Fast Mode 400 kHz
 *   Connectivity > USART2 : Asynchronous, 115200 baud, 8N1
 *   System Core > SYS     : Timebase = SysTick (default)
 */

/* ── Module-private state ────────────────────────────────────────────────── */

static I2C_HandleTypeDef  *s_hi2c    = NULL;
static UART_HandleTypeDef *s_huart   = NULL;
static GPIO_TypeDef        *s_led_port = NULL;
static uint16_t             s_led_pin  = 0U;

/* ── printf retarget ─────────────────────────────────────────────────────── */

/*
 * Redirect the C standard library's putchar() to USART2 so that printf()
 * works without a semihosting debugger.
 *
 * Place this function in only ONE translation unit per project. If another
 * .c file already defines __io_putchar(), remove this one.
 */
int __io_putchar(int ch)
{
    if (s_huart == NULL) {
        return ch;
    }
    HAL_UART_Transmit(s_huart, (uint8_t *)&ch, 1U, HAL_MAX_DELAY);
    return ch;
}

/* ── Public API ──────────────────────────────────────────────────────────── */

void opt4001_ping_init(I2C_HandleTypeDef  *hi2c,
                       UART_HandleTypeDef *huart,
                       GPIO_TypeDef       *led_port,
                       uint16_t            led_pin)
{
    s_hi2c     = hi2c;
    s_huart    = huart;
    s_led_port = led_port;
    s_led_pin  = led_pin;

    printf("opt4001_ping: init OK -- probing 0x%02X every 1 s\r\n",
           (unsigned int)OPT4001_I2C_ADDR);
}

void opt4001_ping_run(void)
{
    HAL_StatusTypeDef result;

    result = HAL_I2C_IsDeviceReady(s_hi2c,
                                   OPT4001_I2C_ADDR_8BIT,
                                   OPT4001_PING_RETRIES,
                                   OPT4001_PING_TIMEOUT_MS);

    if (result == HAL_OK) {
        printf("OPT4001 ACK  -- device found at 0x%02X\r\n",
               (unsigned int)OPT4001_I2C_ADDR);
        HAL_GPIO_TogglePin(s_led_port, s_led_pin);
    } else {
        printf("OPT4001 NACK -- no response (check wiring, ADDR pin, pull-ups)\r\n");
    }
}
