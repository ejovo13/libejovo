#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main() {

    uint64_t i = 15;

    int * iptr = (int * ) &i;


    printf("sizeof(int) = %i\n", sizeof(int));
    printf("sizeof(uint64_t) = %i\n", sizeof(uint64_t));

    printf("Unsigned int value of null = %lu\n", i);
    printf("Integer value of first 32 bytes = %d\n", iptr[0]);
    printf("Integer value of next 32 bytes = %d\n", iptr[1]);



    return 0;
}