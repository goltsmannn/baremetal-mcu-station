#include "temp_sensor.h"

uint16_t read_temp_sensor(void) {
    i2c_init(); 

    i2c_start();
    i2c_transfer_byte(TARGET_READ);
    if (!i2c_read_ack()) {
        // Handle NACK (interrupt in the future)
        i2c_stop();
        return 0; // Indicate error
    }

    uint8_t msb = i2c_read_byte();
    i2c_send_ack();
    uint8_t lsb = i2c_read_byte(); 
    i2c_send_ack();
    i2c_stop();

    uint16_t temp = UNPACK_TEMP(msb, lsb);
    return temp;
}

uint8_t set_pointer_register(uint8_t reg) {
    i2c_init(); 

    i2c_start();
    i2c_transfer_byte(TARGET_WRITE);
    if (!i2c_read_ack()) {
        // Handle NACK (interrupt in the future)
        i2c_stop();
        return 0;
    }

    i2c_transfer_byte(reg);
    if (!i2c_read_ack()) {
        // Handle NACK (interrupt in the future)
        i2c_stop();
        return 0;
    }

    i2c_stop();
    return 1;
}