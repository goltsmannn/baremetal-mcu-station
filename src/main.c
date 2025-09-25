
#include "pin_management.h"
#include "display.h"
#include "i2c.h"
#include "temp_sensor.h"
#include "uart.h"
#include <util/delay.h>


void send_string(const char* str) {
    while (*str) {
        uart_send(*str);
        str++;
    }
}

void init(void) {
    i2c_init();
    uart_init();
}

int main(void) {
    init();
    
    // send_string("UART Test - Interrupt\r\n");
    
    volatile char counter = '0';
    
    while (1) {
        // Send current counter value
        uart_send(counter);
        _delay_ms(1000);
        
        // volatile char received = uart_read();

        // if (RX_BUF.uart_flag == UART_READ_SUCCESSFUL) {
        //     received = uart_read();
        // }

        if (circbuf_available(&RX_BUF.circ_buf)) {
            draw_digit(0); // Indicate data available
            volatile char received = uart_read();
            if (received >= '0' && received <= '9') {
                draw_digit(received - '0');
            }
        }
        
        // Increment counter (cycle through 0-9)
        counter++;
        if (counter > '9') {
            counter = '0';
        }
        
        _delay_ms(1000);
    }

    return 0;
}