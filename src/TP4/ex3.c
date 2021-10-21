// Ecrire le code C permettant de creer un tableau tab a deux dimension de 17 lignes
// et 17 colonnes entiers en utilisant un pointeur et la fonction malloc. Liberer ensuite
// la memoire allouee au tableau avec la fonction free.

#include <stdlib.h>
#include <stdio.h>
#include "ejovo_print.h"

#define NB_LIGNES 15 // number of rows
#define NB_COLONNES 17 // number of columns

int main(void) {

    int * tab = (int *) malloc(sizeof(int) * (NB_LIGNES * NB_COLONNES));

    if(tab) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = 0; j < NB_COLONNES; j++) {
                tab[i * NB_LIGNES + j] = i + j;
            }
        }
    }

    printf("Integer array allocated with malloc: \n");
    for (int i = 0; i < NB_LIGNES; i++) {
        print_int_array(tab + i*NB_LIGNES, NB_COLONNES);
    }

    free(tab);
    printf("Memory freed with free\n");

    return 0;


}
