
#include "pin_management.h"
#include "display.h"
#include "i2c.h"
#include "temp_sensor.h"
#include "uart.h"

void init(void) {
    i2c_init();
    uart_init();
    sei();
}

int main(void) {
    init();
    while (1) {
    // drive_digital_pin(9, HIGH);
        // uint16_t a = read_temp_sensor();
    
        uint8_t b = 1;
        uart_send(b);

        // for(int i = 0; i < 10; ++i) {
        //     draw_digit(i);
        //     for (volatile long j = 0; j < 300000; ++j);
        //     reset_digital_pins();
        // }

        b = uart_read();
        if (uart_read_flag == UART_READ_SUCCESSFUL) {
            if (b > 0 && b < 10) {
                draw_digit(b);
            }
        }
        for (volatile long j = 0; j < 300000; ++j);
    }

    return 0;
}