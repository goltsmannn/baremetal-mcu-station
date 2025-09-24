#ifndef RTOS_H
#define RTOS_H
#include "shared_types.h"

#define GREATER_PRIORITY_TASK_AVAILABLE 1
#define GREATER_PRIORITY_TASK_NOT_AVAILABLE 0

extern uint8_t current_task_id; 
extern uint8_t priority_bitmask;
extern TCB tasks[];

void save_task_state(TCB *task) __asm__("save_task_state");
void restore_task_state(TCB *task) __asm__("restore_task_state");

inline uint8_t next_task_available() {
    if ((1 << tasks[current_task_id].priority) < priority_bitmask) {
        return GREATER_PRIORITY_TASK_AVAILABLE;
    }
    return GREATER_PRIORITY_TASK_NOT_AVAILABLE;
}

void schedule_next_task(uint8_t next_task_id);

#endif // RTOS_H