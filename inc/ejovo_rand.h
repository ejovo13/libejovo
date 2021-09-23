#ifndef EJOVO_RAND
#define EJOVO_RAND

#include <stdlib.h>
#include <math.h>
#include <time.h>

int get_rand_int_range(int min, int max) {
// get random integer in [min, max]
    int spread = (max - min) + 1;
    double x = ((double) rand()) / RAND_MAX; // returns a value in [0, 1[
    return (int) floor(x * spread) + (min) ; // floor(x * spread) returns a vlue in [0, spread[
}

int get_rand_int(int max) {
// get random integer in [1, max]
    return get_rand_int_range(1, max);
}

void fill_rand_array(int * arr, int n, int max) {
// fill integer array whose length is n with elements in [1, max]


}

#endif