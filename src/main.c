
#include "pin_management.h"
#include "display.h"
#include "i2c.h"
#include "temp_sensor.h"
#include "uart.h"
#include "adc_management.h"
#include "timer.h"


#include <avr/sleep.h>
#include <util/delay.h>


void init(void) {
    sei();
    i2c_init();
    uart_init();
    adc_init(3); // Initialize ADC on channel 5 (PC5)
    timer0_init();
}

int main(void) {
    init();
    
    // send_string("UART Test - Interrupt\r\n");
    
    volatile char counter = '0';

    // set_sleep_mode(SLEEP_MODE_IDLE); // Set Idle mode
    // sleep_enable();

    while (1) {
        // _delay_ms(1000); // Simple delay
        // uint8_t val = ADCSRA & (1 << ADSC); // Start ADC conversion
        // uart_send(val ? '1' : '0');
        // _delay_ms(1000);
        // sleep_cpu(); // MCU sleeps until an interrupt occurs

        // Main loop can be empty; all work is done in ISRs
       
    }
    // while (1) {
    //     // Send current counter value
    //     uart_send(counter);
    //     _delay_ms(1000);
        
    //     // volatile char received = uart_read();

    //     // if (RX_BUF.uart_flag == UART_READ_SUCCESSFUL) {
    //     //     received = uart_read();
    //     // }

    //     if (circbuf_available(&RX_BUF.circ_buf)) {
    //         draw_digit(0); // Indicate data available
    //         volatile char received = uart_read();
    //         if (received >= '0' && received <= '9') {
    //             draw_digit(received - '0');
    //         }
    //     }
        
    //     // Increment counter (cycle through 0-9)
    //     counter++;
    //     if (counter > '9') {
    //         counter = '0';
    //     }
        
    //     _delay_ms(1000);
    // }

    return 0;
}