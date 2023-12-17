#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

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

const uint8_t NS[10] = {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};

#define cror(x, n) (((x) >> (n)) | ((x) << (8 * sizeof(x) - (n))))

void display(uint8_t n) {
    uint8_t we = 0b11111011;
    for (uint8_t i = 0; i < 3; i += 1) {
        P0 = 0xff;
        P2_7 = 1;
        P0 = we;
        P2_7 = 0;
        we = cror(we, 1);

        P0 = 0;
        P2_6 = 1;
        P0 = NS[n % 10];
        P2_6 = 0;
        n /= 10;

        // for (uint16_t i = 0; i < 10; i += 1) {}
    }
}

void init_timer0(void) {
    TR0 = 1;
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
}

void init_counter1(void) {
    TR1 = 1;
    TMOD |= 0x50;
    TH1 = 0;
    TL1 = 0;
}

void main(void) {
    init_timer0();
    init_counter1();

    uint16_t i = 0;
    while (true) {
        if (TF0 == 1) {
            TF0 = 0;
            TH0 = 0xFC;
            TL0 = 0x18;
            i += 1;
        }
        if (i >= 1000) {
            i = 0;
            P3_5 = 1;
            P3_5 = 0;
        }

        display(TH1 << 8 | TL1);
    }
}
