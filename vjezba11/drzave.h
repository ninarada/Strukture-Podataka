#pragma once
#ifndef DRZAVE_H
#define DRZAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAZIV 64
#define HASH_VELICINA 11

struct _Stablo;
typedef struct _Stablo *positionGradovi;
typedef struct _Stablo
{
    char grad[MAX_NAZIV];
    long int stanovnici;
    positionGradovi left;
    positionGradovi right;
} Stablo;

struct _Lista;
typedef struct _Lista *positionLista;
typedef struct _Lista
{
    char drzava[MAX_NAZIV];
    positionGradovi rootGradovi;
    positionLista next;
} Lista;

// stablo (gradovi):
positionGradovi stvaranjeNovogGrada(char *grad, long int stanovnici);
positionGradovi dodavanjeGrada(positionGradovi current, positionGradovi novi);
int printGradovi(positionGradovi current); // inorder
positionGradovi izbrisiStablo(positionGradovi current);

// lista (drzave):
positionLista stvoriNovuDrzavu(char *drzava, positionGradovi root);
int dodavanjeDrzave(positionLista head, positionLista new); // sortirano
int printDrzave(positionLista head);
int izbrisiListu(positionLista head);

positionGradovi citanjeGradova(char *nazivDatoteke, positionGradovi root);
int citanjeDrzava(char *nazivDatoteke, positionLista tablica[HASH_VELICINA]);
int traziDrzavu(char *drzava, long int broj, positionLista headP);
positionGradovi traziGradove(long int broj, positionGradovi root);

#endif