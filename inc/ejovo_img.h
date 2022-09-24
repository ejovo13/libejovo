
#pragma once

// Provide functions that allow us to create a bitmap given a Img structure
#include <stdlib.h>

#include "ejovo_matrix.h"


typedef struct {

    Matrix *r;
    Matrix *g;
    Matrix *b;

} img_t;

// Make sure that all of the matricese are the same size
img_t *newImage(const Matrix *r, const Matrix *g, const Matrix *b);

// Start off with a two dimensional matrix and fill in the values as gray
static inline img_t *newImageGrayscale(const Matrix *gray) {
    return newImage(gray, gray, gray);
}

#define FOREACH(MAT) for (size_t i = 0; i < Matrix_size(MAT); i++)


#define FORIJ(MAT, INIT_LOOP, INSIDE_LOOP, OUTSIDE_LOOP) \
    const __m = MAT->nrows; \
    const __n = MAT->ncols; \
        for (size_t i = 0; i < __m; i++) { \
        INIT_LOOP \
        for (size_t j = 0; j < __n; j++) {  \
            INSIDE_LOOP \
        } \
        OUTSIDE_LOOP\
    } \


static inline MATRIX_TYPE at(const Matrix *__A, size_t lin_index) {
    return __A->data[lin_index];
}

static inline MATRIX_TYPE *atp(const Matrix *__A, size_t lin_index) {
    return &(__A->data[lin_index]);
}

// set value at the linear index
static inline Matrix *matsetlin(Matrix *A, size_t lin_index, MATRIX_TYPE val) {
    A->data[lin_index] = val;
    return A;
}

// Normalize via min_max (IN PLACE) a gray scale image from [min, max] to [0, 255]
Matrix *normalize_minmax(Matrix *A);

void writePPM(const img_t *img, const char *filename);

// img_t *toGrayscale(const imt_t *img) {

// }

