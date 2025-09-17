#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/io.h>

#define UART_BAUD_RATE 115200
#define CLOCK_FREQUENCY 16000000UL
#define UART_PARITY_ACTIVE 0
#define UART_STOP_BITS_NUMBER 1


void uart_init();
#endif // UART_H