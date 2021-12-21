#pragma once
#ifndef STABLO_H
#define STABLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RAND 89
#define MIN_RAND 11

struct _Stablo;
typedef struct _Stablo *Position;
typedef struct _Stablo
{
    int broj;
    Position left;
    Position right;
} Stablo;

struct _Lista;
typedef struct _Lista *ListaPok;
typedef struct _Lista
{
    int broj;
    ListaPok next;
} Lista;

Position create(int broj);
Position insert(Position current, Position new);
int replace(Position current, int a);
Position random(Position root);
int printInorder(Position current);
Position delete (Position current);

int printInorderFILE(Position current, ListaPok head); // upisuje brojeve stabla u vezanu listu
int inorderFile(Position current, char *nazivDat);     // pomocu liste upisuje elemente stabla u datoteku

ListaPok stvoriL(int broj);
int unesiL(ListaPok lista, int broj);
int deleteList(ListaPok head);

#endif