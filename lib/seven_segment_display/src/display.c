#include "display.h"
#include "pin_management.h"


extern const uint16_t display_mappings[] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // 0
    SEG_B | SEG_C,                                 // 1
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,         // 2
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,         // 3
    SEG_B | SEG_C | SEG_F | SEG_G,                 // 4
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,         // 5
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 6
    SEG_A | SEG_B | SEG_C,                         // 7
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 8
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G  // 9
};

void draw_digit(uint8_t digit) {
    if (digit < 0 || digit > 9) {
        return;
    }
    drive_pins_from_bitstr(display_mappings[digit]);
}