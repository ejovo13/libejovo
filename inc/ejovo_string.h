#ifndef EJOVO_STRING
#define EJOVO_STRING

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// copy a NULL TERMINATED STRING into another one, without being given the length of the string
char * cpy_str(char * input);

// copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
// We follow the convention established by string.h where str_len() returns the number of characters not including the null string;
char * cpy_n_str(char * input, size_t n);

#endif