#ifndef EJOVO_IMG_H
#define EJOVO_IMG_H

// Provide functions that allow us to create a bitmap given a Img structure
#include <stdlib.h>
#include "ejovo_matrix_generic.h"

// #include "matrix/matrix_i.h"


typedef struct {

    Matrix_d *r;
    Matrix_d *g;
    Matrix_d *b;

} img_t;

// Make sure that all of the matricese are the same size
img_t *newImage(const Matrix_d *r, const Matrix_d *g, const Matrix_d *b);

// Start off with a two dimensional matrix and fill in the values as gray
static inline img_t *newImageGrayscale(const Matrix_d *gray) {
    return newImage(gray, gray, gray);
}


static inline double atd(const Matrix_d *__A, size_t lin_index) {
    return __A->data[lin_index];
}

static inline float atf(const Matrix_f *__A, size_t lin_index) {
    return __A->data[lin_index];
}

static inline int ati(const Matrix_i *__A, size_t lin_index) {
    return __A->data[lin_index];
}

static inline int*atp(const Matrix_i *__A, size_t lin_index) {
    return &(__A->data[lin_index]);
}

// // set value at the linear index
// static inline Matrix_i *TYPED(matsetlin)(Matrix_i *A, size_t lin_index, int val) {
//     A->data[lin_index] = val;
//     return A;
// }

// Normalize via min_max (IN PLACE) a gray scale image from [min, max] to [0, 255]
Matrix_d *normalize_minmax(Matrix_d *A);

void writePPM(const img_t *img, const char *filename);

// img_t *toGrayscale(const imt_t *img) {

// }

#endif