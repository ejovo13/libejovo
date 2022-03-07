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

struct xoshiro256ss_state XOSHIRO_RNG = {0, 0, 0, 0};

//seed xoshiro generator by getting 256 random bits from the getrandom system call.
void seed_xoshiro256ss(struct xoshiro256ss_state * state) {
    // if on linux, seed the 256 bits with a system call of getrandom
    #ifdef __linux
        getrandom(state, 32, 0);
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

// if I want this shit to work on macos, I need to user a different function than get random.


void print_xoshiro256ss_state(struct xoshiro256ss_state * state) {

    printf("State of random generator: %8lx, %8lx, %8lx, %8lx\n", state->s[0], state->s[1], state->s[2], state->s[3]);

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

int get_int_xoshiro(struct xoshiro256ss_state *state) {
// interpret the first 32 bits of the 64 bits as an integer. - this returns a uniform X ~ [0, 2147483647]
    int *iptr = NULL;
    uint64_t bits = xoshiro256ss(state);
    iptr = (int *) &bits;
    return abs(iptr[1]);
    // return iptr[1];
}

// get a double in the range [0, 1]
double get_double() {
    uint64_t val = xoshiro256ss(&XOSHIRO_RNG);
    return (double) val / (double) ULONG_MAX; // This is how we "take the top 53 bits I think........."
}

int unif(int a, int b) {
// return a random variable X ~ [a, b]
    // int = get_int_xoshiro()
    int spread = (b - a) + 1;
    double x = get_double(); // returns a value in [0, 1)

    return (int) floor(x * spread) + (a) ; // floor(x * spread) returns a vlue in [0, spread)
}

double unifd(double a, double b) {

    double spread = (b - a);

    double x = get_double(); // returns a value in [0, 1)

    return x * spread + a;
}

// Generate a variate that follows the standard normal distribution using the Box-Muller transform
double std_norm() {

    double u1 = unifd(0, 1);
    double u2 = unifd(0, 1);

    double R = sqrt(-2 * log(u1));

    return R * cos(2 * M_PI * u2);
}

double normd(double mean, double std) {
    return (std_norm() * std) + mean;
}

// Get a random variable folling the exponential distribution with rate parameter \lambda
// ~ \exp(-\x), where \ is "\lambda"
double expd(double rate) {

    double y = unifd(0, 1);

    return (-1 / rate) * log(1 - y);
}

void ejovo_seed() {
    seed_xoshiro256ss(&XOSHIRO_RNG);
}

// Create a shuffled array with elements 1 to n
int *fischer_yates(int n) {

    int *arr = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }


    int tmp;
    // now go ahead and shuffle them
    for (int j = 0, i = n - 1; i > 0; i--) {
        j = unif(0, i);
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }

    return arr;
}
