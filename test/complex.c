#include "ejovo_comp.h"

int main() {

    Complex z = {4, 5};
    Complex *z1 = Complex_new(4, 5);

    Complex_print(z);
    Complex_print(*z1);

    Complex z2 = Complex_add(z, *z1);
    printf("Performed a copy I guess\n");
    Complex_print(z2);
    Complex_print_polar(z2);

    Complex z3 = Complex_exp(M_PI);
    Complex_print_polar(z3);
    Complex_print(z3);

    Complex one = Complex_one();
    Complex_print_polar(one);

    Complex i = Complex_i();
    Complex_print_polar(i);

    Complex *z4 = Complex_new(10, -3);
    Complex z5 = Complex_exp(0.0);
    Complex z6 = Complex_aexp(3, M_PI);

    Complex_print(*z4);
    Complex_print(z5);
    Complex_print(z6);


    return 0;
}