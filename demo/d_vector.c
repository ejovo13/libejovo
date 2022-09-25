/**========================================================================
 * ?                                ABOUT
 * @author         :  Evan Voyles
 * @email          :  ejovo13@yahoo.com
 * @repo           :
 * @createdOn      :
 * @description    : A sample program that shows how to use different vector
 *                   functions
 *========================================================================**/

#include "ejovo_matrix_generic.h"

// Function declaration for Vector_map_d function
double x_sq(double x);

int main() {

    ejovo_seed(); // Initialize rng with data from /dev/rand

    /**========================================================================
     *!   Compute the dot product of sin and cos over the interval [0, 2PI]
     *========================================================================**/

    // Create a new Vector_dof x values from -pi to pi.
    Vector_d*x = Vector_linspace_d(-PI, PI, 500);

    Vector_d*cosx = Vector_map_d(x, cos);
    Vector_d*sinx = Vector_map_d(x, sin);

    double dp = Vector_dot_d(cosx, sinx); // should be 0!!!

    printf("Dot product of sinx and cosx: %lf\n", dp);
    printf("Dot product of cosx and cosx: %lf\n", Vector_dot_d(cosx, cosx));
    printf("Dot product of sinx and sinx: %lf\n", Vector_dot_d(sinx, sinx));

    printf("x:    ");
    Vector_print_head_d(x, 30);

    printf("cosx: ");
    Vector_print_head_d(cosx, 30);

    printf("sinx: ");
    Vector_print_head_d(sinx, 30);

    /**========================================================================
     *! Alternatively, we can compute the dot product as a matrix multiplication
     *========================================================================**/

    Matrix_d *dp_m = Matrix_multiply_d(asrow_d(sinx), cosx); // Matrix_multiply_d returns a matrix

    // In this case, dp_m only has one element that we access with Matrix_first_d
    printf("Matrix_d multiplication dp: %lf\n", Matrix_first_d(dp_m));

    /**========================================================================
     *! We could even compute the dot product using element-wise multiplication
     *========================================================================**/
    Matrix_d *hadamard_product = Vector_hadamard_d(sinx, cosx);

    // Then, the sum of the hadamard_product is the dot product
    printf("Sum of element-wise multiplication: %lf\n", Vector_sum_d(hadamard_product));



    /**========================================================================
     *!                   Let's showcase some projections
     *========================================================================**/

    Vector_d*u = vector_d(3, 10.0, -1.3, 14.6);
    Vector_d*v = vector_d(3, 1.0, 2.0, 3.0);

    Matrix_d *proj_v = Vector_orthogonal_projection_d(v);

    Vector_d*proj_v_of_u = Vector_project_onto_d(u, v);
    Vector_d*proj_v_mat_u = Matrix_multiply_d(proj_v, u);

    // Both these projections are mathematically equal
    Matrix_print_d(proj_v_of_u);
    Matrix_print_d(proj_v_mat_u);


    /**========================================================================
     *!                Here's an example of the map functionality
     *========================================================================**/

    Vector_d*r = Vector_range_d(1, 50, 2);
    Vector_d*r_sq = Vector_map_d(r, x_sq);

    printf("r    :\t");
    Matrix_print_d(r);
    printf("r.^2 :\t");
    Matrix_print_d(r_sq);


    // This is largely unnecessary since at the end of the programs execution memory will stop. However, when writing your own routines
    // if is important to clean up matrices that are allocated temporarily during certain operations.
    Vector_reset_d(&x);
    Vector_reset_d(&cosx);
    Vector_reset_d(&sinx);
    Vector_reset_d(&r);
    Vector_reset_d(&r_sq);
    Vector_reset_d(&u);
    Vector_reset_d(&v);
    Vector_reset_d(&proj_v);
    Vector_reset_d(&proj_v_of_u);
    Vector_reset_d(&proj_v_mat_u);
    Vector_reset_d(&hadamard_product);
    Vector_reset_d(&dp_m);


    Matrix_anon_free_d(); // Free any leftover anonymous matrices

}

// Custom function for use with Vector_map_d
double x_sq(double x) {
    return x * x;
}