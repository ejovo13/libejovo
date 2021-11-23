#ifndef EJOVO_LIST_H
#define EJOVO_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// header files to declare functions declared in TP6
typedef struct node_t {

    double c;
    int n;
    struct node_t *next;

} Node;

// Malloc a new Node
Node *Node_new(double __c, int __n) {

    Node *n = (Node *) malloc(sizeof(Node));
    n->c = __c;
    n->n = __n;
    n->next = NULL;

    return n;

}

void Node_print(const Node *__node) {
    printf("Node at %x :=  .c: %lf, .n: %d, .next: %x\n", __node, __node->c, __node->n, __node->next);
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

// So my linked list is just going to be an object that stores a header node and has a lot of function
typedef struct list_t {
    Node *head;
    Node *tail;
} List;


List *List_new() {

    List *l = (List *) malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;

    return l;

}


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

    Node *node = __list->head; // traverse the original list

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

    // if list->head is null, insert at the beginning
    if (!__list->head) {
        __list->head = __node;
        __list->tail = __node;
    } else {

        // iterate the list until we find a next element that is larger than __node->n
        Node *n = __list->head;

        while(n->next) {

            if (n->next->n > __node->n) {

                // insert this node at n->next
                Node *temp = n->next;
                n->next = __node;
                __node->next = temp;

                // free(temp);
                return;

            } else if (n->next->n == __node->n) { // duplicate value, add c1 and c2

                n->next->c = __node->c + n->next->c;
                return;

            }

            n = n->next;
        }

        n->next = __node; // If none of the values are greater than n->n, add __node to the end of the list
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

void List_delete_all(List *__list) {




}

// remove the __nth node of our list and deallocate the memory associated
void List_delete_node(List *__list, size_t __n) {




}

// Remove all elements that have a double value of __c
void List_delete_c(List *__list, double __c) {



}

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

double Polynome_eval(const Polynome *__p, double __x) {

    double p_x = 0;

    Node *node = __p->head;

    while (node) {

        p_x += node->c * pow(__x, node->n);
        node = node->next;
    }

    return p_x;

}







#endif