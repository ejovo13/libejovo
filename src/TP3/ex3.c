// Modification de chaines
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ejovo_string.h"

int main() {

    size_t espaces_supprimes = 0;
    char * new_str = NULL;

    char * old_str = "Bon jo u\t r \n\n\tmon\t a  mi   !\n  \n ";

    // supprime_espaces definie en "ejovo_string.c"
    new_str = supprime_espaces_n(old_str, &espaces_supprimes);

    printf("Converted string: \n\n '%s'\n\n to:\n '%s'\n n_deleted_spaces: %ld\n", old_str, new_str, espaces_supprimes);

    return 0;
}