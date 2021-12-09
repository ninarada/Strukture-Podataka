#ifndef ARTIKLI_H
#define ARTIKLI_H

#define MAX 20

struct _Artikli;
typedef struct _Artikli *ArtikliP;

typedef struct _Artikli
{
    char naziv[MAX];
    int kolicina;
    double cijena;
    ArtikliP next;
} Artikli;

ArtikliP StvaranjeArtikla(char *naziv, int kolicina, double cijena);
int DodavanjeIzaArtikla(ArtikliP a);
int SortiranoDodavanjeArtikla(ArtikliP head, char *naziv, int kolicina, double cijena);
int ObrisiArtikl(ArtikliP head, ArtikliP a);
int ObrisiSveArtikle(ArtikliP head);
int IspisArtikala(ArtikliP a);
ArtikliP TrazenjeArtikla(ArtikliP a, char *naziv);
int IspisArtikla(ArtikliP a);

#endif