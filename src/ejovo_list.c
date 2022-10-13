#include "ejovo_list.h"


// Malloc a new Node
Node *Node_new(double __c, int __n) {

    Node *n = (Node *) malloc(sizeof(Node));
    n->c = __c;
    n->n = __n;
    n->next = NULL;

    return n;

}

void Node_print(const Node *__node) {
    printf("Node at %p :=  .c: %lf, .n: %d, .next: %p\n", __node, __node->c, __node->n, __node->next);
}

void Node_print_n(const Node *__node) {
    printf("Node.n: %d", __node->n);
}

void Node_print_c(const Node *__node) {
    printf("Node.c: %lf", __node->c);
}

Node *Node_clone(const Node *__node) {
    Node *node = Node_new(__node->c, __node->n);
    node->next = __node->next;
    return node;
}


List *List_new() {

    List *l = (List *) malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;

    return l;

}

// List *List_clone_node(const Node *__node) {
//     List *list = List_new();
//     list_append_node(Node_clone(__node));
//     return list;
// }

// List *List_from_node()

void List_append_node(List *__list, Node *__node) {

    if (__list->tail) { // if a tail node exists

        __list->tail->next = __node;

    } else { // set the head and tail equal to __node

        __list->head = __node;

    }

    __node->next = NULL;
    __list->tail = __node;

}

// wicked fast
void List_prepend_node(List *__list, Node *__node) {

    if (__list->head) { // if the head exists, prepend the head

        __node->next = __list->head;

    } else {

        __list->tail = __node;

    }

    __list->head = __node;

}

List *List_clone(const List *__list) {

    List *list = List_new();

    list->head = Node_clone(__list->head);
    list->tail = list->head;

    Node *node = __list->head->next; // traverse the original list

    while (node) {

        List_append_node(list, Node_clone(node));

        node = node->next;
    }

    return list;

}

// A list can insert an element in any position, prepend to the beginning, or add to the end
void List_append_new_node(List *__list, double __c, int __n) {

    Node *n = Node_new(__c, __n);
    List_append_node(__list, n);

}

void List_prepend_new_node(List *__list, double __c, int __n) {

    Node *n = Node_new(__c, __n);
    List_prepend_node(__list, n);

}

// Insert an element into a list ordered by n
// assume that the list is already sorted in ascending order
void List_ordered_insert_n(List *__list, Node *__node) {

    if (!__node) return; // If __node is null

    // if list->head is null, insert at the beginning
    if (!__list->head) {

        __list->head = __node;
        __list->tail = __node;

    } else {

        // iterate the list until we find a next element that is larger than __node->n
        Node *inode = __list->head;

        while(inode->next) {

            if (inode->n == __node->n) { // duplicate value, add c1 and c2

                // printf("Adding equal power of n: %d\n", inode->n);
                inode->c = __node->c + inode->c;
                return;

            } else if (inode->next->n > __node->n) {

                Node *temp = inode->next;
                inode->next = __node;
                __node->next = temp;
                return;

            }

            inode = inode->next;
        }

        if (inode->n == __node->n) { // duplicate value, add c1 and c2

            // printf("Adding equal power of n: %d\n", inode->n);
            inode->c = __node->c + inode->c;
            return;

        }

        inode->next = __node; // If none of the values are greater than n->n, add __node to the end of the list
        __node->next = NULL;
    }
}

void List_remove_first(List *__list) {

    // check if the head is null
    if (__list->head) {

        if(__list->head == __list->tail) { // if there is only one element

            __list->head = NULL;
            __list->tail = NULL;
            free(__list->head);

        } else { // there are multiple elements

            Node *del = __list->head;
            __list->head = del->next;
            free(del);

        }
    }
}

void List_remove_last(List *__list) {

    // check if the tail is nonnull
    if (__list->tail) {

        if (__list->tail == __list->head) { // if there is only one element, remove "both"

            __list->head = NULL;
            __list->tail = NULL;

        } else {

            // We want to find the second to last element
            Node *n = __list->head;

            while(n->next != __list->tail) { // iterate until we get to the second to last element

                n = n->next;

            }

            Node *temp = __list->tail;
            n->next = NULL;
            __list->tail = n;
            free(temp);

        }
    }
}

