#pragma once

// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

#include "matrix.h"

bool Matrix_valid_bounds(const Matrix *__m, size_t __i, size_t __j);

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(const Matrix *__A, const Matrix *__B);

// compare the bytes of the data using memcmp
bool matcmp_bytes(const Matrix *__A, const Matrix *__B);

// Are __A and __B compatible for addition?
bool Matrix_comp_add(const Matrix *__A, const Matrix *__B);

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(const Matrix *__A, const Matrix *__B);

size_t Matrix_size(const Matrix *__A);

bool Matrix_is_square(const Matrix *__A);

// return true if __A has one row
bool Matrix_is_row(const Matrix *__A);

// return true if __A has one column
bool Matrix_is_col(const Matrix *__A);

bool Matrix_is_vec(const Matrix *__A);

// Return the limiting dimension of __A.
size_t Matrix_rect_limit(const Matrix *__A);