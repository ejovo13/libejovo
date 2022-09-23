#include "ejovo.h"
#include <assert.h>
#include <stdbool.h>

size_t length(const Matrix *m) {
    return Matrix_size(m);
}

typedef struct {

    double t_initialize; // Allocating memory and stuff
    double t_operation;




} matrix_op_benchmark_t;

Matrix * reshape(Matrix *A, size_t m, size_t n) {
    A->nrows = m;
    A->ncols = n;
    return A;
}

typedef Matrix* (*mat_binop_fn) (const Matrix*, const Matrix*);

void time_matrix_times_vector(int n) {

    Clock *clock = Clock_new();
    Clock *clock2 = Clock_new();

    Clock_tic(clock2);
    // Create two new random matrices and then perform an operation on them
    Clock_tic(clock);
    // Matrix *a = Matrix_rand(n, n);
    // Matrix *b = Matrix_rand(n, n);

    Matrix *A = runif(n * n, 0, 1);
    Matrix *b = runif(n, 0, 1);
    reshape(A, n, n);
    reshape(b, n, 1);

    Clock_toc(clock);

    double init_time = elapsed_time(clock);
    // 

    Clock_tic(clock);
    Matrix *c = Matrix_multiply(A, b);
    Clock_toc(clock);
    Clock_toc(clock2);

    double op_time = elapsed_time(clock);
    double total_time = elapsed_time(clock2);

    // printf("=========================================\n");
    // printf("= %s(A, B)  squares matrices with n: %d\n", str, n);
    // printf("= \n");
    // printf("= Init time:\t %lf\n", init_time);
    // printf("= Op time:\t %lf\n", op_time);
    // printf("= Total time:\t %lf\n", total_time);
    printf("%d, %lf\n", n, op_time);

    free(clock);
    free(clock2);
    Matrix_free(A);
    Matrix_free(b);



}

void time_matrix_op(int n, mat_binop_fn binop, const char* str) {

    Clock *clock = Clock_new();
    Clock *clock2 = Clock_new();

    Clock_tic(clock2);
    // Create two new random matrices and then perform an operation on them
    Clock_tic(clock);
    // Matrix *a = Matrix_rand(n, n);
    // Matrix *b = Matrix_rand(n, n);

    Matrix *a = runif(n * n, 0, 1);
    Matrix *b = runif(n * n, 0, 1);
    reshape(a, n, n);
    reshape(b, n, n);

    Clock_toc(clock);

    double init_time = elapsed_time(clock);
    // 

    Clock_tic(clock);
    Matrix *c = binop(a, b);
    Clock_toc(clock);
    Clock_toc(clock2);

    double op_time = elapsed_time(clock);
    double total_time = elapsed_time(clock2);

    // printf("=========================================\n");
    // printf("= %s(A, B)  squares matrices with n: %d\n", str, n);
    // printf("= \n");
    // printf("= Init time:\t %lf\n", init_time);
    // printf("= Op time:\t %lf\n", op_time);
    // printf("= Total time:\t %lf\n", total_time);
    printf("%d, %lf\n", n, op_time);

    free(clock);
    free(clock2);
    Matrix_free(a);
    Matrix_free(b);
}

void print_double_human(double a) {

    if (fabs(a) < 1e3) {
        printf("%7.3lf", a);
        return;
    } 

    if (fabs(a) < 1e6) {
        printf("%7.3lf K", a / 1e3);
        return;
    }

    if (fabs(a) < 1e9) {
        printf("%7.3lf M", a / 1e6);
        return;
    }

    if (fabs(a) < 1e12) {
        printf("%7.3lf G", a / 1e9);
        return;
    }

    if (fabs(a) < 1e12) {
        printf("%7.3lf T", a / 1e12);
        return;
    }
}

void compute_flops_On(int n) {

    Clock *my_clock = Clock_new();

    Clock_tic(my_clock);
    Matrix *r = runif(n, 0, 1);
    Clock_toc(my_clock);

    double init_time = elapsed_time(my_clock);

    Clock_tic(my_clock);
    double somme = sum(r); // Here we performed N floating point operations
    Clock_toc(my_clock);
    double op_time = elapsed_time(my_clock); 
    double op_per_s = n / op_time;
    // printf("%d, %lf, %lf, %lf, %.5e\n", n, init_time, times->data[i], somme, op_per_s);
    print_double_human(op_per_s);
    printf("FLOPS\n");
    free(my_clock);
}

void compute_flops_On2(int n) {

    // Add two matrices together
    Clock *my_clock = Clock_new();

    Clock_tic(my_clock);
    Matrix *a = reshape(runif(n * n, 0, 1), n, n);
    Matrix *b = reshape(runif(n * n, 0, 1), n, n);
    
    Clock_toc(my_clock);

    double init_time = elapsed_time(my_clock);

    Clock_tic(my_clock);
    Matrix *c = Matrix_add(a, b); // Operation that has complexity O(n^2)
    Clock_toc(my_clock);
    double op_time = elapsed_time(my_clock); 
    double op_per_s = (n * n) / op_time;
    printf("%d, %lf, %lf, %.5e\n", n, init_time, op_time, op_per_s);
    print_double_human(op_per_s);
    printf("FLOPS\n");
    free(my_clock);



}

int main() {

    // Let's test some basic operations of an established array of sizes

    // Matrix *sizes = linspace()
    Matrix *sizes = logspace(2, 4, 10);

    ejovo_seed();

    #ifdef PCG_RANDOM
        DEFAULT_RNG = unif_pcg;
    #endif

    // Matrix_print(sizes); 

    // printf("n, op_times");
    for (int i = 0; i < length(sizes); i++) {

        // time_matrix_op(sizes->data[i], Matrix_add, "add"); // Oh, lol, these are both O(n^2)
        // time_matrix_op(sizes->data[i], Matrix_multiply, "times");
        // time_matrix_times_vector(sizes->data[i]); // O(n^2)

    }

    // Compute the number of addition flops by adding two row 
    // vectors of size n
    // Vector *N = logspace(1, 9, 9);
    Vector *N = logspace(1, 4, 9);
    Vector *times = Matrix_new(1, length(N));

    // Count the number of flops
    printf("n, init_time, op_time, flops\n");
    for (int i = 0; i < length(N); i++) {
    //    compute_flops(N->data[i]); 
       compute_flops_On2(N->data[i]); 
    }


    return 0;
}