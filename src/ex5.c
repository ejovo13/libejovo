#include "hw_printer.h"

int main() {

    ex(5, "Evalue le somme de deux entiers donnes par l'utilisateur");

    printf("Please enter two integers\n");

    int a, b;

    scanf("%d", &a);
    scanf("%d", &b);

    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);


    return 0;
}