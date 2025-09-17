#include "circular_buffer.h"

circular_buffer circ_buf = {
    .buffer = {0},
    .head = 0,
    .tail = 0
};

void add_to_buffer(uint8_t value) {
    circ_buf.buffer[circ_buf.head] = value;
    circ_buf.head = (circ_buf.head + 1) % CIRCULAR_BUFFER_SIZE;

    if (circ_buf.head == circ_buf.tail) {
        circ_buf.tail = (circ_buf.tail + 1) % CIRCULAR_BUFFER_SIZE; 
    }
}

uint8_t read_from_buffer() {
    if (circ_buf.head == circ_buf.tail) {
        return 0; 
    }

    uint8_t value = circ_buf.buffer[circ_buf.tail];
    circ_buf.tail = (circ_buf.tail + 1) % CIRCULAR_BUFFER_SIZE;
    return value;
}