// Initialize a new list with integer values of n
// TODO VALIDATE INPUT!!!!!
List *List_init(void) {

    int n = 0;
    double c = 0;
    int count = 0;
    List *list = List_new();

    printf("Enter an integer value for node_%d.n:    ", count);

    scanf("%d", &n);

    if (n < 0) {
        return list;
    }

    printf("Enter a double value for node_%d.c:    ", count);
    scanf("%lf", &c);
    count ++;

    List_prepend_new_node(list, c, n); // add the very first element

    while (true) {

        printf("node_%d.n:    ", count);

        scanf("%d", &n);

        if (n < 0) {
            return list;
        } else {
            printf("node_%d.c:    ", count);
            scanf("%lf", &c);

            List_append_new_node(list, c, n);
        }

        count++;

    }
}

// void List_delete_all(List *__list) {




// }

// // remove the __nth node of our list and deallocate the memory associated
// void List_delete_node(List *__list, size_t __n) {




// }

// Remove all elements that have a double value of __c
// void List_delete_c(List *__list, double __c) {



// }

// Remove all elements that have an integer value of __n
void List_delete_n(List *__list, int __n) {

    Node *p = __list->head;
    Node *next = __list->head;

    while (next) { // next is the node that we actually want to remove

        if (next->n ==  __n) { // then we want to remove this value

            p->next = next->next;
            next->next = NULL;
            free(next);

        }


    }




}

size_t List_size(const List *__list) {

    size_t count = 0;

    Node *n = __list->head;

    while (n) {
        count ++;
        n = n->next;
    }

    return count;
}

void List_print(const List *__list) {

    Node *n = __list->head;
    size_t count = 0;

    while (n) {
        Node_print(n);
        n = n->next;
        count ++;
    }

    printf("List has %lu elements\n", count);
}

void List_print_c(const List *__list) {

    Node *n = __list->head;
    size_t count = 0;

    while (n) {
        Node_print_c(n);
        n = n->next;
        count ++;
    }

    printf("List has %lu elements\n", count);

}

void List_print_n(const List *__list) {

    Node *n = __list->head;
    size_t count = 0;

    while (n) {
        Node_print_n(n);
        n = n->next;
        count ++;
    }

    printf("List has %lu elements\n", count);

}


void modification_valeur(Node *node, int valeur) {

    while (node) {
        node->n += valeur;
        node = node->next;
    }
}

typedef List Polynome;

//  a: array of coefficients
//  len: number of elements in the array
Polynome *Polynome_new(const double *__a, size_t __len) {

    Polynome *poly = List_new();

    for (size_t i = 0; i < __len; i++) {
        List_append_node(poly, Node_new(__a[i], i));
    }

    return poly;
}

// Create nth degree polynomial where all the coefficients are 0.
Polynome *Polynome_zeros(size_t __n) {

    Polynome *poly = List_new();

    for (size_t i = 0; i <= __n; i++) {
        List_append_node(poly, Node_new(0, i));
    }

    return poly;

}

Polynome *Polynome_ones(size_t __n) {
    Polynome *poly = List_new();

    for (size_t i = 0; i <= __n; i++) {
        List_append_node(poly, Node_new(1, i));
    }

    return poly;
}

/**========================================================================
 *!                           Special types of polynomials
 *========================================================================**/

// PLEASE for the love of god do NOT exceed 25...
long long int ejovo_fact(long long int __n) {

    if (__n == 0) {
        return 1;
    } else {
        return __n * ejovo_fact(__n - 1);
    }

}

// return 1 - x + x^2/2 - x3/3!
// Taylor expansion for the exponential function
Polynome *Polynome_exp(size_t __n) {

    Polynome *poly = List_new();

    for (size_t i = 0; i <= __n; i++) {
        List_append_new_node(poly, 1.0 / ejovo_fact(i), i);
    }

    return poly;
}

