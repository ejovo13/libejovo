#include "ejovo_string.h"

// copy a NULL TERMINATED STRING into another one, without being given the length of the string
char * cpy_str(char * input) {
    size_t len = strlen(input);
    printf("Size input: %ld\n", len);
    char * new_str = (char *) calloc(len + 1, sizeof(char));
    strcpy(new_str, input);
    return new_str;
}

// copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
// We follow the convention established by string.h where str_len() returns the number of characters not including the null string;
char * cpy_n_str(char * input, size_t n) {
    char * new_str = (char *) calloc(n + 1, sizeof(char));
    strcpy(new_str, input);
    return new_str;
}