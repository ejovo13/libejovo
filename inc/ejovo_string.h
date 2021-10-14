#ifndef EJOVO_STRING
#define EJOVO_STRING

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ejovo_string.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/** @file
 * @brief Provide essential string manipulation functions for use throughout the TP exercises.
 *
 */


/**
 *  copy a NULL TERMINATED STRING into another one, without being given the length of the string
 *
 */
char * cpy_str(char * __input);

/**
 * copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
 * We follow the convention established by string.h where str_len() returns the number of characters not including the null string;
 *
 *
 */
char * cpy_n_str(char * __input, size_t __n);

/**
 *  Get a substr starting at position __start_index (INCLUSIVE) and ending at __end_index (EXCLUSIVE)
 *
 *
 *
 */
char * substr(const char * __s1, const size_t __start_index, const size_t __end_index);

/**
 * This function attempts to replicate the python slice. Thus, __end_index_py is NOT INCLUDED in the resulting slice
 * Thus, slice(__s1, x, x) returns a string with length 0 (a character pointer to the null character)
 */
char * slice(const char * __s1, const int __start_index_py, const int __end_index_py);

/**
 *  take an input string and return a copy that has been reversed.
 *
 */
char * reverse_string(const char * __string);

/**
 *  Tell me how long the string is (without null-terminating character) and then reverse the string
 *
 */
char * reverse_string_n(const char * __string, size_t __string_length);

/**
 *  Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
 *
 */
char * supprime_espaces(const char * __input);

/**
 *  Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
 *
 */
char * supprime_espaces_n(const char * __input, size_t * __nb_esp_supp);

/**
 *  Determine whether or not s2 is a substring of s1
 *
 */
bool is_substr(const char * __s1, const char * __s2);

/**
 *  Delete the substring from a given string, no matter how many times it appears in the string
 *
 */
char * del_substr(const char * const __s1, const char * const __substr);

/**
 * Ecrire une fonction qui prend une expression algebrique en entree et
 * renvoi un tableau de caracteres ne contenant que les parentheses
 *
 *
 */
char * extract_parentheses(const char * const __expr_alg);

/**
 *  Check if an expression has a proper number of parentheses
 *
 *
 */
bool est_bien_parenthesee(const char * const __expr);

/**
 *  Check if an expression has a proper number of parentheses, while passing the length of the string that you want to check.
 *
 *
 */
bool est_bien_parenthesee_n(const char * const __expr, size_t __n);

/**
 * Find the longest string that is properly parenthesized
 *
 * @param __expr_alg Algebraic expression that may or may not be properly parenthesized
 * @return Longest sequence of valid parentheses pairs
 */
char * plus_longue_expr(const char * const __expr_alg);

/**
 * Store the value of x as a decimal string
 */
char * int_to_string(int x);

// Internal procedure to count the number of digits that an integer has
static int nb_chiffres_(long x);

#endif