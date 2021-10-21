// Ecrire une fonction pour echanger des valeurs d'un tableau

#include <stdlib.h>
#include <stdio.h>
#include "ejovo_print.h"

void ech(int *__tab, int __i, int __j) {

    int temp = __tab[__i];
    __tab[__i] = __tab[__j];
    __tab[__j] = temp;

}


int main(void) {

    int tab[2] = {1, 2};

    print_int_array(tab, 2);

    printf("Swapping values [0] and [1]...\n");
    ech(tab, 0, 1);

    print_int_array(tab, 2);

    return 0;


}
