#include "ejovo_time.h"
#include "ejovo_matrix_generic.h"
#include "ejovo_dataframe.h"
#include "ejovo_rand.h"
#include <assert.h>
#include <stdbool.h>


#define N 500
#define N_RAND 100000

void add_one(double *x) {
    *x = *x + 1;
}

double time_passed_xoroshiro() {

    // uniformly distributed on the interval 0, 1 via
    // xoroshiro
    Clock *clock = Clock_new();
    MATRIX_T *m;


    Clock_tic(clock);
    m = TYPED_FN(runif_gen)(N_RAND, 0, 1, unif_xoroshiro);
    Clock_toc(clock);

    double time = elapsed_time(clock);

    fprintf(stderr, "%d", MATRIX_FN(size)(m));

    free(clock);
    MATRIX_FN(free)(m);
    return time;

}
#ifdef PCG_RANDOM
double time_passed_pcg() {

    // uniformly distributed on the interval 0, 1 via
    // xoroshiro
    Clock *clock = Clock_new();
    MATRIX_T *m;


    Clock_tic(clock);
    m = TYPED_FN(runif_gen)(N_RAND, 0, 1, unif_pcg);
    Clock_toc(clock);

    double time = elapsed_time(clock);

    fprintf(stderr, "%d", MATRIX_FN(size)(m));

    free(clock);
    MATRIX_FN(free)(m);
    return time;

}
#endif

// double time_passed_rng() {

//     // compute the time it takes to get 1000 random numbers
//     // uniformly distributed on the interval 0, 1 via
//     // xoroshiro
//     Clock *clock = Clock_new();
//     MATRIX_T *m;


//     Clock_tic(clock);
//     m = MATRIX_FN(random)(1, N_RAND, 0, 1);
//     Clock_toc(clock);

//     double time = elapsed_time(clock);

//     fprintf(stderr, "%d", MATRIX_FN(size)(m));

//     free(clock);
//     MATRIX_FN(free)(m);
//     return time;

// }

// define a new function that creates a new matrix of size N 
// and then times the operation of summing
double time_passed_sum_fn() {

    MATRIX_T *m = MATRIX_FN(rand)(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double t = TYPED_FN(sum)(m);
    fprintf(stderr, "%lf, ", t);
    Clock_toc(clock);

    MATRIX_FN(free)(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

double time_passed_sum_loop() {

    MATRIX_T *m = MATRIX_FN(rand)(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double loop_sum = 0;
    double *data = m->data;
    for (int i = 0; i < MATRIX_FN(size)(m); i++) {
        loop_sum += data[i];
    }
    fprintf(stderr, "%lf, ", loop_sum);
    Clock_toc(clock);

    MATRIX_FN(free)(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

int main() {

    ejovo_seed();


    Clock* clock = Clock_new();

    MATRIX_T * m = MATRIX_FN(rand)(N, N);
    MATRIX_T * b = MATRIX_FN(from)((double []) {1., 2., 3., 4.,}, 1, 4);

    // MATRIX_FN(print)(m);
    // MATRIX_FN(print)(b);


    // printf("Max of [1 2 3 4]: %lf \n", TYPED_FN(max)(b));
    // // printf("Sum of [1 2 3 4]: %lf \n", TYPED_FN(sum)(b));

    // Clock_tic(clock);
    // printf("Sum :%lf, Mean: %lf, Std: %lf, Var: %lf\n", TYPED_FN(sum)(m), TYPED_FN(mean)(m), TYPED_FN(std)(m), TYPED_FN(var)(m));
    // Clock_toc(clock);

    // printf("Elapsed time: %lf\n", elapsed_time(clock));

    // I'd like to test which is faster:
    // using my MatIters or just iterating with regular pointers?

    // Start with MatIters
    // MATRIX_FN(iter)

    // Use a regular for loop
    // Clock_tic(clock);
    // double loop_sum = 0;
    // double *data = m->data;
    // for (int i = 0; i < MATRIX_FN(size)(m); i++) {
    //     loop_sum += data[i];
    // }
    // Clock_toc(clock);

    // double loop_time = elapsed_time(clock);

    // Clock_tic(clock);
    // double fn_sum = TYPED_FN(sum)(m);
    // Clock_toc(clock);

    // double fn_time = elapsed_time(clock);

    // printf("Loop time:\t\t%lf\n", loop_time);
    // printf("Function time:\t\t %lf\n", fn_time);

    Clock_tic(clock);

    const int n_tests = 100;

    MATRIX_T *fn_time = save_doubles(time_passed_sum_fn, n_tests);
    MATRIX_T *loop_time = save_doubles(time_passed_sum_loop, n_tests);

    MATRIX_T *xoroshiro_time = save_doubles(time_passed_xoroshiro, n_tests);

    #ifdef PCG_RANDOM
        MATRIX_T *pcg_time = save_doubles(time_passed_pcg, n_tests);
    #endif
    // MATRIX_FN(print)(fn_time);
    Clock_toc(clock);
    // printf("Time taken to run test total: %lf\n", elapsed_time(clock));
    // printf("Avg time to compute sums: %lf\n", TYPED_FN(mean)(fn_time));

    printf("Mean(fn_time): %lf\n", TYPED_FN(mean)(fn_time));
    printf("Mean(loop_time): %lf\n", TYPED_FN(mean)(loop_time));

    // MATRIX_T *rand_time = save_doubles(time_passed_rng, 100);
    // printf("Rand unifd %d times in %lf seconds\n", N_RAND, TYPED_FN(mean)(rand_time));
    // printf("Generation rate: %lf Doubles /s\n", N_RAND / TYPED_FN(mean)(rand_time));


    printf("XOROSHIRO: %lf D/s\n", N_RAND / TYPED_FN(mean)(xoroshiro_time));

    #ifdef PCG_RANDOM
        printf("PCG: %lf D/s\n", N_RAND / TYPED_FN(mean)(pcg_time));
    #endif

    MATRIX_FN(free)(fn_time);
    MATRIX_FN(free)(loop_time);
    #ifdef PCG_RANDOM
        MATRIX_FN(free)(pcg_time);
    #endif
    MATRIX_FN(free)(xoroshiro_time);
    MATRIX_FN(free)(m);
    MATRIX_FN(free)(b);
    free(clock);

    return 0;
}