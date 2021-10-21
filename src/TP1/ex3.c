#include "hw_printer.h"

int main() {

    ex(3, "Affiche un entier n = 2; ");

    int n = 2;
    printf("%d\n\n", n);

    ex(4, "Initialise un entier par l'utilisateur");

    printf("Please input an integer\n");

    scanf("%d", &n);

    printf("The value that you input is: %d\n", n);


    return 0;
}