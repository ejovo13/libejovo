// #include "matrix/matrix_linear.h"
#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Unary TYPED(Matrix) Operators
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_pow)(TYPED(Matrix) * __A, size_t __power) {

    assert(TYPED(Matrix_is_square)(__A));
    if ( __power == 0 ) {
        return TYPED(Matrix_identity)(__A->nrows);
    }

    if ( __power == 1 ) {
        return TYPED(Matrix_clone)(__A);
    }

TYPED(Matrix) *m = TYPED(Matrix_clone)(__A);

    for (size_t i = 2; i <= __power; i++) {
        TYPED(Matrix_catch)(&m, TYPED(Matrix_multiply)(__A, m));
    }

    return m;

}

// Create the n x n Vandermonde matrix
TYPED(Matrix) *TYPED(Matrix_vandermonde)(const TYPED(Vector)*__v) {

    size_t size = TYPED(Matrix_size)(__v);
    TYPED(Matrix) *V = TYPED(Matrix_new)(size, size);

    // Set the first column to 1
    TYPED(MatIter_apply_set_k)(TYPED(Matrix_col_begin)(V, 0), TYPED(Matrix_col_end)(V, 0), 1.0);

    // Iterate through the columns
    for (size_t i = 1; i < size; i++) {
        TYPED(MatIter_apply_set_iter_pow)(TYPED(Matrix_col_begin)(V, i), TYPED(Matrix_col_end)(V, i), TYPED(Matrix_begin)(__v), (double) i);
    }

    return V;
}

// A 1st degree polynomial has 2 points that completely characterise it
TYPED(Matrix) *TYPED(Matrix_vandermonde_reduced)(const TYPED(Vector)*__v, size_t __degree) {

    // Only create the first __degree + 1 columns
    size_t size = TYPED(Matrix_size)(__v);
    TYPED(Matrix) *Vr = TYPED(Matrix_new)(size, __degree + 1);

    TYPED(MatIter_apply_set_k)(TYPED(Matrix_col_begin)(Vr, 0), TYPED(Matrix_col_end)(Vr, 0), 1.0);

    for (size_t i = 1; i < __degree + 1; i++) {
        TYPED(MatIter_apply_set_iter_pow)(TYPED(Matrix_col_begin)(Vr, i), TYPED(Matrix_col_end)(Vr, i), TYPED(Matrix_begin)(__v), (double) i);
    }

    return Vr;
}


// recursive algorithm to compute the determinant of a matrix
double TYPED(Matrix_det)(const TYPED(Matrix) * __A) {

    assert(TYPED(Matrix_is_square)(__A));

    double local_det = 0;
    TYPED(Matrix) *minor = NULL;

    if (__A->ncols == 1 && __A->nrows == 1) {
        return TYPED(matat)(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            TYPED(Matrix_catch)(&minor, TYPED(Matrix_minor)(__A, i, j));
            double cofactor = pow(-1.0, j)*TYPED(Matrix_det)(minor);
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * TYPED(matat)(__A, i, j);
        }

        TYPED(Matrix_reset)(&minor);

    }

    return local_det;
}

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix- TYPED(Vector)Operators
 *================================================================================================**/

// TYPED(Matrix) dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-TYPED(Matrix) Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE TYPED(matcdr_check)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B, size_t __irow, size_t __icol) {

    MATRIX_TYPE inner_product = 0;
    for (size_t i = 0; i < __A->ncols; i++) {
        inner_product += (TYPED(Matrix_at)(__A, __irow, i) * TYPED(Matrix_at)(__B, i, __icol));
    }
    return inner_product;
}

// Compute the dot product without checking any indices
// inline MATRIX_TYPE TYPED(matcdr)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B, size_t __irow, size_t __icol) {
//         MATRIX_TYPE inner_product = 0;
//         for (size_t i = 0; i < __A->ncols; i++) {
//             inner_product += (TYPED(matat)(__A, __irow, i) * TYPED(matat)(__B, i, __icol));
//         }
//         return inner_product;
// }

