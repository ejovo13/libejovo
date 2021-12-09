#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Unary Matrix Operators
 *================================================================================================**/

Matrix *Matrix_pow(Matrix * __A, size_t __power) {

    assert(Matrix_is_square(__A));
    if ( __power == 0 ) {
        return Matrix_identity(__A->nrows);
    }

    if ( __power == 1 ) {
        return Matrix_clone(__A);
    }

    Matrix *m = Matrix_clone(__A);

    for (size_t i = 2; i <= __power; i++) {
        Matrix_catch(&m, Matrix_multiply(__A, m));
    }

    return m;

}


// recursive algorithm to compute the determinant of a matrix
double Matrix_det(const Matrix * __A) {

    assert(Matrix_is_square(__A));

    double local_det = 0;
    Matrix *minor = NULL;

    if (__A->ncols == 1 && __A->nrows == 1) {
        return matat(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            Matrix_catch(&minor, Matrix_minor(__A, i, j));
            double cofactor = pow(-1.0, j)*Matrix_det(minor);
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * matat(__A, i, j);
        }

        Matrix_reset(&minor);

    }

    return local_det;
}

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Vector Operators
 *================================================================================================**/

// Matrix dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-Matrix Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE matcdr_check(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {

    // #if MATRIX_TYPE == Complex

    //     MATRIX_TYPE inner_product = Complex_zero();
    //     for (size_t i = 0; i < __A->ncols; i++) {
    //         inner_product = Complex_add(inner_product, ())
    //     }

    // #else
        // We are assuming that __A and __B are compatible matrices for matrix multiplication
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (Matrix_at(__A, __irow, i) * Matrix_at(__B, i, __icol));
        }
        return inner_product;
    // #endif
}

// Compute the dot product without checking any indices
MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (matat(__A, __irow, i) * matat(__B, i, __icol));
        }
        return inner_product;
}

Matrix *matmul(const Matrix *__A, const Matrix *__B) {

    Matrix *product = Matrix_new(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                matset(product, i, j, matcdr(__A, __B, i, j));
            }
        }
    }

    return product;
}

Matrix * Matrix_multiply(const Matrix *__A, const Matrix *__B) {

    Matrix *prod = NULL;

    if (Matrix_comp_mult(__A, __B)) {
        prod = matmul(__A, __B);
    } else {
        perror("Trying to multiply incompatible matrices");
    }

    return prod;
}

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void matadd(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a += *b;
        }
    }
}

Matrix *Matrix_add(const Matrix *__A, const Matrix *__B) {

    Matrix *sum = NULL;

    if (Matrix_comp_add(__A, __B)) {

        sum = matclone(__A); // clone the matrix and modify this new matrix in place
        matadd(sum, __B);

    } else {

        perror("Trying to add two incompatible matrices");

    }

    return sum;
}

void mathad(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a *= *b;
        }
    }
}

// Call hadamard multiplication, checking the indices with each access.
void mathad_check(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc_check(__A, i, j);
            b = matacc_check(__B, i, j);

            *a *= *b;
        }
    }
}

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
Matrix *Matrix_hadamard(const Matrix *__A, const Matrix *__B) {
    // Don't compute the product in place.
    if (!Matrix_comp_add(__A, __B)) {
        perror("Cannot take the hadamard product of two incompatible matrices!");
    }
    // verify that the matrices can be added

    Matrix *C = matclone(__A);
    mathad(C, __B);

    return C;
}

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void matsub(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a -= *b;

        }
    }
}

Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B) {

    Matrix *A = Matrix_clone(__A);
    matsub(A, __B);
    return A;

}

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using ColIter's
MATRIX_TYPE colnorm(const ColIter *__begin, const ColIter *__end) {

    ColIter *c = ColIter_clone(__begin);
    MATRIX_TYPE sum = 0;

    do {
        sum += ColIter_value(c) * ColIter_value(c);
        ColIter_next(c);
    } while(!ColIter_cmp(c, __end));

    free(c);
    return sqrt(sum);

}

