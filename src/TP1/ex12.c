#include "hw_printer.h"
#include <stdlib.h>
#include <math.h>

int main() {

    long int n = 0;

    ex(12, "Afficher le nombre de chiffres 1 dans un entier");

    printf("Please enter an integer\n\n");

    scanf("%ld", &n);


    long int num_digits = (int) log10(n) + 1;

    printf("Value entered: %ld\n", n);
    printf("Number of digits: %ld\n", num_digits);

    // char n_str[num_digits + 1];
    char *n_str = (char *) malloc(sizeof(char) * (num_digits + 1));
    n_str[num_digits] = '\0';

    sprintf(n_str, "%ld", n);

    int ones_count = 0;

    for (int i = 0; i < num_digits; i++) {
        if (n_str[i] == '1') {
            ones_count ++;
        }
    }

    printf("Integer: %s has %d ones \n", n_str, ones_count);

    return 0;
}