// inline TYPED(Matrix) *TYPED(matmul)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

//     TYPED(Matrix) *product = TYPED(Matrix_new)(__A->nrows, __B->ncols);

//     if (product){
//         for (size_t i = 0; i < __A->nrows; i++) {
//             for (size_t j = 0; j < __B->ncols; j++) {
//                 TYPED(matset)(product, i, j, TYPED(matcdr)(__A, __B, i, j));
//             }
//         }
//     }

//     return product;
// }

TYPED(Matrix) * TYPED(Matrix_multiply)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    TYPED(Matrix) *prod = NULL;

    if (TYPED(Matrix_comp_mult)(__A, __B)) {
        prod = TYPED(matmul)(__A, __B);
    } else {
        perror("Trying to multiply incompatible matrices");
    }

    return prod;
}

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void TYPED(matadd)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = TYPED(matacc)(__A, i, j);
            b = TYPED(matacc)(__B, i, j);

            *a += *b;
        }
    }
}

TYPED(Matrix) *TYPED(Matrix_add)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    TYPED(Matrix) *sum = NULL;

    if (TYPED(Matrix_comp_add)(__A, __B)) {

        sum = TYPED(matclone)(__A); // clone the matrix and modify this new matrix in place
        TYPED(matadd)(sum, __B);

    } else {

        perror("Trying to add two incompatible matrices");

    }

    return sum;
}

void TYPED(mathad)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = TYPED(matacc)(__A, i, j);
            b = TYPED(matacc)(__B, i, j);

            *a *= *b;
        }
    }
}

// Take the exponential hadamard ie {1, 2, 3} to the 3rd => {1, 8, 27}
void TYPED(mathadexp)(TYPED(Matrix) *__A, int __k) {

    // Iterate through the elements and raise them to an exponential
    // I should really implement a macro to get a foriterator loop....
    // Go through and replace all of the elements with their value raised to a power
    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__A); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__A)); it = TYPED(MatIter_next)(it)) {
        TYPED(MatIter_set)(it, pow(TYPED(MatIter_value)(it), __k)); // not bad huh??
    }
}

// Call hadamard multiplication, checking the indices with each access.
void TYPED(mathad_check)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = TYPED(matacc_check)(__A, i, j);
            b = TYPED(matacc_check)(__B, i, j);

            *a *= *b;
        }
    }
}

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
TYPED(Matrix) *TYPED(Matrix_hadamard)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    // Don't compute the product in place.
    if (!TYPED(Matrix_comp_add)(__A, __B)) {
        perror("Cannot take the hadamard product of two incompatible matrices!");
    }
    // verify that the matrices can be added

    TYPED(Matrix) *C = TYPED(matclone)(__A);
    TYPED(mathad)(C, __B);

    return C;
}

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void TYPED(matsub)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    // MATRIX_TYPE *a = NULL;
    // MATRIX_TYPE *b = NULL;

    // for (size_t i = 0; i < __A->nrows; i++) {
    //     for (size_t j = 0; j < __A->ncols; j++) {

    //         a = TYPED(matacc)(__A, i, j);
    //         b = TYPED(matacc)(__B, i, j);

    //         *a -= *b;
    //     }
    // }

    // We are assuming that the shape of __A and __B is the same. 
    const size_t n = TYPED(Matrix_size)(__A); 

    for (size_t i = 0; i < n; i++) {
        __A->data[i] -= __B->data[i];
    }
}

TYPED(Matrix) *TYPED(Matrix_subtract)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    TYPED(Matrix) *A = TYPED(Matrix_clone)(__A);
    TYPED(matsub)(A, __B);
    return A;
}

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using MatIter's
MATRIX_TYPE TYPED(colnorm)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    TYPED(MatIter) c = __begin;
    MATRIX_TYPE sum = 0;

    do {
        sum += TYPED(MatIter_value)(c) * TYPED(MatIter_value)(c);
        c = TYPED(MatIter_next)(c);
    } while(!TYPED(MatIter_cmp)(c, __end));

    return sqrt(sum);

}

