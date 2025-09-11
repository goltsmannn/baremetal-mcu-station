#include "adc_management.h"

void init_adc(uint8_t input_channel, uint8_t reference_voltage) {
    PRR &= ~(1 << PRADC); // disable power reduction mode
    ADMUX = (ADMUX & 0x3F) | (reference_voltage & 0xC0) | (input_channel & 0x0F); // choose ref_voltage and mux the channel
    ADCSRA &= ~(1 << ADSC); // enable adc conversion

    asm volatile (
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
    ); // wait for adc conversion to finish
}

inline uint16_t read_adc(void) {
    return (ADCH << 8) | ADCL;
}
