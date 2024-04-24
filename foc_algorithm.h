#ifndef __FOC_ALGORITHM_H
#define __FOC_ALGORITHM_H
/**
 * FOC的克拉克变换所需向量
*/
#include "foc_config.h"
#include "math.h"
#include "stdint.h"

#define PI 3.1415927

typedef struct _foc_vector
{
    double alpha;
    double beta;
} foc_vector;

/**
 * FOC的电流设置
*/
typedef struct _foc_cur
{
    double a;
    double b;
    double c;
} foc_cur;

typedef struct _foc_vol
{
    double a;
    double b;
    double c;
} foc_vol;

double _constrain(double x,double xmin,double xmax);
double _constrain_angle(double x);
double foc_ra_to_ea(double x);
foc_vector *park_inv_transform(double iq,double id,double angle);
foc_cur *clark_inv_transform(foc_vector *vct);
foc_vol *foc_cur2vol(foc_cur *cur);
foc_vol *foc_algorithm(double iq,double id,double angle);

#endif