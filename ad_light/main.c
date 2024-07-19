#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAIN_Fosc 11059200UL // 宏定义主时钟HZ

#define CS P3_7
#define DCLK P2_1
#define DIN P2_0
#define DOUT P2_5
#define DU P2_6 // 数码管段选
#define WE P2_7 // 数码管段选

__sbit __at(0xEC) P4_4;
#define DAC_DATA P4_4

unsigned char DAC_VAL; // 占空比参数 模拟8位DA输出，取值范围0-255
unsigned char pwm_t;   // 周期
/*====================================
使用typedef给已有数据类型取别名
====================================*/
typedef unsigned char INT8U;
typedef unsigned char uchar;
typedef unsigned char u8;

typedef unsigned int INT16U;
typedef unsigned int uint;
typedef unsigned int u16;

uint voltage; // 电压值

#define AD_CH0 0x94
#define AD_CH1 0xd4
#define AD_CH2 0xa4
#define AD_CH3 0xe4
// 通道0光敏cmd：0x94  通道1热敏cmd：0xd4  通道2电位器cmd：0xa4
// 通道3外部输入AIN3 cmd：0xe4

// 共阴数码管段选表0-9
const uchar SMGduan[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                         0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// 数码管位选码
const uchar SMGwei[] = {0xfe, 0xfd, 0xfb, 0xf7};

/*====================================
函数：void Delay_Ms(INT16U ms)
参数：ms，毫秒延时形参
描述：12T 51单片机自适应主时钟毫秒级延时函数
====================================*/
void Delay_Ms(INT16U ms) {
    INT16U i;
    do {
        i = MAIN_Fosc / 96000;
        while (--i)
            ; // 96T per loop
    } while (--ms);
}

/*====================================
函数	：display(uchar i)
参数	：i 显示变量取值0-9999
返回值	：无
描述	：数码管动态显示函数
====================================*/
void display(uint i) {
    uchar q, b, s, g;
    static uchar wei;
    q = i / 1000;
    b = i % 1000 / 100;
    s = i % 100 / 10;
    g = i % 10;
    P0 = 0XFF; // 清除断码
    WE = 1;    // 打开位选锁存器
    P0 = SMGwei[wei];
    WE = 0;    // 锁存位选数据
    P0 = 0XFF; // 清除断码
    switch (wei) {
    case 0:
        DU = 1;
        P0 = SMGduan[q] | 0x80;
        DU = 0;
        break; // 0x80加上小数点
    case 1:
        DU = 1;
        P0 = SMGduan[b];
        DU = 0;
        break;
    case 2:
        DU = 1;
        P0 = SMGduan[s];
        DU = 0;
        break;
    case 3:
        DU = 1;
        P0 = SMGduan[g];
        DU = 0;
        break;
    }
    wei++;
    if (wei == 4)
        wei = 0;
}

/*====================================
函数	：SPI_Write(uchar DAT)
参数	：DAT需要发送的数据
返回值	：无
描述	：发送一个字节数据
====================================*/
void SPI_Write(uchar DAT) {
    uchar i;
    for (i = 0; i < 8; i++) // 分别写8次，每次写1位
    {
        DCLK = 0;       // 拉低时钟总线，允许DIN变化
        if (DAT & 0x80) // 先写数据最高位
            DIN = 1;    // 写1
        else
            DIN = 0; // 写0
        DCLK = 1;    // 拉高时钟，让从机读DIN
        DAT <<= 1;   // 为发送下一位左移1位
    }
}
/*====================================
函数	：ReadByte()
参数	：无
返回值	：返回读出的数据
描述	：
====================================*/
uint SPI_Read() {
    uchar i;
    uint DAT = 0;
    for (i = 0; i < 12; i++) // 分别读12次，每次读一位
    {
        DAT <<= 1; // 数据左移1位，准备接收一位
        DCLK = 1;  // 拉高时钟总线，读取SDA上的数据
        DCLK = 0;  // 拉低时钟总线，允许从机控制SDA变化
        if (DOUT)
            DAT |= 0X01; // 为1则写1，否则不行执行写1，通过左移补0
    }
    return (DAT); // 返回读出的数据
}

inline static void _nop_() {
    __asm__("nop");
}

/*====================================
函数	：PCF8591Read(uchar cmd)
参数	：cmd XPT2046控制字节
返回值	：AD转出的数字量
描述	：读指定通道的输入的模拟量专为数字量
====================================*/
uint ReadAD(uchar cmd) {
    uint DAT;
    CS = 0;
    SPI_Write(cmd);
    DCLK = 0; // 拉低时钟总线
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    DAT = SPI_Read();
    CS = 1;
    return (DAT); // 返回读出数据
}

/************
 DA输出部分
*************/
// 定时器0中断
void timer0() __interrupt 1 {
    pwm_t++;              // 周期自加到255溢出后自动归零
    if (pwm_t <= DAC_VAL) // 设置占空比
        DAC_DATA = 1;
    else
        DAC_DATA = 0;
}

// 定时器1中断
void timer1() __interrupt 3 {
    display(voltage);
}

void main() // main函数自身会循环
{
    TMOD |= 0x02; // 8位自动重装模块
    TH0 = 220;
    TL0 = 220; // 11.0592M晶振下占空比最大比值是256,输出100HZ
    TR0 = 1;   // 启动定时器0
    ET0 = 1;   // 允许定时器0中断
    EA = 1;    // 总中断允许

    // TMOD |= 0x20; // 8位自动重装模块
    // TH1 = 0;
    // TL1 = 0;
    // TR1 = 1; // 启动定时器1
    // ET1 = 1; // 允许定时器1中断
    // EA = 1;  // 总中断允许

    while (1) {
        // 通道0光敏cmd：0x94  通道1热敏cmd：0xd4
        // 通道2电位器cmd：0xa4 通道3外部输入AIN3 cmd：0xe4
        voltage = ReadAD(AD_CH0) * 1.2207;
        DAC_VAL = voltage / 16; // 12位AD值转8位DA输出
        Delay_Ms(100);
    }
}
