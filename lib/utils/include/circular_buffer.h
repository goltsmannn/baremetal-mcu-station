#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#define CIRCULAR_BUFFER_SIZE 16


typedef struct {
    uint8_t buffer[16];
    uint8_t head;
    uint8_t tail;
} circular_buffer;

extern circular_buffer circ_buf;

void add_to_buffer(uint8_t value);
uint8_t read_from_buffer();



#endif // CIRCULAR_BUFFER_H