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

    ejovo_seed();

    xor_rng rng;
    seed_xoshiro256ss(&rng);
    seed_xoshiro256ss(&XOSHIRO_RNG);
    // print_xoshiro256ss_state(&rng);
    // print_xoshiro256ss_state(&XOSHIRO_RNG);

    int random;

    printf("\n\nStarting xoshiro256** trials:\n\n");

    for(int i = 0; i < 50; i ++) {
        random = unif(1,10);
        printf("%d  ", random);
        // print_xoshiro256ss_state(&XOSHIRO_RNG);

    }

    printf("\n");


}