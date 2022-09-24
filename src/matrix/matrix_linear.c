#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Unary MATRIX_T Operators
 *================================================================================================**/

MATRIX_T *MATRIX_FN(pow)(MATRIX_T * __A, size_t __power) {

    assert(MATRIX_FN(is_square)(__A));
    if ( __power == 0 ) {
        return MATRIX_FN(identity)(__A->nrows);
    }

    if ( __power == 1 ) {
        return MATRIX_FN(clone)(__A);
    }

MATRIX_T *m = MATRIX_FN(clone)(__A);

    for (size_t i = 2; i <= __power; i++) {
        MATRIX_FN(catch)(&m, MATRIX_FN(multiply)(__A, m));
    }

    return m;

}

// Create the n x n Vandermonde matrix
MATRIX_T *MATRIX_FN(vandermonde)(const Vector *__v) {

    size_t size = MATRIX_FN(size)(__v);
    MATRIX_T *V = MATRIX_FN(new)(size, size);

    // Set the first column to 1
    MATITER_FN(apply_set_k)(MATRIX_FN(col_begin)(V, 0), MATRIX_FN(col_end)(V, 0), 1.0);

    // Iterate through the columns
    for (size_t i = 1; i < size; i++) {
        MATITER_FN(apply_set_iter_pow)(MATRIX_FN(col_begin)(V, i), MATRIX_FN(col_end)(V, i), MATRIX_FN(begin)(__v), (double) i);
    }

    return V;
}

// A 1st degree polynomial has 2 points that completely characterise it
MATRIX_T *MATRIX_FN(vandermonde_reduced)(const Vector *__v, size_t __degree) {

    // Only create the first __degree + 1 columns
    size_t size = MATRIX_FN(size)(__v);
    MATRIX_T *Vr = MATRIX_FN(new)(size, __degree + 1);

    MATITER_FN(apply_set_k)(MATRIX_FN(col_begin)(Vr, 0), MATRIX_FN(col_end)(Vr, 0), 1.0);

    for (size_t i = 1; i < __degree + 1; i++) {
        MATITER_FN(apply_set_iter_pow)(MATRIX_FN(col_begin)(Vr, i), MATRIX_FN(col_end)(Vr, i), MATRIX_FN(begin)(__v), (double) i);
    }

    return Vr;
}


// recursive algorithm to compute the determinant of a matrix
double MATRIX_FN(det)(const MATRIX_T * __A) {

    assert(MATRIX_FN(is_square)(__A));

    double local_det = 0;
    MATRIX_T *minor = NULL;

    if (__A->ncols == 1 && __A->nrows == 1) {
        return MAT_FN(at)(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            MATRIX_FN(catch)(&minor, MATRIX_FN(minor)(__A, i, j));
            double cofactor = pow(-1.0, j)*MATRIX_FN(det)(minor);
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * MAT_FN(at)(__A, i, j);
        }

        MATRIX_FN(reset)(&minor);

    }

    return local_det;
}

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Vector Operators
 *================================================================================================**/

// MATRIX_T dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-MATRIX_T Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE MAT_FN(cdr_check)(const MATRIX_T *__A, const MATRIX_T *__B, size_t __irow, size_t __icol) {

    MATRIX_TYPE inner_product = 0;
    for (size_t i = 0; i < __A->ncols; i++) {
        inner_product += (MATRIX_FN(at)(__A, __irow, i) * MATRIX_FN(at)(__B, i, __icol));
    }
    return inner_product;
}

// Compute the dot product without checking any indices
// inline MATRIX_TYPE MAT_FN(cdr)(const MATRIX_T *__A, const MATRIX_T *__B, size_t __irow, size_t __icol) {
//         MATRIX_TYPE inner_product = 0;
//         for (size_t i = 0; i < __A->ncols; i++) {
//             inner_product += (MAT_FN(at)(__A, __irow, i) * MAT_FN(at)(__B, i, __icol));
//         }
//         return inner_product;
// }

// inline MATRIX_T *MAT_FN(mul)(const MATRIX_T *__A, const MATRIX_T *__B) {

//     MATRIX_T *product = MATRIX_FN(new)(__A->nrows, __B->ncols);

//     if (product){
//         for (size_t i = 0; i < __A->nrows; i++) {
//             for (size_t j = 0; j < __B->ncols; j++) {
//                 MAT_FN(set)(product, i, j, MAT_FN(cdr)(__A, __B, i, j));
//             }
//         }
//     }

