#include <mcs51/8051.h>
#include <stdint.h>

#define WELA P2_7
#define DULA P2_6

#define crol(x, n) (((x) << (n)) | ((x) >> (8*sizeof(x) - (n))))

void delay(void) {
    for (uint16_t i = 0; i < 65535; i += 1) {
    }
}

//                   hgfedcba
const uint8_t N0 = 0b00111111;
const uint8_t N1 = 0b00000110;
const uint8_t N2 = 0b01011011;
const uint8_t N3 = 0b01001111;
const uint8_t N4 = 0b01100110;
const uint8_t N5 = 0b01101101;
const uint8_t N6 = 0b01111101;
const uint8_t N7 = 0b00000111;
const uint8_t N8 = 0b01111111;
const uint8_t N9 = 0b01101111;

void main(void) {
    uint8_t NS[10] = { N0, N1, N2, N3, N4, N5, N6, N7, N8, N9 };

    uint8_t we_tmp = 0b11111110;
    int du_idx = 0;

    while (1) {
        WELA = 1;
        P0 = we_tmp;
        we_tmp = crol(we_tmp, 1);
        WELA = 0;

        DULA = 1;
        P0 = NS[du_idx];
        if (du_idx == 9) {
            du_idx = 0;
        } else {
            du_idx += 1;
        }
        DULA = 0;

        delay();
    }
}
