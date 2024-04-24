#include "foc_pid.h"

void foc_pid_forward(foc_pid *p,double x,double std)
{
    double err = x-std;
    p->fb = p->kp * err + p->ki * p->_err_sum + p->kd * (err - p->_err_prev);
    p->_err_prev = err;
    p->_err_sum += err;
}

void foc_pid_init(foc_pid *p,double kp,double ki,double kd)
{
    p->kp = kp;
    p->ki = ki;
    p->kd = kd;
    p->_err_prev = 0.0;
    p->_err_sum = 0.0;
    p->fb = 0.0;
}