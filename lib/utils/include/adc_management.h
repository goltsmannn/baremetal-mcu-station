#ifndef ADC_MANAGEMENT_H
#define ADC_MANAGEMENT_H

#include <stdint.h>
#include <avr/io.h>

void init_adc(uint8_t input_channel, uint8_t reference_voltage);
uint16_t read_adc(void);

#endif // ADC_MANAGEMENT_H