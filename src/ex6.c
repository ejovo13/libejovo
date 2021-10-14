// Sous-chaines

// Ecrire une fonction qui prend en entree deux chaines de caracteres
// s1 et s2 et se modifie s1 de facon a supprimer la sous chaine s2.
// si s2 n'est pas incluse dans s1, la fonction ne modifie pas s1. Si
// s2 est presente plusiers fois dans s1, on supprime chaque occurence
#include "ejovo_print.h"
#include "ejovo_rand.h"
#include "ejovo_string.h"
#include <stdbool.h>

int main() {

    char full_str[] = "This is  full string";
    char sub_str[] = "is  ";

    char full_str2[] = "Hello this is a full string";
    char sub_str2[] = "is";

    printf("Full string: '%s'\n", full_str);
    printf("substring:   '%s'\n", sub_str);

    printf("full string - substr: '%s'\n", del_substr(full_str, sub_str));

    printf("\nFull string: '%s'\n", full_str2);
    printf("substring:   '%s'\n", sub_str2);
    printf("full string - substr: '%s'\n", del_substr(full_str2, sub_str2));
    return 0;
}