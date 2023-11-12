/*
5. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack* Position;
struct Stack {
	int element;
	Position next;
};

int readPostfixFromFile(Position head);
int push(Position,int);
int pop(Position,int*);

int main()
{
	struct Stack Head;
	Head.next = NULL;
	readPostfixFromFile(&Head);
	printf("\nRezultat je %d\n", Head.next->element);

	while (1) 
	{
		int poppedElement;
		int afterPop = pop(&Head, &poppedElement);
		if (afterPop == 0)
			break;
	}

	return EXIT_SUCCESS;
}

int readPostfixFromFile(Position head)
{
	FILE* filePointer = NULL;
	filePointer = fopen("postfix.txt", "r");
	
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return EXIT_FAILURE;
	}

	char operatorOrOperand[10];
	int x, y; // operandi

	while (!feof(filePointer))
	{
		fscanf(filePointer, "%s", operatorOrOperand);
		printf("|%s|\n", operatorOrOperand);

		if (strcmp(operatorOrOperand, "+") == 0) 
		{
			pop(head, &x), pop(head, &y);
			push(head, y + x);
		}
		else if (strcmp(operatorOrOperand, "-") == 0)
		{
			pop(head, &x), pop(head, &y);
			push(head, y - x);
		}
		else if (strcmp(operatorOrOperand, "*") == 0)
		{
			pop(head, &x), pop(head, &y);
			push(head, y * x);
		}
		else if (strcmp(operatorOrOperand, "/") == 0)
		{
			pop(head, &x), pop(head, &y);
			push(head, y / x);
		}
		else
			push(head, atoi(operatorOrOperand));
	}
	
	return EXIT_SUCCESS;
}

int push(Position head, int element)
{
	Position new;
	new = (Position)malloc(sizeof(struct Stack));
	
	if (!new)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}
	new->element = element;
	new->next = head->next;
	head->next = new;

	return EXIT_SUCCESS;
}

int pop(Position head, int* element)
{
	Position temporary = NULL;
	
	if (head->next == NULL) 
	{
		printf("\nStog je prazan!\n");
		return EXIT_SUCCESS;
	}
	else 
	{
		temporary = head->next;
		*element = temporary->element;
		head->next = temporary->next;
		free(temporary);
		
		return EXIT_FAILURE;
	}
}
