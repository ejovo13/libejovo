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
        A->data[i] = 255 * (atd(A, i) - low) / (high - low);
    }
    // matsetind_i()
    return A;
}

void writePPM(const img_t *img, const char *filename) {
    FILE *file;
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

    FILE *file;
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

    FILE *file;
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

    FILE *file;
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

// Write a Matrix_d to a .ppm file using a mapping from [min, max] -> [0, 255] and then applying 
// a color palette
void write_ppm_color_minmax_d(const Matrix_d *image, const ColorPalette *cp, double min, double max, const char *filename) {

    // First thing to do is simply create the color palette
    Matrix_i *colors = ColorPalette_to_matrix(cp, 256);

    FILE *file;
    // Start off the first couple lines with ASCII
    file = fopen(filename, "w");
    fprintf(file, "P6\n");
    fprintf(file, "%zu %zu\n", image->ncols, image->nrows);
    fprintf(file, "255\n");
    // fclose(file);

    // file_bin = fopen(filename, "ab");
    // file = fopen(filename, "ab");
    int color_index = 0;
    double scaling = 255.0 / (max - min);
    
    for (size_t i = 0; i < image->nrows; i++) {
        for (size_t j = 0; j < image->ncols; j++) {

            // compute the color index based on the value
            color_index = matat_d(image, i, j) * scaling;

            char r = matat_i(colors, color_index, 0);
            char g = matat_i(colors, color_index, 1);
            char b = matat_i(colors, color_index, 2);
            fprintf(file, "%c%c%c", r, g, b);

        }
    }

    fclose(file);

}

Matrix_d *map2_d(const Matrix_d *__x, const Matrix_d *__y, function2_d __f_xy) {

    assert(Matrix_size_d(__x) == Matrix_size_d(__y));
    Matrix_d *out = Matrix_new_d(__x->nrows, __x->ncols);

    for (size_t i = 0; i < __x->nrows; i++) {
        for (size_t j = 0; j < __x->ncols; j++) {
            double x = matat_d(__x, i, j);
            double y = matat_d(__y, i, j);
            matset_d(out, i, j, __f_xy(x, y));
        }
    }

    return out;
}

Matrix_i *d_to_i(const Matrix_d *dub) {
    Matrix_i *out = Matrix_new_i(dub->nrows, dub->ncols);
    
    for (size_t i = 0; i < dub->nrows; i++) {
        for (size_t j = 0; j < dub->ncols; j++) {
            *matacc_i(out, i, j) = matat_d(dub, i, j); 
        }
    }

    return out;
}

double euler(double x, double y) {
    return sqrt(x * x + y * y);
}


Matrix_i *read_pgm(const char *filename) {

    int im_w = 0, im_h = 0;
    int version = 0;
    int num_colors = 0;

    // First read the header
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
    }


    if (fscanf(file, "P%d", &version) == 1) {
        // success
        printf("Version: %d\n", version);
    } else {
        exit(1);
    }

    // printf("Running in read_pgm\n");

    fscanf(file, "%d %d", &im_w, &im_h);
    fscanf(file, "%d\n", &num_colors);
    // printf("%d colors\n", num_colors);

    int cur_pos = ftell(file);

    // printf("Current pos: %d bytes\n", cur_pos);
    
    fclose(file);
    file = fopen(filename, "rb");
    fseek(file, cur_pos, SEEK_CUR);

    Matrix_i *im = Matrix_new_i(im_h, im_w);

    Matrix_summary_i(im);
    uint8_t byte;

    for (size_t i = 0; i < im->nrows; i++) {
        for (size_t j = 0; j < im->ncols; j++) {
            // read a single byte
            fread(&byte, sizeof(byte), 1, file);
            matset_i(im, i, j, (int) byte); 
        }
    }

    return im;
}

Matrix_i *img_x_gradient(const Matrix_i *frame) {

    Matrix_i *I_x = Matrix_new_i(frame->nrows, frame->ncols);

    for (size_t i = 0; i < frame->nrows; i++) {
        for (size_t j = 0; j < frame->ncols - 1; j++) {
            int x  = matat_i(frame, i, j);
            int xi = matat_i(frame, i, j + 1); 
            matset_i(I_x, i, j, xi - x);
        }
    }

    return I_x;
}

Matrix_i *img_y_gradient(const Matrix_i *frame) {

    Matrix_i *I_y = Matrix_new_i(frame->nrows, frame->ncols);
    // For x, we can only go to the second to last col
    for (size_t i = 0; i < frame->nrows - 1; i++) {
        for (size_t j = 0; j < frame->ncols; j++) {
            int y  = matat_i(frame, i, j);
            int yi = matat_i(frame, i + 1, j); 
            matset_i(I_y, i, j, yi - y);
        }
    }

    return I_y;
}

