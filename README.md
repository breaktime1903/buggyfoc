# BuggyFOC

为了备战电赛控制组，我自己写了个FOC库，这个库因为问题是在是比较多，所以暂且就叫BuggyFOC吧（乐）。

设计原则
- 采用硬件抽象层设计，方便后期对于树莓派PICO和其他设备的移植
- 电机控制代码采用面向过程设计，结构尽可能清晰易读（就连Park逆变换和Clark逆变换都给你写清楚了），适合初学者对FOC的原理进行学习
- 对PID采用结构体，方便多环控制

目前已经实现
- 对FOC电机的开环控制
- 对FOC电机的闭环控制（使用AS5600作为角度传感器）
- PID算法（使用foc_pid结构体）以及位置环控制

未来目标
- 对STM32G4的CORDIC加速做特定优化，加快三角函数的运算速度
- 对三角函数计算提供查找表的计算方式，牺牲精度以加快计算速度


# 使用方法

#### 开环控制代码

```c
#include "foc.h"
int main()
{
    //在各个外设初始化之后
    while(1)
    {
        //以每秒1圈的速度开环旋转
        foc_openloop(1);
    }
}
```

#### 闭环控制代码（基于AS5600）

```c
#include "foc.h"
int main()
{
    //对各个外设初始化之后
    double ea; //电气角度
    double ra; //实际角度
    while(1)
    {
        ra = foc_as5600_read_angle();
        ea = foc_ra_to_ea(ra); //将实际角度转为电气角度
        foc_closeloop(0.8,ea); //以0.8的力矩转动电机
    }
}
```

#### PID位置环（基于AS5600）

```c
#include "foc.h"
int main()
{
    //对各个外设初始化之后
    double ea; //电气角度
    double ra; //实际角度
    double moment; //输入力矩
    foc_pid pid;
    foc_pid_init(&pid,0.8,0,0); //结构体初始化，并设置Kp,Ki,Kd参数
    while(1)
    {
        ra = foc_as5600_read_angle();
        ea = foc_ra_to_ea(ra); //将实际角度转为电气角度
        //计算补偿力矩
        foc_pid_forward(&pid,ra,PI);
        moment = pid.fb;
        foc_closeloop(moment,ea); //以补偿力矩转动电机
        
    }
}
```