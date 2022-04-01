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