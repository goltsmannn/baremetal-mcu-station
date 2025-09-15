#include "i2c.h"
#include "pin_management.h"

void i2c_init(void) {
    DDRB |= (1 << (SCL_PIN - 8));
    DDRB |= (1 << (SDA_PIN - 8));
    SCL_HIGH(); // active-low
    SDA_HIGH(); // active-low
}

void i2c_start(void) {
    set_pin_as_output(SDA_PIN);

    SDA_HIGH(); 
    SCL_HIGH(); //initial conditions

    SDA_LOW(); // start emitted
    
    SCL_LOW();
 // the transfer will assign next bit and then pulse clock
}

void i2c_stop(void) { // expects SCL_LOW()
    set_pin_as_output(SDA_PIN);

    SCL_HIGH(); // set clock high to distinguish from data
     
    SDA_HIGH(); // stop emitted
}

void i2c_send_ack(void) { // expects SCL_LOW()
    set_pin_as_output(SDA_PIN);

    SDA_LOW();  // pull SDA low to send ACK
    SCL_HIGH(); // clock high to complete ACK 
    DELAY_SHORT(); // let device read ACK
    SCL_LOW();  // release clock
}

void i2c_transfer_byte(uint8_t data) { // expects SCL_LOW()
    set_pin_as_output(SDA_PIN);

    for (int i = 0; i < 8; ++i) {
        if (data & (1 << i)) {
            SDA_HIGH();
        } else {
            SDA_LOW();
        }
        DELAY_SHORT();
        SCL_HIGH();
        DELAY_SHORT();
        SCL_LOW(); // leaves on low 
    }
}

uint8_t i2c_read_byte(void) {  // expects SCL_LOW(), since always after read_ack
    uint8_t data = 0x00;

    SCL_HIGH();

    for (int i = 0; i < 7; ++i) {
        data |= (read_digital_pin(SDA_PIN) << i);
        PULSE();
    }
    data |= (read_digital_pin(SDA_PIN) << 7); // last bit no pulse
    SCL_LOW(); // leave clock low
    return data;
}

uint8_t i2c_read_ack(void) {
    // we are starting with low so device has time to set-ack
    DELAY_SHORT(); // device is expeceted to have set clock

    SCL_HIGH(); // locking clock high to read ack bit
    uint8_t data = read_digital_pin(SDA_PIN); 
    SCL_LOW(); // release clock 
    return data;
}