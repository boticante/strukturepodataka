/*
1. Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (128)
#define MAX_POINTS (30)
#define FILE_NOT_OPEN (-1)

typedef struct _student {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int points;
}student;

int countNoRowsInFile(char*);
void readStudentsFromFile(char*, student*);
void printStudents(student*, int);

int main()
{
    char filename[MAX_LINE];
    int counter = 0;
    student* students;

    printf("Unesite naziv datoteke (s nastavkom) > ");
    scanf(" %s", filename);

    counter = countNoRowsInFile(filename);

    students = (student*)malloc(counter * sizeof(student));

    if (!students)
    {
        printf("Neuspjesna alokacija memorije!\n");
    }

    printf("Broj studenata u datoteci %s je %d.\n", filename, counter);

    readStudentsFromFile(filename, students);
    printStudents(students, counter);

    free(students);

    return EXIT_SUCCESS;
}

int countNoRowsInFile(char* filename)
{
    FILE* filePointer = NULL;
    int counter = 0;
    char buffer[MAX_LINE] = { 0 };

    filePointer = fopen(filename, "r");

    if (!filePointer)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return FILE_NOT_OPEN;
    }

    while (fgets(buffer, MAX_LINE, filePointer) != NULL)
    {
        if (strcmp("\n", buffer) != 0 && strcmp("\r\n", buffer) != 0)
        {
            counter++;
        }
    }

    fclose(filePointer);

    return counter;
}

void readStudentsFromFile(char* filename, student* students)
{
    FILE* filePointer = NULL;
    int i = 0;

    filePointer = fopen(filename, "r");

    if (!filePointer)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return FILE_NOT_OPEN;
    }

    while (fscanf(filePointer, "%s %s %d", students[i].name, students[i].surname, &students[i].points) == 3)
    {
        i++;
    }

    fclose(filePointer);

}

void printStudents(student* students, int counter)
{
    int i;
    double relativePoints;

    for (i = 0; i < counter; i++)
    {
        relativePoints = (double)students[i].points / MAX_POINTS * 100;
        printf("%s %s ima %d bodova sto je %.2f relativnih bodova.\n", students[i].name, students[i].surname, students[i].points, relativePoints);
    }
}