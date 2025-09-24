#include "rtos.h"

void schedule_next_task(uint8_t next_task_id) {
    save_task_state(&TCB[current_task_id]);
    
}