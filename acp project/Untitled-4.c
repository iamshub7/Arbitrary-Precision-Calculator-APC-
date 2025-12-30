#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d <-", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    if (head)
		        printf("> ");
	    }
    	printf(" Tail\n");
    }
}

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
	//Allocating the memory for new node
	Dlist *new = malloc(sizeof (Dlist));

	// If the node is not created the returning failure
	if (!new)
	{
		return FAILURE;
	}
	new -> data = data;
	new -> prev = NULL;
	new -> next = NULL;

	// If the list is empty then inserting the node as first node
	if (!*head && !*tail)
	{	
		*head = *tail = new;
		return SUCCESS;
	}
	new -> prev = *tail;
	(*tail) -> next = new;
	*tail = new;
	return SUCCESS;
}

void digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[])
{
    char *num1 = argv[1];
    char *num2 = argv[3];

    for (int i = 0; num1[i] != '\0'; i++)
    {
        if (num1[i] >= '0' && num1[i] <= '9')
            insert_at_last(head1, tail1, num1[i] - '0');
    }

    for (int i = 0; num2[i] != '\0'; i++)
    {
        if (num2[i] >= '0' && num2[i] <= '9')
            insert_at_last(head2, tail2, num2[i] - '0');
    }
}

int insert_at_first(Dlist **head, Dlist **tail, int data)
{
   //creating a new node
   Dlist *new = malloc(sizeof(Dlist));
   if(new == NULL)
   {
       return FAILURE;
   }
   new->data = data;
   new->prev = NULL;
   new->next = NULL;
   
   //1. LIST is empty
   if(*head == NULL)
   {
      *head = new;
      *tail = new;
       return SUCCESS;
   }
   else
   {
       new->next = *head;
       (*head)->prev = new;
       *head = new;
       return SUCCESS;
   }
}

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int carry = 0, data;

    while(temp1 || temp2)
    {
        int d1, d2;

        // For first number
        if (temp1 != NULL)
            d1 = temp1->data;
        else
            d1 = 0;

        // For second number
        if (temp2 != NULL)
            d2 = temp2->data;
        else
            d2 = 0;
            
        data = d1 + d2 + carry;
            if (data > 9)
            {
                data = data % 10;
                carry = (d1 + d2 + carry) / 10; /* compute carry properly */
            }
        insert_at_first(headR, tailR, data);

        if (temp1) 
            temp1 = temp1->prev;
        if (temp2) 
            temp2 = temp2->prev;
    }
    // If carry remains after the last addition
    if (carry)
        insert_at_first(headR, tailR, carry);

    printf("Result: ");
    print_list(*headR);

    return SUCCESS;
}