//     return product;
// }

MATRIX_T * MATRIX_FN(multiply)(const MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_T *prod = NULL;

    if (MATRIX_FN(comp_mult)(__A, __B)) {
        prod = MAT_FN(mul)(__A, __B);
    } else {
        perror("Trying to multiply incompatible matrices");
    }

    return prod;
}

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void MAT_FN(add)(MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = MAT_FN(acc)(__A, i, j);
            b = MAT_FN(acc)(__B, i, j);

            *a += *b;
        }
    }
}

MATRIX_T *MATRIX_FN(add)(const MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_T *sum = NULL;

    if (MATRIX_FN(comp_add)(__A, __B)) {

        sum = MAT_FN(clone)(__A); // clone the matrix and modify this new matrix in place
        MAT_FN(add)(sum, __B);

    } else {

        perror("Trying to add two incompatible matrices");

    }

    return sum;
}

void MAT_FN(had)(MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = MAT_FN(acc)(__A, i, j);
            b = MAT_FN(acc)(__B, i, j);

            *a *= *b;
        }
    }
}

// Take the exponential hadamard ie {1, 2, 3} to the 3rd => {1, 8, 27}
void MAT_FN(hadexp)(MATRIX_T *__A, int __k) {

    // Iterate through the elements and raise them to an exponential
    // I should really implement a macro to get a foriterator loop....
    // Go through and replace all of the elements with their value raised to a power
    for (MATITER_T it = MATRIX_FN(begin)(__A); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__A)); it = MATITER_FN(next)(it)) {
        MATITER_FN(set)(it, pow(MATITER_FN(value)(it), __k)); // not bad huh??
    }
}

// Call hadamard multiplication, checking the indices with each access.
void MAT_FN(had_check)(MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = MAT_FN(acc_check)(__A, i, j);
            b = MAT_FN(acc_check)(__B, i, j);

            *a *= *b;
        }
    }
}

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
MATRIX_T *MATRIX_FN(hadamard)(const MATRIX_T *__A, const MATRIX_T *__B) {
    // Don't compute the product in place.
    if (!MATRIX_FN(comp_add)(__A, __B)) {
        perror("Cannot take the hadamard product of two incompatible matrices!");
    }
    // verify that the matrices can be added

    MATRIX_T *C = MAT_FN(clone)(__A);
    MAT_FN(had)(C, __B);

    return C;
}

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void MAT_FN(sub)(MATRIX_T *__A, const MATRIX_T *__B) {

    // MATRIX_TYPE *a = NULL;
    // MATRIX_TYPE *b = NULL;

    // for (size_t i = 0; i < __A->nrows; i++) {
    //     for (size_t j = 0; j < __A->ncols; j++) {

    //         a = MAT_FN(acc)(__A, i, j);
    //         b = MAT_FN(acc)(__B, i, j);

    //         *a -= *b;
    //     }
    // }

    // We are assuming that the shape of __A and __B is the same. 
    const size_t n = MATRIX_FN(size)(__A); 

    for (size_t i = 0; i < n; i++) {
        __A->data[i] -= __B->data[i];
    }
}

MATRIX_T *MATRIX_FN(subtract)(const MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_T *A = MATRIX_FN(clone)(__A);
    MAT_FN(sub)(A, __B);
    return A;
}

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using MatIter's
MATRIX_TYPE TYPED_FN(colnorm)(const MATITER_T __begin, const MATITER_T __end) {

    MATITER_T c = __begin;
    MATRIX_TYPE sum = 0;

    do {
        sum += MATITER_FN(value)(c) * MATITER_FN(value)(c);
        c = MATITER_FN(next)(c);
    } while(!MATITER_FN(cmp)(c, __end));

    return sqrt(sum);

}

// Calculate the norm of a specific column
MATRIX_TYPE MATRIX_FN(col_norm)(const MATRIX_T *__A, size_t __j) {

    MATITER_T begin = MATITER_FN(null)();
    MATITER_T end = MATITER_FN(null)();
    double out = 0;

    if (__j < __A->ncols) {
        begin = MATRIX_FN(col_begin)(__A, __j);
        end = MATRIX_FN(col_end)(__A, __j);
        out = TYPED_FN(colnorm)(begin, end);
        return out;
    } else {
        perror("Col requested exceeds bounds");
        return -1;
    }
}

