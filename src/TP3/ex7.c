// Parentheses
#include "ejovo_string.h"

int main() {

    char exp_alg[] = "(a + x - 2)*(e^x - (2 * 2))+(3)";
    char test[] = "())))";

    printf("Expression: '%s', reduced: '%s'\n", exp_alg, extract_parentheses(exp_alg)); // extract_parenthesis defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(exp_alg)); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(test)); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee("()(())")); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee("()")); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee_n(test, 3)); // est_bien_parenthesee defined in "ejovo_string.c"

    printf("Longest section of '%s': '%s'\n", test, plus_longue_expr(test));
    printf("Longest section of '%s': '%s'\n", exp_alg, plus_longue_expr(exp_alg));

    return 0;
}