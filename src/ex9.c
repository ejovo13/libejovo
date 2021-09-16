// Fractions Egyptiennes

#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 10000

int PGCD(int a, int b) {
// Euclid's algorithm to find the greates common divisor

    int r = 0;

    do {
        if (a > b) {
            a = a % b;
            r = a;
        } else {
            b = b % a;
            r = b;
        }
    } while(r != 0);

    if (a > b) {
        return a;
    } else {
        return b;
    }
}

struct EgyptianFraction {
// Structure to hold the numerator and denominators of an egyptian fraction
    int * den;
    int length;
};

struct EgyptianFraction egyptian_fraction_decomp(int n, int d) {



    int i = 2;

    int temp_n = n;
    int temp_d = d;
    int gcd = 0;
    int i_d = i;
    int i_n = 1;
    int num_fractions = 0;
    int * denominators = malloc(sizeof(n) * 1000);
    struct EgyptianFraction ef;

    while(i < MAX_ITER && temp_n != 0) {
        // cross multiply to get temp_n and temp_d that have the same denominator
        // (temp_n/temp_d) x (1/i)

        i_n = temp_d;
        i_d = i;
        temp_n *= i;
        temp_d *= i;

        // printf("i_n = %d  ", i_n);
        // printf("i = %d, and dealing with temp fraction: %d/%d\n", i, temp_n, temp_d);

        if ( temp_n > i_n ) { // If the remaining fraction is larger than the potential 1/i

            // printf("%d > %d", temp_n, temp_i);
            temp_n -= i_n;

            // increment the number of fractions, and append to the list
            denominators[num_fractions] = i;
            num_fractions ++;

        } else if ( temp_n == i_n ) {
            denominators[num_fractions] = i;
            num_fractions ++;
            // printf("I should be done here wtf\n");
            break;
        }

        // reduce the leftover fractions

        gcd = PGCD(temp_n, temp_d);

        // printf("gcd(%d, %d) = %d\n", temp_n, temp_d, gcd);

        temp_n /= gcd;
        temp_d /= gcd;

        i++;
    }

    if (i == MAX_ITER) {
        printf("Something went wrong\n");
    }

    ef.den = denominators;
    ef.length = num_fractions;

    return ef;

}


int main() {

    // get the numerator and denominator

    printf("Please input the numerator and denominator of a positive fraction to decompose\n");
    printf("You must follow this format: num/den\n\n");

    int n = 7, d = 8;

    int scan_out = scanf("%d/%d", &n, &d);

    if (scan_out != 2) {
        printf("Program input failed. Exiting with code 1\n");
        return 1;
    }

    if ( n <= 0 || d <= 0) {
        printf("Please input strictly positif integers\n");
        printf("Exiting with error code 2\n");
        return 2;
    }

    if ( n > d ) {
        printf("Please enter a numerator that is smaller than the denominator\n");
        return 3;
    }

    // solve the egyptian fractions
    struct EgyptianFraction ef;

    ef = egyptian_fraction_decomp(n, d);

    printf("%d/%d = ", n, d);

    for (int i = 0; i < ef.length - 1; i ++) {
        printf("1/%d + ", ef.den[i]);
    }
    printf("1/%d\n", ef.den[ef.length - 1]);

    return 0;
}