// Calculate the norm of a specific column
MATRIX_TYPE TYPED(Matrix_col_norm)(const TYPED(Matrix) *__A, size_t __j) {

    TYPED(MatIter) begin = TYPED(MatIter_null)();
    TYPED(MatIter) end = TYPED(MatIter_null)();
    double out = 0;

    if (__j < __A->ncols) {
        begin = TYPED(Matrix_col_begin)(__A, __j);
        end = TYPED(Matrix_col_end)(__A, __j);
        out = TYPED(colnorm)(begin, end);
        return out;
    } else {
        perror("Col requested exceeds bounds");
        return -1;
    }
}

void TYPED(matnormcol)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    TYPED(MatIter) c = __begin;
    MATRIX_TYPE norm = TYPED(colnorm)(__begin, __end);

    // now that we have calculated the norm, divide the columns values by the norm

    while (!TYPED(MatIter_cmp)(c, __end)) {
        *(c.ptr) /= norm;
        c = TYPED(MatIter_next)(c);
    }
    // *(c->ptr) /= norm;
}

void TYPED(matnormcols)(TYPED(Matrix) *__A) {

    TYPED(MatIter) begin = TYPED(MatIter_null)();
    TYPED(MatIter) end = TYPED(MatIter_null)();

    for (size_t j = 0; j < __A->ncols; j++) {
        begin = TYPED(Matrix_col_begin)(__A, j);
        end = TYPED(Matrix_col_end)(__A, j);
        TYPED(matnormcol)(begin, end);
    }
}

void TYPED(Matrix_normalize_col)(TYPED(Matrix) *__A, size_t __j) {

    TYPED(MatIter) begin = TYPED(MatIter_null)();
    TYPED(MatIter) end = TYPED(MatIter_null)();

    if (__j < __A->ncols) {
        begin = TYPED(Matrix_col_begin)(__A, __j);
        end = TYPED(Matrix_col_end)(__A, __j);
        TYPED(matnormcol)(begin, end);
    } else {
        printf("selected column is out of bounds");
        return;
    }
}

void TYPED(Matrix_normalize_cols)(TYPED(Matrix) *__A) {
    TYPED(matnormcols)(__A);
}

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE TYPED(Matrix_frobenius)(const TYPED(Matrix) *__A) {
    return TYPED(vecnorm)(__A);
}

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
TYPED(Matrix) *TYPED(matlu_nopivot)(TYPED(Matrix) *__A) {

    // first step is to create an identity matrix that starts off being L
    // TYPED(Matrix) *L = TYPED(Matrix_identity)(__A->nrows);
    TYPED(Matrix) *L = TYPED(Matrix_id)(__A->nrows, __A->ncols);

    // Do a big for loop that is going to iterate through the diagonals of __A.
    // In order to do so, we should determine the smallest value of nrows and ncols
    const size_t dim_small = TYPED(Matrix_rect_limit)(__A); //  smallest dimension of __A;
    MATRIX_TYPE pivot_value = 0;
    MATRIX_TYPE scaling_factor = 0;

    for (size_t d = 0; d < dim_small; d++) {

        // Now I want to iterate along down the column of __A(d, d);

        pivot_value = TYPED(matat)(__A, d, d);

        for (size_t i = d + 1; i < __A->nrows; i++) {

            // for each row, the first thing I need to do is compute the scalar multiple,
            // which will always be the first element divided by the pivot

            scaling_factor = TYPED(matat)(__A, i, d) / pivot_value;
            TYPED(matset)(L, i, d, scaling_factor);
            TYPED(matrowop_add_scaled)(__A, i, d, -scaling_factor, d);

        }
    }

    return L;

}

