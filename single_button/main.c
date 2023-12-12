#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

#define WELA P2_7
#define DULA P2_6

#define crol(x, n) (((x) << (n)) | ((x) >> (8 * sizeof(x) - (n))))

// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
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
    int indexes[4] = {0, 0, 0, 0};
    bool flags[4] = {false, false, false, false};

    while (true) {
        for (int i = 0; i < 4; i += 1) {
            // 没想到更好的思路
            bool p;
            if (i == 0) {
                p = P3_0 == 0;
            } else if (i == 1) {
                p = P3_1 == 0;
            } else if (i == 2) {
                p = P3_2 == 0;
            } else if (i == 3) {
                p = P3_3 == 0;
            } else {
                p = P3_4 == 0;
            }

            if (p && !flags[i]) {
                flags[i] = true;

                if (indexes[i] == 9) {
                    indexes[i] = 0;
                } else {
                    indexes[i] += 1;
                }

                P1 = 0;
                P2_3 = 0;
                delay(100);
                P1 = 0xff;
                P2_3 = 1;
            }

            if (!p) {
                flags[i] = false;
            }
        }

        for (int i = 0; i < 4; i += 1) {
            P0 = 0xff; // 这里不知道为啥要重置，叫做清除断码
            P2_7 = 1;
            P0 = WES[i];
            P2_7 = 0;

            P0 = 0;
            P2_6 = 1;
            P0 = NS[indexes[i]];
            P2_6 = 0;

            delay(5);
        }
    }
}
