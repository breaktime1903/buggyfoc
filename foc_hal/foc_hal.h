/**
 * 对大部分外设采用硬件抽象层
 * 方便后期移植
*/

#ifndef __FOC_HAL_H
#define __FOC_HAL_H
#include "stdint.h"
#include "foc_config.h"

#ifdef FOC_USE_STM32
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "spi.h"

#if defined(STM32F407xx)
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#endif

#if defined(STM32G030xx)
#include "stm32g030xx.h"
#include "stm32g0xx_hal.h"
#endif

#endif

#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3


void foc_hal_i2c_read(uint8_t addr,uint8_t * buf, uint16_t len);
void foc_hal_i2c_write(uint8_t addr,uint8_t * buf, uint16_t len);
void foc_hal_spi_read(uint8_t * buf, uint16_t len);
void foc_hal_spi_read(uint8_t * buf, uint16_t len);
void foc_hal_set_pwm(uint8_t channel,double duty);
void foc_hal_delay(uint32_t delay_ms);
uint32_t foc_hal_get_tick();
#endif