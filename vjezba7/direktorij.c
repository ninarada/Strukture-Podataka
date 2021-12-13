#include "direktorij.h"

Position stvaranje(char *ime)
{
    Position new = NULL;

    new = (Position)malloc(sizeof(Stablo));
    if (new == NULL)
    {
        perror("greska alociranja memorije!\n");
        return NULL;
    }

    strcpy(new->naziv, ime);
    new->child = NULL;
    new->sibling = NULL;

    return new;
}

Position unos(Position current, Position new)
{
    if (current == NULL)
    {
        return new;
    }
    if (strcmp(current->naziv, new->naziv) > 0)
    {
        new->sibling = current;
        return new;
    }
    else if (strcmp(current->naziv, new->naziv) < 0)
    {
        current->sibling = unos(current->sibling, new);
    }
    else
    { // kad su jednaki
        printf("direktorij vec postoji!\n");
        free(new);
    }
    return current;
}

int ispis(Position current)
{
    if (current == NULL)
    {
        return 0;
    }
    printf("\t%s\n", current->naziv);
    ispis(current->sibling);
    return 0;
}

Position cd(PozicijaS stogA, char *naziv, Position current)
{
    Position temp = NULL;
    Position temp2 = NULL;

    temp = current->child;
    while (temp != NULL)
    {
        if (strcmp(temp->naziv, naziv) == 0)
        {
            temp2 = temp;
        }
        temp = temp->sibling;
    }
    if (temp2 == NULL)
    {
        printf("direktorij ne postoji!\n");
        return current;
    }
    push(stogA, current);

    return temp2;
}

PozicijaS stvoriElementStoga(Position a)
{
    PozicijaS new = NULL;
    new = (PozicijaS)malloc(sizeof(Stog));
    if (new == NULL)
    {
        perror("greska alociranja memorije!\n");
        return NULL;
    }

    new->direktorij = a;
    new->next = NULL;
    return new;
}

int push(PozicijaS head, Position dir)
{
    PozicijaS new = stvoriElementStoga(dir);
    new->next = head->next;
    head->next = new;
    return 0;
}

Position pop(PozicijaS head)
{
    Position q = NULL;
    PozicijaS temp;
    q = head->next->direktorij;
    temp = head->next;
    head->next = head->next->next;
    free(temp);

    return q;
}
