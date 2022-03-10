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

int main() {

    ejovo_seed();

    /**========================================================================
     *!   Compute the dot product of sin and cos over the interval [0, 2PI]
     *========================================================================**/

    // Create a new Vector of x values from -pi to pi.
    Vector *x = Vector_linspace(-PI, PI, 5000);

    Vector *cosx = Vector_map(x, cos);
    Vector *sinx = Vector_map(x, sin);

    double dp = Vector_dot(cosx, sinx); // should be 0!!!

    printf("Dot product of sinx and cosx: %lf\n", dp);
    printf("Dot product of cosx and cosx: %lf\n", Vector_dot(cosx, cosx));
    printf("Dot product of sinx and sinx: %lf\n", Vector_dot(sinx, sinx));

    printf("x:    ");
    Vector_print_head(x, 30);

    printf("cosx: ");
    Vector_print_head(cosx, 30);

    printf("sinx: ");
    Vector_print_head(sinx, 30);

    /**========================================================================
     *! Alternatively, we can compute the dot product as a matrix multiplication
     *========================================================================**/

    Matrix *dp_m = Matrix_multiply(asrow(sinx), cosx); // Matrix_multiply returns a matrix

    // In this case, dp_m only has one element that we access with Matrix_first
    printf("Matrix multiplication dp: %lf\n", Matrix_first(dp_m));

    /**========================================================================
     *! We could even compute the dot product using element-wise multiplication
     *========================================================================**/
    Matrix *hadamard_product = Vector_hadamard(sinx, cosx);

    // Then, the sum of the hadamard_product is the dot product
    printf("Sum of element-wise multiplication: %lf\n", Vector_sum(hadamard_product));



    /**========================================================================
     *!                   Let's showcase some projections
     *========================================================================**/

    Vector *u = vector(3, 10.0, -1.3, 14.6);
    Vector *v = vector(3, 1.0, 2.0, 3.0);

    Matrix *proj_v = Vector_orthogonal_projection(v);

    Vector *proj_v_of_u = Vector_project_onto(u, v);
    Vector *proj_v_mat_u = Matrix_multiply(proj_v, u);


    Matrix_print(proj_v_of_u);
    Matrix_print(proj_v_mat_u);


    Vector_reset(&x);
    Vector_reset(&cosx);
    Vector_reset(&sinx);

    Matrix_anon_free(); // Free any leftover anonymous matrices

}