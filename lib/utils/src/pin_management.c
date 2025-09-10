#include "pin_management.h"

void drive_pins_from_bitstr(uint16_t pins_data) { // driving pins from binary string
    for (int pin_number = 0; pin_number < 16; ++pin_number) {
        if (pins_data & (1 << pin_number)) {
            drive_digital_pin(pin_number, HIGH);
        }
    }
}

void drive_digital_pin(uint16_t pin_number, uint8_t value) {
    if (pin_number >= 8 && pin_number <= 13) {
        DDRB |= (1 << (pin_number - 8));
        if (value)
            PORTB |= (1 << (pin_number - 8));
        else
            PORTB &= ~(1 << (pin_number - 8));
    } else if (pin_number <= 7) {
        DDRD |= (1 << pin_number);
        if (value)
            PORTD |= (1 << pin_number);
        else
            PORTD &= ~(1 << pin_number);
    }
}

inline void reset_digital_pins() {
    PORTD = 0x00;
    PORTB = 0x00;
}