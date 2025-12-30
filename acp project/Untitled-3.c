#include "apc.h"

/* Helper: delete the list */
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

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Definition goes here */
    Dlist *temp1 = *tail1; 
    Dlist *temp2 = *tail2;    // start from least significant digit
    Dlist *headT1 = NULL, *tailT1 = NULL; // temp product
    Dlist *headT2 = NULL, *tailT2 = NULL; // cumulative sum
    int count = 0, carry = 0;

    while(temp2)
    {
        for(int i=0; i<count; i++)
        {
            insert_at_last(headR2, tailR2, 0);
        }
        while(temp1)
        {
            int res = (temp1->data * temp2->data) + carry;
            if(temp2->next == NULL)
            insert_at_first(headR1, tailR1, res%10);
            
            carry = res/10;
            temp1 = temp1->prev;
        }
        if(temp2->next != NULL)
        {
            addition(&headT1, &tailT1, &headT2, &tailT2, headR, tailR);
            delete_list(headR1);
            delete_list(headR2);

            headR1 = headR;
            tailR1 = tailR;
            headR = tailR = NULL;
        }
        count++;
        temp2 = temp2->prev;
        temp1 = tail1;
    }
}