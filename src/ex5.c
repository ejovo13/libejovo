// ecrire une fonction permettant de multiplier deux matrices. On n'oubliera pas de traiter les
// cas d'erreur

// Need to obviously implement a simple matrix class
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#ifndef MATRIX_TYPE
#define MATRIX_TYPE int
#endif
typedef struct mat_t {
    MATRIX_TYPE * data;
    size_t nrows;
    size_t ncols;
} Matrix;

Matrix * Matrix_new(int __nrows, int __ncols) {

    Matrix * x = (Matrix *) malloc(sizeof(Matrix));

    if ( __nrows > 0 && __ncols > 0) {
        MATRIX_TYPE * data = (MATRIX_TYPE *) calloc(__nrows * __ncols, sizeof(MATRIX_TYPE));
        x->data = data;
        if (data) { // if the data is allocated properly
            x->nrows = __nrows;
            x->ncols = __ncols;
        } else {
            x->nrows = 0;
            x->ncols = 0;
        }
    } else {
        x->data = NULL;
        x->nrows = 0;
        x->ncols = 0;
    }

    return x;
}

// Free the memory associated with the matrix and then free the pointer itself
void Matrix_free(Matrix * __A) {
    if (__A) {
        if (__A->data) {
            free(__A->data);
        }
        __A->ncols = 0;
        __A->nrows = 0;
        free(__A);
    }
}

bool Matrix_valid_bounds(Matrix * __m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
MATRIX_TYPE Matrix_at(Matrix * __m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {

        return __m->data[__i*__m->ncols + __j];

    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return 0;
    }

}

// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return 1;
    }
}

// return a pointer to the element at __m(__i, __j) [zero indexed]
MATRIX_TYPE * Matrix_access(Matrix * __m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return NULL;
    }

}

void Matrix_print(Matrix * __m) {

    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%3d ", Matrix_at(__m, i, j));
        }

        printf("|\n");
    }
}

void Matrix_summary(Matrix * __m) {
    printf("%lu x %lu matrix\n", __m->nrows, __m->ncols);
}


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE col_dot_row(Matrix * __A, Matrix * __B, size_t __irow, size_t __icol) {

    // We are assuming that __A and __B are compatible matrices for matrix multiplication
    MATRIX_TYPE inner_product = 0;

    for (size_t i = 0; i < __A->ncols; i++) {
        inner_product += (Matrix_at(__A, __irow, i) * Matrix_at(__B, i, __icol));
    }

    return inner_product;

}

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(Matrix * __A, Matrix * __B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    // check every element
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if ( Matrix_at(__A, i, j) != Matrix_at(__B, i, j) ) {
                return false;
            }
        }
    }
    return true;
}

// Are __A and __B compatible for addition?
bool Matrix_comp_add(Matrix * __A, Matrix * __B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(Matrix * __A, Matrix * __B) {
    return (__A->ncols == __B->nrows);
}

// Copy the bytes
// this is a utility function and should not be used by the end user
static bool matcpy(Matrix * __dest, Matrix * __src) {

    // Copy the bytes of __src->data into __dest->data
    memcpy(__dest->data, __src->data, sizeof(MATRIX_TYPE)*(__src->nrows * __src->nrows));
    __dest->ncols = __src->ncols;
    __dest->nrows = __src->nrows;
    if(__dest && __src && __dest->data) { // if all the pointers are not null, return true
        return  true;
    } else {
        return false;
    }
}


// copy the contents of matrix __src into __dest
Matrix * matclone(Matrix * __src) {

    Matrix * clone = NULL;

    clone = Matrix_new(__src->ncols, __src->nrows);
    if (clone) {
        matcpy(clone, __src);
    }

    return clone;
}

Matrix * matmul(Matrix * __A, Matrix * __B) {

    // if compatible, multiply the matrices

    // else, return Null pointer

    Matrix * product = NULL;

    if (Matrix_comp_mult(__A, __B)) {

        product = Matrix_new(__A->nrows, __B->ncols);

        if (product){
            for (size_t i = 0; i < __A->nrows; i++) {
                for (size_t j = 0; j < __B->ncols; j++) {
                    Matrix_set(product, i, j, col_dot_row(__A, __B, i, j));
                }
            }
        }
    }

    return product;
}
Matrix * Matrix_multiply(Matrix * __A, Matrix * __B) {
    return matmul(__A, __B);
}

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
Matrix * matadd(Matrix * __A, Matrix * __B) {

    Matrix * sum = NULL;

    if (Matrix_comp_add(__A, __B)) {

        sum = Matrix_new(__A->nrows, __B->ncols);

        if (sum) {
            for (size_t i = 0; i < __A->nrows; i++) {
                for (size_t j = 0; j < __A->ncols; j++) {
                    Matrix_set(sum, i, j, Matrix_at(__A, i, j) + Matrix_at(__B, i, j));
                }
            }
        }
    }

    return sum;
}

Matrix * Matrix_add(Matrix * __A, Matrix * __B) {
    return matadd(__A, __B);
}

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
Matrix * submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {

    // printf("Entered submat with i0: %lu if: %lu j0: %lu jf: %lu\n", __istart, __iend, __jstart, __jend);

    Matrix * sub = NULL;

    // if the upper bounds are lower than the starting bounds or if the upper indices are larger than the number of rows | cols, return null
    if (__iend < __istart || __jend < __jstart || __iend >= __A->nrows || __jend >= __A->ncols) {
        return sub;
    }

    // printf("First condition passed\n");

    size_t nrows = __iend - __istart + 1;
    size_t ncols = __jend - __jstart + 1;
    size_t irow = 0, icol = 0;

    sub = Matrix_new(nrows, ncols);


    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {

        for (size_t j = __jstart, icol = 0; j <= __jend; j++, icol++) {
            printf("Setting (%lu,%lu) to %d\n", irow, icol, Matrix_at(__A, i, j));
            Matrix_set(sub, irow, icol, Matrix_at(__A, i, j));
        }
    }

    return sub;
}

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {
    return submat(__A, __istart, __iend, __jstart, __jend);
}


int main(void) {

    Matrix *A = Matrix_new(1, 2);
    Matrix *B = Matrix_new(2, 1);
    Matrix *B_2 = Matrix_new(2, 1);

    Matrix_summary(A);
    Matrix_set(A, 0, 0, 2);
    Matrix_set(A, 0, 1, -1);
    Matrix_print(A);

    Matrix_summary(B);
    Matrix_set(B, 0, 0, 5);
    Matrix_set(B, 1, 0, 10);
    Matrix_print(B);

    Matrix_summary(B_2);
    Matrix_set(B_2, 0, 0, 5);
    Matrix_set(B_2, 1, 0, 10);
    Matrix_print(B_2);

    Matrix * C = matmul(B, A);
    assert(C);
    Matrix_summary(C);
    Matrix_print(C);

    Matrix * B_sum = matadd(B, B_2);
    assert(B_sum);
    Matrix_summary(B_sum);
    Matrix_print(B_sum);

    Matrix * C_sub = submat(C, 0, 1, 1,1);
    assert(C_sub);
    Matrix_summary(C_sub);
    Matrix_print(C_sub);

    Matrix_free(A);
    Matrix_free(B);
    Matrix_free(C);
    Matrix_free(B_sum);

    printf("Freed all matrices\n");


    return 0;
}