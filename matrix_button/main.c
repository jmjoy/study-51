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

int disKey = 0;

void display(int key) {
    int bits[2] = {key / 10, key % 10};

    for (int i = 0; i < 2; i += 1) {
        P0 = 0xff;
        P2_7 = 1;
        P0 = WES[i];
        P2_7 = 0;

        P0 = 0;
        P2_6 = 1;
        P0 = NS[bits[i]];
        P2_6 = 0;

        delay(5);
    }
}

int press_key() {
    int key = 0;

    P3 = 0b11110000;
    if (P3 != 0b11110000) {
        delay(20);
        // 防止抖动
        if (P3 != 0b11110000) {
            switch (P3) {
            case 0b11100000:
                key = 1;
                break;
            case 0b11010000:
                key = 2;
                break;
            case 0b10110000:
                key = 3;
                break;
            case 0b01110000:
                key = 4;
                break;
            }

            P3 = 0b00001111;
            switch (P3) {
            case 0b00001110:
                key = key + 0;
                break;
            case 0b00001101:
                key = key + 4;
                break;
            case 0b00001011:
                key = key + 8;
                break;
            case 0b00000111:
                key = key + 12;
                break;
            }

            while (P3 != 0b00001111) {
                P2_3 = 0;
            }
            P2_3 = 1;
        }
    } else {
        P3 = 0xff;
        if (P3 != 0xff) {
            delay(20);
            // 防止抖动
            if (P3 != 0xff) {
                switch (P3) {
                case 0b11111110:
                    key = 17;
                    break;
                case 0b11111101:
                    key = 18;
                    break;
                case 0b11111011:
                    key = 19;
                    break;
                case 0b11110111:
                    key = 20;
                    break;
                }

                while (P3 != 0xff) {
                    P2_3 = 0;
                }
                P2_3 = 1;
            }
        }
    }

    return key;
}

void main(void) {
    while (true) {
        int key = press_key();
        if (key) {
            disKey = key;
        }
        display(disKey);
    }
}
