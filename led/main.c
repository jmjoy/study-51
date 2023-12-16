#include <mcs51/8051.h>
#include <stdint.h>

#define __P1_0 0x0090
// #define CLR(P) __asm__("clr %0" :: "i" (P))
#define CLR(P) do { \
    __asm \
        clr __P1_0 ; 清除给定地址的值 \
    __endasm; \
} while(0)


// void Delay(unsigned int ms);

// 毫秒级延时函数定义
void delay(uint8_t z) {
    for (uint8_t x = z; x > 0; x--) {
        for (uint8_t y = 114; y > 0; y--) {
        }
    }
}

void main() {
    // P1_0 = 0;
    // P1_0 = 1;
    // P1_0 = 2;
    // P1 = 0xff;
    // P1 = 0x00;

    // uint8_t *p = (uint8_t *)0x0090;
    // *p = 0xfc;

    // CLR(__P1_0);

    __asm__("mov 0x0090, #0xfe");
    delay(1000);
    __asm__("mov 0x0090, #0b11111101");
    delay(1000);
    __asm__("mov 0x0090, #0b11111011");
    delay(1000);

    // while(1){
    // 		//自行对照开发板引脚图。
    //         P1_0 = 0;
    //         P1_1 = 0;
    //         P1_2 = 0;
    //         P1_3 = 0;

    //         Delay(500);

    //         P1_0 = 1;
    //         P1_1 = 1;
    //         P1_2 = 1;
    //         P1_3 = 1;

    //         //led灯以一秒为一个周期闪烁。
    //         Delay(500);
    // }
}

// void Delay(unsigned int ms){
//         unsigned int a, b;
//         for(a = ms; a > 0; a--){
//                 for(b = 100; b > 0; b--);
//         }
// }
