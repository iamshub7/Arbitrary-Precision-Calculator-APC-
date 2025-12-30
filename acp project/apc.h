#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} Dlist;

/* basic list operations */
int insert_at_last(Dlist **head, Dlist **tail, int data);
int insert_at_first(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void delete_list(Dlist **head);

/* parse input into lists */
void digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[]);

/* arithmetic operations (some may be stubs) */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* helper used by main to compare magnitude */
int sub_fun(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);

/* global flag used to indicate negative result for subtraction */
extern int flag;

#endif /* APC_H */
