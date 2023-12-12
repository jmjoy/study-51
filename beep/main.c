#include <mcs51/8051.h>

typedef unsigned short ushort;
typedef unsigned char uchar;

#define crol(x, n) (((x) << (n)) | ((x) >> (8*sizeof(x) - (n))))

void delay(void) {
    for (ushort i = 0; i < 65535; i += 1) {
    }
}

void main(void) {
    // uchar tmp = 0b11111000;
    // P2_3 = 1;

    while (1) {
        P2_3 = !P2_3;
        delay();

        // P1 = tmp;
        // tmp = crol(tmp, 1);
    }
}
