#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define SEG_A (1 << 4)
#define SEG_B (1 << 5)
#define SEG_C (1 << 9)
#define SEG_D (1 << 7)
#define SEG_E (1 << 6) // ?
#define SEG_F (1 << 3)
#define SEG_G (1 << 2)
#define SEG_DP (1 << 8)

extern const uint16_t display_mappings[];

void draw_digit(uint8_t digit);

#endif // DISPLAY_H