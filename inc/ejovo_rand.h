#ifndef EJOVO_RAND
#define EJOVO_RAND

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#ifdef __linux__
    #include <sys/random.h>
    #include <sys/types.h>
#endif
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>

#ifdef PCG_RANDOM
    #include "pcg_variants.h"
#endif

#define _USE_MATH_DEFINES // acces M_PI
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/**========================================================================
 *!                           Dependency
 *========================================================================**/
// !!!!! This file depends on a pcg generator being downloaded and who's

/**========================================================================
 *!                           PCG
 *========================================================================**/
/// C translation of rust's implementation of the PCG64

// typedef struct {

//     uint64_t state[2];
//     uint64_t increment[2];

// } pcg64_t;

// typedef struct {
//     uint64_t low;
//     uint64_t high;
// } uint128_t;



// // implement function to add a 128bit integer
// uint64_t * u128_add(uint128_t a, uint128_t b) {
    
// }


/**@file
 * @brief Utilities for non-naive random number generation in C
 *
 * This header file contains an implementation of the xoshiro** algorithm
 * with 256 bits of state.
 *
 */


/**
 *  @brief Structure to contain the 256 bits of state needed for xoshiro random number generation
 *
 *  The xorshiro algorithm is a class of `xorshift` algorithms that encorporates
 *  bit rotations and linear shifts combined with xor bit operations to create
 *  uniform random bits
 *
 *  There is a global structure `XOSHIRO_RNG` that servers as a default rng for this module.
 *  To use it and the proceeding rng functions that rely on it, always remember to seed `XOSHIRO_RNG`
 *  by calling `ejovo_seed()` in `main`.
 */
typedef struct xoshiro256ss_state {
	uint64_t s[4];
} xor_rng;

extern xor_rng XOSHIRO_RNG;

#ifdef PCG_RANDOM
    extern pcg64_random_t PCG64_RNG;
#endif

// Get x in [min, max]
/**
 * Return a uniform random integer in [min, max] using c stdlib's rand() default rng
 *
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)

 * @return \f$X \in [min, max]\f$.
 */
int get_rand_int_range(int min, int max);

// Get random x in [1, max]
/**
 * Get a random integer x in [1, max]
 *
 * Similar to `get_rand_int_range` but with an assumed minimum value of 1
 * @param max Maximum value (inclusive)
 *
 * @return \f$X \in [1, max]\f$
 */
int get_rand_int(int max);

// use more cryptographically secure functions to generate much better random numbers
/**
 * Perform a left bit rotation of k bits
 *
 * Consider the byte `10110110`. A left roll of 2 bits results in `110110 10`. The left two bits have
 * rolled over to the right side, in contrast with a simple bit shift.
 *
 * @param x 64 bits that will get rolled
 * @param k Number of bits to rollover
 *
 * @return `x` after it has rolled `k` bits left
 */
uint64_t rol64(uint64_t x, int k);

/**
 * Seed xoshiro generator by getting 256 random bytes from the getrandom system call.
 *
 */
void seed_xoshiro256ss(struct xoshiro256ss_state * state);

/**
 * Print the 256 bits of state for an xoshiro256ss_state structure
 *
 */
void print_xoshiro256ss_state(struct xoshiro256ss_state * state);

/**
 * This xoshiro256** algorithm was taken from the wikipedia page on xorshift generators
 * The rest of the code interpreting these 64 random bits was all written by me, Evan Voyles
 *
 *
 *
 */
uint64_t xoshiro256ss(struct xoshiro256ss_state *state);


typedef uint64_t (*RNG_FN) (); // return an int between [0, ULONG_MAX]
extern RNG_FN DEFAULT_RNG;

/**========================================================================
 *!                   Different unif(0, ULONG_MAX) generators
 *========================================================================**/
uint64_t unif_xoroshiro();

#ifdef PCG_RANDOM

    uint64_t unif_pcg();

    void seed_pcg64(pcg64_random_t *rng);

    uint64_t pcg64_next(pcg64_random_t *rng);

    double pcg64_next_double(pcg64_random_t *rng);

    double get_double_pcg();

#endif

/**========================================================================
 *!                 Distributions with RNG argument
 *========================================================================**/
double std_unifd_rng(RNG_FN rng);


double unifd_rng(double a, double b, RNG_FN rng);

double complex unifc_rng(double complex a, double complex b, RNG_FN rng);


int unifi_rng(int a, int b, RNG_FN rng);

// Generate a variate that follows the standard normal distribution using the Box-Muller transform
double std_norm_rng(RNG_FN rng);

double normd_rng(double mean, double std, RNG_FN rng);

double complex normc_rng(double complex mean, double complex sigma, RNG_FN rng);

/**========================================================================
 *!                           Default generators
 *========================================================================**/ 
// Unif(0, 1)
double std_unifd();

// Unif(a, b)
double unifd(double a, double b);

// Discrete uniform distribution (a, b)
int unifi(int a, int b);

// Norm(0, 1)
double std_norm();

double normd(double mean, double std);

double complex normc(double complex mean, double complex sigma);


/**
 * Get 32 bits of data from an xor_rng and interpret them as an integer
 *
 */
int xoroshiro_get_int(struct xoshiro256ss_state *state);

// Use the xoshiro rng to get a 
// uint64_t unif_xoroshiro();

int unifi(int a, int b);

int unifi_gen(int a, int b, RNG_FN);

// /**
//  * Return a Integer that follows a uniform distribution [a,b]
//  *
//  */
// int unif(int a, int b);


/**
 * @brief Return a uniform random variabl X ~ [a, b)
 *
 * @param a
 * @param b
 * @return double
 */
double unifd(double a, double b);

// Generate a variate that follows the standard normal distribution using the Box-Muller transform
double std_norm();

double normd(double mean, double std);

// Get a random variable folling the exponential distribution with rate parameter \lambda
// ~ \exp(-\x), where \ is "\lambda"
double expd(double rate);

double get_double();

/**
 * Seed the default XOSHIRO_RNG rng included in this header
 *
 * This function should be called sometime in `main` before using any of the other
 * associated xoshiro functions.
 *
 */
void ejovo_seed();

int *fischer_yates(int n);

#endif