#include "ejovo_color.h"
#include "ejovo_img.h"

int main() {

    color_red();

    printf("ERROR: ");

    color_reset();

    printf("You done fucked up\n");


    printf("Yuh\n");

    // Now let's create our own colors

    char col_str[] = "#ff0f34";

    Color col = Color_from_hex(col_str);

    printf("%s\n", col_str);
    Color_print(col);
    Color_print_hex(col);

    ColorPalette *cp = viridis();
    ColorPalette_print(cp);

    Matrix_i *pal = ColorPalette_to_matrix(cp, 255);

    // Matrix_print_i(pal);


    // Let's create a new matrix that can test out the color palette



    Matrix_d *test_palette = Matrix_new_d(100, 1000);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1000; j++) {
            matset_d(test_palette, i, j, j);
        }
    }

    normalize_minmax(test_palette);

    // write_ppm_color_minmax_d(test_palette, cp, 0, 255, "test_palette.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(viridis, 5), 0, 255, "virids.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(inferno, 5), 0, 255, "inferno.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(magma, 5), 0, 255, "magma.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(plasma, 5), 0, 255, "plasma.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(cp1, 4), 0, 255, "cp1.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(cp2, 4), 0, 255, "cp2.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(green, 4), 0, 255, "green.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(purp, 4), 0, 255, "purp.ppm"); 
    // write_ppm_color_minmax_d(test_palette, ColorPalette_new(red, 4), 0, 255, "red.ppm"); 


    Matrix_free_i(pal);

    return 0;
}