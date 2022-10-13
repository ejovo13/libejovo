#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "ejovo_matrix_generic.h"

// Simple routines that print ascii escape sequences to set the color of output.
void color_red();

void color_yellow();

void color_green();

void color_blue();

void color_purple();

void color_cyan();

void color_white();

void color_reset();

/**========================================================================
 *!                 Color structure used in color palettes
 *========================================================================**/

typedef struct Color {

    uint8_t r;
    uint8_t g;
    uint8_t b;

} Color;

// Create a color from a hex string

static inline uint8_t hex_to_bin(const char hex) {

    if (hex == '0') return 0;
    if (hex == '1') return 1;
    if (hex == '2') return 2;
    if (hex == '3') return 3;
    if (hex == '4') return 4;
    if (hex == '5') return 5;
    if (hex == '6') return 6;
    if (hex == '7') return 7;
    if (hex == '8') return 8;
    if (hex == '9') return 9;
    if (hex == 'a' || hex == 'A') return 10;
    if (hex == 'b' || hex == 'B') return 11;
    if (hex == 'c' || hex == 'C') return 12;
    if (hex == 'd' || hex == 'D') return 13;
    if (hex == 'e' || hex == 'E') return 14;
    if (hex == 'f' || hex == 'F') return 15;

    perror("Invalid hex character passed\n");
    exit(EXIT_FAILURE);
}

static inline char bin_to_hex(const uint8_t bin) {

    if (bin == 0) return '0';
    if (bin == 1) return '1';
    if (bin == 2) return '2';
    if (bin == 3) return '3';
    if (bin == 4) return '4';
    if (bin == 5) return '5';
    if (bin == 6) return '6';
    if (bin == 7) return '7';
    if (bin == 8) return '8';
    if (bin == 9) return '9';
    if (bin == 10) return 'A';
    if (bin == 11) return 'B';
    if (bin == 12) return 'C';
    if (bin == 13) return 'D';
    if (bin == 14) return 'E';
    if (bin == 15) return 'F';

    perror("Invalid bin value passed\n");
    exit(EXIT_FAILURE);
}

// Convert two hex characters to a uint8_t. f(0, 0) -> 0; f(F, F) -> 255
static inline uint8_t hex_pair_to_rgb(const char l, const char r) {
    return 16 * hex_to_bin(l) + hex_to_bin(r);
}

static inline char *bin_value_to_hex(const uint8_t bin) {

    uint8_t rem = bin % 16;
    uint8_t flr = bin / 16;
    char *out = (char *) malloc(sizeof(char) * 3);
    out[0] = bin_to_hex(flr);
    out[1] = bin_to_hex(rem);
    out[2] = 0;
    return out;
}

// Convert a string of the form #FFFFFF to a rgb color
Color Color_from_hex(const char *hex_color);

Color Color_from_rgb(uint8_t r, uint8_t g, uint8_t b);

void Color_print(const Color col);

void Color_print_hex(const Color col);

char *Color_to_hex(const Color col);

Matrix_i *Color_to_rgb_i(const Color col);
Matrix_d *Color_to_rgb_d(const Color col);

// Let's start working with a color palette type

typedef struct ColorPalette {

    Color *colors;
    int n; // Number of colors in this palette

} ColorPalette;

ColorPalette *ColorPalette_new(const char** colors, int n_colors);

void ColorPalette_print(const ColorPalette *cp);


// lambda = 0 corresponds to the left color, lambda = 1 returns the right color
static inline Color Color_complex_combination(double lambda, const Color left, const Color right) {

    double new_r = lambda * right.r + (1 - lambda) * left.r;
    double new_g = lambda * right.g + (1 - lambda) * left.g;
    double new_b = lambda * right.b + (1 - lambda) * left.b;

    Color out = {.r = new_r, .g = new_g, .b = new_b};

    return out;
}

// I need a function that takes in a ColorPalette and a double value, then returns a color
// x shall be a double value between 0 and 255
// ASSUME that length(boundaries) = length(cp)
static inline Color ColorPalette_assign_color(const ColorPalette *cp, double x, const Matrix_d *boundaries, const double dx) {

    assert(x >= 0 && x <= 255);

    if (x == 0) return cp->colors[0]; // just return the first color
    if (x == 255) return cp->colors[cp->n - 1]; // just return the last color

    // Check which boundary we belong to
    int left_boundary = 0;

    for (int i = 1; i < cp->n; i++) {

        if (x <= boundaries->data[i]) {
            left_boundary = i - 1;
            break;
        }
    }

    // now that we've found the left boundary, compute the combination of the two colors
    const double left_x  = boundaries->data[left_boundary];

    // we first compute lambda
    double lambda = (x - left_x) / dx;

    // then we return the complex combination of c1 and c2
    return Color_complex_combination(lambda, cp->colors[left_boundary], cp->colors[left_boundary + 1]);
}


// Now I need a function to send a color palette to an integer matrix via linear interpolation
Matrix_i *ColorPalette_to_matrix(const ColorPalette *cp, int n);

/**========================================================================
 *!                          Fixed Color Palettes
 *========================================================================**/
ColorPalette *viridis();
ColorPalette *my_palette();
ColorPalette *inferno();
ColorPalette *magma();
ColorPalette *plasma();
ColorPalette *cp1();
ColorPalette *cp2();
ColorPalette *green();
ColorPalette *purp();
ColorPalette *red();