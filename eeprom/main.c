#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    TMOD |= 0x01;

    TH0 = 0xee;
    TL0 = 0xee;
}

#define SCL P2_1
#define SDA P2_0

void delay5us() {
    __asm__("nop");
}

// 毫秒级延时函数定义
void delay(uint16_t z) {
    for (uint16_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

const uint8_t AT24C02_ADDR = 0b10100000;
const uint8_t I2C_READ = 1;
const uint8_t I2C_WRITE = 0;

void i2c_start() {
    SCL = 1;
    SDA = 1;
    delay5us();
    SDA = 0;
    delay5us();
    SCL = 0;
    SDA = 1;
}

void i2c_stop() {
    SCL = 0;
    SDA = 0;
    SCL = 1;
    delay5us();
    SDA = 1;
    delay5us();
    SDA = 0;
}

void i2c_write_ack(bool b) {
    SCL = 0;
    if (b) {
        SDA = 0;
    } else {
        SDA = 1;
    }
    SCL = 1;
    delay5us();
    SCL = 0;
    SDA = 1;
}

bool i2c_read_ack() {
    SCL = 0;
    SCL = 1;
    delay5us();
    if (SDA) {
        SCL = 0;
        return false;
    } else {
        SCL = 0;
        return true;
    }
}

void i2c_write_byte(uint8_t num) {
    for (uint8_t i = 0; i < 8; i += 1) {
        SCL = 0;
        if (num & 0x80) {
            SDA = 1;
        } else {
            SDA = 0;
        }
        SCL = 1;
        num <<= 1;
    }

    SCL = 0;
    SDA = 1;
}

uint8_t i2c_read_byte() {
    uint8_t num = 0;

    for (uint8_t i = 0; i < 8; i += 1) {
        num <<= 1;

        SCL = 0;
        SCL = 1;

        if (SDA) {
            num |= 1;
        }
    }

    return num;
}

void main(void) {
    init_timer0();

    EA = 0;

    bool success = true;

    const uint8_t ADDR = 100;

    // 写入
    i2c_start();
    i2c_write_byte(AT24C02_ADDR + I2C_WRITE);
    success &= i2c_read_ack();
    i2c_write_byte(ADDR); // 地址
    success &= i2c_read_ack();
    i2c_write_byte(123); // 数据
    success &= i2c_read_ack();
    i2c_stop();

    // 写入之后需要给时间EEPROM时间整理
    delay(100);

    // 写入
    i2c_start();
    i2c_write_byte(AT24C02_ADDR + I2C_WRITE);
    success &= i2c_read_ack();
    i2c_write_byte(ADDR); // 地址
    success &= i2c_read_ack();
    i2c_start();
    i2c_write_byte(AT24C02_ADDR + I2C_READ);
    success &= i2c_read_ack();
    TIME = i2c_read_byte();
    i2c_write_ack(true);
    i2c_stop();

    EA = 1;

    // 如果未应答则LED全亮
    P1 = success ? 0xff : 0;

    while (true) {
    }
}

void timer0() __interrupt 1 {
    TH0 = 0xee;
    TL0 = 0xee;

    display(TIME);
}
