#ifndef EJOVO_SORT
#define EJOVO_SORT

#include "ejovo_rand.h"
#include "stdbool.h"
// Collection of basic sorting routines

// initialize an array with random elements
void init_tab(int __max, int *__tab, int __n);

// exchange two values in an array
void ech(int *__tab, int __i, int __j);

// return index of the smallest value in the array
int find_min_index(int *__tab, int __n);

void tri_selec(int *__tab, int __n);

void tri_bulle(int *__tab, int __n);

// insert a value into a sorted sub array array of size __n_sorted_array
void insert(int *__full_array, int __n_sorted_array, int __ivalue);

void tri_insertion(int *__tab, int __n);



#endif