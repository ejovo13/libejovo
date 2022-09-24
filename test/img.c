#include "ejovo.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    // Let's go ahead and create a linspace then normalize it
    const int w = 100;
    const int h = 100;

    Matrix *sp = reshape(linspace(0, 20, w * h), h, w);

    // printf("min: %lf\n", min(sp));
    // printf("max: %lf\n", max(sp));

    normalize_minmax(sp);

    img_t *img = newImageGrayscale(sp);

    writePPM(img, "test.ppm");

    Matrix_print(sp);




    return 0;
}