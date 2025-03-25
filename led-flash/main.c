#include <mcs51/8051.h>

void main(void) {
    unsigned short i;

    while (1) {
        P1 = 0;
        i = 65535;
        while (i--);
        P1 = 1;
        i = 65535;
        while (i--);
    }

    // i = 65535;
    // while (i--);

    // P1 = 0xff;

    // i = 65535;
    // while (i--);

    // P1 = 0b11101001;
}
