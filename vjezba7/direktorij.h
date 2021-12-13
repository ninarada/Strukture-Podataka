#pragma once
#ifndef DIREKTORIJ_H
#define DIREKTORIJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

struct _Stablo;
typedef struct _Stablo *Position;

typedef struct _Stablo
{
    char naziv[MAX];
    Position sibling;
    Position child;
} Stablo;

struct _Stog; // stog sluzi za povratak u roditelj direktorij
typedef struct _Stog *PozicijaS;
typedef struct _Stog
{
    Position direktorij;
    PozicijaS next;
} Stog;

PozicijaS stvoriElementStoga(Position a);
int push(PozicijaS head, Position dir);
Position pop(PozicijaS head);

Position stvaranje(char *ime);
Position unos(Position current, Position new);
int ispis(Position current);
Position cd(PozicijaS stogA, char *naziv, Position current);

#endif