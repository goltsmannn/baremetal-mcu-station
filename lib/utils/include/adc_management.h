#ifndef ADC_MANAGEMENT_H
#define ADC_MANAGEMENT_H
#include "uart.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define ADC_REF_VOLTAGE_AVCC 0x40

void adc_init(uint8_t input_channel);
uint16_t adc_read(void);

#endif // ADC_MANAGEMENT_H