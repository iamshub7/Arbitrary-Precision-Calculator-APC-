#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

/* global flag (used by subtraction to print sign) */
int flag = 0;

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s <num1> <operator> <num2>\n", argv[0]);
		return 1;
	}

	/* Declare the pointers */
	Dlist *head1 = NULL, *tail1 = NULL;
	Dlist *head2 = NULL, *tail2 = NULL;
	Dlist *headR = NULL, *tailR = NULL;

	char operator = argv[2][0];

	switch (operator)
	{
		case '+':
			digit_to_list(&head1, &tail1, &head2, &tail2, argv);
			/* call the function to perform the addition operation */
			addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			break;
		case '-':
			/* call the function to perform the subtraction operation */
			digit_to_list(&head1, &tail1, &head2, &tail2, argv);
			{
				int ret = sub_fun(&head1, &tail1, &head2, &tail2);
				if (ret == 1)
					subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
				else
				{
					subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
					flag = 1;
				}
			}
			break;
		case 'x':
		case '*':
			/* call the function to perform the multiplication operation */
			digit_to_list(&head1, &tail1, &head2, &tail2, argv);
			multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			break;
		case '/':
			/* call the function to perform the division operation */
			digit_to_list(&head1, &tail1, &head2, &tail2, argv);
			division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
			break;
		default:
			printf("Invalid Input:-( Try again...\n");
	}
	return 0;
}
