// Ecrire le code C permettant de creer un tableau tab de 17 entiers en utilisant un pointeur
// et la fonction malloc. Liberer ensuite la memoire allouee au tableau avec la fonction free.

#include <stdlib.h>
#include <stdio.h>
#include "ejovo_print.h"

#define SIZE_ARRAY 17 // size of the array of integers


int main(void) {

    int * tab = (int *) malloc(sizeof(int) * (SIZE_ARRAY));

    if(tab) {
        for (int i = 0; i < SIZE_ARRAY; i++) {
            tab[i] = i;
        }
    }

    printf("Integer array allocated with malloc: \n");
    print_int_array(tab, SIZE_ARRAY);

    free(tab);
    printf("Memory freed with free\n");

    return 0;


}
