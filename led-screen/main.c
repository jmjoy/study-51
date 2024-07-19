#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

#define DI P3_4
#define LE P3_6
#define CLK P3_5

// 跳动的心
static const unsigned char bitmap_bit_bytes[][8] = {
    {
        0b10111101,
        0b00011000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b10000001,
        0b11000011,
        0b11100111,
    },

    {
        0b11111111,
        0b10111101,
        0b00011000,
        0b00000000,
        0b10000001,
        0b11000011,
        0b11100111,
        0b11111111,
    },
};

// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

inline void clk() {
    CLK = 0;
    CLK = 1;
}

inline void le() {
    LE = 0;
    LE = 1;
}

void display(uint8_t col, uint8_t row) {
    LE = 0;

    for (int i = 0; i < 8; i += 1) {
        CLK = 0;
        DI = col & 1; // 获取个位
        CLK = 1;
        col >>= 1;
    }

    for (int i = 0; i < 8; i += 1) {
        CLK = 0;
        DI = row & 1; // 获取个位
        CLK = 1;
        row >>= 1;
    }

    LE = 1;
}

void main() {
    while (true) {
        for (int j = 0; j < 2; j += 1) { // 两个心轮流显示
            for (int z = 0; z < 100; z += 1) { // 每个心显示100次
                uint8_t row = 1;
                for (int i = 0; i < 8; i += 1) { // 逐行扫描显示心
                    display(bitmap_bit_bytes[j][i], row);
                    row <<= 1;
                }
            }
        }
    }
}
