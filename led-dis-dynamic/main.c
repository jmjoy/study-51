#include <mcs51/8051.h>
#include <stdint.h>

/**
 * 数码管位选
 */
#define WELA P2_7

/**
 * 数码管段选
 */
#define DULA P2_6

#define crol(x, n) (((x) << (n)) | ((x) >> (8 * sizeof(x) - (n))))

void Delay1ms() //@11.0592MHz
{
    unsigned char i, j;

    // _nop_();
    i = 2;
    j = 199;
    do {
        while (--j)
            ;
    } while (--i);
}

void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	// _nop_();
	i = 43;
	while (--i);
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

void main(void) {
    // P1 = 0;

    // 看了一遍江协科技的51单片机视频，了解了数码管的消隐的知识，
    // 写出来完美的动态数码管扫描代码！
    while (1) {
        for (int i = 0; i < 8; i += 1) {
            P0 = 0xff;
            WELA = 1;
            // P0 = crol(0b11111110, i);
            P0 = WES[i];
            WELA = 0;

            P0 = 0x00;
            DULA = 1;
            P0 = NS[i + 1];
            Delay100us();
            P0 = 0x00;
            DULA = 0;
        }
    }
}