Polynome *Polynome_sin(size_t __n) {

    Polynome *poly = List_new();

    double sign = 1;


    for (size_t i = 1; i < __n; i += 2) {
        List_append_new_node(poly, sign / ejovo_fact(i), i);
        sign *= -1;
    }

    return poly;

}

Polynome *Polynome_cos(size_t __n) {

    Polynome *poly = List_new();

    double sign = 1;


    for (size_t i = 0; i < __n; i += 2) {
        List_append_new_node(poly, sign / ejovo_fact(i), i);
        sign *= -1;
    }

    return poly;

}

double Polynome_eval(const Polynome *__p, double __x) {

    double p_x = 0;

    Node *node = __p->head;

    while (node) {

        p_x += node->c * pow(__x, node->n);
        node = node->next;
    }

    return p_x;

}

// Vector_d *Polynome_eval_vec(const Polynome *__p, const Vector_d *__v) {



// }

void Polynome_print(const Polynome *__p) {

    int n = 0;

    Node *node = __p->head;

    if (node) {
        printf("%lfx^%d + ", node->c, node->n);
        n++;;
        node = node->next;
    }

    while (node->next) {

        printf("%lfx^%d + ", node->c, node->n);
        n++;
        node = node->next;
    }

    printf("%lfx^%d", node->c, node->n);

    printf("\n");
}

// Low level routine that adds a polynomial
// TODO I should really just learn variadic functions
// we've already implemented the functionality in place. We are just going to take the right side and add it to the left side. After
// this function is called, __lhs and __rhs will have the head and tail pointing to the same elements.
void polysum(Polynome *__lhs, Polynome *__rhs) {

    // iterate through __rhs and add to __lhs
    Node *r = __rhs->head;

    while (r) {

        List_ordered_insert_n(__lhs, r); // The right hand list should now be in scrambles, let's modify it
        r = r->next;
    }

    __rhs->head = __lhs->head;
    __rhs->tail = __lhs->tail;

}

// First clone the elements of __rhs, and then add them to __lhs
Polynome *Polynome_sum(const Polynome *__lhs, const Polynome *__rhs) {

    List *lhs = List_clone(__lhs);
    List *rhs = List_clone(__rhs);
    polysum(lhs, rhs);
    return lhs;

}

// Add multiple polymomes together:
// polysum_var(p1, p2, p3)
void polysum_var(Polynome *__lhs, ...) {

    va_list args;
    va_start(args, __lhs);





}

void polymult_k(Polynome *__lhs, double __k) {

    Node *node = __lhs->head;

    while (node) {

        node->c *= __k;
        node = node->next;
    }
}

// Don't modify the original array
Polynome *Polynome_mult_k(const Polynome *__lhs, double __k) {

    List *lhs = List_clone(__lhs);
    polymult_k(lhs, __k);
    return lhs;

}

void polymult_monome(Polynome *__lhs, const Node *__monome) {

    Node *node = __lhs->head;

    while (node) {

        node->c *= __monome->c;
        node->n += __monome->n;

        node = node->next;
    }
}

Polynome *Polynome_mult_monome(const Polynome *__lhs, const Node *__monome) {

    Polynome *lhs = List_clone(__lhs);
    polymult_monome(lhs, __monome);
    return lhs;

}

// since we can multiply by a monome, now we can multiply by an entire polynomial. That's incredible. Then add up (distributive property) all of the polynomials!
Polynome *polymultpoly(const Polynome *__lhs, const Polynome *__rhs) {

    // I think that I have to duplicate this
    Polynome *lhs = List_clone(__lhs);
    polymult_k(lhs, 0); // effective set lhs to 0

    Node *r = __rhs->head;

    while (r) {

        polysum(lhs, Polynome_mult_monome(__lhs, r));

        r = r->next;
    }

    return lhs;
}

Polynome *Polynome_mult_poly(const Polynome *__lhs, const Polynome *__rhs) {
    return polymultpoly(__lhs, __rhs);
}

