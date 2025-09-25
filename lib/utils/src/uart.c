#include "uart.h"
#include "display.h"

uart_buffer RX_BUF = {
    .circ_buf = {
        .buffer = {0},
        .head = 0,
        .tail = 0,
        .read_flag = 0
    },
    .uart_flag = UART_READ_FAILED
};

uart_buffer TX_BUF = {
    .circ_buf = {
        .buffer = {0},
        .head = 0,
        .tail = 0,
        .read_flag = 0
    },
    .uart_flag = UART_WRITE_FAILED
};



void uart_init() {
    // Clear U2X bit for normal speed (not double speed)
    UCSR0A &= ~(1 << U2X0);
    
    // Calculate baud rate for normal mode: UBRR = (F_CPU / (16 * BAUD)) - 1
    UBRR0 = (CLOCK_FREQUENCY / (16UL * UART_BAUD_RATE) - 1); // set baud rate registers

    UCSR0C &=  ~(1 << USBS0); // set number of stop bits to 1

    UCSR0C &= ~((1 << UPM01) | (1 << UPM00)); // clear parity (no parity)

    // Set character size to 8 bits explicitly
    UCSR0C &= ~(1 << UCSZ02); // Clear bit 2 (in UCSR0B)
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set 8-bit character size
    UCSR0B &= ~(1 << UCSZ02); // Ensure bit 2 is cleared

    UCSR0B |= (1 << RXEN0);
    UCSR0B |= (1 << TXEN0); // enable receiver and transmitter

    UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0); // enable interrupts

    sei(); // enable global interrupts
}

void uart_send(uint8_t value) {
    // Disable interrupts while modifying shared data
    cli();
    
    add_to_buffer(&TX_BUF.circ_buf, value);
    
    // Enable UDRE interrupt to start transmission if not already enabled
    UCSR0B |= (1 << UDRIE0);
    
    // Re-enable interrupts
    sei();
}

uint8_t uart_read() {
    uint8_t ans = read_from_buffer(&RX_BUF.circ_buf);
    if (RX_BUF.circ_buf.read_flag == CIRCBUF_READ_FAILED) {
        // draw_digit(0);
        RX_BUF.uart_flag = UART_READ_FAILED;
        return 0;
    }
    // draw_digit(1);
    RX_BUF.uart_flag = UART_READ_SUCCESSFUL;
    return ans;
}


ISR(USART_RX_vect) {
    volatile uint8_t RX_BYTE = UDR0;
    add_to_buffer(&RX_BUF.circ_buf, RX_BYTE);
}

ISR(USART_UDRE_vect) {
    volatile uint8_t TX_BYTE;
    TX_BYTE = read_from_buffer(&TX_BUF.circ_buf);
    if (TX_BUF.circ_buf.read_flag == CIRCBUF_READ_SUCCESSFUL) {
        UDR0 = TX_BYTE;  // Send the byte
        TX_BUF.uart_flag = UART_WRITE_SUCCESSFUL;
    } else {
        UCSR0B &= ~(1 << UDRIE0);  // Disable interrupt when buffer empty
        TX_BUF.uart_flag = UART_WRITE_FAILED;
    }
}
