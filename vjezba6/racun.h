#ifndef RACUN_H
#define RACUN_H

#include "artikli.h"
#include "datum.h"

#define MAX 20
#define MAX_LINE 1024

struct _Racuni;
typedef struct _Racuni *RacuniP;

typedef struct _Racuni
{
    DatumP date;
    Artikli artikliLista;
    RacuniP next;
} Racuni;

int CitanjeRacunaIzDatoteke(RacuniP head, char *naziv);
int IspisRacuna(RacuniP x);
int Citanje(RacuniP head, char *naziv);
ArtikliP UkupnoPotrosenoNaArtikl(RacuniP head, char *trazeniArtikl, DatumP x, DatumP y);
int IzbrisiSveRacune(RacuniP a);

#endif