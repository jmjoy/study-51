#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

__sbit __at (0XEC) P4_4;

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

const uint8_t SMG_DUAN[10] = {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};

const uint8_t SMG_WEI[4] = {0b11111110, 0b11111101, 0b11111011, 0b11110111};

static uint16_t NUM = 0;

static uint8_t STEP = 0;

// 按教程的首位太亮了，我改成了每次只显示一位，通过定时器中断来刷新显示
// num取值0～9999
void display(uint16_t num) {
    static uint8_t wei;

    uint8_t q, b, s, g;

    q = num / 1000;
    b = num % 1000 / 100;
    s = num % 100 / 10;
    g = num % 10;

    P0 = 0xff;
    P2_7 = 1; // 打开位选锁存器
    P0 = SMG_WEI[wei];
    P2_7 = 0; // 锁存位选数据

    P0 = 0;
    P2_6 = 1;
    switch (wei) {
    case 0:
        P0 = SMG_DUAN[q] | 0x80; // 0x80加上小数点
        break;
    case 1:
        P0 = SMG_DUAN[b];
        break;
    case 2:
        P0 = SMG_DUAN[s];
        break;
    case 3:
        P0 = SMG_DUAN[g];
        break;
    }
    P2_6 = 0;

    wei++;
    if (wei == 4)
        wei = 0;
}

void init_timer0(void) {
    EA = 1;
    ET0 = 1;

    TR0 = 1;
    TMOD |= 0x02;

    TH0 = 0x00;
    TL0 = 0x00;
}

void init_timer1(void) {
    EA = 1;
    ET1 = 1;

    TR1 = 1;
    TMOD |= 0x20;

    TH1 = 220;
    TL1 = 220;
}

// 毫秒级延时函数定义
void delay(uint16_t z) {
    for (uint16_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

#define CS P3_7
#define DCLK P2_1
#define DIN P2_0
#define DOUT P2_5

void xpt2046_write(uint8_t cmd) {
    for (uint8_t i = 0; i < 8; i += 1) {
        DCLK = 0;

        if (cmd & 0x80) {
            DIN = 1;
        } else {
            DIN = 0;
        }

        DCLK = 1;

        cmd <<= 1;
    }
}

uint8_t xpt2046_read() {
    uint8_t num = 0;

    for (uint8_t i = 0; i < 8; i += 1) {
        num <<= 1;

        DCLK = 1;
        DCLK = 0;

        if (DOUT) {
            num += 1;
        }
    }

    return num;
}

void main(void) {
    init_timer0();
    init_timer1();

    while (true) {
        CS = 0;

        xpt2046_write(0b10011100);

        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");

        uint8_t num = xpt2046_read();
        NUM = 5000 * num / 256;

        CS = 1;

        delay(500);
    }
}

void timer0() __interrupt 1 {
    display(NUM);
}

const uint8_t DAC_VAL = 169;

void timer1() __interrupt 3 {
    STEP += 1;
    if (STEP <= DAC_VAL) {
        P4_4 = 1;
    } else {
        P4_4 = 0;
    }
}
