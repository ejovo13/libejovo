#include "ejovo_time.h"
#include "ejovo_matrix.h"
#include "ejovo_dataframe.h"
#include "ejovo_rand.h"
#include <assert.h>
#include <stdbool.h>


#define N 500
#define N_RAND 100000

void add_one(double *x) {
    *x = *x + 1;
}

double time_passed_rng() {

    // compute the time it takes to get 1000 random numbers
    // uniformly distributed on the interval 0, 1 via
    // xoroshiro
    Clock *clock = Clock_new();
    Matrix *m;


    Clock_tic(clock);
    m = Matrix_random(1, N_RAND, 0, 1);
    Clock_toc(clock);

    double time = elapsed_time(clock);

    fprintf(stderr, "%d", Matrix_size(m));

    free(clock);
    Matrix_free(m);
    return time;

}

// define a new function that creates a new matrix of size N 
// and then times the operation of summing
double time_passed_sum_fn() {

    Matrix *m = Matrix_rand(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double t = sum(m);
    fprintf(stderr, "%lf, ", t);
    Clock_toc(clock);

    Matrix_free(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

double time_passed_sum_loop() {

    Matrix *m = Matrix_rand(N, N);
    Clock *clock = Clock_new();
    Clock_tic(clock);
    double loop_sum = 0;
    double *data = m->data;
    for (int i = 0; i < Matrix_size(m); i++) {
        loop_sum += data[i];
    }
    fprintf(stderr, "%lf, ", loop_sum);
    Clock_toc(clock);

    Matrix_free(m);

    double time = elapsed_time(clock);
    free(clock);

    return time;
}

int main() {

    ejovo_seed();


    Clock* clock = Clock_new();

    Matrix* m = Matrix_rand(N, N);
    Matrix* b = Matrix_from((double []) {1., 2., 3., 4.,}, 1, 4);

    // Matrix_print(m);
    // Matrix_print(b);


    // printf("Max of [1 2 3 4]: %lf \n", max(b));
    // // printf("Sum of [1 2 3 4]: %lf \n", sum(b));

    // Clock_tic(clock);
    // printf("Sum :%lf, Mean: %lf, Std: %lf, Var: %lf\n", sum(m), mean(m), std(m), var(m));
    // Clock_toc(clock);

    // printf("Elapsed time: %lf\n", elapsed_time(clock));

    // I'd like to test which is faster:
    // using my MatIters or just iterating with regular pointers?

    // Start with MatIters
    // Matrix_iter

    // Use a regular for loop
    // Clock_tic(clock);
    // double loop_sum = 0;
    // double *data = m->data;
    // for (int i = 0; i < Matrix_size(m); i++) {
    //     loop_sum += data[i];
    // }
    // Clock_toc(clock);

    // double loop_time = elapsed_time(clock);

    // Clock_tic(clock);
    // double fn_sum = sum(m);
    // Clock_toc(clock);

    // double fn_time = elapsed_time(clock);

    // printf("Loop time:\t\t%lf\n", loop_time);
    // printf("Function time:\t\t %lf\n", fn_time);

    Clock_tic(clock);
    Matrix *fn_time = save_doubles(time_passed_sum_fn, 10);
    Matrix *loop_time = save_doubles(time_passed_sum_loop, 10);
    // Matrix_print(fn_time);
    Clock_toc(clock);
    // printf("Time taken to run test total: %lf\n", elapsed_time(clock));
    // printf("Avg time to compute sums: %lf\n", mean(fn_time));

    printf("Mean(fn_time): %lf\n", mean(fn_time));
    printf("Mean(loop_time): %lf\n", mean(loop_time));

    Matrix *rand_time = save_doubles(time_passed_rng, 100);

    printf("Rand unifd %d times in %lf seconds\n", N_RAND, mean(rand_time));


    Matrix_free(fn_time);
    Matrix_free(loop_time);
    Matrix_free(m);
    Matrix_free(b);
    free(clock);

    return 0;
}