// Calculate the norm of a specific column
MATRIX_TYPE Matrix_col_norm(const Matrix *__A, size_t __j) {

    ColIter *begin = NULL;
    ColIter *end = NULL;
    double out = 0;

    if (__j < __A->ncols) {
        begin = Matrix_col_begin(__A, __j);
        end = Matrix_col_end(__A, __j);
        out = colnorm(begin, end);
        free(begin);
        free(end);
        return out;
    } else {
        perror("Col requested exceeds bounds");
        return -1;
    }
}

void matnormcol(const ColIter *__begin, const ColIter *__end) {

    ColIter *c = ColIter_clone(__begin);
    MATRIX_TYPE norm = colnorm(__begin, __end);

    // now that we have calculated the norm, divide the columns values by the norm

    while (!ColIter_cmp(c, __end)) {
        *(c->ptr) /= norm;
        ColIter_next(c);
    }
    free(c);
    // *(c->ptr) /= norm;
}

void matnormcols(Matrix *__A) {

    ColIter *begin = NULL;
    ColIter *end = NULL;

    for (size_t j = 0; j < __A->ncols; j++) {
        begin = Matrix_col_begin(__A, j);
        end = Matrix_col_end(__A, j);
        matnormcol(begin, end);
        free(begin);
        free(end);
    }
}

void Matrix_normalize_col(Matrix *__A, size_t __j) {

    ColIter *begin = NULL;
    ColIter *end = NULL;

    if (__j < __A->ncols) {
        begin = Matrix_col_begin(__A, __j);
        end = Matrix_col_end(__A, __j);
        matnormcol(begin, end);
        free(begin);
        free(end);
    } else {
        printf("selected column is out of bounds");
        return;
    }
}

void Matrix_normalize_cols(Matrix *__A) {
    matnormcols(__A);
}

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE Matrix_frobenius(const Matrix *__A) {
    return vecnorm(__A);
}

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
Matrix *matlu_nopivot(Matrix *__A) {

    // first step is to create an identity matrix that starts off being L
    Matrix *L = Matrix_identity(__A->nrows); // TODO I need to add support for rectangular identity matrices

    // Do a big for loop that is going to iterate through the diagonals of __A.
    // In order to do so, we should determine the smallest value of nrows and ncols
    const size_t dim_small = Matrix_rect_limit(__A); //  smallest dimension of __A;
    MATRIX_TYPE pivot_value = 0;
    MATRIX_TYPE scaling_factor = 0;

    for (size_t d = 0; d < dim_small; d++) {

        // Now I want to iterate along down the column of __A(d, d);

        pivot_value = matat(__A, d, d);

        for (size_t i = d + 1; i < __A->nrows; i++) {

            // for each row, the first thing I need to do is compute the scalar multiple,
            // which will always be the first element divided by the pivot

            scaling_factor = matat(__A, i, d) / pivot_value;
            matset(L, i, d, scaling_factor);
            matrowop_add_scaled(__A, i, d, -scaling_factor, d);

        }
    }

    return L;

}

LU Matrix_lu(const Matrix *__A) {

    Matrix *U = Matrix_clone(__A);
    Matrix *L = matlu_nopivot(U);
    LU lu = {L, U};
    return lu;

}

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

