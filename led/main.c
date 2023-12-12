#include <mcs51/8051.h>

// void Delay(unsigned int ms);

void main() {
    P1_0 = 0;
    P1_0 = 1;
    P1_0 = 2;
    P1 = 0xff;
    P1 = 0x00;

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
