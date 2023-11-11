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

typedef struct Poly* Position;
struct Poly {
    int coefficient;
    int exponent;
    Position next;
};

int readFromFile(Position);
int printPoly(Position);
int sort(Position);
Position sumPoly(Position, Position);
Position multiplyPoly(Position, Position);

int main()
{
    struct Poly p1;
    struct Poly p2;

    readFromFile(&p1);
    sort(&p1);
    printf("ispis prvog polinoma: \n");
    printPoly(p1.next);

    printf("\n");

    readFromFile(&p2);
    sort(&p2);
    printf("ispis drugog polinoma: \n");
    printPoly(p2.next);

    printf("\n");

    Position sumResult = sumPoly(&p1, &p2);
    printf("Zbroj polinoma je:\n");
    printPoly(sumResult->next);

    printf("\n");

    Position multiplyResult = multiplyPoly(&p1, &p2);
    printf("Umnozak polinoma je:\n");
    printPoly(multiplyResult->next);

    return EXIT_SUCCESS;
}

int readFromFile(Position P)
{
    char filename[MAX_LENGTH];
    P->next = NULL;

    printf("Unesite ime datoteke iz koje zelite ucitat polinom: ");
    scanf(" %s", &filename);
    FILE* filePointer = NULL;
    filePointer = fopen(filename, "r");
    
    if (!filePointer)
    {
        printf("Datoteka ne postoji!\n");
        return;
    }

    while (!feof(filePointer))
    {
        Position current = NULL;
        current = (Position)malloc(sizeof(struct Poly));
        
        if (!current)
        {
            printf("Greska u alokaciji memorije!\n");
        }
        fscanf(filePointer, "%d %d", &current->coefficient, &current->exponent);
        
        current->next = P->next;
        P->next = current;
        P = P->next;
    }
    
    fclose(filePointer);
    printf("Lista ucitana iz datoteke, ");

    return EXIT_SUCCESS;
}

int printPoly(Position P) 
{
    printf("p(x) = ");
    while (P != NULL) 
    {
        printf("%c%dx^%d ", P->coefficient > 0 ? '+' : ' ', P->coefficient, P->exponent);
        P = P->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int sort(Position P) {
    Position new = NULL;
    Position previous = NULL;
    Position temporary = NULL;
    Position last = NULL;

    while (P->next != last)
    {
        previous = P;
        new = P->next;
        while (new->next != last)
        {
            if (new->exponent > new->next->exponent)
            {
                temporary = new->next;
                previous->next = temporary;
                new->next = temporary->next;
                temporary->next = new;
                new = temporary;
            }
            previous = new;
            new = new->next;
        }
        last = new;
    }

    return EXIT_SUCCESS;
}

Position sumPoly(Position p1, Position p2) 
{
    Position sumResult = NULL;
    sumResult = (Position)malloc(sizeof(struct Poly));
    
    if (!sumResult) 
    {
        printf("Greska u alokaciji memorije prilikom zbrajanja polinoma!");
        return EXIT_SUCCESS;
    }
    sumResult->next = NULL;

    p1 = p1->next; 
    p2 = p2->next;
    Position currentResult = sumResult;

    while (p1 != NULL || p2 != NULL) 
    {
        Position new = NULL;
        new = (Position)malloc(sizeof(struct Poly));
        
        if (!new) 
        {
            printf("Greska u alokaciji memorije prilikom zbrajanja polinoma!");
            return EXIT_SUCCESS;
        }
        
        if (p1 == NULL) 
        {
            new->exponent = p2->exponent;
            new->coefficient = p2->coefficient;
            p2 = p2->next;
        }
        else if (p2 == NULL) 
        {
            new->exponent = p1->exponent;
            new->coefficient = p1->coefficient;
            p1 = p1->next;
        }
        else if (p1->exponent == p2->exponent) 
        {
            new->exponent = p1->exponent;
            new->coefficient = p1->coefficient + p2->coefficient;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exponent > p2->exponent) 
        {
            new->exponent = p2->exponent;
            new->coefficient = p2->coefficient;
            p2 = p2->next;
        }
        else if (p1->exponent < p2->exponent) 
        {
            new->exponent = p1->exponent;
            new->coefficient = p1->coefficient;
            p1 = p1->next;
        }

        new->next = NULL;
        currentResult->next = new;
        currentResult = currentResult->next;
    }

    return sumResult;
}

Position multiplyPoly(Position p1, Position p2) 
{
    p1 = p1->next; 
    p2 = p2->next;
    Position multiplyResult = NULL;
    
    multiplyResult = (Position)malloc(sizeof(struct Poly));
    
    if (!multiplyResult) 
    {
        printf("Greska u alokaciji memorije prilikom mnozenja polinoma!");
        return NULL;
    }
    multiplyResult->next = NULL;

    Position headPoly2 = p2;

    while (p1 != NULL) 
    {
        Position productPoly = NULL;
        productPoly = (Position)malloc(sizeof(struct Poly));
        
        if (!productPoly) 
        {
            printf("Greska u alokaciji memorije prilikom mnozenja polinoma!");
            return EXIT_SUCCESS;
        }
        productPoly->next = NULL;

        Position currentResult = productPoly;

        while (p2 != NULL) 
        {
            Position new = NULL;
            new = (Position)malloc(sizeof(struct Poly));
            
            if (!new) 
            {
                printf("Greska u alokaciji memorije prilikom mnozenja polinoma!");
                return EXIT_SUCCESS;
            }

            new->exponent = p1->exponent + p2->exponent;
            new->coefficient = p1->coefficient * p2->coefficient;
            new->next = NULL;
            currentResult->next = new;
            currentResult = currentResult->next;
            p2 = p2->next;
        }

        Position newProductPoly = sumPoly(productPoly, multiplyResult);
        free(multiplyResult);
        multiplyResult = newProductPoly;

        p1 = p1->next;
        p2 = headPoly2;
    }

    return multiplyResult;
}
