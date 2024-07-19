#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 毫秒级延时函数定义
void delay(uint16_t z) {
    for (uint16_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

void init_uart(void) {
    EA = 1;
    // ES = 1;

    // 串口工作方式1,8位UART波特率可变
    SM0 = 0;
    SM1 = 1;

    // REN = 1;

    TR1 = 1;
    TMOD |= 0x20; // 8位自动重载

    TH1 = 0xfd; // 9600比特率： 256 - (11.0592 * 1000000 / 9600 / 32 / 12)
    TL1 = 0xfd;
}

int putchar(int c) {
    while (!TI) {}
    TI = 0;
    SBUF = (char) c;
    return 1;
}

void main(void) {
    init_uart();

    while (true) {
        TI = 1;
        printf("我在学习单片机！\n");
        TI = 1;
        printf("I am studying MCU！\n");
        delay(1000);
    }
}
