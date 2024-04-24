#ifndef __FOC_CONFIG_H
#define __FOC_CONFIG_H

/**
 * 关于FOC电机的一些参数设置
*/

//转子极数
#define FOC_PALE_NUM 7

//使用设备
#define FOC_USE_STM32 //使用STM32
//#define FOC_USE_RP2040 //使用RP2040

#ifdef FOC_USE_STM32
//选定使用的SPI和I2C
#define FOC_USE_STM32_HSPI hspi1
#define FOC_USE_STM32_HI2C hi2c1
//选定使用的定时器
#define FOC_USE_STM32_PWM_CH1_CCR TIM1->CCR1
#define FOC_USE_STM32_PWM_CH2_CCR TIM1->CCR2
#define FOC_USE_STM32_PWM_CH3_CCR TIM3->CCR3
#define FOC_USE_STM32_PWM_CNT_MAX (256-1)

#endif


#endif
