/*
4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 50

typedef struct Polinom* listaPoli;
struct Polinom {
    int koef;
    int pot;
    listaPoli next;
};

int readFromFile(listaPoli);
int printPolinom(listaPoli);

int main() {
    struct Polinom p1;
    struct Polinom p2;

    readFromFile(&p1);
    printf("Ispis prvog polinoma: \n");
    printPolinom(p1.next);

    readFromFile(&p2);
    printf("Ispis drugog polinoma: \n");
    printPolinom(p2.next);

    return EXIT_SUCCESS;
}

int readFromFile(listaPoli P)
{
    char filename[MAX_LENGTH];
    int counter = 0;
    P->next = NULL;

    printf("Unesite ime datoteke iz koje zelite ucitat polinom: ");
    scanf(" %s", &filename);
    FILE* filePointer = NULL;
    filePointer = fopen(filename, "r");
    
    if (filePointer == NULL)
    {
        printf("Datoteka ne postoji!\n");
        return;
    }

    while (!feof(filePointer))
    {
        listaPoli q = NULL;
        q = (listaPoli)malloc(sizeof(struct Polinom));
        
        if (!q)
        {
            printf("Greska u alokaciji memorije!\n");
        }
        fscanf(filePointer, "%d %d", &q->koef, &q->pot);
        
        q->next = P->next;
        P->next = q;
        P = P->next;
    }
    
    fclose(filePointer);
    printf("Lista ucitana iz datoteke.\n");

    return EXIT_SUCCESS;
}

int printPolinom(listaPoli P) 
{
    printf("p(x) = ");
    while (P != NULL) 
    {
        printf("%c%dx^%d ", P->koef > 0 ? '+' : ' ', P->koef, P->pot);
        P = P->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
