#include "foc_as5600.h"


uint16_t foc_as5600_read_raw_angle()
{
    uint16_t raw_angle;
    uint8_t buffer[2];
    uint8_t reg = FOC_AS5600_RAW_ANGLE_REG;
    foc_hal_i2c_write(FOC_AS5600_ST_ADDR,&reg,1);
    foc_hal_i2c_read(FOC_AS5600_ST_ADDR,buffer,2);
    raw_angle = (buffer[0] << 8) | buffer[1];
    return raw_angle;
}


double foc_as5600_read_angle()
{
    uint16_t raw_angle = 0x00;double angle;
    raw_angle = foc_as5600_read_raw_angle();
    angle = _constrain_angle(raw_angle/4096.0*2.0*PI);
    return angle;
}