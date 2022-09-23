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

double compute_flops_On2(int n) {

    // Add two matrices together
    Clock *my_clock = Clock_new();

    Clock_tic(my_clock);
    Matrix *a = Matrix_value(n, n, 3.4);
    Matrix *b = Matrix_value(n, n, 1.3);
    
    Clock_toc(my_clock);

    double init_time = elapsed_time(my_clock);

    Clock_tic(my_clock);
    Matrix *c = Matrix_add(a, b); // Operation that has complexity O(n^2)
    Clock_toc(my_clock);
    double op_time = elapsed_time(my_clock); 
    double op_per_s = (n * n) / op_time;
    // printf("%d, %lf, %lf, %.5e\n", n, init_time, op_time, op_per_s);
    print_double_human(op_per_s);
    printf("FLOPS\n");
    free(my_clock);

    return op_time;
}

// Write a regression 
void write_regression(Vector *x, Vector *y) {

}

// [2.4 12.5 -2.4 18.9] -> 2.4*x**0 + 12.5*x**1 + -2.4*x**2 + 18.9*x**3
void print_polynomial(const Vector *a) {

    const size_t degree = length(a) - 1;

    for (int i = 0; i < degree; i++) {
        printf("%lf*x**%d + ", a->data[i], i);
    }

    printf("%lf*x**%d\n", a->data[degree], degree);

} 


double f(double x) {
    return 3.4 * pow(x, 3);
}

double f2(double x) {
    return 4.5 * pow(x, 5.8) + 15.3 * pow(x, 4.3) + 2.4 * pow(x, 1.8) + 3.4 * pow(x, .5);
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
    const int len = 20;

    Vector *N = reshape(logspace(1, 4, len), len, 1);
    Vector *op_times = Matrix_new(len, 1);

    // Matrix_print(N);
    // Matrix_print(op_times);

    // // Count the number of flops
    // printf("n, init_time, op_time, flops\n");
    for (int i = 0; i < length(N); i++) {
    //    compute_flops(N->data[i]); 
       op_times->data[i] = compute_flops_On2(N->data[i]); 
    }

    // Now we can actually write the N values and op_times to a file
    DataFrame *df = newDataFrame(newChainVar(2, "n", "op_times"), newSpaceVar(2, N, op_times));

    writeGP(df, "test_bench.gp");

    Vector *x = reshape(linspace(2, 100, 1000), 100, 1);
    // Vector *y = map(x, log);
    Vector *y = map(x, x_cubed);
    // Vector *y = Matrix_clone(x);

    Vector *a_lin = loglog_regression(N, op_times);
    Vector *a_log = linear_regression(N, op_times);
    // Vector *xy_lin = linear_regression(x, y);
    // Vector *xy_log = logistical_regression(x, y);
    Vector *x3_reg = least_squares(x, y, 3);
    Vector *x3_log = loglog_regression(x, y);
    Vector *fn_reg = least_squares(x, map(x, f), 3);
    Vector *f2_log = loglog_regression(x, map(x, f2));
    // Vector *

    print_polynomial(x3_log);
    print_polynomial(fn_reg);
    print_polynomial(f2_log);

    DataFrame *df2 = newDataFrame(newChainVar(4, "x", "y", "fx", "f2"),
        newSpaceVar(4, x, y, map(x, f), map(x, f2)));

    writeGP(df2, "test_bench2.gp");




    // Matrix_print(a_lin);
    // Matrix_print_fixed(a_log);
    // Matrix_print(xy_lin);
    // Matrix_print(xy_log);
    Matrix_print(x3_reg);
    Matrix_print(x3_log);
    Matrix_print(fn_reg);

    // for (int i = 0; i < length(N); i++) {
    //     printf("%d %lf\n", (int) N->data[i], op_times->data[i]);
    // }


    return 0;
}