double local_average(const Matrix_d *__m, int i, int j) {

    // check border conditions

}

void update_flow_field(Matrix_d *u, Matrix_d *v, const Matrix_i* I_x, const Matrix_i* I_y, const Matrix_i* I_t) {

    double lambda = 1;
    // double mu_v = mean_d(v);
    // double mu_u = mean_d(u);
    double mu_v = 0;
    double mu_u = 0;

    // let's try using _local_ averages...

    const Matrix_d *u_copy = Matrix_clone_d(u);
    const Matrix_d *v_copy = Matrix_clone_d(v);

    double u_next = 0, v_next = 0;
    int Ix, Iy, It;

    assert(Matrix_size_d(u) == Matrix_size_d(v));
    assert(Matrix_size_i(I_x) == Matrix_size_i(I_y));
    assert(Matrix_size_i(I_y) == Matrix_size_i(I_t));

    // printf("About to update field values!\n");
    // printf("mu_u: %lf, mu_v: %lf\n", mu_u, mu_v);

    // Matrix_summary_d(u);
    // Matrix_summary_d(v);

    for (size_t i = 0; i < u->nrows; i++) {
        for (size_t j = 0; j < u->ncols; j++) {

            // mu = local_average()

            // if we are on any border
            if (i == 0 || i == u->nrows - 1|| j == 0 || j == u->ncols - 1) {
                mu_u = 0;
                // mu_v = matat_d(v, i, j);
                mu_v = 0;
            } else {
                mu_u = (matat_d(u_copy, i + 1, j) + matat_d(u_copy, i, j + 1) + matat_d(u_copy, i - 1, j) + matat_d(u_copy, i, j - 1)) / 4.0;
                mu_v = (matat_d(v_copy, i + 1, j) + matat_d(v_copy, i, j + 1) + matat_d(v_copy, i - 1, j) + matat_d(v_copy, i, j - 1)) / 4.0;
            }

            // obviously we can't be updating these values and computing the laplacian



            Ix = matat_i(I_x, i, j);
            Iy = matat_i(I_y, i, j);
            It = matat_i(I_t, i, j);
            // printf("Finished iteration \n");
            u_next = mu_u - Ix * (Ix * mu_u + Iy * mu_v + It) / ((1.0 / lambda) + Ix * Ix + Iy * Iy);
            v_next = mu_v - Iy * (Ix * mu_u + Iy * mu_v + It) / ((1.0 / lambda) + Ix * Ix + Iy * Iy);
            matset_d(v, i, j, v_next);
            matset_d(u, i, j, u_next);
        }
    }
    // printf("Done...\n");
    Matrix_free_d(u_copy);
    Matrix_free_d(v_copy);

}

optical_flow_t calc_optical_flow_hs(const Matrix_i *f0, const Matrix_i *f1, int nb_iter) {

    // Let's compute the differece
    Matrix_i *I_t = Matrix_subtract_i(f0, f1);
    Matrix_i *I_x = img_x_gradient(f0);
    Matrix_i *I_y = img_y_gradient(f0);

    // Initialize flow fields
    Matrix_d *u = Matrix_new_d(f0->nrows, f0->ncols);
    Matrix_d *v = Matrix_new_d(f0->nrows, f0->ncols);

    for (int i = 0; i < nb_iter; i++) {
        update_flow_field(u, v, I_x, I_y, I_t);
    }

    optical_flow_t uv = { .It = I_t, .Ix = I_x, .Iy = I_y, .u = u, .v = v };
    return uv;
}

void save_optical_flow(const char *prefix, optical_flow_t flow) {

    Matrix_d *dir = map2_d(flow.u, flow.v, atan2);
    Matrix_d *mag = map2_d(flow.u, flow.v, euler);

    normalize_minmax(mag);
    normalize_minmax(dir);

    write_ppm_gray(d_to_i(mag), prepend("mag.ppm", prefix));
    // write_ppm_color_minmax_d(mag, viridis(), -10, 10, prepend("mag_vir.ppm", prefix));
    write_ppm_gray(d_to_i(dir), prepend("dir.ppm", prefix));
    // write_ppm_gray(flow.It, prepend("diff.ppm", prefix));
    // write_ppm_gray(flow.Ix, prepend("Ix.ppm", prefix));
    // write_ppm_gray(flow.Iy, prepend("Iy.ppm", prefix));

}