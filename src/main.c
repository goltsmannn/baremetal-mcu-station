
#include "pin_management.h"
#include "display.h"
#include "i2c.h"
#include "temp_sensor.h"

int main(void) {
    i2c_init(); 

    
    while (1) {
    // drive_digital_pin(9, HIGH);
        uint16_t a = read_temp_sensor();
        for(int i = 0; i < 10; ++i) {
            draw_digit(i);
            for (volatile long j = 0; j < 300000; ++j);
            reset_digital_pins();
        }
    }

    return 0;
}