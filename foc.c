#include "foc.h"

uint32_t prev_tick; //之前的tick
double prev_angle; //之前的电角度

/*
    这里必须记住这个公式
    电角度 = 极对数 * 机械角度
    计算时除了开环的转速计算外统一使用电角度作为FOC算法输入角度
*/


/**
 * @brief 开环运行，需要在每次执行时调用
 * @param speed_expected 开环时的速度
*/
void foc_openloop(double speed_expected)
{
    //输入的转速是以r/s为单位
    uint32_t cur_tick = foc_hal_get_tick();
    double cur_angle;
    foc_vol *vol;
    double dt = cur_tick - prev_tick; //时间间隔

    cur_angle = prev_angle + dt*speed_expected*(2*PI)/1000*FOC_PALE_NUM; //必须乘上极对数

    //约束角度并计算
    cur_angle = _constrain_angle(cur_angle);
    vol = foc_algorithm(1,0,cur_angle);
    
    //设置PWM占空比
    foc_hal_set_pwm(PWM_CHANNEL_1,vol->a);
    foc_hal_set_pwm(PWM_CHANNEL_2,vol->b);
    foc_hal_set_pwm(PWM_CHANNEL_3,vol->c);
    
    //更新tick和电角度
    prev_tick = cur_tick;
    prev_angle = cur_angle;
}

/**
 * @brief 闭环运行，在运行时按当前角度和力矩计算PWM输出
 * @param moment 力矩大小
 * @param angle 当前角度
*/
void foc_closeloop(double moment,double angle)
{
    //将力矩约束在[0,1]区间内
    moment = _constrain(moment,-1.0,1.0);

    //读取电角度
    //double angle;
    //foc_read_angle(&angle);

    //计算力矩
    foc_vol *vol;
    vol = foc_algorithm(moment,0,angle);

    //更新PWM
    foc_hal_set_pwm(PWM_CHANNEL_1,vol->a);
    foc_hal_set_pwm(PWM_CHANNEL_2,vol->b);
    foc_hal_set_pwm(PWM_CHANNEL_3,vol->c);
}