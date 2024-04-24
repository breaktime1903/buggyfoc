#ifndef __AS5600_H
#define __AS5600_H

#include "foc_hal/foc_hal.h"
#include "foc_algorithm.h"

#define FOC_AS5600_RAW_ADDR 0x36
#define FOC_AS5600_RESOLUTION 4096
#define FOC_AS5600_RAW_ANGLE_REG 0x0c


/**
 * STM32的I2C和其他的I2C库有部分不同
 * 设备地址需要左移一位
*/
#ifdef FOC_USE_STM32
#define FOC_AS5600_ST_ADDR (FOC_AS5600_RAW_ADDR << 1)
#define FOC_AS5600_READ_ST_ADDR (FOC_AS5600_RAW_ADDR << 1)
#define FOC_AS5600_WRITE_ST_ADDR ((FOC_AS5600_RAW_ADDR << 1) | 1)
#endif

uint16_t foc_as5600_read_raw_angle();
double foc_as5600_read_angle();

#endif