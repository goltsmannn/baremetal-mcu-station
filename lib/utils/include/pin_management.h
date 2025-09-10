#ifndef PIN_MANAGEMENT_H
#define PIN_MANAGEMENT_H

#include <stdint.h>
#include <avr/io.h>

#define NUM_DIGITAL_PINS 14 
#define HIGH 1
#define LOW 0

void drive_pins_from_bitstr(uint16_t pins_data);
void drive_digital_pin(uint16_t pin_number, uint8_t value);
void reset_digital_pins();

#endif // PIN_MANAGEMENT_H