#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 50

int get_rand_int(int max) {
// get random integer between 1 and max
    double x = ((double) rand()) / RAND_MAX;
    return (int) ceil(x * max);
}

int main() {

    srand( time( NULL ) );

    int arr[N];
    int arr_og[N]; // Unchanged array
    int P = 50;
    int rn = 0; // random n

    printf("Generating array of length %d with max value %d...\n", N, P);

    // generate random array with length N and max value P
    for(int i = 0; i < N; i ++) {

        rn = get_rand_int(P);
        arr[i] = rn;
        arr_og[i] = rn;

    }

    int index = -1;
    int ncount = 0;

    // check every single integer from 1 to P
    for (int n = 1; n <= P; n ++ ) {
        // check every element
        for (int i = 0; i < N; i ++) {
            if (arr[i] == n) {
                ncount ++;
                if (ncount > 1) {
                    arr[i] = 0;
                }
            }
        }

        ncount = 0;
    }

    printf("Filtering duplicate integers...\n\n");

    printf("Original array:\n");
    printf("{");
    for(int i = 0; i < N; i ++) {

        printf("%d, ", arr_og[i]);
    }
    printf("}\n\n");

    printf("Modified array:\n");
    printf("{");
    for(int i = 0; i < N; i ++) {

        printf("%d, ", arr[i]);
    }
    printf("}\n");


    return 0;
}