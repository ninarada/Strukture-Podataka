#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _StogElement;
typedef struct _StogElement *Pozicija;

typedef struct _StogElement
{
    double broj;
    Pozicija next;
} StogElement;

int CitanjePostfixaIzDatoteke(char *nazivDatoteke, double *rezultat);
Pozicija StvaranjeElementa(double broj);
int Push(Pozicija head, double broj);
int DodavanjeIza(Pozicija el, Pozicija noviEl);
int Pop(double *iznosEl, Pozicija head);
int IzbrisiIza(Pozicija el);
int IzbrisiSve(Pozicija head);
int IzvodenjeOperacija(Pozicija head, char operacija);

int main(void)
{
    double rez = 0;
    CitanjePostfixaIzDatoteke("postfix.txt", &rez);
    printf("%lf ", rez);
    return 0;
}

Pozicija StvaranjeElementa(double broj)
{
    Pozicija noviElement = NULL;
    noviElement = (Pozicija)malloc(sizeof(StogElement));
    if (noviElement == NULL)
    {
        perror("Greska alociranja memorije.\n");
        return NULL;
    }
    noviElement->broj = broj;
    noviElement->next = NULL;
    return noviElement;
}

int DodavanjeIza(Pozicija el, Pozicija noviEl)
{
    noviEl->next = el->next;
    el->next = noviEl;
    return EXIT_SUCCESS;
}

int Push(Pozicija head, double broj)
{
    Pozicija noviElement = StvaranjeElementa(broj);
    if (noviElement == NULL)
    {
        return -1;
    }
    DodavanjeIza(head, noviElement);
    return EXIT_SUCCESS;
}

int IzbrisiIza(Pozicija el)
{
    Pozicija temp = el->next;
    if (temp == NULL)
    {
        return EXIT_SUCCESS;
    }
    el->next = el->next->next;
    free(temp);
    return EXIT_SUCCESS;
}

int IzbrisiSve(Pozicija head)
{
    while (head->next != NULL)
    {
        IzbrisiIza(head);
    }
    return EXIT_SUCCESS;
}

int Pop(double *iznosEl, Pozicija head)
{

    if (head->next == NULL)
    {
        perror("Postfix neispravan. Provjeri postfix.\n");
        return -1;
    }
    *iznosEl = head->next->broj;
    IzbrisiIza(head);
    return EXIT_SUCCESS;
}

int IzvodenjeOperacija(Pozicija head, char operacija)
{
    double operand1 = 0;
    double operand2 = 0;
    int status = EXIT_SUCCESS;
    double rezultat = 0;

    status = Pop(&operand2, head);
    if (status != EXIT_SUCCESS)
    {
        return -1;
    }

    status = Pop(&operand1, head);
    if (status != EXIT_SUCCESS)
    {
        return -1;
    }

    switch (operacija)
    {
    case '+':
        rezultat = operand1 + operand2;
        Push(head, rezultat);
        break;

    case '-':
        rezultat = operand1 - operand2;
        Push(head, rezultat);
        break;

    case '*':
        rezultat = operand1 * operand2;
        Push(head, rezultat);
        break;

    case '/':
        if (operand2 == 0)
        {
            printf("Ne moze se dijeliti s 0. Provjerite postfix.\n");
            return -1;
        }
        rezultat = operand1 / operand2;
        Push(head, rezultat);
        break;

    default:
        printf("Operacija nije ispravnja.\n");
        return -1;
        break;
    }
    return EXIT_SUCCESS;
}

int CitanjePostfixaIzDatoteke(char *nazivDatoteke, double *rezultat)
{
    FILE *datoteka = NULL;
    int bytes = 0;
    char *buffer = NULL;
    char *bufferP = NULL;
    int duzinaDatoteke = 0;

    double broj = 0;
    StogElement head = {.broj = 0, .next = NULL};
    Pozicija headP = &head;
    int status = EXIT_SUCCESS;
    char operacija = 0;

    datoteka = fopen(nazivDatoteke, "rb");
    if (datoteka == NULL)
    {
        perror("Greska kod otvaranja datoteke.\n");
        return -1;
    }

    fseek(datoteka, 0, SEEK_END);
    duzinaDatoteke = ftell(datoteka);
    rewind(datoteka);

    buffer = (char *)calloc(duzinaDatoteke + 1, sizeof(char));
    if (buffer == NULL)
    {
        perror("Greska kod alociranja memorije.\n");
        return -1;
    }

    fread(buffer, sizeof(char), duzinaDatoteke, datoteka);
    fclose(datoteka);

    bufferP = buffer;
    while (strlen(bufferP) > 0)
    {
        if (sscanf(bufferP, " %lf %n", &broj, &bytes) == 1)
        {
            Push(headP, broj);
            bufferP += bytes;
        }
        else
        {
            if (sscanf(bufferP, " %c %n", &operacija, &bytes) == 1)
            {
                IzvodenjeOperacija(headP, operacija);
                bufferP += bytes;
            }
        }
    }

    if (headP->next == NULL)
    {
        return -1;
    }
    *rezultat = headP->next->broj;

    free(buffer);
    IzbrisiSve(headP);
    return EXIT_SUCCESS;
}