#include "apc.h"

int sub_fun(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    Dlist *temp1 = *head1;
    Dlist *temp2 = *head2;
    int len1 = 0, len2 = 0;
/* Find the lengths */
    while(temp1)
    {
        len1++;
        temp1 = temp1->next;
    }
     while(temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    if(len1 > len2)
       return 1;           // 1st number is larger
    else if(len2 > len1)
       return 0;           // 2nd number is larger
    else if(len1 == len2)  /* If same length, compare digit by digit */
    {
        temp1 = *head1;
        temp2 = *head2;
        while(temp1 && temp2)
        {
            if(temp1->data > temp2->data)
               return 1;
            else if(temp1->data < temp2->data)
                return 0;
            else if(temp1->data == temp2->data)
            {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }
    }
    /* If both are exactly equal */
    return 1; // treat as first ≥ second
}

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Definition goes here */
    int borrow = 0, diff;
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    
    while (t1 && t2)
    {
        int val1 = t1->data - borrow;
        if (val1 < t2->data)
        {
            val1 = val1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        
        diff = val1 - t2->data;
        insert_at_first(headR, tailR, diff);
        
        t1 = t1->prev;
        t2 = t2->prev;
    }
    
    /* Process remaining digits of t1 if any */
    while (t1)
    {
        int val1 = t1->data - borrow;
        if (val1 < 0)
        {
            val1 = val1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        insert_at_first(headR, tailR, val1);
        t1 = t1->prev;
    }

    /* Print result with sign if negative */
    if (flag)
        printf("Result: -");
    else
        printf("Result: ");
    print_list(*headR);

    return SUCCESS;
}