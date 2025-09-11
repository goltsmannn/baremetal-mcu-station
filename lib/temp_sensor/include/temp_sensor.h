#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H
#include "i2c.h"

#define UNPACK_TEMP(msb, lsb) ((((msb) << 8) | (lsb) & 0xF00) >> 4)
#define TEMP_REGISTER 0x00

uint16_t read_temp_sensor(void);
uint8_t set_pointer_register(uint8_t reg);

#endif // TEMP_SENSOR_H