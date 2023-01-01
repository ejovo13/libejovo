#include "ejovo.h"
#include <assert.h>
#include <stdbool.h>

void t_load_pgm();
void t_optical_flow();
// void update_flow_field(Matrix_d *u, Matrix_d *v, const Matrix_i* I_x, const Matrix_i* I_y, const Matrix_i* I_t);


int main() {

    // Let's go ahead and create a linspace then normalize it
    const int w = 100;
    const int h = 100;

    Matrix_d *sp = reshape_d ( linspace_d (0, 20, w * h), 
                                   h,
                                   w );

    // printf("min: %lf\n", min_d(sp));
    // printf("max: %lf\n", max_d(sp));

    normalize_minmax(sp);

    img_t *img = newImageGrayscale(sp);

    writePPM(img, "test.ppm");

    // Matrix_print_d(sp);

    t_load_pgm();
    t_optical_flow();

    return 0;
}

void t_load_pgm() {

    Matrix_i *img = Matrix_new_i(10, 10);
    // Matrix_print_i(img);

    img = read_pgm("f0.pgm");
    Matrix_i *img2 = read_pgm("mbf0.pgm");

    write_ppm_gray(img, "test_f0.ppm");
    write_ppm_gray(img2, "test_2.ppm");

    printf("t_load_pgm passed\n");

}

#define STRF_BUFFER_SIZE 100

char *strf_(const char *__format, va_list args) {
    char *str = (char *) calloc(STRF_BUFFER_SIZE, sizeof(*str));
    sprintf(str, __format, args);
    return str;
}

// form a new string using the format feature
char *strf(const char *__format, ...) {

    va_list args;
    va_start(args, __format);
    return strf_(__format, args);
}

#define catf(__format, args) \
char __this_buff[100] = {0}; \
sprintf(__this_buff, __format, args);


void t_optical_flow() {

    // Matrix_i *f0 = read_pgm("f0.pgm");
    // Matrix_i *f1 = read_pgm("f1.pgm");

    Matrix_i *f0 = read_pgm("mbf0.pgm");
    Matrix_i *f1 = read_pgm("mbf1.pgm");

    // printf("u_min: %lf, u_max: %lf, |u|_mu : %lf\n", min_d(u), max_d(u), mean_d(map_d(u, fabs)));
    // printf("u_min: %lf, u_max: %lf, |u|_mu : %lf\n", min_d(u), max_d(u), mean_d(u));
    // Updated flow fields u and v!!!
    int nb_iter = 100; 

    optical_flow_t flow;

    // optical_flow_t flow = calc_optical_flow_hs(f0, f1, nb_iter);
    // save_optical_flow("moving_bodies_", flow); 

    // printf("Wrote optical flow images for moving bodies\n");

    // f0 = read_pgm("c60.pgm");
    // f1 = read_pgm("c60t.pgm");

    // printf("Read in pgm\n");

    // flow = calc_optical_flow_hs(f0, f1, nb_iter);
    // save_optical_flow("cg_", flow);


    f0 = read_pgm("f35.pgm");
    f1 = read_pgm("f36.pgm");
    Matrix_i *f2 = read_pgm("f37.pgm");

    flow = calc_optical_flow_hs(f0, f1, nb_iter, 0.5);
    save_optical_flow("moving_bodies2_", flow);

    flow = calc_optical_flow_hs(f1, f2, nb_iter, 0.5);
    save_optical_flow("mb_1_2_", flow);


}
