#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#define TASK_STACK_SIZE 64
#include <stdint.h>

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED,
    TASK_DELETED
} TaskState;


typedef struct {
    uint16_t stack_ptr; // LEAVE IT FIRST HERE REQUIRED FOR ASSEMBLY

    void* function_ptr;
    TaskState state;
    uint8_t priority;
} TCB;



#endif // SHARED_TYPES_H