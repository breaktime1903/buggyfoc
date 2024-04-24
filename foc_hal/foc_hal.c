#include "foc_hal.h"

void foc_hal_i2c_read(uint8_t addr,uint8_t * buf,uint16_t len)
{
#ifdef FOC_USE_STM32
    HAL_I2C_Master_Receive(&FOC_USE_STM32_HI2C,addr,buf,len,0xffff);
#endif
}

void foc_hal_i2c_write(uint8_t addr,uint8_t * buf,uint16_t len)
{
#ifdef FOC_USE_STM32
    HAL_I2C_Master_Transmit(&FOC_USE_STM32_HI2C,addr,buf,len,0xffff);
#endif
}

void foc_hal_spi_read(uint8_t * buf,uint16_t len)
{
#ifdef FOC_USE_STM32
    HAL_SPI_Receive(&FOC_USE_STM32_HSPI,buf,len,0xffff);
#endif
}

void foc_hal_spi_write(uint8_t * buf,uint16_t len)
{
#ifdef FOC_USE_STM32
    HAL_SPI_Transmit(&FOC_USE_STM32_HI2C,buf,len,0xffff);
#endif
}

void foc_hal_set_pwm(uint8_t channel,double duty)
{
    #ifdef FOC_USE_STM32
    uint16_t value = (uint16_t)(duty*FOC_USE_STM32_PWM_CNT_MAX);
    switch (channel)
    {
    case PWM_CHANNEL_1:
        FOC_USE_STM32_PWM_CH1_CCR = value;
        break;
    case PWM_CHANNEL_2:
        FOC_USE_STM32_PWM_CH2_CCR = value;
        break;
    case PWM_CHANNEL_3:
        FOC_USE_STM32_PWM_CH3_CCR = value;
        break;
    default:
        break;
    }
    #endif
} 

void foc_hal_delay(uint32_t delay_ms)
{
    #ifdef FOC_USE_STM32
    //对HAL库而言只需要一个简单的delay函数
    HAL_Delay((uint32_t)delay_ms);
    #endif
}

uint32_t foc_hal_get_tick()
{
    #ifdef FOC_USE_STM32
    return HAL_GetTick();
    #endif
}