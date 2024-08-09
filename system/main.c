#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

static uint8_t STACK_TASK[32];

void task0(void) {
    P1_0 = !P1_0;
}

void switch_task(void) {
    STACK_TASK[0] = (uint8_t) (uintptr_t) task0;
    STACK_TASK[1] = (uint8_t) (((uintptr_t) task0) >> 8);
    SP = STACK_TASK[0];
}

void main(void) {
    switch_task();
}
