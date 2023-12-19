#include <math.h>
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

static uint8_t TIME = 0;

// 按教程的首位太亮了，我改成了每次只显示一位，通过定时器中断来刷新显示
void display(uint8_t n) {
    uint8_t we = 0b11111011;

    static uint8_t I = 0;

    P0 = 0xff;
    P2_7 = 1;
    P0 = (we >> I) | 0b11110000;
    P2_7 = 0;

    P0 = 0;
    P2_6 = 1;
    for (uint8_t i = 0; i < I; i += 1) {
        n /= 10;
    }
    P0 = NS[n % 10];
    P2_6 = 0;

    if (I == 2) {
        I = 0;
    } else {
        I += 1;
    }
}

void init_timer0(void) {
    EA = 1;
    ET0 = 1;

    TR0 = 1;
    TMOD |= 0x01; // 8位自动重载

    TH0 = 0xee;
    TL0 = 0xee;
}

void init_uart(void) {
    EA = 1;
    ES = 1;

    // 串口工作方式1,8位UART波特率可变
    SM0 = 0;
    SM1 = 1;

    REN = 1;

    TR1 = 1;
    TMOD |= 0x20; // 8位自动重载

    TH1 = 0xfd; // 9600比特率： 256 - (11.0592 * 1000000 / 9600 / 32 / 12)
    TL1 = 0xfd;
}

void main(void) {
    init_timer0();
    init_uart();

    while (true) {
    }
}

void timer0() __interrupt 1 {
    TH0 = 0xee;
    TL0 = 0xee;

    display(TIME);
}

void uart() __interrupt 4 {
    if (TI) {
        TI = 0;
    }

    if (RI) {
        TIME = SBUF;
        RI = 0;
        SBUF = TIME + 1;
    }
}
