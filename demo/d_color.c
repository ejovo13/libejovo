#include "ejovo_color.h"
#include "ejovo_img.h"

int main() {

    const char *my_palette[] = {"#fa0707", "#33e60b", "#0bd7e6", "#160be6", "#f20feb"};
    const char *viridis[] = {"#fde725", "#5ec962", "#21918c", "#3b528b", "#440154"};
    const char *inferno[] = {"#fcffa4", "#f98e09", "#bc3754", "#57106e", "#000004"};
    const char *magma[] = {"#fcfdbf", "#fc8961", "#b73779", "#51127c", "#000004"};
    const char *plasma[] = {"#f0f921", "#f89540", "#cc4778", "#7e03a8", "#0d0887"};
    const char *cp1[] = {"#541690", "#FF4949", "#FF8D29", "#FFCD38"};
    const char *cp2[] = {"#2F2519", "#4A3F35", "#FA7D09", "#FF4301"};
    const char *green[] = {"#000000", "#3E432E", "#616F39", "#A7D129"};
    const char *purp[] = {"#000000", "#3E065F", "#700B97", "#8E05C2"};
    const char *red[] = {"#000000", "#3D0000", "#950101", "#FF0000"};

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

    ColorPalette *cp = ColorPalette_new(my_palette, 5);
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


    return 0;
}