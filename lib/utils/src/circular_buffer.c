#include "circular_buffer.h"

circular_buffer RX_BUF = {
    .buffer = {0},
    .head = 0,
    .tail = 0
};

circular_buffer TX_BUF = {
    .buffer = {0},
    .head = 0,
    .tail = 0
};

volatile uint8_t circbuf_read_flag;

void add_to_buffer(circular_buffer* circ_buf, uint8_t value) {
    circ_buf->buffer[circ_buf->head] = value;
    circ_buf->head = (circ_buf->head + 1) % CIRCULAR_BUFFER_SIZE;

    if (circ_buf->head == circ_buf->tail) {
        circ_buf->tail = (circ_buf->tail + 1) % CIRCULAR_BUFFER_SIZE; 
    }
}

uint8_t read_from_buffer(circular_buffer* circ_buf) {
    if (circ_buf->head == circ_buf->tail) {
        circbuf_read_flag = CIRCBUF_READ_FAILED;
        return 0; 
    }

    circbuf_read_flag = CIRCBUF_READ_SUCCESSFUL;
    uint8_t value = circ_buf->buffer[circ_buf->tail];
    circ_buf->tail = (circ_buf->tail + 1) % CIRCULAR_BUFFER_SIZE;
    return value;
}
