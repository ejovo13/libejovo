#ifndef EJOVO_STRING
#define EJOVO_STRING

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ejovo_string.h"
#include <stdbool.h>

// copy a NULL TERMINATED STRING into another one, without being given the length of the string
char * cpy_str(char * __input);

// copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
// We follow the convention established by string.h where str_len() returns the number of characters not including the null string;
char * cpy_n_str(char * __input, size_t __n);

// take an input string and return a copy that has been reversed.
char * reverse_string(const char * __string);

// Tell me how long the string is (without null-terminating character)
char * reverse_string_n(const char * __string, size_t __string_length);

// Delete spaces from a string and return a new string who has no spaces
char * supprime_espaces(const char * __input, size_t * __nb_esp_supp);

// Determine whether or not s2 is a substring of s1
bool is_substr(const char * __s1, const char * __s2);

#endif