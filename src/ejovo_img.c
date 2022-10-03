#include "ejovo_img.h"

// Make sure that all of the matricese are the same size
img_t *newImage(const Matrix_d *r, const Matrix_d *g, const Matrix_d *b) {

    if (Matrix_comp_add_d(r, g) && Matrix_comp_add_d(g, b)) { // If they are all the same size

        img_t *img = (img_t*) malloc(sizeof(img_t));
        img->r = matclone_d(r);
        img->g = matclone_d(g);
        img->b = matclone_d(b); // Now I have my own copy and I can perform all the manipulations that I want

        return img;

    }

    return NULL;    
}

size_t imageWidth(const img_t *img) {
    return img->b->ncols;
}

size_t imageHeight(const img_t *img) {
    return img->b->nrows;
}


// Normalize via min_max (IN PLACE) a gray scale image from [min, max] to [0, 255]
// Take a DOUBLE MATRIX and return an INTEGER MATRIX
Matrix_d *normalize_minmax(Matrix_d *A) {
    // find the min and the max
    double low = min_d(A);
    double high = max_d(A);

    FOREACH(A) {
        // *(atp(A, i)) = 
        Vector_set_d(A, i, 255 * (atd(A, i) - low) / (high - low));
    }
    // matsetind_i()
    return A;
}

void writePPM(const img_t *img, const char *filename) {
    FILE *file, *file_bin;
    // Start off the first couple lines with ASCII
    file = fopen(filename, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%zu %zu\n", imageWidth(img), imageHeight(img));
    fprintf(file, "255\n");
    // fclose(file);

    // file_bin = fopen(filename, "ab");
    // file = fopen(filename, "ab");
    
    FORIJ(img->b
        , 
        uint8_t buffer[3]; // write 3 bytes at time
            ,
            // fill the buffer
            buffer[0] = (int) matat_d(img->r, i, j); // r value
            buffer[1] = (int) matat_d(img->g, i, j); 
            buffer[2] = (int) matat_d(img->b, i, j); 
            // fwrite((void *) buffer, sizeof(uint8_t), 3, file);
            fprintf(file, "%c%c%c", buffer[0], buffer[1], buffer[2]);

        , 
        continue;
    );

    fclose(file);

}

void write_ppm_gray(const Matrix_i *image, const char *filename) {

    FILE *file, *file_bin;
    // Start off the first couple lines with ASCII
    file = fopen(filename, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%zu %zu\n", image->ncols, image->nrows);
    fprintf(file, "255\n");
    // fclose(file);

    // file_bin = fopen(filename, "ab");
    // file = fopen(filename, "ab");
    
    FORIJ(image
        ,
            ,
            char pixel = matat_i(image, i, j);
            fprintf(file, "%c%c%c", pixel, pixel, pixel);

        , 
        continue;
    );

    fclose(file);


}

void write_ppm_gray_d(const Matrix_d *image, const char *filename) {

    FILE *file, *file_bin;
    // Start off the first couple lines with ASCII
    file = fopen(filename, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%zu %zu\n", image->ncols, image->nrows);
    fprintf(file, "255\n");
    // fclose(file);

    // file_bin = fopen(filename, "ab");
    // file = fopen(filename, "ab");
    
    FORIJ(image
        ,
            ,
            char pixel = matat_d(image, i, j);
            fprintf(file, "%c%c%c", pixel, pixel, pixel);

        , 
        continue;
    );

    fclose(file);

}

// If we know the max value (for example 100), then we can 
// scale the output image by multiplying by (255 / 100)
void write_ppm_grayscale(const Matrix_i *image, const char *filename, double scaling) {

    FILE *file, *file_bin;
    // Start off the first couple lines with ASCII
    file = fopen(filename, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%zu %zu\n", image->ncols, image->nrows);
    fprintf(file, "255\n");
    // fclose(file);

    // file_bin = fopen(filename, "ab");
    // file = fopen(filename, "ab");
    
    FORIJ(image
        ,
            ,
            char pixel = matat_i(image, i, j) * scaling;
            fprintf(file, "%c%c%c", pixel, pixel, pixel);

        , 
        continue;
    );

    fclose(file);



}



