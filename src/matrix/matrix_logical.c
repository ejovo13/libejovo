// This module contains essential routines to deal with a "logical" Matrix data type that is represented
// by A matrix that is UNIQUELY ones and zeros

#include "matrix_logical.h"

double TRUE = 1.0;
double FALSE = 0.0;

// A Logical Matrix shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// Matrix_as_logical(m, true_fn); as Matrix_as_logical will accept a
// predicate as an argument
double true_fn(double d) {
    return TRUE;
}

double NOT(double d) {
    if (d == FALSE) return TRUE;
    else return FALSE;
}

double AND(double a, double b) {
    return (a == TRUE) && (b == TRUE);
}

double OR(double a, double b) {
    return (a == TRUE) || (b == TRUE);
}

// First routine that I should implement is having the notion of "if the vector is logical"
bool Matrix_is_logical(const Matrix *__log) {

    // All of the elements MUST be either 1.0 or 0.0
    MatIter it = Matrix_begin(__log);
    MatIter end = Matrix_end(__log);
    double val = 0;

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {

        val = MatIter_value(it);
        if (!(val == TRUE || val == FALSE)) {
            // printf("%lf registered as different \n", val);
            return false;
        }
    }

    return true;
}


bool Vector_is_logical(const Vector *__log) {
    return Matrix_is_logical(__log);
}

// I need to be able to create logical vectors now...
int Matrix_mask_count(const Matrix *__mask) {
    return Vector_mask_count(__mask);
}

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int Vector_mask_count(const Vector *__mask) {

    if (!Matrix_is_logical(__mask)) return -1;

    return sum(__mask);
}

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
Matrix *Matrix_as_logical(const Matrix *__m, pred_fn __fn) {

    Matrix *log = matalloc(__m->nrows, __m->ncols);

    MatIter end = Matrix_end(__m);
    MatIter logit = Matrix_begin(log);

    // printf("logit points to: %lf\n", MatIter_value(logit));

    for (MatIter it = Matrix_begin(__m); !MatIter_cmp(it, end); it = MatIter_next(it), logit = MatIter_next(logit)) {
        // printf("Processing: %lf\n", MatIter_value(it));
        MatIter_set(logit, __fn(MatIter_value(it)));
    }

    return log;
}

Matrix *Matrix_as_true(const Matrix *__m) {
    return Matrix_as_logical(__m, true_fn);
}

// Wherever the mask is true, set __m to the __val
void matsetmask(Matrix *__m, const Matrix *__mask, MATRIX_TYPE __val) {

    MatIter it_mask = Matrix_begin(__mask);

    for (MatIter it = Matrix_begin(__m); !MatIter_cmp(it, Matrix_end(__m)); it = MatIter_next(it), it_mask = MatIter_next(it_mask)) {

        if (MatIter_value(it_mask) == TRUE) MatIter_set(it, __val);
    }
}

void matsetpred(Matrix *__m, pred_fn __predicate, MATRIX_TYPE __val) {

    for (MatIter it = Matrix_begin(__m); !MatIter_cmp(it, Matrix_end(__m)); it = MatIter_next(it)) {
        if (__predicate(MatIter_value(it)) == TRUE) MatIter_set(it, __val);
    }
}

// Return a column vector of elements that correspond to a particular mask
Vector *Matrix_filter_mask(const Matrix *__m, const Matrix *__mask) {

    // First thing to do is a forward pass to count the number of nonzeros
    int count = Vector_mask_count(__mask);

    // Now allocate a new column vector
    if (count == -1) return NULL;

    Vector *new = matalloc(count, 1);

    MatIter nit = Matrix_begin(new);
    MatIter mask_it = Matrix_begin(__mask);

    for (MatIter it = Matrix_begin(__m); !MatIter_cmp(it, Matrix_end(__m)); it = MatIter_next(it), mask_it = MatIter_next(mask_it)) {

        if (MatIter_value(mask_it) == TRUE) {
            MatIter_set(nit, MatIter_value(it));
            nit = MatIter_next(it);
        }
    }

    return new;
}

// return true if count == size of the mask
bool Logical_all(const Matrix *__mask) {
    return (Matrix_mask_count(__mask) == Matrix_size(__mask));
}

// return true is any of the logical components are true
bool Logical_any(const Matrix *__mask) {

    MatIter it = Matrix_begin(__mask);
    MatIter end = Matrix_end(__mask);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {
        if (MatIter_value(it) == TRUE) return true;
    }

    return false;
}

// Return !__mask
Logical *Logical_not(const Matrix *__mask) {
    return map(__mask, NOT);
}