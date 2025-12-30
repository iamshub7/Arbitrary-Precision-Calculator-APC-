#include "apc.h"

/* single, safe helper to free a list */
void delete_list(Dlist **head)
{
    Dlist *temp = *head, *next;
    while (temp)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}

/*
 * Multiplication and division are not fully implemented in the original
 * project. Provide simple stubs so the project compiles and + / - work.
 */
/* Helper function to multiply a number by a single digit and power of 10 */
static int multiply_by_digit(Dlist **head1, Dlist **tail1, int digit, int zeros, Dlist **headR, Dlist **tailR)
{
    if (digit == 0)
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *temp = *tail1;
    int carry = 0;

    /* First multiply by the digit */
    while (temp)
    {
        int prod = (temp->data * digit) + carry;
        insert_at_first(headR, tailR, prod % 10);
        carry = prod / 10;
        temp = temp->prev;
    }
    
    if (carry)
        insert_at_first(headR, tailR, carry);

    /* Then add trailing zeros */
    for (int i = 0; i < zeros; i++)
        insert_at_last(headR, tailR, 0);

    return SUCCESS;
}

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp2 = *tail2;
    int position = 0;

    /* Create temporary lists for intermediate results */
    Dlist *sumHead = NULL, *sumTail = NULL;
    Dlist *prodHead = NULL, *prodTail = NULL;

    /* Process each digit of second number from right to left */
    while (temp2)
    {
        /* Clear previous product */
        if (prodHead)
        {
            delete_list(&prodHead);
            prodTail = NULL;
        }

        /* Multiply first number with current digit and add appropriate zeros */
        multiply_by_digit(head1, tail1, temp2->data, position, &prodHead, &prodTail);

        /* Add to running sum */
        if (!sumHead)
        {
            /* First product becomes the sum */
            sumHead = prodHead;
            sumTail = prodTail;
            prodHead = prodTail = NULL;
        }
        else
        {
            /* Add current product to running sum */
            Dlist *newSumHead = NULL, *newSumTail = NULL;
            addition(&sumHead, &sumTail, &prodHead, &prodTail, &newSumHead, &newSumTail);
            
            /* Update sum and free old sum */
            delete_list(&sumHead);
            sumHead = newSumHead;
            sumTail = newSumTail;
        }

        position++;
        temp2 = temp2->prev;
    }

    /* Move final result to output parameters */
    *headR = sumHead;
    *tailR = sumTail;

    return SUCCESS;
}

/* Helper function to convert list to number */
static int list_to_num(Dlist *head)
{
    int num = 0;
    while (head)
    {
        num = num * 10 + head->data;
        head = head->next;
    }
    return num;
}

/* Helper function to convert number to list */
static void num_to_list(int num, Dlist **head, Dlist **tail)
{
    if (num == 0)
    {
        insert_at_first(head, tail, 0);
        return;
    }

    /* Handle negative numbers */
    if (num < 0)
    {
        flag = 1;  /* Set global flag for negative result */
        num = -num;
    }

    /* Convert number to list */
    while (num > 0)
    {
        insert_at_first(head, tail, num % 10);
        num /= 10;
    }
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Convert lists to numbers */
    int num1 = list_to_num(*head1);
    int num2 = list_to_num(*head2);

    /* Check for division by zero */
    if (num2 == 0)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    /* Perform division */
    int result = num1 / num2;

    /* Convert result back to list */
    num_to_list(result, headR, tailR);

    /* Print result */
    printf("Result: ");
    print_list(*headR);

    return SUCCESS;
}