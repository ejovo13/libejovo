// Modification de chaines
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ejovo_string.h"

char * supprime_espaces(char * __input, size_t * __nb_esp_supp) {

    // return the number of spaces deleted,
    size_t len = strlen(__input);

    size_t num_spaces = 0;
    // count number of spaces
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] == ' ' || __input[i] == '\n') { num_spaces ++; }
    }

    // initialize a new string whose length is len - num_spaces
    size_t new_str_capacity = len - num_spaces + 1;
    char * new_str = (char *) malloc(sizeof(char) * new_str_capacity);

    // Fill new string
    new_str[new_str_capacity-1] = '\0';

    size_t i_new = 0; // index of new string
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] != ' ' && __input[i] != '\n') {
            new_str[i_new] = __input[i];
            i_new ++;
        }
    }

    *__nb_esp_supp = num_spaces;

    return new_str;
}

int main() {

    size_t espaces_supprimes = 0;
    char * new_str = NULL;

    char * old_str = "Su  p bi  tch  !";

    new_str = supprime_espaces(old_str, &espaces_supprimes);

    printf("Converted s:\n %s\n to:\n %s\n n_deleted_spaces: %ld\n", old_str, new_str, espaces_supprimes);



    return 0;
}