#include "racun.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CitanjeRacunaIzDatoteke(RacuniP head, char *naziv)
{
    FILE *datoteka = NULL;
    char buffer[MAX_LINE];
    char *bufferP = NULL;
    int duzinaDatoteke = 0;
    char naz[20];
    char *nap = naz;
    int br;
    double cij;
    RacuniP noviRacun;
    Artikli art;
    art.next = NULL;

    noviRacun = (RacuniP)malloc(sizeof(Racuni));
    if (noviRacun == NULL)
    {
        perror("Greska kod alociranja memorije.\n");
        return -1;
    }
    noviRacun->artikliLista = art;
    noviRacun->next = NULL;

    datoteka = fopen(naziv, "r");
    if (datoteka == NULL)
    {
        perror("Greska kod otvaranja datoteke.\n");
        return -1;
    }

    fgets(buffer, MAX_LINE, datoteka);
    noviRacun->date = CitanjeDatuma(buffer);

    while (!feof(datoteka))
    {

        fgets(buffer, MAX_LINE, datoteka);
        if (sscanf(buffer, " %s %d %lf", nap, &br, &cij) == 3)
        {
            SortiranoDodavanjeArtikla(&noviRacun->artikliLista, naz, br, cij);
        }
    }
    fclose(datoteka);

    while (head->next != NULL && UsporedbaDatuma(head->next->date, noviRacun->date) < 0)
    {
        head = head->next;
    }
    noviRacun->next = head->next;
    head->next = noviRacun;

    return 0;
}

int IspisRacuna(RacuniP x)
{
    while (x != NULL)
    {

        IspisDatuma(x->date);
        IspisArtikala(&x->artikliLista);

        x = x->next;
    }

    return 0;
}

int Citanje(RacuniP head, char *naziv)
{
    FILE *datoteka = NULL;
    char buffer[MAX_LINE];
    char buffer2[MAX_LINE];
    char *cp = buffer;
    int n = 0;

    datoteka = fopen(naziv, "r");
    if (datoteka == NULL)
    {
        perror("Greska kod alociranja memorije.\n");
        return -1;
    }

    while (!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        sscanf(cp, " %s", buffer2);
        CitanjeRacunaIzDatoteke(head, buffer2);
    }
    return 0;
}

ArtikliP UkupnoPotrosenoNaArtikl(RacuniP head, char *trazeniArtikl, DatumP x, DatumP y)
{
    ArtikliP trazeni = NULL;
    ArtikliP temp = NULL;

    int ukKolicina = 0;
    double ukCijena = 0;

    trazeni = (ArtikliP)malloc(sizeof(Artikli));

    while (head != NULL)
    {
        if (UsporedbaDatuma(head->date, x) >= 0 && UsporedbaDatuma(head->date, y) <= 0)
        {
            temp = TrazenjeArtikla(&head->artikliLista, trazeniArtikl);
            if (temp != NULL)
            {
                ukCijena = ukCijena + temp->cijena;
                ukKolicina = ukKolicina + temp->kolicina;
            }
        }
        head = head->next;
    }
    trazeni->cijena = ukCijena;
    trazeni->kolicina = ukKolicina;
    strcpy(trazeni->naziv, trazeniArtikl);
    trazeni->next = NULL;

    return trazeni;
}

int IzbrisiSveRacune(RacuniP head)
{
    RacuniP temp;
    while (head->next != NULL)
    {
        temp = head->next;
        ObrisiSveArtikle(&temp->artikliLista);
        free(temp->date);
        free(temp);
        head->next = head->next->next;
    }
    return 0;
}