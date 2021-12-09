#include "artikli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArtikliP StvaranjeArtikla(char *naziv, int kolicina, double cijena)
{
    ArtikliP noviArtikl = NULL;
    noviArtikl = (ArtikliP)malloc(sizeof(Artikli));
    if (noviArtikl == NULL)
    {
        perror("Greska alokacije memorije.\n");
        return NULL;
    }
    noviArtikl->next = NULL;
    noviArtikl->cijena = cijena;
    noviArtikl->kolicina = kolicina;
    strcpy(noviArtikl->naziv, naziv);
    return noviArtikl;
}

int SortiranoDodavanjeArtikla(ArtikliP head, char *naziv, int kolicina, double cijena)
{
    ArtikliP a = StvaranjeArtikla(naziv, kolicina, cijena);

    while (head->next != NULL && strcmp(head->next->naziv, a->naziv) < 0)
    {
        head = head->next;
    }
    a->next = head->next;
    head->next = a;

    return 0;
}

int ObrisiArtikl(ArtikliP head, ArtikliP a)
{
    while (head->next != NULL && strcmp(head->next->naziv, a->naziv) != 0)
    {
        head = head->next;
    }
    if (head->next == NULL)
    {
        printf("Artikl ne postoji u listi.\n");
        return 1;
    }
    head->next = head->next->next;
    free(a);
    return 0;
}

int ObrisiSveArtikle(ArtikliP head)
{
    ArtikliP temp;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }
    return 0;
}

int IspisArtikala(ArtikliP a)
{
    a = a->next;
    while (a != NULL)
    {
        printf("%-10s %-2d %.2f\n", a->naziv, a->kolicina, a->cijena);
        a = a->next;
    }
    return 0;
}

ArtikliP TrazenjeArtikla(ArtikliP a, char *naziv)
{
    a = a->next;
    while (a != NULL && strcmp(a->naziv, naziv) != 0)
    {
        a = a->next;
    }
    return a;
}

int IspisArtikla(ArtikliP a)
{
    printf("%-10s %-2d %.2f\n", a->naziv, a->kolicina, a->cijena);
    return 0;
}