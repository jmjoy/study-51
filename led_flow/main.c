#include <mcs51/8051.h>

typedef unsigned short ushort;
typedef unsigned char uchar;

#define crol(x, n) (((x) << (n)) | ((x) >> (8*sizeof(x) - (n))))

void delay(void) {
    for (ushort i = 0; i < 65535; i += 1) {
    }
}

void main(void) {
    uchar tmp = 0b11111111;
    while (1) {
        P1 = tmp;
        delay();
        tmp = crol(tmp, 1);
        tmp = (tmp << 1) | (tmp >> 7);

        if (tmp == 0b01111111) {
            break;
        }

        // __asm__("cjne	%0,#0x7f,00104$"
        //        : "=r"(&tmp));

        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
    }
}
