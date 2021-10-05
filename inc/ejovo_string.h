#ifndef EJOVO_STRING
#define EJOVO_STRING

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ejovo_string.h"
#include <stdbool.h>
#include <stdint.h>

// copy a NULL TERMINATED STRING into another one, without being given the length of the string
char * cpy_str(char * __input);

// copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
// We follow the convention established by string.h where str_len() returns the number of characters not including the null string;
char * cpy_n_str(char * __input, size_t __n);

// take an input string and return a copy that has been reversed.
char * reverse_string(const char * __string);

// Tell me how long the string is (without null-terminating character) and then reverse the string
char * reverse_string_n(const char * __string, size_t __string_length);

// Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
char * supprime_espaces(const char * __input);

// Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
char * supprime_espaces_n(const char * __input, size_t * __nb_esp_supp);

// Determine whether or not s2 is a substring of s1
bool is_substr(const char * __s1, const char * __s2);

// Delete the substring from a given string, no matter how many times it appears in the string
char * del_substr(const char * const __s1, const char * const __substr);

// ecrire une fonction qui prend une expression algebrique en entree et
// renvoi un tableau de caracteres ne contenant que les parentheses
char * extract_parentheses(const char * const __expr_alg);

// Check if an expression has a proper number of parentheses
bool est_bien_parenthesee(const char * const __expr);

#endif