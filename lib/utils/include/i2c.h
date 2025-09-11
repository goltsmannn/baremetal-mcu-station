#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <avr/io.h>

#define SCL_PIN 12
#define SDA_PIN 13
#define TARGET_ADDRESS 0b1001000 // AD0 to GROUND
#define TARGET_READ (TARGET_ADDRESS << 1) | 1 // w is active-low
#define TARGET_WRITE (TARGET_ADDRESS << 1) | 0


#define SCL_HIGH() PORTB |= (1 << (SCL_PIN - 8))
#define SCL_LOW() PORTB &= ~(1 << (SCL_PIN - 8))
#define SDA_HIGH() PORTB |= (1 << (SDA_PIN - 8))
#define SDA_LOW() PORTB &= ~(1 << (SDA_PIN - 8)) 
#define DELAY_SHORT() for (volatile int i = 0; i < 50; ++i) {}
#define PULSE() SCL_LOW(); DELAY_SHORT(); SCL_HIGH(); DELAY_SHORT();


void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_send_ack(void);
uint8_t i2c_read_ack(void);
void i2c_transfer_byte(uint8_t data);
uint8_t i2c_read_byte(void);

#endif // I2C_H