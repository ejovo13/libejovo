// Why can't I fucking figure this out
// I just want to extract the 53 bits from my random
// number generator and then move on with my fucking life.
#ifndef EJOVO_BIN
#define EJOVO_BIN

// #pragma once

#include "ejovo_rand.h"
#include <stdint.h>

static inline void use(void *thing) {
    if (thing == NULL) exit(2);
}

// Should inlude functions that can print out the bit representation
// of any type

// print the bits of a double
void print_bitsd(double __d);

void print_bits(void *__v, size_t __nbytes);

#endif