TYPED(LU) TYPED(Matrix_lu)(const TYPED(Matrix) *__A) {

    TYPED(Matrix) *U = TYPED(Matrix_clone)(__A);
    TYPED(Matrix) *L = TYPED(matlu_nopivot)(U);
    TYPED(LU) lu = {L, U};
    return lu;

}

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_solve_lu)(const TYPED(Matrix) *__A, const TYPED(Vector)*__b) {

    // printf("Entered matrix_solve\n");
    // TYPED(Matrix_print)(__A);
    // TYPED(Matrix_print)(__b);

    TYPED(LU) lu = TYPED(Matrix_lu)(__A);

    // printf("L:\t");
    // TYPED(Matrix_print)(lu.L);
    // printf("U:\t");
    // TYPED(Matrix_print)(lu.U);

    // Not pivoting, if there are zeros on the pivot then I'm fucked

    // I need to perform "back substitution"
    // A = LU
    // Ax = LUx = b
    //
    // first step sovle Ly = b, where y = Ux
    // this is easy because L is LOWER triangular!

    TYPED(Vector)*y = TYPED(Vector_new)(__A->nrows);
    TYPED(Vector)*b = TYPED(Matrix_clone)(__b);
    TYPED(Vector)*x = TYPED(Vector_new)(__A->nrows);

    MATRIX_TYPE b_i = 0;

    // traverse the lower matrix
    for (size_t i = 0; i < lu.L->nrows; i++) {

        // printf("i before loop: %d\n", i);
        b_i = TYPED(Matrix_at)(__b, i, 0);
        // printf("traversing L");

        // traverse x_j
        for (size_t j = 0; j < i; j++) {
            // printf("i in loop: %d\n", i);

            // printf("processing i: %d, j: %d, b_i: %lf, lu_i,j: %lf\n", i, j, b_i, TYPED(Matrix_at)(lu.L, i, j));
            // printf("Inner L");
            b_i -= TYPED(Matrix_at)(y, j, 0) * TYPED(Matrix_at)(lu.L, i, j);

        }

        TYPED(Matrix_set)(y, i, 0, b_i / TYPED(Matrix_at)(lu.L, i, i) );
    }

    // printf("L(y) = b ");
    // TYPED(Matrix_print)(b);
    // printf("y: ");
    // TYPED(Matrix_print)(y);

    // Now that we've solved for y, Solve Ux = y for x !

    MATRIX_TYPE y_i = 0;
    for (int i = lu.U->nrows - 1; i >= 0; i--) {

        y_i = TYPED(Matrix_at)(y, i, 0);

        for (int j = lu.U->nrows - 1; j > i; j--) {

            // printf("Inner U");
            y_i -= TYPED(Matrix_at)(lu.U, i, j) * TYPED(Matrix_at)(x, j, 0);

        }

        TYPED(Matrix_set)(x, i, 0, y_i / TYPED(Matrix_at)(lu.U, i, i) );

    }

    TYPED(Matrix_reset)(&y);
    TYPED(Matrix_reset)(&b);
    TYPED(Matrix_reset)(&(lu.L));
    TYPED(Matrix_reset)(&(lu.U));

    return x;

}

