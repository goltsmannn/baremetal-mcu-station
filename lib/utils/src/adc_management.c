#include "adc_management.h"

void adc_init(uint8_t input_channel) {
    PRR &= ~(1 << PRADC); // disable power reduction mode
    ADMUX = (ADMUX & 0x3F) | ADC_REF_VOLTAGE_AVCC | (input_channel & 0x0F); // mux the channel
    ADCSRA |= (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADPS2); // enable adc interrupts and set prescaler = 64
    ADCSRA |= (1 << ADEN); // Enable ADC
    // asm volatile (
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    //     "nop\n\t"
    // ); // wait for adc conversion to finish
}

uint16_t adc_read(void) {
    volatile uint16_t value = (ADCH << 8) | ADCL;
    // char buffer[6]; // Enough for max 65535 + null terminator
    // itoa(value, buffer, 10); // Convert uint16_t to string
    char buffer[6]= {'a', 'b', 'c', 'd', 'e', '\0'};
    uart_send_string(buffer);
    return value;
}

ISR(ADC_vect) {
    adc_read();
}