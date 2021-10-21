#include "ejovo_print.h"
#include "ejovo_rand.h"

#define N 50

int main() {

    ex(3, "Garder que la premiere occurrence de chaque entier");

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

    printf("Filtering duplicate integers...\n\n");

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

    printf("Original array:\n");
    print_int_array(arr_og, N);

    printf("Modified array:\n");
    print_int_array(arr, N);

    return 0;
}