#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

void int1(void) __interrupt 2 {
    P1 = ~P1;
}

void main(void) {
    EA = 1;
    EX1 = 1;
    IT1 = 1;

    for (int i = 0; i < 10; i += 1) {
        for (int i = 0; i < 10000; i += 1) {
        }

        P3_3 = 1;
        P3_3 = 0;
    }

    while (true) {
    }
}