// Return a matrix that contains the solutions tot Ax = B
// this matrix will be null if there are no solutions/infinitely many solutions
TYPED(Matrix) *TYPED(gausselim)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    if (!TYPED(Matrix_is_square)(__A)) return NULL;

    TYPED(Matrix) *aug = TYPED(Matrix_ccat)(__A, __B);      // Create augmented matrix
    TYPED(Index) *ind = TYPED(range)(0, __A->nrows - 1, 1); // keep track of indices to enable pivoting

    /**============================================
     *!               Row Reductions
     *=============================================**/
    // iterate through all of the columns except for the last one
    for (size_t j = 0; j < __A->ncols - 1; j++) {

        // Get index of the pivot (max element) in a slightly weird way.
        size_t pivot_index = j + TYPED(Matrix_col_max_index_from_row)(aug, ind->data[j], j);
        double pivot_value = TYPED(Matrix_at)(aug, ind->data[pivot_index], j);

        // make sure that the pivot_index is not zero.
        if (fabs(pivot_value) < EPS) {
            perror ("__A does not have full rank and thus no solutions exist. Returning NULL\n");
            return NULL;
        }

        TYPED(Row_switch)(ind, pivot_index, j);

        // Perform elementary row operations.
        for (size_t i = j + 1; i < __A->nrows; i++) {

            int row_index = ind->data[i];
            double scalar = -TYPED(Matrix_at)(aug, row_index, j) / pivot_value;
            TYPED(Row_addition_k)(aug, ind, i, j, scalar);

        }
    }

    /**============================================
     *!               Back substitution
     *=============================================**/
    TYPED(Matrix) *x = TYPED(Matrix_new)(__A->nrows, __B->ncols);
    double x_ij = 0;

    // Iterate through the columns of x
    for (size_t j = 0; j < x->ncols; j++) {
        // Traverse the indices vector backwards:
        for (int i = x->nrows - 1; i >= 0; i--) {

            x_ij = TYPED(Matrix_at)(aug, ind->data[i], j + __A->ncols); // Initialize xi to bi,j

            for (size_t k = i; k < x->nrows - 1; k++) {
                x_ij -= TYPED(Matrix_at)(x, k + 1, j) * TYPED(Matrix_at)(aug, ind->data[i], k + 1);
            }

            double den = TYPED(Matrix_at)(aug, ind->data[i], i);
            TYPED(Matrix_set)(x, i, j, x_ij / den);
        }
    }

    TYPED(Matrix_reset)(&ind);
    TYPED(Matrix_reset)(&aug);

    return x;
}

// Compute the inverse of a matrix via gaussian elimination
TYPED(Matrix) *TYPED(Matrix_inverse)(const TYPED(Matrix) *__A) {

    if (!TYPED(Matrix_is_square)(__A)) {
        fprintf(stderr, "TYPED(Matrix_inverse): TYPED(Matrix) is not square; returning NULL\n");
        return NULL;
    }
    TYPED(Matrix) *Id = TYPED(Matrix_id)(__A->nrows, __A->ncols);
    TYPED(Matrix) *inv = TYPED(gausselim)(__A, Id);

    TYPED(Matrix_reset)(&Id);
    return inv;
}

/**================================================================================================
 *!                                        Iterative Algorithms
 *================================================================================================**/