Matrix *Matrix_solve_lu(const Matrix *__A, const Vector *__b) {

    // printf("Entered matrix_solve\n");
    // Matrix_print(__A);
    // Matrix_print(__b);

    LU lu = Matrix_lu(__A);

    // printf("L:\t");
    // Matrix_print(lu.L);
    // printf("U:\t");
    // Matrix_print(lu.U);

    // Not pivoting, if there are zeros on the pivot then I'm fucked

    // I need to perform "back substitution"
    // A = LU
    // Ax = LUx = b
    //
    // first step sovle Ly = b, where y = Ux
    // this is easy because L is LOWER triangular!

    Vector *y = Vector_new(__A->nrows);
    Vector *b = Matrix_clone(__b);
    Vector *x = Vector_new(__A->nrows);

    MATRIX_TYPE b_i = 0;

    // traverse the lower matrix
    for (int i = 0; i < lu.L->nrows; i++) {

        // printf("i before loop: %d\n", i);
        b_i = Matrix_at(__b, i, 0);
        // printf("traversing L");

        // traverse x_j
        for (int j = 0; j < i; j++) {
            // printf("i in loop: %d\n", i);

            // printf("processing i: %d, j: %d, b_i: %lf, lu_i,j: %lf\n", i, j, b_i, Matrix_at(lu.L, i, j));
            // printf("Inner L");
            b_i -= Matrix_at(y, j, 0) * Matrix_at(lu.L, i, j);

        }

        Matrix_set(y, i, 0, b_i / Matrix_at(lu.L, i, i) );
    }

    // printf("L(y) = b ");
    // Matrix_print(b);
    // printf("y: ");
    // Matrix_print(y);

    // Now that we've solved for y, Solve Ux = y for x !

    MATRIX_TYPE y_i = 0;
    for (int i = lu.U->nrows - 1; i >= 0; i--) {

        y_i = Matrix_at(y, i, 0);

        for (int j = lu.U->nrows - 1; j > i; j--) {

            // printf("Inner U");
            y_i -= Matrix_at(lu.U, i, j) * Matrix_at(x, j, 0);

        }

        Matrix_set(x, i, 0, y_i / Matrix_at(lu.U, i, i) );

    }

    Matrix_reset(&y);
    Matrix_reset(&b);
    Matrix_reset(&(lu.L));
    Matrix_reset(&(lu.U));

    return x;

}




// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
Matrix *gausselim(Matrix *__A, const Matrix *__B) {

    // I think that gausselim performs LU decomposition in place while modifying the right hand side which is more
    // efficient for a single operation but not more efficient if we are going to solve Ax = b multiple times






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
Vector *jacobi_iteration(const Matrix *__A, const Vector *__b, const Vector *__x0, MATRIX_TYPE __crit) {

    // let's start out by implementing the algorithm for x_1
    // I'll need a temporary x variable

    Vector *xk = Matrix_clone(__x0);
    Vector *res = Vector_new(Vector_size(__b));

    MATRIX_TYPE res_i = 0;

    size_t nsteps = 0;
    bool all_res_pass = false;

    // Since jacobi uses the older x_0, I actually don't want to mutate them in place.
    // I want to create a second

    printf("Initial guess: ");
    Matrix_print(__x0);

    while(nsteps < MAX_STEP_SIZE) {
    // for (size_t s = 0; s < 3; s++) {
        // For jacobi iteration we have an initial guess, we have a residual,
        for (size_t i = 0; i < Vector_size(__b); i++) { // loop through the rows

            // compute the residual
            res_i = Vector_at(__b, i) - matcdr(__A, xk, i, 0);
            res_i = res_i / matat(__A, i, i);

            Matrix_set(res, i, 0, res_i);

        }

        // printf("res: ");
        // Matrix_print(res);
        matadd(xk, res); // perform x(k + 1) = x(k) + R/a, saving the contents in xk

        // printf("k: %d, xk: ", nsteps + 1);
        // Matrix_print(xk);


        // if all the components of res are below the critical threshold __crit, stop iterating
        all_res_pass = true;
        for (size_t r = 0; r < Vector_size(res); r++) {
            if ( fabs(Vector_at(res, r)) > __crit ) {
                all_res_pass = false;
            }
        }

        if (all_res_pass) {
            printf("Breaking at %d steps\n", nsteps);
            break;
        }

        nsteps ++;
    }

    if (nsteps >= MAX_STEP_SIZE) perror("Jacobi iteration reached MAX_STEP_SIZE");

    printf("Jacobi iteration ran for %d steps\n", nsteps);

    Matrix_free(res);

    return xk;
}


