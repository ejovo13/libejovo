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







uint8_t diff_u8(uint8_t a, uint8_t b);


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

// This function takes a bitmap and writes it to a PGM file to 
// be visualized
void writePGM(const Matrix_b *image, const char* filename);

void write_ppm_gray(const Matrix_i *image, const char *filename);

void write_ppm_gray_d(const Matrix_d *image, const char *filename);

void write_ppm_grayscale(const Matrix_i *image, const char *filename, double scale);

void write_ppm_color_minmax_d(const Matrix_d *image, const ColorPalette *cp, double min, double max, const char *filename);
// img_t *toGrayscale(const imt_t *img) {

// }

/**========================================================================
 *!                           uint8_t image processing
 *========================================================================**/
// Take a grayscale image and set to black if below a certain threshold,
// modifying the image in place
static inline Matrix_b *filterImage_(Matrix_b *img, uint8_t luminosity) {
    FORIJ(img,
        , 
        ///
        *matacc_b(img, i, j) = matat_b(img, i, j) < luminosity ? 0 : 255;
        ,
    )
    return img;
}

static inline Matrix_b *filterImage(const Matrix_b *img, uint8_t luminosity) {
    // First copy the img
    Matrix_b *img_copy = Matrix_clone_b(img);
    filterImage_(img_copy, luminosity);
    return img_copy;
}

// Compute the x gradient of a single image
Matrix_b *gradientX(const Matrix_b *img);

Matrix_b *gradientY(const Matrix_b *img); 

Matrix_b *gradientT(const Matrix_b *img_0, const Matrix_b *img_1);

// Compute the discrete laplacian, ignoring the border pixels
Matrix_b *laplacian(const Matrix_b *img);



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

optical_flow_t calc_optical_flow_hs(const Matrix_i *f0, const Matrix_i *f1, int nb_iter, double alpha);

Matrix_d *map2_d(const Matrix_d *__x, const Matrix_d *__y, function2_d __f_xy);

Matrix_i *d_to_i(const Matrix_d *dub);

double euler(double x, double y);

Matrix_i *img_x_gradient(const Matrix_i *frame);

Matrix_i *img_y_gradient(const Matrix_i *frame);

void update_flow_field(Matrix_d *u, Matrix_d *v, const Matrix_i* I_x, const Matrix_i* I_y, const Matrix_i* I_t, double alpha);

void save_optical_flow(const char *prefix, optical_flow_t flow);

Matrix_b *hornSchunckMagnitude(const Matrix_b *__f0, const Matrix_b *__f1, int nb_iter, double alpha);

Matrix_b *dToBitmap(const Matrix_d *__values, double min, double max);

Matrix_b *d_to_b(const Matrix_d *__values);

Matrix_d *opticalMagnitude(const optical_flow_t uv);

// We aren't calculating the discrete laplacian here instead we are doing a simple convolution by averaging the values to see if
// we can filter out the noise
Matrix_b *smoothFrame(const Matrix_b *frame);

#endif