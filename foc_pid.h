#ifndef __FOC_PID_H
#define __FOC_PID_H


typedef struct _foc_pid
{
    double kp;
    double ki;
    double kd;
    double _err_prev;
    double _err_sum;
    double fb;
} foc_pid;

void foc_pid_forward(foc_pid *p,double x,double std);
void foc_pid_init(foc_pid *p,double kp,double ki,double kd);

#endif