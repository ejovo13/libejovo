#ifndef EJOVO_IMG_H
#define EJOVO_IMG_H

// Provide functions that allow us to create a bitmap given a Img structure
#include <stdlib.h>
#include "ejovo_matrix_generic.h"
#include "ejovo_color.h"
#include "ejovo_string.h"

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

void write_ppm_gray(const Matrix_i *image, const char *filename);

void write_ppm_gray_d(const Matrix_d *image, const char *filename);

void write_ppm_grayscale(const Matrix_i *image, const char *filename, double scale);

void write_ppm_color_minmax_d(const Matrix_d *image, const ColorPalette *cp, double min, double max, const char *filename);
// img_t *toGrayscale(const imt_t *img) {

// }


/**========================================================================
 *!                           PGM functionality for optical flow
 *========================================================================**/
Matrix_i *read_pgm(const char *filename);


typedef struct optical_flow_t {

    Matrix_d *u;
    Matrix_d *v;
    Matrix_i *Ix;
    Matrix_i *Iy;
    Matrix_i *It;

} optical_flow_t;

typedef double (* function2_d) (double, double);

optical_flow_t calc_optical_flow_hs(const Matrix_i *f0, const Matrix_i *f1, int nb_iter);

Matrix_d *map2_d(const Matrix_d *__x, const Matrix_d *__y, function2_d __f_xy);

Matrix_i *d_to_i(const Matrix_d *dub);

double euler(double x, double y);

Matrix_i *img_x_gradient(const Matrix_i *frame);

Matrix_i *img_y_gradient(const Matrix_i *frame);

void update_flow_field(Matrix_d *u, Matrix_d *v, const Matrix_i* I_x, const Matrix_i* I_y, const Matrix_i* I_t);

void save_optical_flow(const char *prefix, optical_flow_t flow);
#endif