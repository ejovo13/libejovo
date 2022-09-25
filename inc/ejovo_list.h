#pragma once

#ifndef EJOVO_LIST_H
#define EJOVO_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>
#include "ejovo_matrix_generic.h"

// header files to declare functions declared in TP6
typedef struct node_t {

    double c;
    int n;
    struct node_t *next;

} Node;

// Malloc a new Node
Node *Node_new(double __c, int __n);

void Node_print(const Node *__node);

void Node_print_n(const Node *__node);

void Node_print_c(const Node *__node);

Node *Node_clone(const Node *__node);

// So my linked list is just going to be an object that stores a header node and has a lot of function
typedef struct list_t {
    Node *head;
    Node *tail;
} List;


List *List_new();

// List *List_clone_node(const Node *__node);

// List *List_from_node()

void List_append_node(List *__list, Node *__node);

// wicked fast
void List_prepend_node(List *__list, Node *__node);

List *List_clone(const List *__list);

// A list can insert an element in any position, prepend to the beginning, or add to the end
void List_append_new_node(List *__list, double __c, int __n);

void List_prepend_new_node(List *__list, double __c, int __n);

// Insert an element into a list ordered by n
// assume that the list is already sorted in ascending order
void List_ordered_insert_n(List *__list, Node *__node);

void List_remove_first(List *__list);

void List_remove_last(List *__list);

// Initialize a new list with integer values of n
// TODO VALIDATE INPUT!!!!!
List *List_init(void);

void List_delete_all(List *__list);

// remove the __nth node of our list and deallocate the memory associated
void List_delete_node(List *__list, size_t __n);

// Remove all elements that have a double value of __c
void List_delete_c(List *__list, double __c);

// Remove all elements that have an integer value of __n
void List_delete_n(List *__list, int __n);

size_t List_size(const List *__list);

void List_print(const List *__list);

void List_print_c(const List *__list);

void List_print_n(const List *__list);


void modification_valeur(Node *node, int valeur);

typedef List Polynome;

//  a: array of coefficients
//  len: number of elements in the array
Polynome *Polynome_new(const double *__a, size_t __len);

// Create nth degree polynomial where all the coefficients are 0.
Polynome *Polynome_zeros(size_t __n);

Polynome *Polynome_ones(size_t __n);

/**========================================================================
 *!                           Special types of polynomials
 *========================================================================**/

// PLEASE for the love of god do NOT exceed 25...
long long int ejovo_fact(long long int __n);

// return 1 - x + x^2/2 - x3/3!
// Taylor expansion for the exponential function
Polynome *Polynome_exp(size_t __n);

Polynome *Polynome_sin(size_t __n);

Polynome *Polynome_cos(size_t __n);

double Polynome_eval(const Polynome *__p, double __x);

Vector_d *Polynome_eval_vec(const Polynome *__p, const Vector_d *__v);

void Polynome_print(const Polynome *__p);

// Low level routine that adds a polynomial
// TODO I should really just learn variadic functions
// we've already implemented the functionality in place. We are just going to take the right side and add it to the left side. After
// this function is called, __lhs and __rhs will have the head and tail pointing to the same elements.
void polysum(Polynome *__lhs, Polynome *__rhs);

// First clone the elements of __rhs, and then add them to __lhs
Polynome *Polynome_sum(const Polynome *__lhs, const Polynome *__rhs);

// Add multiple polymomes together:
// polysum_var(p1, p2, p3)
void polysum_var(Polynome *__lhs, ...);

void polymult_k(Polynome *__lhs, double __k);

// Don't modify the original array
Polynome *Polynome_mult_k(const Polynome *__lhs, double __k);

void polymult_monome(Polynome *__lhs, const Node *__monome);

Polynome *Polynome_mult_monome(const Polynome *__lhs, const Node *__monome);

// since we can multiply by a monome, now we can multiply by an entire polynomial. That's incredible. Then add up (distributive property) all of the polynomials!
Polynome *polymultpoly(const Polynome *__lhs, const Polynome *__rhs);

Polynome *Polynome_mult_poly(const Polynome *__lhs, const Polynome *__rhs);





#endif