/**========================================================================
 * ?                                ABOUT
 * @author         :  Evan Voyles
 * @email          :  ejovo13@yahoo.com
 * @repo           :
 * @createdOn      :
 * @description    : A sample program that shows how to use different vector
 *                   functions
 *========================================================================**/

#include "ejovo_matrix.h"

// Function declaration for VECTOR_FN(map) function
double x_sq(double x);

int main() {

    ejovo_seed(); // Initialize rng with data from /dev/rand

    /**========================================================================
     *!   Compute the dot product of sin and cos over the interval [0, 2PI]
     *========================================================================**/

    // Create a new Vector of x values from -pi to pi.
    Vector *x = VECTOR_FN(linspace)(-PI, PI, 500);

    Vector *cosx = VECTOR_FN(map)(x, cos);
    Vector *sinx = VECTOR_FN(map)(x, sin);

    double dp = VECTOR_FN(dot)(cosx, sinx); // should be 0!!!

    printf("Dot product of sinx and cosx: %lf\n", dp);
    printf("Dot product of cosx and cosx: %lf\n", VECTOR_FN(dot)(cosx, cosx));
    printf("Dot product of sinx and sinx: %lf\n", VECTOR_FN(dot)(sinx, sinx));

    printf("x:    ");
    VECTOR_FN(print_head)(x, 30);

    printf("cosx: ");
    VECTOR_FN(print_head)(cosx, 30);

    printf("sinx: ");
    VECTOR_FN(print_head)(sinx, 30);

    /**========================================================================
     *! Alternatively, we can compute the dot product as a matrix multiplication
     *========================================================================**/

    MATRIX_T *dp_m = MATRIX_FN(multiply)(asrow(sinx), cosx); // MATRIX_FN(multiply) returns a matrix

    // In this case, dp_m only has one element that we access with MATRIX_FN(first)
    printf("MATRIX_T multiplication dp: %lf\n", MATRIX_FN(first)(dp_m));

    /**========================================================================
     *! We could even compute the dot product using element-wise multiplication
     *========================================================================**/
    MATRIX_T *hadamard_product = VECTOR_FN(hadamard)(sinx, cosx);

    // Then, the sum of the hadamard_product is the dot product
    printf("Sum of element-wise multiplication: %lf\n", VECTOR_FN(sum)(hadamard_product));



    /**========================================================================
     *!                   Let's showcase some projections
     *========================================================================**/

    Vector *u = vector(3, 10.0, -1.3, 14.6);
    Vector *v = vector(3, 1.0, 2.0, 3.0);

    MATRIX_T *proj_v = VECTOR_FN(orthogonal_projection)(v);

    Vector *proj_v_of_u = VECTOR_FN(project_onto)(u, v);
    Vector *proj_v_mat_u = MATRIX_FN(multiply)(proj_v, u);

    // Both these projections are mathematically equal
    MATRIX_FN(print)(proj_v_of_u);
    MATRIX_FN(print)(proj_v_mat_u);


    /**========================================================================
     *!                Here's an example of the map functionality
     *========================================================================**/

    Vector *r = VECTOR_FN(range)(1, 50, 2);
    Vector *r_sq = VECTOR_FN(map)(r, x_sq);

    printf("r    :\t");
    MATRIX_FN(print)(r);
    printf("r.^2 :\t");
    MATRIX_FN(print)(r_sq);


    // This is largely unnecessary since at the end of the programs execution memory will stop. However, when writing your own routines
    // if is important to clean up matrices that are allocated temporarily during certain operations.
    VECTOR_FN(reset)(&x);
    VECTOR_FN(reset)(&cosx);
    VECTOR_FN(reset)(&sinx);
    VECTOR_FN(reset)(&r);
    VECTOR_FN(reset)(&r_sq);
    VECTOR_FN(reset)(&u);
    VECTOR_FN(reset)(&v);
    VECTOR_FN(reset)(&proj_v);
    VECTOR_FN(reset)(&proj_v_of_u);
    VECTOR_FN(reset)(&proj_v_mat_u);
    VECTOR_FN(reset)(&hadamard_product);
    VECTOR_FN(reset)(&dp_m);


    MATRIX_FN(anon_free)(); // Free any leftover anonymous matrices

}

// Custom function for use with VECTOR_FN(map)
double x_sq(double x) {
    return x * x;
}