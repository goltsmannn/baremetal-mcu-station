#include <avr/io.h>

.macro PUSH_ALL
    PUSH R0
    PUSH R1
    PUSH R2
    PUSH R3
    PUSH R4
    PUSH R5
    PUSH R6
    PUSH R7
    PUSH R8
    PUSH R9
    PUSH R10
    PUSH R11
    PUSH R12
    PUSH R13
    PUSH R14
    PUSH R15
    PUSH R16
    PUSH R17
    PUSH R18
    PUSH R19
    PUSH R20
    PUSH R21
    PUSH R22
    PUSH R23
    PUSH R24
    PUSH R25
    PUSH R26
    PUSH R27
    PUSH R28
    PUSH R29
    PUSH R30
    PUSH R31
.endmacro



.macro POP_ALL
    POP R31
    POP R30
    POP R29
    POP R28
    POP R27
    POP R26
    POP R25
    POP R24
    POP R23
    POP R22
    POP R21
    POP R20
    POP R19
    POP R18
    POP R17
    POP R16
    POP R15
    POP R14
    POP R13
    POP R12
    POP R11
    POP R10
    POP R9
    POP R8
    POP R7
    POP R6
    POP R5
    POP R4
    POP R3
    POP R2
    POP R1
    POP R0
.endmacro


.global save_task_state

save_task_state:
    PUSH_ALL

    IN   R0, __SREG__
    PUSH R0

    ; save SP into TCB
    ; Z points to tcb[current].sp
    IN   R0, SPL
    ST   Z+, R0
    IN   R0, SPH
    ST   Z, R0

    ; return to scheduler
    RET

.global restore_task_state
restore_task_state:
    LD R0, Z+
    OUT SPL, R0

    LD R0, Z 
    OUT SPH, R0
    
    POP R0 
    OUT __SREG__, R0

    POP_ALL
    RET