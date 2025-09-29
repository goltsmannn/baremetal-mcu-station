#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "circular_buffer.h"

#define UART_BAUD_RATE 9600
#define CLOCK_FREQUENCY 1000000UL
#define UART_PARITY_ACTIVE 0
#define UART_STOP_BITS_NUMBER 1
#define UART_READ_FAILED 2
#define UART_READ_SUCCESSFUL 3
#define UART_WRITE_FAILED 4
#define UART_WRITE_SUCCESSFUL 5



typedef struct uart_buffer {
    circular_buffer circ_buf;
    volatile uint8_t uart_flag;  
} uart_buffer;

extern uart_buffer RX_BUF;  
extern uart_buffer TX_BUF;

void uart_init();

void uart_send(uint8_t value);

uint8_t uart_read();

void uart_send_string(const char* str);

#endif // UART_H