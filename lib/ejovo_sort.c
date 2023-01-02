#include "ejovo_sort.h"



void init_tab(int __max, int *__tab, int __n) {

    for (int i = 0; i < __n; i++) {

        __tab[i] = unifi(0, __max);

    }
}

void ech(int *__tab, int __i, int __j) {

    int temp = __tab[__i];
    __tab[__i] = __tab[__j];
    __tab[__j] = temp;

}

// return index of the smallest value in the array
int find_min_index(int *__tab, int __n) {

    int min = __tab[0];
    int min_index = 0;

    for (int i = 1; i < __n; i++) {

        if (__tab[i] < min) {
            min = __tab[i];
            min_index = i;
        }
    }

    return min_index;

}

void tri_selec(int *__tab, int __n) {

    int min_index = -1;

    for (int i = 0; i < __n; i++) {

        // find min index from __tab + i to the end of the array
        min_index = find_min_index(__tab + i, __n - i);
        // printf("min_index %d = %d\n", i, min_index);
        // exchange current index with the min index adjusted for the large array
        ech(__tab, i, min_index + i);

    }
}

void tri_bulle(int *__tab, int __n) {

    bool is_sorted = false; // true if every element i + 1 is greater than i

    while (!is_sorted) {

        // sort the elements
        is_sorted = true; // if we can make it through the entire array with __tab[i] < __tab[i + 1], this doesnt change!

        for (int i = 0; i < __n - 1; i++) { // go to the second to last element

            if (__tab[i] > __tab[i + 1] ) { // if two adjacent elements are not in the right order, sort them
                ech(__tab, i, i + 1);
                is_sorted = false;
            } else {
                continue;
            }
        }
    }
}

// insert a value into a sorted sub array array of size __n_sorted_array
void insert(int *__full_array, int __n_sorted_array, int __ivalue) {

    // find out where the element belongs
    for (int i = 0; i < __n_sorted_array; i++) {

        if (__full_array[__ivalue] < __full_array[i]) { // then place our value at the position i and SHIFT the rest of the table over

            for(int j = i; j < __ivalue; j++) {

                ech(__full_array, __ivalue, j); // im pretty sure this should work

            }
        }
    }
}

void tri_insertion(int *__tab, int __n) {
    for (int i = 1; i < __n; i++) {
        insert(__tab, i, i);
    }
}