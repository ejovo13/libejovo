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
    Matrix_d *m;


    Clock_tic(clock);
    m = runif_rng_d(N_RAND, 0, 1, unif_xoroshiro);
    Clock_toc(clock);

    double time = elapsed_time(clock);

    fprintf(stderr, "%lu", Matrix_size_d(m));

    free(clock);
    Matrix_free_d(m);
    return time;

}
#ifdef PCG_RANDOM
double time_passed_pcg() {

    // uniformly distributed on the interval 0, 1 via
    // xoroshiro
    Clock *clock = Clock_new();
    Matrix_d *m;


    Clock_tic(clock);
    m = runif_rng_d(N_RAND, 0, 1, unif_pcg);
    Clock_toc(clock);

    double time = elapsed_time(clock);

    fprintf(stderr, "%lu", Matrix_size_d(m));

    free(clock);
    Matrix_free_d(m);
    return time;

}
#endif

// double time_passed_rng() {

//     // compute the time it takes to get 1000 random numbers
//     // uniformly distributed on the interval 0, 1 via
//     // xoroshiro
//     Clock *clock = Clock_new();
//     Matrix_d *m;


//     Clock_tic(clock);
//     m = Matrix_random_d(1, N_RAND, 0, 1);
//     Clock_toc(clock);

//     double time = elapsed_time(clock);

//     fprintf(stderr, "%d", Matrix_size_d(m));

//     free(clock);
//     Matrix_free_d(m);
//     return time;

// }

// define a new function that creates a new matrix of size N 
// and then times the operation of summing
double time_passed_sum_fn() {

    Matrix_d *m = Matrix_rand_d(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double t = sum_d(m);
    fprintf(stderr, "%lf, ", t);
    Clock_toc(clock);

    Matrix_free_d(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

double time_passed_sum_loop() {

    Matrix_d *m = Matrix_rand_d(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double loop_sum = 0;
    double *data = m->data;
    for (size_t i = 0; i < Matrix_size_d(m); i++) {
        loop_sum += data[i];
    }
    fprintf(stderr, "%lf, ", loop_sum);
    Clock_toc(clock);

    Matrix_free_d(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

int main() {

    ejovo_seed();


    Clock* clock = Clock_new();

    Matrix_d * m = Matrix_rand_d(N, N);
    Matrix_d * b = Matrix_from_d((double []) {1., 2., 3., 4.,}, 1, 4);

    // Matrix_print_d(m);
    // Matrix_print_d(b);


    // printf("Max of [1 2 3 4]: %lf \n", max_d(b));
    // // printf("Sum of [1 2 3 4]: %lf \n", sum_d(b));

    // Clock_tic(clock);
    // printf("Sum :%lf, Mean: %lf, Std: %lf, Var: %lf\n", sum_d(m), mean_d(m), std_d(m), var_d(m));
    // Clock_toc(clock);

    // printf("Elapsed time: %lf\n", elapsed_time(clock));

    // I'd like to test which is faster:
    // using my MatIters or just iterating with regular pointers?

    // Start with MatIters
    // Matrix_iter_d

    // Use a regular for loop
    // Clock_tic(clock);
    // double loop_sum = 0;
    // double *data = m->data;
    // for (int i = 0; i < Matrix_size_d(m); i++) {
    //     loop_sum += data[i];
    // }
    // Clock_toc(clock);

    // double loop_time = elapsed_time(clock);

    // Clock_tic(clock);
    // double fn_sum = sum_d(m);
    // Clock_toc(clock);

    // double fn_time = elapsed_time(clock);

    // printf("Loop time:\t\t%lf\n", loop_time);
    // printf("Function time:\t\t %lf\n", fn_time);

    Clock_tic(clock);

    const int n_tests = 100;

    Matrix_d *fn_time = save_doubles(time_passed_sum_fn, n_tests);
    Matrix_d *loop_time = save_doubles(time_passed_sum_loop, n_tests);

    Matrix_d *xoroshiro_time = save_doubles(time_passed_xoroshiro, n_tests);

    #ifdef PCG_RANDOM
        Matrix_d *pcg_time = save_doubles(time_passed_pcg, n_tests);
    #endif
    // Matrix_print_d(fn_time);
    Clock_toc(clock);
    // printf("Time taken to run test total: %lf\n", elapsed_time(clock));
    // printf("Avg time to compute sums: %lf\n", mean_d(fn_time));

    printf("Mean(fn_time): %lf\n", mean_d(fn_time));
    printf("Mean(loop_time): %lf\n", mean_d(loop_time));

    // Matrix_d *rand_time = save_doubles(time_passed_rng, 100);
    // printf("Rand unifd %d times in %lf seconds\n", N_RAND, mean_d(rand_time));
    // printf("Generation rate: %lf Doubles /s\n", N_RAND / mean_d(rand_time));


    printf("XOROSHIRO: %lf D/s\n", N_RAND / mean_d(xoroshiro_time));

    #ifdef PCG_RANDOM
        printf("PCG: %lf D/s\n", N_RAND / mean_d(pcg_time));
    #endif

    Matrix_free_d(fn_time);
    Matrix_free_d(loop_time);
    #ifdef PCG_RANDOM
        Matrix_free_d(pcg_time);
    #endif
    Matrix_free_d(xoroshiro_time);
    Matrix_free_d(m);
    Matrix_free_d(b);
    free(clock);

    return 0;
}