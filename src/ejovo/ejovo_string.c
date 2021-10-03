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

// take an input string and return a copy that has been reversed.
char * reverse_string(const char * __string) {

    size_t __string_length = strlen(__string);
    char * duplicate = (char *) malloc (sizeof(char) * (__string_length + 1));

    for (size_t i = 0; i < __string_length; i ++) {
        duplicate[__string_length - 1 - i] = __string[i];
    }
    duplicate[__string_length] = '\0';

    return duplicate;

}

// Tell me how long the string is (without null-terminating character) and then reverse the string
char * reverse_string_n(const char * __string, size_t __string_length) {

    char * duplicate = (char *) malloc (sizeof(char) * (__string_length + 1));

    for (size_t i = 0; i < __string_length; i ++) {
        duplicate[__string_length - 1 - i] = __string[i];
    }
    duplicate[__string_length] = '\0';
    return duplicate;

}

// Delete spaces from a string and return a new string who has no spaces
char * supprime_espaces(const char * __input, size_t * __nb_esp_supp) {

    // return the number of spaces deleted,
    size_t len = strlen(__input);

    size_t num_spaces = 0;
    // count number of spaces
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] == ' ' || __input[i] == '\n' || __input[i] == '\t') { num_spaces ++; }
    }

    // initialize a new string whose length is len - num_spaces
    size_t new_str_capacity = len - num_spaces + 1;
    char * new_str = (char *) malloc(sizeof(char) * new_str_capacity);

    // Fill new string
    new_str[new_str_capacity-1] = '\0';

    size_t i_new = 0; // index of new string
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] != ' ' && __input[i] != '\n'&& __input[i] != '\t') {
            new_str[i_new] = __input[i];
            i_new ++;
        }
    }

    *__nb_esp_supp = num_spaces;

    return new_str;
}