#ifndef OPT4001_PING_H
#define OPT4001_PING_H

#include "stm32f3xx_hal.h"
#include <stdint.h>

/*
 * opt4001_ping.h
 *
 * Lesson 13 demo: probe the OPT4001 ambient light sensor over I2C1,
 * report the result over USART2, and toggle LD2 on each successful ACK.
 *
 * Usage in main.c:
 *
 *   USER CODE BEGIN Includes
 *     #include "opt4001_ping.h"
 *   USER CODE END Includes
 *
 *   USER CODE BEGIN 2
 *     opt4001_ping_init(&hi2c1, &huart2, LD2_GPIO_Port, LD2_Pin);
 *   USER CODE END 2
 *
 *   USER CODE BEGIN WHILE
 *     while (1) {
 *       opt4001_ping_run();
 *       HAL_Delay(1000);
 *     }
 *   USER CODE END WHILE
 */

/* 7-bit I2C address of the OPT4001 when ADDR pin is tied to GND. */
#define OPT4001_I2C_ADDR       0x44U

/*
 * 8-bit form required by HAL_I2C_Master_Transmit / Master_Receive.
 * HAL_I2C_IsDeviceReady also expects this form.
 */
#define OPT4001_I2C_ADDR_8BIT  (OPT4001_I2C_ADDR << 1U)

/* Number of retries passed to HAL_I2C_IsDeviceReady. */
#define OPT4001_PING_RETRIES   3U

/* Timeout in milliseconds for each I2C transaction. */
#define OPT4001_PING_TIMEOUT_MS 100U

/*
 * Store peripheral handles and LED pin for use by opt4001_ping_run().
 * Call once from USER CODE BEGIN 2, after all MX_xxx_Init() calls.
 */
void opt4001_ping_init(I2C_HandleTypeDef  *hi2c,
                       UART_HandleTypeDef *huart,
                       GPIO_TypeDef       *led_port,
                       uint16_t            led_pin);

/*
 * Probe the sensor once, print the result over USART, and toggle the LED
 * if the device responded with ACK. Call from the main while(1) loop.
 */
void opt4001_ping_run(void);

#endif /* OPT4001_PING_H */
