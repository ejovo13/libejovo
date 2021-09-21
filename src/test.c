#include "ejovo_rand.h"
#include <stdio.h>

int main() {

    for (int i = 0; i < 200; i++) {
        printf("%d ", get_rand_int(10));
    }

    printf("\n\n");

    for (int i = 0; i < 200; i ++) {
        printf("%d ", get_rand_int_range(5, 10));
    }
}