void MAT_FN(normcol)(const MATITER_T __begin, const MATITER_T __end) {

    MATITER_T c = __begin;
    MATRIX_TYPE norm = TYPED_FN(colnorm)(__begin, __end);

    // now that we have calculated the norm, divide the columns values by the norm

    while (!MATITER_FN(cmp)(c, __end)) {
        *(c.ptr) /= norm;
        c = MATITER_FN(next)(c);
    }
    // *(c->ptr) /= norm;
}

void MAT_FN(normcols)(MATRIX_T *__A) {

    MATITER_T begin = MATITER_FN(null)();
    MATITER_T end = MATITER_FN(null)();

    for (size_t j = 0; j < __A->ncols; j++) {
        begin = MATRIX_FN(col_begin)(__A, j);
        end = MATRIX_FN(col_end)(__A, j);
        MAT_FN(normcol)(begin, end);
    }
}

void MATRIX_FN(normalize_col)(MATRIX_T *__A, size_t __j) {

    MATITER_T begin = MATITER_FN(null)();
    MATITER_T end = MATITER_FN(null)();

    if (__j < __A->ncols) {
        begin = MATRIX_FN(col_begin)(__A, __j);
        end = MATRIX_FN(col_end)(__A, __j);
        MAT_FN(normcol)(begin, end);
    } else {
        printf("selected column is out of bounds");
        return;
    }
}

void MATRIX_FN(normalize_cols)(MATRIX_T *__A) {
    MAT_FN(normcols)(__A);
}

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE MATRIX_FN(frobenius)(const MATRIX_T *__A) {
    return TYPED_FN(vecnorm)(__A);
}

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
MATRIX_T *MAT_FN(lu_nopivot)(MATRIX_T *__A) {

    // first step is to create an identity matrix that starts off being L
    // MATRIX_T *L = MATRIX_FN(identity)(__A->nrows);
    MATRIX_T *L = MATRIX_FN(id)(__A->nrows, __A->ncols);

    // Do a big for loop that is going to iterate through the diagonals of __A.
    // In order to do so, we should determine the smallest value of nrows and ncols
    const size_t dim_small = MATRIX_FN(rect_limit)(__A); //  smallest dimension of __A;
    MATRIX_TYPE pivot_value = 0;
    MATRIX_TYPE scaling_factor = 0;

    for (size_t d = 0; d < dim_small; d++) {

        // Now I want to iterate along down the column of __A(d, d);

        pivot_value = MAT_FN(at)(__A, d, d);

        for (size_t i = d + 1; i < __A->nrows; i++) {

            // for each row, the first thing I need to do is compute the scalar multiple,
            // which will always be the first element divided by the pivot

            scaling_factor = MAT_FN(at)(__A, i, d) / pivot_value;
            MAT_FN(set)(L, i, d, scaling_factor);
            MAT_FN(rowop_add_scaled)(__A, i, d, -scaling_factor, d);

        }
    }

    return L;

}

TYPED(LU) MATRIX_FN(lu)(const MATRIX_T *__A) {

    MATRIX_T *U = MATRIX_FN(clone)(__A);
    MATRIX_T *L = MAT_FN(lu_nopivot)(U);
    TYPED(LU) lu = {L, U};
    return lu;

}

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

