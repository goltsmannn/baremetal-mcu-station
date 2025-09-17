#include "uart.h"

void uart_init() {
    UBRR0 = (CLOCK_FREQUENCY / (16 * UART_BAUD_RATE) - 1); // set baud rate registers

    UCSR0C &=  ~(1 << USBS0); // set number of stop bits to 1

    UCSR0C &= ~((1 << UPM01) | (1 << UPM00)); // clear parity
    UCSR0C |= (1 << UPM01);                   // set even parity

    UCSR0B |= (1 << RXEN0);
    UCSR0B |= (1 << TXEN0); // enable receiver and transmitter
    
    // leave char.size default (8 bits)
}