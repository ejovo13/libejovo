#include "ejovo_rand.h"

int get_rand_int_range(int min, int max) {
// get random integer in [min, max]
    int spread = (max - min) + 1;
    double x = ((double) rand()) / RAND_MAX; // returns a value in [0, 1)
    return (int) floor(x * spread) + (min) ; // floor(x * spread) returns a vlue in [0, spread)
}

int get_rand_int(int max) {
// get random integer in [1, max]
    return get_rand_int_range(1, max);
}

// use more cryptographically secure functions to generate much better random numbers
uint64_t rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

struct xoshiro256ss_state XOSHIRO_RNG = { .s = {0, 0, 0, 0}};

#ifdef PCG_RANDOM
    pcg64_random_t PCG64_RNG;
#endif

//seed xoshiro generator by getting 256 random bits from the getrandom system call.
void seed_xoshiro256ss(struct xoshiro256ss_state * state) {
    // if on linux, seed the 256 bits with a system call of getrandom
    #ifdef __linux
        ssize_t bytes_read = getrandom(state, 32, 0);
        if (bytes_read != 32) { exit(EXIT_FAILURE); }
        assert(bytes_read > 0);
    #else

        uint32_t * data = malloc(32); // allocate 32 bytes of memory, where each uint32_t is 4 bytes, so 8 uint32_t's
        uint32_t temp = 0;
        for (uint32_t i = 0; i < 8; i++) {

            temp = get_rand_int_range(INT_MIN, INT_MAX);
            data[i] = temp;

        }

        uint64_t * state_data = (uint64_t *) data; // still 32 bytes, but now in 4 8 byte chunks
        state->s[0] = state_data[0];
        state->s[1] = state_data[1];
        state->s[2] = state_data[2];
        state->s[3] = state_data[3];


    #endif
    // else, use the generic rand function to get 32 bits of data 8 times

}

#ifdef PCG_RANDOM

void seed_pcg64(pcg64_random_t *rng) {

    pcg128_t seeds[2];
    getrandom((void *) seeds, 16, 0);
    pcg64_srandom_r(rng, seeds[0], seeds[1]);
}

uint64_t pcg64_next(pcg64_random_t *rng) {
    return pcg64_random_r(rng);
}

#endif
// if I want this shit to work on macos, I need to user a different function than get random.


void print_xoshiro256ss_state(struct xoshiro256ss_state * state) {

    // printf("State of random generator: %8lx, %8lx, %8lx, %8lx\n", state->s[0], state->s[1], state->s[2], state->s[3]);
#if defined __APPLE__
    printf("State of random generator: %8llu, %8llu, %8llu, %8llu\n", state->s[0], state->s[1], state->s[2], state->s[3]);
#else
    printf("State of random generator: %8lu, %8lu, %8lu, %8lu\n", state->s[0], state->s[1], state->s[2], state->s[3]);
#endif


}

/* This xoshiro256** algorithm was taken from the wikipedia page on xorshift generators
   The rest of the code interpreting these 64 random bits was all written by me, Evan Voyles */
uint64_t xoshiro256ss(struct xoshiro256ss_state *state)
{
	uint64_t *s = state->s;
	uint64_t const result = rol64(s[1] * 5, 7) * 9;
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}

int xoroshiro_get_int(struct xoshiro256ss_state *state) {
// interpret the first 32 bits of the 64 bits as an integer. - this returns a uniform X ~ [0, 2147483647]
    int *iptr = NULL;
    uint64_t bits = xoshiro256ss(state);
    iptr = (int *) &bits;
    return abs(iptr[1]);
    // return iptr[1];
}

/**========================================================================
 *!                   Different unif(0, ULONG_MAX) generators
 *========================================================================**/
uint64_t unif_xoroshiro() {
    return xoshiro256ss(&XOSHIRO_RNG);
}


#ifdef PCG_RANDOM
uint64_t unif_pcg() {
    return pcg64_next(&PCG64_RNG);
}
#endif
/**========================================================================
 *!                 Distributions with RNG argument
 *========================================================================**/
double std_unifd_rng(RNG_FN rng) {
    uint64_t val = rng();
    return (double) val / (double) ULONG_MAX;
}


double unifd_rng(double a, double b, RNG_FN rng) {
    double spread = (b - a);
    double x = std_unifd_rng(rng);
    return x * spread + a;
}

double complex unifc_rng(double complex a, double complex b, RNG_FN rng) {
    return __builtin_complex( unifd_rng(creal(a), creal(b), rng), 
                  unifd_rng(cimag(a), cimag(b), rng) );
}


int unifi_rng(int a, int b, RNG_FN rng) {
    int spread = (b - a) + 1;
    double x = std_unifd_rng(rng);

    return (int) floor(x * spread) + a;
}

// Generate a variate that follows the standard normal distribution using the Box-Muller transform
double std_norm_rng(RNG_FN rng) {

    double u1 = std_unifd_rng(rng);
    double u2 = std_unifd_rng(rng);

    double R = sqrt(-2 * log(u1));

    return R * cos(2 * M_PI * u2);
}

double normd_rng(double mean, double std, RNG_FN rng) {
    return (std_norm_rng(rng) * std) + mean;
}

double complex normc_rng(double complex mean, double complex sigma, RNG_FN rng) {
    return __builtin_complex( normd_rng(creal(mean), cabs(sigma), rng), 
                  normd_rng(cimag(mean), cabs(sigma), rng) );
}

/**========================================================================
 *!                           Default generators
 *========================================================================**/ 
RNG_FN DEFAULT_RNG = unif_xoroshiro;

// Unif(0, 1)
double std_unifd() {
    return std_unifd_rng(DEFAULT_RNG);
}

// Unif(a, b)
double unifd(double a, double b) {
    return unifd_rng(a, b, DEFAULT_RNG);
}

double unifc(double complex a, double complex b) {
    return unifc_rng(a, b, DEFAULT_RNG);
}

// Discrete uniform distribution (a, b)
int unifi(int a, int b) {
    return unifi_rng(a, b, DEFAULT_RNG);
}

// Norm(0, 1)
double std_norm() {
    return std_norm_rng(DEFAULT_RNG);
}

double normd(double mean, double std) {
    return normd_rng(mean, std, DEFAULT_RNG);
}

double complex normc(double complex mu, double complex sigma) {
    return normc_rng(mu, sigma, DEFAULT_RNG);
}

/**========================================================================
 *!                           Old implementation
 *========================================================================**/

// Get a random variable folling the exponential distribution with rate parameter \lambda
// ~ \exp(-\x), where \ is "\lambda"
double expd(double rate) {

    double y = unifd(0, 1);

    return (-1 / rate) * log(1 - y);
}

void ejovo_seed() {
    seed_xoshiro256ss(&XOSHIRO_RNG);

    #ifdef PCG_RANDOM
        seed_pcg64(&PCG64_RNG);
    #endif
}

// Create a shuffled array with elements 1 to n
int *fischer_yates(int n) {

    int *arr = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    int tmp = 0;

    // now go ahead and shuffle them
    for (int j = 0, i = n - 1; i > 0; i--) {
        j = unifi(0, i);
        tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }

    return arr;
}