MATRIX_T *MATRIX_FN(solve_lu)(const MATRIX_T *__A, const Vector *__b) {

    // printf("Entered matrix_solve\n");
    // MATRIX_FN(print)(__A);
    // MATRIX_FN(print)(__b);

    TYPED(LU) lu = MATRIX_FN(lu)(__A);

    // printf("L:\t");
    // MATRIX_FN(print)(lu.L);
    // printf("U:\t");
    // MATRIX_FN(print)(lu.U);

    // Not pivoting, if there are zeros on the pivot then I'm fucked

    // I need to perform "back substitution"
    // A = LU
    // Ax = LUx = b
    //
    // first step sovle Ly = b, where y = Ux
    // this is easy because L is LOWER triangular!

    Vector *y = VECTOR_FN(new)(__A->nrows);
    Vector *b = MATRIX_FN(clone)(__b);
    Vector *x = VECTOR_FN(new)(__A->nrows);

    MATRIX_TYPE b_i = 0;

    // traverse the lower matrix
    for (int i = 0; i < lu.L->nrows; i++) {

        // printf("i before loop: %d\n", i);
        b_i = MATRIX_FN(at)(__b, i, 0);
        // printf("traversing L");

        // traverse x_j
        for (int j = 0; j < i; j++) {
            // printf("i in loop: %d\n", i);

            // printf("processing i: %d, j: %d, b_i: %lf, lu_i,j: %lf\n", i, j, b_i, MATRIX_FN(at)(lu.L, i, j));
            // printf("Inner L");
            b_i -= MATRIX_FN(at)(y, j, 0) * MATRIX_FN(at)(lu.L, i, j);

        }

        MATRIX_FN(set)(y, i, 0, b_i / MATRIX_FN(at)(lu.L, i, i) );
    }

    // printf("L(y) = b ");
    // MATRIX_FN(print)(b);
    // printf("y: ");
    // MATRIX_FN(print)(y);

    // Now that we've solved for y, Solve Ux = y for x !

    MATRIX_TYPE y_i = 0;
    for (int i = lu.U->nrows - 1; i >= 0; i--) {

        y_i = MATRIX_FN(at)(y, i, 0);

        for (int j = lu.U->nrows - 1; j > i; j--) {

            // printf("Inner U");
            y_i -= MATRIX_FN(at)(lu.U, i, j) * MATRIX_FN(at)(x, j, 0);

        }

        MATRIX_FN(set)(x, i, 0, y_i / MATRIX_FN(at)(lu.U, i, i) );

    }

    MATRIX_FN(reset)(&y);
    MATRIX_FN(reset)(&b);
    MATRIX_FN(reset)(&(lu.L));
    MATRIX_FN(reset)(&(lu.U));

    return x;

}

// Return a matrix that contains the solutions tot Ax = B
// this matrix will be null if there are no solutions/infinitely many solutions
MATRIX_T *TYPED_FN(gausselim)(const MATRIX_T *__A, const MATRIX_T *__B) {

    if (!MATRIX_FN(is_square)(__A)) return NULL;

    MATRIX_T *aug = MATRIX_FN(ccat)(__A, __B);      // Create augmented matrix
    Index *ind = TYPED_FN(range)(0, __A->nrows - 1, 1); // keep track of indices to enable pivoting

    /**============================================
     *!               Row Reductions
     *=============================================**/
    // iterate through all of the columns except for the last one
    for (size_t j = 0; j < __A->ncols - 1; j++) {

        // Get index of the pivot (max element) in a slightly weird way.
        size_t pivot_index = j + MATRIX_FN(col_max_index_from_row)(aug, ind->data[j], j);
        double pivot_value = MATRIX_FN(at)(aug, ind->data[pivot_index], j);

        // make sure that the pivot_index is not zero.
        if (fabs(pivot_value) < EPS) {
            perror ("__A does not have full rank and thus no solutions exist. Returning NULL\n");
            return NULL;
        }

        TYPED_FN(Row_switch)(aug, ind, pivot_index, j);

        // Perform elementary row operations.
        for (size_t i = j + 1; i < __A->nrows; i++) {

            int row_index = ind->data[i];
            double scalar = -MATRIX_FN(at)(aug, row_index, j) / pivot_value;
            TYPED_FN(Row_addition_k)(aug, ind, i, j, scalar);

        }
    }

    /**============================================
     *!               Back substitution
     *=============================================**/
    MATRIX_T *x = MATRIX_FN(new)(__A->nrows, __B->ncols);
    double x_ij = 0;

    // Iterate through the columns of x
    for (int j = 0; j < x->ncols; j++) {
        // Traverse the indices vector backwards:
        for (int i = x->nrows - 1; i >= 0; i--) {

            x_ij = MATRIX_FN(at)(aug, ind->data[i], j + __A->ncols); // Initialize xi to bi,j

            for (int k = i; k < x->nrows - 1; k++) {
                x_ij -= MATRIX_FN(at)(x, k + 1, j) * MATRIX_FN(at)(aug, ind->data[i], k + 1);
            }

            double den = MATRIX_FN(at)(aug, ind->data[i], i);
            MATRIX_FN(set)(x, i, j, x_ij / den);
        }
    }

    MATRIX_FN(reset)(&ind);
    MATRIX_FN(reset)(&aug);

    return x;
}

