// Ecrire une fonction init_tab

#include <stdlib.h>
#include <stdio.h>
#include "ejovo_print.h"
#include "ejovo_rand.h"

void init_tab(int __max, int *__tab, int __n) {

    for (int i = 0; i < __n; i++) {

        __tab[i] = unif(0, __max);

    }
}

int main() {

    ejovo_seed(); // seed my random generator

    int tab[100] = {0};

    init_tab(50, tab, 50); // initialize the first 50 elements
    print_int_array(tab, 100); // print the entire array

    return 0;
}
