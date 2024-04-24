#ifndef __FOC_H
#define __FOC_H

#include "foc_algorithm.h"
#include "foc_pid.h"
#include "foc_config.h"

#include "foc_hal/foc_hal.h"

#include "foc_sensors/foc_as5600.h"


void foc_openloop(double speed_expected);
void foc_closeloop(double moment,double angle);
#endif