#include "datum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

DatumP CitanjeDatuma(char *p)
{
    DatumP x = NULL;

    x = (DatumP)malloc(sizeof(Datum));
    if (x == NULL)
    {
        perror("Greska alociranja memorije (datum)!\n");
        return NULL;
    }

    if (sscanf(p, "%d-%d-%d", &x->godina, &x->mjesec, &x->dan) != 3)
    {
        printf("Pogresno unesen datum!\n");
        free(x);
        return NULL;
    }

    return x;
}

int IspisDatuma(DatumP x)
{
    printf("\t----------\n");

    printf("\t%d-%d-%d\n", x->godina, x->mjesec, x->dan);
    printf("\t----------\n");
    return 0;
}

int UsporedbaDatuma(DatumP x, DatumP y)
{
    if (x->godina > y->godina)
    {
        return 1;
    }
    else if (x->godina < y->godina)
    {
        return -1;
    }
    else if (x->mjesec > y->mjesec)
    {
        return 1;
    }
    else if (x->mjesec < y->mjesec)
    {
        return -1;
    }
    else if (x->dan > y->dan)
    {
        return 1;
    }
    else if (x->dan < y->dan)
    {
        return -1;
    }
    return 0;
}
