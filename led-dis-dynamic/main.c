#include <mcs51/8051.h>
#include <stdint.h>

/**
 * 数码管位选
 */
#define WELA P2_7

/**
 * 数码管段选
 */
#define DULA P2_6

#define crol(x, n) (((x) << (n)) | ((x) >> (8 * sizeof(x) - (n))))

void delay(void) {
    for (uint16_t i = 0; i < 65; i += 1) {
    }
}

//           hgfedcba
#define N0 0b00111111
#define N1 0b00000110
#define N2 0b01011011
#define N3 0b01001111
#define N4 0b01100110
#define N5 0b01101101
#define N6 0b01111101
#define N7 0b00000111
#define N8 0b01111111
#define N9 0b01101111

const uint8_t WES[8] = {0b11111110, 0b11111101, 0b11111011, 0b11110111,
                        0b11101111, 0b11011111, 0b10111111, 0b01111111};
const uint8_t NS[10] = {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};

void main(void) {
    // P1 = 0;
    while (1) {
        for (int i = 0; i < 8; i += 1) {
            P0 = 0xff;
            WELA = 1;
            // P0 = crol(0b11111110, i);
            P0 = WES[i];
            WELA = 0;

            DULA = 1;
            P0 = NS[i + 1];
            DULA = 0;

            P0 = 0xff;

            delay();
        }
    }
}
