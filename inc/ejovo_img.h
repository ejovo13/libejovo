#ifndef EJOVO_IMG_H
#define EJOVO_IMG_H

// Provide functions that allow us to create a bitmap given a Img structure
#include <stdlib.h>

#include "ejovo_matrix_generic.h"


typedef struct {

    MATRIX_T *r;
    MATRIX_T *g;
    MATRIX_T *b;

} img_t;

// Make sure that all of the matricese are the same size
img_t *newImage(const MATRIX_T *r, const MATRIX_T *g, const MATRIX_T *b);

// Start off with a two dimensional matrix and fill in the values as gray
static inline img_t *newImageGrayscale(const MATRIX_T *gray) {
    return newImage(gray, gray, gray);
}



static inline MATRIX_TYPE at(const MATRIX_T *__A, size_t lin_index) {
    return __A->data[lin_index];
}

static inline MATRIX_TYPE *atp(const MATRIX_T *__A, size_t lin_index) {
    return &(__A->data[lin_index]);
}

// set value at the linear index
static inline MATRIX_T *MAT_FN(setlin)(MATRIX_T *A, size_t lin_index, MATRIX_TYPE val) {
    A->data[lin_index] = val;
    return A;
}

// Normalize via min_max (IN PLACE) a gray scale image from [min, max] to [0, 255]
MATRIX_T *normalize_minmax(MATRIX_T *A);

void writePPM(const img_t *img, const char *filename);

// img_t *toGrayscale(const imt_t *img) {

// }

#endif