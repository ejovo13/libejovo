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
    print_xoshiro256ss_state(&rng);
    print_xoshiro256ss_state(&XOSHIRO_RNG);

    for(int i = 0; i < 15; i ++) {
        printf("%d\n", unif(1, 10));
        print_xoshiro256ss_state(&XOSHIRO_RNG);

    }


}