// Compute the inverse of a matrix via gaussian elimination
MATRIX_T *MATRIX_FN(inverse)(const MATRIX_T *__A) {

    if (!MATRIX_FN(is_square)(__A)) {
        fprintf(stderr, "MATRIX_FN(inverse): MATRIX_T is not square; returning NULL\n");
        return NULL;
    }
    MATRIX_T *Id = MATRIX_FN(id)(__A->nrows, __A->ncols);
    MATRIX_T *inv = TYPED_FN(gausselim)(__A, Id);

    MATRIX_FN(reset)(&Id);
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
Vector *TYPED_FN(jacobi_iteration)(const MATRIX_T *__A, const Vector *__b, const Vector *__x0, MATRIX_TYPE __crit) {

    // let's start out by implementing the algorithm for x_1
    // I'll need a temporary x variable

    Vector *xk = MATRIX_FN(clone)(__x0);
    Vector *res = VECTOR_FN(new)(VECTOR_FN(size)(__b));

    MATRIX_TYPE res_i = 0;

    size_t nsteps = 0;
    bool all_res_pass = false;

    // Since jacobi uses the older x_0, I actually don't want to mutate them in place.
    // I want to create a second

    printf("Initial guess: ");
    MATRIX_FN(print)(__x0);

    while(nsteps < MAX_STEP_SIZE) {
    // for (size_t s = 0; s < 3; s++)
        // For jacobi iteration we have an initial guess, we have a residual,
        for (size_t i = 0; i < VECTOR_FN(size)(__b); i++) { // loop through the rows

            // compute the residual
            res_i = VECTOR_FN(at)(__b, i) - MAT_FN(cdr)(__A, xk, i, 0);
            res_i = res_i / MAT_FN(at)(__A, i, i);

            MATRIX_FN(set)(res, i, 0, res_i);

        }

        // printf("res: ");
        // MATRIX_FN(print)(res);
        MAT_FN(add)(xk, res); // perform x(k + 1) = x(k) + R/a, saving the contents in xk

        // printf("k: %d, xk: ", nsteps + 1);
        // MATRIX_FN(print)(xk);


        // if all the components of res are below the critical threshold __crit, stop iterating
        all_res_pass = true;
        for (size_t r = 0; r < VECTOR_FN(size)(res); r++) {
            if ( fabs(VECTOR_FN(at)(res, r)) > __crit ) {
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

    MATRIX_FN(free)(res);

    return xk;
}

// Now I want to implement Gaussian Elimination with pivoting for numerical stability

// I'll start off by introducing an elementary row operations interface.

// There are 3 elementary row operations. Let's also implement their column counterparts...
// These operation will operate on a matrix and modify the matrix in place!!!

// Here's one hiccup. I want these functions to accept A MATRIX_T with an accompanying index matrix.
// Therefore, Changing "row3" and "row2" is going to edit the elements of this index matrix. Let's see this
// in action

// typedef struct {

    // MATRIX_T *m;
    // Index  *ind;

// } OrderedMatrix;

// Interpret the order indices as the indices of the rows
// MATRIX_T *MATRIX_FN(from_row_order)(const OrderedMATRIX_T __m) {
//     return MATRIX_FN(extract_rows)(__m.m, __m.ind);
// }

// These elementary operations will be considered low level and don't consider checking bounds...
// void MATRIX_FN(switch_rows)(OrderedMATRIX_T m, size_t __r1, size_t __r2) {
void TYPED_FN(Row_switch)(const MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2) {

    double tmp = __ind->data[__r1];

    __ind->data[__r1] = __ind->data[__r2];
    __ind->data[__r2] = tmp;

}

void TYPED_FN(Row_multiply)(MATRIX_T *__m, Index *__ind, size_t __r, double __k) {

    // multiply the row pointed to by __ind->data[__r] with __k
    MATRIX_FN(mult_row_k)(__m, __ind->data[__r], __k);
}

// Modify the contents of __r1 by adding __r2 in place.
void TYPED_FN(Row_addition)(MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2) {

    MATITER_T r1 = MATRIX_FN(row_begin)(__m, __ind->data[__r1]);
    const MATITER_T end = MATRIX_FN(row_end)(__m, __ind->data[__r1]);
    MATITER_T r2 = MATRIX_FN(row_begin)(__m, __ind->data[__r2]);

    MATITER_FN(apply_add_iter)(r1, end, r2);
}

// r1 = r1 + k * r2
void TYPED_FN(Row_addition_k)(MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2, double __k) {

    MATITER_T r1 = MATRIX_FN(row_begin)(__m, __ind->data[__r1]);
    const MATITER_T end = MATRIX_FN(row_end)(__m, __ind->data[__r1]);
    MATITER_T r2 = MATRIX_FN(row_begin)(__m, __ind->data[__r2]);

    MATITER_FN(apply_add_iter_scaled)(r1, end, r2, __k);
}


// void MATRIX_FN(switch)