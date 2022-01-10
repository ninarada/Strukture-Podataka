#pragma once
#ifndef DRZAVEB_H
#define DRZAVEB_H

// b.) zadatak - drzave u stablu, a gradovi u vezanim listama

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAZIV 64

struct _ListaGradova;
typedef struct _ListaGradova *positionListaGradova;
typedef struct _ListaGradova
{
    char nazivGrada[MAX_NAZIV];
    long int brojStanovnika;
    positionListaGradova next;
} ListaGradova;

struct _StabloDr;
typedef struct _StabloDr *positionDrzave;
typedef struct _StabloDr
{
    char nazivDrzave[MAX_NAZIV];
    positionListaGradova gradovi;
    positionDrzave left;
    positionDrzave right;

} StabloDr;

// gradovi - lista:
positionListaGradova BstvaranjeNovogGrada(char *naziv, long int brStanovnika);
int BdodavanjeGrada(positionListaGradova head, positionListaGradova novi);
int BprintGradovi(positionListaGradova head);
int BizbrisiGradove(positionListaGradova head);
int BtraziGradove(positionListaGradova head, long int broj);

// drzave - stablo:
positionDrzave BstvaranjeNoveDrzave(char *naziv, positionListaGradova gradovi);
positionDrzave BdodavanjeDrzave(positionDrzave current, positionDrzave nova);
int BprintDrzave(positionDrzave current);
int BizbrisiDrzave(positionDrzave current);
positionDrzave BtraziDrzavu(positionDrzave current, char *naziv, long int broj);

int BcitanjeGradova(char *nazDat, positionListaGradova head);
positionDrzave BcitanjeDrzava(char *nazDat, positionDrzave current);

#endif