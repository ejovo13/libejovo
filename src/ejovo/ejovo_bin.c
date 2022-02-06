// Why can't I fucking figure this out
// I just want to extract the 53 bits from my random
// number generator and then move on with my fucking life.

#include "ejovo_bin.h"

// Should inlude functions that can print out the bit representation
// of any type

// print the bits of a double
void print_bitsd(double __d) {

    // First thing to do is interpret the bits as a uint64_t
    print_bits(&__d, 8);

}

void print_bits(void *__v, size_t __nbytes) {

    uint8_t *p8;
    uint16_t *p16;
    uint32_t *p32;
    uint64_t *p64;
    uint64_t one = 1;

    switch (__nbytes) {

        case 1:

            p8 = __v;
            for (uint8_t i = 1 << 7; i > 0; i /= 2)
                (*p8) & i ? printf("1") : printf("0");

            break;

        case 2:

            p16 = __v;
            for (uint16_t i = 1 << 15; i > 0; i /= 2)
                (*p16) & i ? printf("1") : printf("0");

            break;

        case 4:

            p32 = __v;
            for (uint32_t i = 1 << 31; i > 0; i /= 2)
                (*p32 & i) ? printf("1") : printf("0");

            break;

        case 8:

            p64 = __v;
            for (uint64_t i = one << 62; i > 0; i /= 2)
                (*p64 & i) ? printf("1") : printf("0");

            break;

        default:

            printf("You dumb bitch\n");


    }

    printf("\n");

}