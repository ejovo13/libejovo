#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    int n = 0;

    printf("Please enter an integer\n\n");

    scanf("%d", &n);


    int num_digits = (int) log10(n) + 1;

    printf("Value entered: %d\n", n);
    printf("Number of digits: %d\n", num_digits);

    char n_str[num_digits + 1];
    // n_str[num_digits] = '\0';

    sprintf(n_str, "%d", n);

    int ones_count = 0;

    for (int i = 0; i < num_digits; i++) {
        if (n_str[i] == '1') {
            ones_count ++;
        }
    }

    printf("Integer: %s has %d ones \n", n_str, ones_count);

    return 0;
}