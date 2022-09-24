#include "ejovo_img.h"

// Make sure that all of the matricese are the same size
img_t *newImage(const MATRIX_T *r, const MATRIX_T *g, const MATRIX_T *b) {

    if (MATRIX_FN(comp_add)(r, g) && MATRIX_FN(comp_add)(g, b)) { // If they are all the same size

        img_t *img = (img_t*) malloc(sizeof(img_t));
        img->r = MAT_FN(clone)(r);
        img->g = MAT_FN(clone)(g);
        img->b = MAT_FN(clone)(b); // Now I have my own copy and I can perform all the manipulations that I want

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
MATRIX_T *normalize_minmax(MATRIX_T *A) {
    // find the min and the max
    double low = min(A);
    double high = max(A);

    FOREACH(A) {
        // *(atp(A, i)) = 
        MAT_FN(setlin)(A, i, 255 * (at(A, i) - low) / (high - low));
    }
    // MAT_FN(setind)()
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
            buffer[0] = (int) MAT_FN(at)(img->r, i, j); // r value
            buffer[1] = (int) MAT_FN(at)(img->g, i, j); 
            buffer[2] = (int) MAT_FN(at)(img->b, i, j); 
            // fwrite((void *) buffer, sizeof(uint8_t), 3, file);
            fprintf(file, "%c%c%c", buffer[0], buffer[1], buffer[2]);

        , 
        continue;
    )

    fclose(file);

}