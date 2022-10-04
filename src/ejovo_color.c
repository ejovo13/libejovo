#include "ejovo_color.h"

void color_red() {
  printf("\033[1;31m");
}

void color_yellow() {
  printf("\033[1;33m");
}

void color_green() {
    printf("\033[0;32m");
}

void color_blue() {
    printf("\033[0;34m");
}

void color_purple() {
    printf("\033[0;35m");
}

void color_cyan() {
    printf("\033[0;36m");
}

void color_white() {
    printf("\033[0;37m");
}

void color_reset() {
  printf("\033[0m");
}

/**========================================================================
 *!                           Color functions
 *========================================================================**/
Color Color_from_hex(const char *hex_color) {
    // assure that the first character is #
    assert(hex_color[0] == '#');
    const uint8_t r = hex_pair_to_rgb(hex_color[1], hex_color[2]);
    const uint8_t g = hex_pair_to_rgb(hex_color[3], hex_color[4]);
    const uint8_t b = hex_pair_to_rgb(hex_color[5], hex_color[6]);

    Color col = {.r = r, 
                 .g = g,
                 .b = b};

    return col;
}

Color Color_from_rgb(uint8_t r, uint8_t g, uint8_t b) {
    Color col = {.r = r, .g = g, .b = b};
    return col;
}


// Return a 1 by 3 matrix whose elements are the rgb colors
Matrix_d *Color_to_rgb_d(const Color col) {
    Matrix_d *rgb = Matrix_new_d(1, 3);
    rgb->data[0] = col.r;
    rgb->data[1] = col.g;
    rgb->data[2] = col.b;
    return rgb; 
}

// Return a 1 by 3 matrix whose elements are the rgb colors
Matrix_i *Color_to_rgb_i(const Color col) {
    Matrix_i *rgb = Matrix_new_i(1, 3);
    rgb->data[0] = col.r;
    rgb->data[1] = col.g;
    rgb->data[2] = col.b;
    return rgb; 
}

char *Color_to_hex(const Color col) {
    char *r = bin_value_to_hex(col.r);
    char *g = bin_value_to_hex(col.g);
    char *b = bin_value_to_hex(col.b);

    char *out = (char *) malloc(sizeof(char) * 8);
    out[7] = 0;
    out[0] = '#';
    out[1] = r[0];
    out[2] = r[1];
    out[3] = g[0];
    out[4] = g[1];
    out[5] = b[0];
    out[6] = b[1];

    free(r); free(g); free(b);

    return out;
}

void Color_print(const Color col) {
    printf("r: %lu, g: %lu, b: %lu\n", col.r, col.g, col.b);    
}

void Color_print_hex(const Color col) {
    char *hex = Color_to_hex(col);
    printf("%s\n", hex);
    free(hex);
}

ColorPalette *ColorPalette_new(const char** colors, int n_colors) {

    ColorPalette *cp = (ColorPalette *) malloc(sizeof(ColorPalette));

    cp->n = n_colors;
    cp->colors = (Color *) malloc(sizeof(Color) * n_colors);

    for (int i = 0; i < n_colors; i++) {
        cp->colors[i] = Color_from_hex(colors[i]);
    }

    return cp;
}

void ColorPalette_print(const ColorPalette *cp) {
    printf("{");
    char *hex = NULL;
    for (int i = 0; i < cp->n - 1; i++) {
        hex = Color_to_hex(cp->colors[i]); // allocates memory
        printf("%s, ", hex);
        free(hex); // and frees it
    }
    hex = Color_to_hex(cp->colors[cp->n - 1]);
    printf("%s}\n", hex);
    free(hex);
}

// I want to convert a color palette to a n by 3 matrix
Matrix_i *ColorPalette_to_matrix(const ColorPalette *cp, int n) {

    // Let's first create the boundaries

    Matrix_d *boundaries = linspace_d(0, 255, cp->n);
    double dx = boundaries->data[1] - boundaries->data[0];

    // X values of the new colors (from 0 to 255)
    Matrix_d *new_x  = linspace_d(0, 255, n);
    Matrix_i *cp_out = Matrix_new_i(n, 3);

    for (int i = 0; i < n; i++) {
        Color temp = ColorPalette_assign_color(cp, new_x->data[i], boundaries, dx);
        matset_i(cp_out, i, 0, temp.r);
        matset_i(cp_out, i, 1, temp.g);
        matset_i(cp_out, i, 2, temp.b);
    }

    Matrix_free_d(boundaries);
    Matrix_free_d(new_x);

    return cp_out;
}