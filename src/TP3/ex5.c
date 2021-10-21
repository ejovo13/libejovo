// Palindrome

// indiquez si une chaine de caracteres est un palindrome.

#include "ejovo_print.h"
#include "ejovo_rand.h"
#include "ejovo_string.h"
#include "stdbool.h"

bool is_palindrome(const char * __string) {

    size_t n_spaces_deleted = 0;
    char * __string_moins_espaces = supprime_espaces_n(__string, &n_spaces_deleted);
    char * __string_reverse = reverse_string(__string_moins_espaces);
    int strcase_return = strcasecmp(__string_moins_espaces, __string_reverse);
    return strcase_return == 0;

}

int main() {

    char racecar[] = "racecar"; // Gotta make sure my program works in english too ;)
    char rever[] = "rever";
    char radar[] = "radar";
    char mr_owl[] = "Mr Owl ate my metal worm"; // allows me to test supprime espace function
    char cheeseball[] = "Cheeseball";

    printf("Is '%s' a palindrome? %d\n", racecar, is_palindrome(racecar));
    printf("Is '%s' a palindrome? %d\n", rever, is_palindrome(rever));
    printf("Is '%s'a palindrome? %d\n", radar, is_palindrome(radar));
    printf("Is '%s' a palindrome? %d\n", mr_owl, is_palindrome(mr_owl));
    printf("Is '%s' a palindrome? %d\n", cheeseball, is_palindrome(cheeseball));

    return 0;
}