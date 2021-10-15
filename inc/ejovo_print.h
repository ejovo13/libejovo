#ifndef EJOVO_PRINT
#define EJOVO_PRINT

/**@file
 * @brief Provide a few functions to print the description of an exercise
 *
 */
#include <stdio.h>


/**
 * Print a line of characters
 *
 * @param __num_chars Number of characters to display
 * @param __border_char Character used to construct the line
 */
void print_line(int __num_chars, char  __border_char);

/**
 * Print a header to introduce a new exercise
 *
 * @param __ex_num Number of the exercise
 * @param __description Description of the exercise
 */
void ex(int __ex_num, char * __description);

/**
 * Print the contents of an array of integers
 *
 * @param __arr Array to be printed
 * @param __n Number of elements to print
 */
void print_int_array(int * __arr, int __n);

#endif