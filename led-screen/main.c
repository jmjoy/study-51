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
        0b00000000#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

// 定义显示数据的输入引脚
#define DI P3_4
// 定义锁存器使能引脚
#define LE P3_6
// 定义时钟引脚
#define CLK P3_5

// 心形图案的位图数据，二维数组存储每一行的二进制数据
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

// 毫秒级延时函数，用于控制显示刷新速率
// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

// 发送时钟脉冲的函数，用于同步数据传输
inline void clk() {
    CLK = 0;
    CLK = 1;
}

// 触发锁存器使能的函数，用于将数据锁存到显示设备
inline void le() {
    LE = 0;
    LE = 1;
}

// 在LED显示设备上显示指定行列数据的函数
// col: 要显示的列数#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

// 定义显示数据的输入引脚
#define DI P3_4
// 定义锁存器使能引脚
#define LE P3_6
// 定义时钟引脚
#define CLK P3_5

// 心形图案的位图数据，二维数组存储每一行的二进制数据
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

// 毫秒级延时函数，用于控制显示刷新速率
// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

// 发送时钟脉冲的函数，用于同步数据传输
inline void clk() {
    CLK = 0;
    CLK = 1;
}

// 触发锁存器使能的函数，用于将数据锁存到显示设备
inline void le() {
    LE = 0;
    LE = 1;
}

// 在LED显示设备上显示指定行列数据的函数
// col: 要显示的列数据
// row: 要显示的行数据
void display(uint8_t col, uint8_t row) {
    LE = 0; // 先关闭锁存器使能

    // 逐位发送列数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0; // 时钟脉冲的低电平周期
        DI = col & 1; // 获取最低位数据
        CLK = 1; // 时钟脉冲的高电平周期
        col >>= 1; // 移位准备下一位数据
    }

    // 逐位发送行数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0;
        DI = row & 1;
        CLK = 1;
        row >>= 1;
    }

    LE = 1; // 打开锁存器使能，完成数据传输
}

// 主函数，程序的入口点
void main() {
    while (true) {
        // 循环显示两个心形图案
        for (int j = 0; j < 2; j += 1) { // 两个心轮流显示
            for (int z = 0; z < 100; z += 1) { // 每个心显示100次
                uint8_t row = 1;
                // 逐行扫描显示心形图案
                for (int i = 0; i < 8; i += 1) { // 逐行扫描显示心
                    display(bitmap_bit_bytes[j][i], row);
                    row <<= 1; // 下一行数据
                }
            }
        }
    }
}据// 心形图案的位图数据，二维数组存储每一行的二进制数据

// row: 要显示的行数据
void display(uint8_t col, uint8_t row) {
    LE = 0; // 先关闭锁存器使能

    // 逐位发送列数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0; // 时钟脉冲的低电平周期
        DI = col & 1; // 获取最低位数据
        CLK = 1; // 时钟脉冲的高电平周期
        col >>= 1; // 移位准备下一位数据
    }

    // 逐位发送行数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0;
        DI = row & 1;
        CLK = 1;
        row >>= 1;
    }

    LE = 1; // 打开锁存器使能，完成数据传输
}

// 主函数，程序的入口点
void main() {
    while (true) {
        // 循环显示两个心形图案
        for (int j = 0; j < 2; j += 1) { // 两个心轮流显示
            for (int z = 0; z < 100; z += 1) { // 每个心显示100次
                uint8_t row = 1;
                // 逐行扫描显示心形图案
                for (int i = 0; i < 8; i += 1) { // 逐行扫描显示心
                    display(bitmap_bit_bytes[j][i], row);
                    row <<= 1; // 下一行数据
                }
            }
        }
    }
},
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
 #include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

// 定义显示数据的输入引脚
#define DI P3_4
// 定义锁存器使能引脚
#define LE P3_6
// 定义时钟引脚
#define CLK P3_5

// 心形图案的位图数据，二维数组存储每一行的二进制数据
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

// 毫秒级延时函数，用于控制显示刷新速率
// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

// 发送时钟脉冲的函数，用于同步数据传输
inline void clk() {
    CLK = 0;
    CLK = 1;
}

// 触发锁存器使能的函数，用于将数据锁存到显示设备
inline void le() {
    LE = 0;
    LE = 1;
}

// 在LED显示设备上显示指定行列数据的函数
// col: 要显示的列数据
// row: 要显示的行数据
void display(uint8_t col, uint8_t row) {
    LE = 0; // 先关闭锁存器使能

    // 逐位发送列数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0; // 时钟脉冲的低电平周期
        DI = col & 1; // 获取最低位数据
        CLK = 1; // 时钟脉冲的高电平周期
        col >>= 1; // 移位准备下一位数据
    }

    // 逐位发送行数据
    for (int i = 0; i < 8; i += 1) {
        CLK = 0;
        DI = row & 1;
        CLK = 1;
        row >>= 1;
    }

    LE = 1; // 打开锁存器使能，完成数据传输
}

// 主函数，程序的入口点
void main() {
    while (true) {
        // 循环显示两个心形图案
        for (int j = 0; j < 2; j += 1) { // 两个心轮流显示
            for (int z = 0; z < 100; z += 1) { // 每个心显示100次
                uint8_t row = 1;
                // 逐行扫描显示心形图案
                for (int i = 0; i < 8; i += 1) { // 逐行扫描显示心
                    display(bitmap_bit_bytes[j][i], row);
                    row <<= 1; // 下一行数据
                }
            }
        }
    }
}        for (int j = 0; j < 2; j += 1) { // 两个心轮流显示
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
