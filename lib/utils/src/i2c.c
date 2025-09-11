#include "i2c.h"
#include "pin_management.h"

void i2c_init(void) {
    DDRB |= (1 << (SCL_PIN - 8));
    DDRB |= (1 << (SDA_PIN - 8));
    SCL_HIGH(); // active-low
    SDA_HIGH(); // active-low
}

void i2c_start(void) {
    DDRB |= (1 << (SDA_PIN - 8)); // Set SDA as output

    SDA_HIGH(); 
    SCL_HIGH(); //initial conditions

    SDA_LOW(); // start emitted
    
    SCL_LOW();
    SDA_HIGH();
    SCL_HIGH(); // get ready for data transfer
}

void i2c_stop(void) {
    DDRB |= (1 << (SDA_PIN - 8)); // Set SDA as output

    SCL_HIGH(); // initial conditions
     
    SDA_HIGH(); // stop emitted
    
    PULSE();
}

void i2c_send_ack(void) {
    DDRB |= (1 << (SDA_PIN - 8)); // Set SDA as output

    SCL_HIGH(); // ensure clock is initially high
    SDA_LOW();  // pull SDA low to send ACK
    DELAY_SHORT();
    SCL_LOW();  // clock low to prepare for next byte
    DELAY_SHORT();
    SCL_HIGH(); // clock high to complete ACK
}

void i2c_transfer_byte(uint8_t data) {
    DDRB |= (1 << (SDA_PIN - 8)); // Set SDA as output

    SCL_HIGH(); // ensure clock is initially high
    for (int i = 0; i < 8; ++i) {
        if (data & (1 << i)) {
            SDA_HIGH();
        } else {
            SDA_LOW();
        }
        SCL_LOW();
        DELAY_SHORT();
        SCL_HIGH();
        DELAY_SHORT();
    }
}

uint8_t i2c_read_byte(void) { 
    uint8_t data = 0x00;

    for (int i = 0; i < 8; ++i) {
        data |= (read_digital_pin(SDA_PIN) << i);
        PULSE();
    }
    return data;
}

uint8_t i2c_read_ack(void) {
    DDRB &= ~(1 << (SDA_PIN - 8)); // Set SDA as input 
    SCL_HIGH(); // ensure clock is initially high 
    uint8_t data = read_digital_pin(SDA_PIN); 
    PULSE();
    return data;
}