/**
 * @brief Jacobi Iteration
 *
 * Jacobi iteration consists of solving for the diagonals (x_i) of each equation (the rows of A) when given
 * the equation Ax = b to solve.
 *
 * @param __A an Invertible matrix
 * @param __b a column or row Vector
 * @param __x0 Initial guess of the solution
 * @attention The parameter __b will be treated exclusively as a col vector to resolve the equation Ax = b,
 * where x and b are column vectors
 *
 * @returns a newly allocated vector
 *
 */
 TYPED(Vector)*TYPED(jacobi_iteration)(const TYPED(Matrix) *__A, const TYPED(Vector)*__b, const TYPED(Vector)*__x0, MATRIX_TYPE __crit) {

    // let's start out by implementing the algorithm for x_1
    // I'll need a temporary x variable

    TYPED(Vector)*xk = TYPED(Matrix_clone)(__x0);
    TYPED(Vector)*res = TYPED(Vector_new)(TYPED(Vector_size)(__b));

    MATRIX_TYPE res_i = 0;

    size_t nsteps = 0;
    bool all_res_pass = false;

    // Since jacobi uses the older x_0, I actually don't want to mutate them in place.
    // I want to create a second

    printf("Initial guess: ");
    TYPED(Matrix_print)(__x0);

    while(nsteps < MAX_STEP_SIZE) {
    // for (size_t s = 0; s < 3; s++)
        // For jacobi iteration we have an initial guess, we have a residual,
        for (size_t i = 0; i < TYPED(Vector_size)(__b); i++) { // loop through the rows

            // compute the residual
            res_i = TYPED(Vector_at)(__b, i) - TYPED(matcdr)(__A, xk, i, 0);
            res_i = res_i / TYPED(matat)(__A, i, i);

            TYPED(Matrix_set)(res, i, 0, res_i);

        }

        // printf("res: ");
        // TYPED(Matrix_print)(res);
        TYPED(matadd)(xk, res); // perform x(k + 1) = x(k) + R/a, saving the contents in xk

        // printf("k: %d, xk: ", nsteps + 1);
        // TYPED(Matrix_print)(xk);


        // if all the components of res are below the critical threshold __crit, stop iterating
        all_res_pass = true;
        for (size_t r = 0; r < TYPED(Vector_size)(res); r++) {
        #ifdef MATRIX_COMPLEX
            if ( cabs(TYPED(Vector_at)(res, r)) > cabs(__crit) ) {
        #else
            if ( TYPED(ejovo_fabs)(res->data[r]) > __crit ) {
        #endif
                all_res_pass = false;
            }
        }

        if (all_res_pass) {
            printf("Breaking at %ld steps\n", nsteps);
            break;
        }

        nsteps ++;
    }

    if (nsteps >= MAX_STEP_SIZE) perror("Jacobi iteration reached MAX_STEP_SIZE");

    printf("Jacobi iteration ran for %ld steps\n", nsteps);

    TYPED(Matrix_free)(res);

    return xk;
}

// Now I want to implement Gaussian Elimination with pivoting for numerical stability

// I'll start off by introducing an elementary row operations interface.

// There are 3 elementary row operations. Let's also implement their column counterparts...
// These operation will operate on a matrix and modify the matrix in place!!!

// Here's one hiccup. I want these functions to accept A TYPED(Matrix) with an accompanying index matrix.
// Therefore, Changing "row3" and "row2" is going to edit the elements of this index matrix. Let's see this
// in action

// typedef struct {

    // TYPED(Matrix) *m;
    // TYPED(Index)  *ind;

// } OrderedMatrix;

// Interpret the order indices as the indices of the rows
// TYPED(Matrix) *TYPED(Matrix_from_row_order)(const OrderedTYPED(Matrix) __m) {
//     return TYPED(Matrix_extract_rows)(__m.m, __m.ind);
// }

// These elementary operations will be considered low level and don't consider checking bounds...
// void TYPED(Matrix_switch_rows)(OrderedTYPED(Matrix) m, size_t __r1, size_t __r2) {
void TYPED(Row_switch)(TYPED(Index) *__ind, size_t __r1, size_t __r2) {

    double tmp = __ind->data[__r1];

    __ind->data[__r1] = __ind->data[__r2];
    __ind->data[__r2] = tmp;

}

void TYPED(Row_multiply)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r, double __k) {

    // multiply the row pointed to by __ind->data[__r] with __k
    TYPED(Matrix_mult_row_k)(__m, __ind->data[__r], __k);
}

// Modify the contents of __r1 by adding __r2 in place.
void TYPED(Row_addition)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r1, size_t __r2) {

    TYPED(MatIter) r1 = TYPED(Matrix_row_begin)(__m, __ind->data[__r1]);
    const TYPED(MatIter) end = TYPED(Matrix_row_end)(__m, __ind->data[__r1]);
    TYPED(MatIter) r2 = TYPED(Matrix_row_begin)(__m, __ind->data[__r2]);

    TYPED(MatIter_apply_add_iter)(r1, end, r2);
}

// r1 = r1 + k * r2
void TYPED(Row_addition_k)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r1, size_t __r2, double __k) {

    TYPED(MatIter) r1 = TYPED(Matrix_row_begin)(__m, __ind->data[__r1]);
    const TYPED(MatIter) end = TYPED(Matrix_row_end)(__m, __ind->data[__r1]);
    TYPED(MatIter) r2 = TYPED(Matrix_row_begin)(__m, __ind->data[__r2]);

    TYPED(MatIter_apply_add_iter_scaled)(r1, end, r2, __k);
}


// void TYPED(Matrix_switch)