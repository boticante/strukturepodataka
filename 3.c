/*
3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

typedef struct person* Position;
struct person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
};

int insertAtFront(Position head);
int printList(Position head);
int insertAtEnd(Position head);
int findPerson(Position head);
int deletePerson(Position head);
int addAfter(Position head);
int addBefore(Position head);
int sort(Position head);
int write(Position head);
int readFromFile(Position head);

int main()
{
	struct person head;
	head.next = NULL;
	int number;
	while (1)
	{
		printf("Unesite broj(0-10):\n 1 - Dinamicki dodati novi element na pocetak liste\n 2 - Ispisati listu\n 3 - Dinamicki dodati novi element na kraj liste\n 4 - Pronaci element u listi (po prezimenu)\n 5 - Obrisati odredeni element iz liste\n 6 - Dinamicki dodati novi element iza odredenog elementa\n 7 - Dinamicki dodati novi element ispred odredenog elementa\n 8 - Sortirati listu po prezimenima\n 9 - Upisati listu u datoteku\n 10 - Procitati listu iz datoteke\n 0 - Izlazak iz programa\n");
		scanf(" %d", &number);

		if (number == 1)
			insertAtFront(&head);
		else if (number == 2)
			printList(head.next);
		else if (number == 3)
			insertAtEnd(&head);
		else if (number == 4)
			findPerson(head.next);
		else if (number == 5)
			deletePerson(&head);
		else if (number == 6)
			addAfter(&head);
		else if (number == 7)
			addBefore(&head);
		else if (number == 8)
			sort(&head);
		else if (number == 9)
			write(head.next);
		else if (number == 10)
			readFromFile(&head);
		else if (number == 0)
			break;
		else
			printf("Greska, pogresan unos znamenke!\n");
	}

	return EXIT_SUCCESS;
}

int insertAtFront(Position head)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(struct person));

	if (!newPerson)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	printf("Unesite ime osobe: ");
	scanf("%s", newPerson->name);

	printf("Unesite prezime osobe: ");
	scanf("%s", newPerson->surname);

	printf("Unesite godinu rodenja osobe: ");
	scanf("%d", &newPerson->birthYear);

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int printList(Position head)
{
	while (head != NULL)
	{
		printf("%s %s %d \n", head->name, head->surname, head->birthYear);
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int insertAtEnd(Position head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}

	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(struct person));

	if (!newPerson)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	printf("Unesite ime osobe: ");
	scanf("%s", newPerson->name);

	printf("Unesite prezime osobe: ");
	scanf("%s", newPerson->surname);

	printf("Unesite godinu rodenja osobe: ");
	scanf("%d", &newPerson->birthYear);

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int findPerson(Position head)
{
	char surname[MAX_LENGTH] = { 0 };

	if (head == NULL) {
		printf("Greska!");
		return NULL;
	}

	printf("\nUnesi prezime:");
	scanf(" %s", &surname);

	while (head->next != NULL && strcmp(surname, head->surname) != 0)
	{
		head = head->next;
	}

	if (!strcmp(surname, head->surname))
		printf("\nOsoba pronadena ->\t ime: %s\t prezime: %s\t godina rodenja: %d\n", head->name, head->surname, head->birthYear);
	else
		printf("\nOsoba ne postoji!\n");

	return EXIT_SUCCESS;
}


int deletePerson(Position head)
{
	Position previous = NULL;
	char deleteSurname[MAX_LENGTH];

	printf("Unesite prezime osobe koju zelite izbrisati: ");
	scanf("%s", deleteSurname);

	if (!deleteSurname)
	{
		printf("Osoba ne postoji!\n");
	}

	while (head->next != NULL && strcmp(deleteSurname, head->surname) != 0)
	{
		previous = head;
		head = head->next;
	}

	if (previous != NULL && strcmp(deleteSurname, head->surname) == 0)
	{
		previous->next = head->next;
		free(head);
	}

	return EXIT_SUCCESS;
}

int addAfter(Position head)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(struct person));

	printf("Unesi ime osobe: ");
	scanf(" %s", newPerson->name);
	printf("Unesi prezime osobe: ");
	scanf(" %s", newPerson->surname);
	printf("Unesi godinu rodenja osobe: ");
	scanf(" %d", &newPerson->birthYear);

	char afterSurname[MAX_LENGTH];
	printf("Unesi prezime osobe iza koje zelite dodati novu osobu: ");
	scanf(" %s", afterSurname);
	
	while (head->next != NULL && strcmp(afterSurname, head->surname) != 0)
	{
		head = head->next;
	}
	if (strcmp(afterSurname, head->surname) == 0)
	{
		newPerson->next = head->next;
		head->next = newPerson;
		printf("Osoba unesena.\n");
	}
	else
	{
		printf("Greska - nema osobe s tim prezimenom!\n");
	}
	return EXIT_SUCCESS;
}

int addBefore(Position head)
{

	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(struct person));

	printf("Unesi ime osobe: ");
	scanf(" %s", newPerson->name);
	printf("Unesi prezime osobe: ");
	scanf(" %s", newPerson->surname);
	printf("Unesi godinu rodenja osobe: ");
	scanf(" %d", &newPerson->birthYear);

	char beforeSurnamne[MAX_LENGTH];
	printf("Unesi prezime osobe ispred koje zelite dodati novu osobu: ");
	scanf(" %s", beforeSurnamne);
	
	while (head->next != NULL && strcmp(beforeSurnamne, head->next->surname) != 0)
	{
		head = head->next;
	}
	if (head->next != NULL) {
		newPerson->next = head->next;
		head->next = newPerson;
		printf("Osoba unesena.\n");
	}
	else {
		printf("Greska - nema osobe s tim prezimenom!\n");
	}
	return EXIT_SUCCESS;
}

int sort(Position head)
{
	Position current = NULL;
	Position previous = NULL;
	Position temp = NULL;
	Position last = NULL;
	
	while (head->next != last)
	{
		previous = head;
		current = head->next;
		
		while (current->next != last)
		{
			if (strcmp(current->surname, current->next->surname) > 0)
			{
				temp = current->next;
				previous->next = temp;
				current->next = temp->next;
				temp->next = current;

				current = temp;
			}

			previous = current;
			current = current->next;
		}
		last = current;
	}

	printf("Lista je sortirana.\n");
	return EXIT_SUCCESS;
}

int write(Position head)
{
	char filename[MAX_LENGTH];
	printf("Unesite ime datoteke u koje zelite upisati listu: ");
	scanf(" %s", &filename);
	FILE* filePointer = NULL;
	filePointer = fopen(filename, "w");
	if (filePointer == NULL)
	{
		printf("Greska!\n");
		return EXIT_FAILURE;
	}
	while (head != NULL)
	{
		fprintf(filePointer, "%s\t %s\t %d\t\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}
	printf("Lista ispisana u datoteku.\n");
	fclose(filePointer);
	return EXIT_SUCCESS;
}

int readFromFile(Position head)
{
	char filename[MAX_LENGTH];
	int counter = 0;
	head->next = NULL;
	Position P = head;
	Position q = NULL;

	printf("Unesite ime datoteke iz koje zelite ucitat listu: ");
	scanf(" %s", &filename);
	FILE* filePointer = NULL;
	filePointer = fopen(filename, "r");
	
	if (filePointer == NULL)
	{
		printf("Greska!\n");
		return EXIT_FAILURE;
	}

	while (!feof(filePointer))
	{
		if (fgetc(filePointer) == '\n')
			counter++;
	}
	rewind(filePointer);
	
	if (counter != 0)
	{
		for (int i = 0; i < counter; i++) {
			q = (Position)malloc(sizeof(struct person));
			if (q == NULL)
			{
				printf("Greska u alokaciji memorije!\n");
				return EXIT_FAILURE;
			}
			fscanf(filePointer, "%s %s %d", q->name, q->surname, &q->birthYear);
			
			q->next = P->next;
			P->next = q;
			P = P->next;
		}
	}
	fclose(filePointer);

	printf("Lista ucitana iz datoteke.\n");

	return EXIT_SUCCESS;
}
