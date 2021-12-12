#ifndef STABLO_H
#define STABLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Stablo;
typedef struct _Stablo *Position;

typedef struct _Stablo
{
    int el;
    Position left;
    Position right;
} Stablo;

struct _red;
typedef struct _red *RedP;
typedef struct _red
{
    Position x;
    RedP next;
} red;

Position create(int broj);                    // stvara novi element
Position add(Position current, Position new); // dodaje novi elment u stablo
int printInorder(Position current);
int printPreorder(Position current);
int printPostorder(Position current);
int printLevelOrder(Position current, RedP a);
Position delete (Position current, int broj); // brise element
Position find(Position current, int broj);    // trazi element
Position findMin(Position current);

// red:

RedP stvaranjeElementaReda(Position a);
int dodavanjeNaKraj(RedP head, Position a);
Position skidanjeSaPocetka(RedP head);
int printRed(RedP head);

#endif