
#include "pin_management.h"
#include "display.h"

int main(void) {
    while (1) {
    // drive_digital_pin(9, HIGH);
        for(int i = 0; i < 10; ++i) {
            draw_digit(i);
            for (volatile long j = 0; j < 300000; ++j);
            reset_digital_pins();

        }
    }

    return 0;
}