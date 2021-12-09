#ifndef DATUM_H
#define DATUM_H

struct _Datum;
typedef struct _Datum *DatumP;

typedef struct _Datum
{
    int godina;
    int mjesec;
    int dan;
} Datum;

DatumP CitanjeDatuma(char *p);
int IspisDatuma(DatumP x);
int UsporedbaDatuma(DatumP x, DatumP y);

#endif