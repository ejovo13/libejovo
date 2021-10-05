#ifndef EJOVO_RAND
#define EJOVO_RAND

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <sys/random.h>
#include <limits.h>

typedef struct xoshiro256ss_state {
	uint64_t s[4];
} xor_rng;

extern xor_rng XOSHIRO_RNG;

// Get x in [min, max]
int get_rand_int_range(int min, int max);

// Get random x in [1, max]
int get_rand_int(int max);

void fill_rand_array(int * arr, int n, int max);

// use more cryptographically secure functions to generate much better random numbers
uint64_t rol64(uint64_t x, int k);

//seed xoshiro generator by getting 256 random bytes from the getrandom system call.
ssize_t seed_xoshiro256ss(struct xoshiro256ss_state * state);

void print_xoshiro256ss_state(struct xoshiro256ss_state * state);

/* This xoshiro256** algorithm was taken from the wikipedia page on xorshift generators
   The rest of the code interpreting these 64 random bits was all written by me, Evan Voyles */
uint64_t xoshiro256ss(struct xoshiro256ss_state *state);

int get_int_xoshiro(struct xoshiro256ss_state *state);

int unif(int a, int b);

void ejovo_seed();


#endif