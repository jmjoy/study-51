#include <mcs51/8051.h>
#include <stdbool.h>
#include <stdint.h>

// const uint16_t PER_NS = 1 / (11.0592 * 1000000) * 12 * 1000000000;

// const uint16_t TWENTY_MS_START = 63335 - (20 * 1000000 / PER_NS);

void main(void) {
    TR0 = 1;
    TMOD = 0x01;
    TH0=0xFC;
	TL0=0x18;

    int i = 0;
    while (true) {
        if (TF0 == 1) {
            TH0=0xFC;
            TL0=0x18;
            TF0 = 0;
            i += 1;
        }
        if (i == 1000) {
            i = 0;
            P1 = ~P1;
        }
    }
}
