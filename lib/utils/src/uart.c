#include "uart.h"

volatile uint8_t uart_read_flag;
volatile uint8_t uart_write_flag;

extern circular_buffer RX_BUF;  
extern circular_buffer TX_BUF;


void uart_init() {
    UBRR0 = (CLOCK_FREQUENCY / (16 * UART_BAUD_RATE) - 1); // set baud rate registers

    UCSR0C &=  ~(1 << USBS0); // set number of stop bits to 1

    UCSR0C &= ~((1 << UPM01) | (1 << UPM00)); // clear parity
    UCSR0C |= (1 << UPM01);                   // set even parity

    UCSR0B |= (1 << RXEN0);
    UCSR0B |= (1 << TXEN0); // enable receiver and transmitter

    UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0); // enable interrupts

    // leave char.size default (8 bits)

    sei(); // enable global interrupts
}

void uart_send(uint8_t value) {
    add_to_buffer(&TX_BUF, value);
    UCSR0B |= (1 << UDRIE0);  // Enable UDRE interrupt to start transmission
}

uint8_t uart_read() {
    uint8_t ans = read_from_buffer(&RX_BUF);
    if (circbuf_read_flag == CIRCBUF_READ_FAILED) {
        uart_read_flag = UART_READ_FAILED;
        return 0;
    }
    uart_read_flag = UART_READ_SUCCESSFUL;
    return ans;
}

ISR(USART_RX_vect) {
    volatile uint8_t RX_BYTE = UDR0;
    add_to_buffer(&RX_BUF, RX_BYTE);
}

ISR(USART_UDRE_vect) {
    volatile uint8_t TX_BYTE;
    TX_BYTE = read_from_buffer(&TX_BUF);
    if (circbuf_read_flag == CIRCBUF_READ_SUCCESSFUL) {
        UDR0 = TX_BYTE;  // Send the byte
        uart_write_flag = UART_WRITE_SUCCESSFUL;
    } else {
        UCSR0B &= ~(1 << UDRIE0);  // Disable interrupt when buffer empty
        uart_write_flag = UART_WRITE_FAILED;
    }
}
