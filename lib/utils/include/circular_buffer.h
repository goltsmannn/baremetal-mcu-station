#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#define CIRCULAR_BUFFER_SIZE 16
#define CIRCBUF_READ_SUCCESSFUL 1
#define CIRCBUF_READ_FAILED 0


typedef struct {
    uint8_t buffer[CIRCULAR_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    volatile uint8_t read_flag;
} circular_buffer;


void add_to_buffer(circular_buffer* circ_buf, uint8_t value);
uint8_t read_from_buffer(circular_buffer* circ_buf);
uint8_t circbuf_available(circular_buffer* circ_buf);  // Returns 1 if data available, 0 if empty



#endif // CIRCULAR_BUFFER_H