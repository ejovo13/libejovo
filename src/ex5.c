#include <stdio.h>

int main() {

    printf("Please enter two integers\n");

    int a, b;

    scanf("%d", &a);
    scanf("%d", &b);

    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);


    return 0;
}