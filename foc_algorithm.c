/**
 * 这一段代码主要目的是实现帕克逆变换和克拉克逆变换
 * 以及一些乱七八糟的算法部分
 * 我写的确实和shit一样
*/

#include "foc_algorithm.h"

/**
 * @brief 帕克逆变换
 * @param iq 力矩Iq
 * @param id 力矩Id
 * @param angle 当前角度
 * @retval 帕克逆变换后所得的向量
*/
foc_vector *park_inv_transform(double iq,double id,double angle)
{
    //代码有误 需修改
    //已作修改
    static foc_vector vct;
    static double sv,cv;
    //优化一下
    sv = sin(angle);
    cv = cos(angle);
    vct.alpha = id*cv-iq*sv;
    vct.beta = id*sv+iq*cv;
    return &vct;
}

/**
 * @brief 克拉克逆变换
 * @param vct 帕克逆变换后所得向量
 * @retval 克拉克逆变换后所得到的三相电流
*/
foc_cur *clark_inv_transform(foc_vector *vct)
{
    static foc_cur cur;
    //不用等幅变换
    cur.a = (vct->alpha);
    cur.b = (0.866025404*(vct->beta)-0.5*(vct->alpha));
    //基于KCL我没必要这么复杂的再算一次
    //cur.c = (-0.866025404*(vct->beta)-0.5*(vct->alpha)) * 0.666666;
    cur.c = - cur.a - cur.b;
    return &cur;
}


/**
 * @brief 约束函数，使数据在[xmin,xmax]区间内
 * @param x 输入值
 * @param xmin 最小值
 * @param xmax 最大值
 * @retval 约束上下界后的最终值
*/
double _constrain(double x,double xmin,double xmax)
{
    if(x < xmin) return xmin;
    else if(x > xmax) return xmax;
    else return x;
}

/**
 * @brief 角度约束函数，使数据在[0,2pi]区间内
 * @param x 输入值
 * @retval 约束上下界后的最终值
*/
double _constrain_angle(double x)
{
    while(x >= 2*PI) { x -= 2*PI; }
    return x;
}




/**
 * @brief 将克拉克逆变换所计算得到的电流值转为电压
 * @param cur 克拉克逆变换计算所得三相电流
 * @retval 计算所得到的三相电压（按占空比计算）
*/
foc_vol *foc_cur2vol(foc_cur *cur)
{
    static foc_vol vol;
    vol.a = (cur->a/2.0)+0.5;
    vol.b = (cur->b/2.0)+0.5;
    vol.c = (cur->c/2.0)+0.5;

    //约束数据
    vol.a = _constrain(vol.a,0.0,1.0);
    vol.b = _constrain(vol.b,0.0,1.0);
    vol.c = _constrain(vol.c,0.0,1.0);
    
    return &vol;
}

/**
 * @brief 进行一次完整的FOC算法计算
 * @param iq 切向力矩
 * @param id 法向力矩（建议置零）
 * @param angle 由霍尔读出的电角度
 * @retval 基于foc_cur类型的驱动器电流
*/
foc_vol *foc_algorithm(double iq,double id,double angle)
{
    static foc_vector *vct;
    static foc_cur *cur;
    static foc_vol *vol;
    vct = park_inv_transform(iq,id,angle);
    cur = clark_inv_transform(vct);
    vol = foc_cur2vol(cur);
    return vol;
}

/**
 * @brief 将机械角度转为电角度给FOC闭环使用
*/

double foc_ra_to_ea(double x)
{
    return _constrain_angle(x*FOC_PALE_NUM);
}
