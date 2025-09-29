#include "timer.h"

void timer0_init(void) {

    TCCR0A = 0; // Normal mode

    TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler = 1024

    TIMSK0 |= (1 << TOIE0); // Enable Timer0 overflow interrupt
} 

ISR(TIMER0_OVF_vect) {
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    // TIFR0 |= (1 << TOV0); // Clear Timer0 overflow flag
}