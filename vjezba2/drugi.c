#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

struct _Osoba;
typedef struct _Osoba *Pozicija;

typedef struct _Osoba
{
    char ime[MAX];
    char prezime[MAX];
    int godina_rodenja;
    Pozicija next;
} Osoba;

Pozicija StvaranjeNoveOsobe(char *ime, char *prezime, int godina_rodenja);
void DodavanjeNakon(Pozicija a, Pozicija novaOsoba);
void IspisListe(Pozicija prvi);
void DodavanjeNaKraj(Pozicija a, Pozicija novaOsoba);
Pozicija PronalaziElementPoPrezimenu(Pozicija a, char *prezime);
void BrisanjeElementa(Pozicija a, char *prezime);
Pozicija PronalaziPrethodni(Pozicija a, char *prezime);

int main(void)
{
    Osoba head;
    head.next = NULL;
    Pozicija p = &head;
    char ime[MAX], prezime[MAX];
    int godina = 0;
    char odabir;
    char trazenoPrezime[MAX];
    Pozicija x;

    while (1)
    {
        printf("Odaberite:\nA - Unos novog elementa na pocetak liste\nB - Ispis liste\nC - Dodavanje elementa na kraj liste\n"
               "D - Pronaci element u listi(po prezimenu)\nE - Obrisi element iz liste\nF - Kraj\n");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'A':
            printf("Unesite ime, prezime i godinu rodenja:\n");
            scanf(" %s %s %d", &ime, &prezime, &godina);
            x = StvaranjeNoveOsobe(ime, prezime, godina);
            DodavanjeNakon(&head, x);
            break;

        case 'B':
            IspisListe(head.next);
            break;

        case 'C':
            printf("Unesite ime, prezime i godinu rodenja:\n");
            scanf(" %s %s %d", &ime, &prezime, &godina);
            x = StvaranjeNoveOsobe(ime, prezime, godina);
            DodavanjeNaKraj(&head, x);
            break;

        case 'D':
            printf("Unesite prezime: ");
            scanf(" %s", &trazenoPrezime);
            x = PronalaziElementPoPrezimenu(&head, trazenoPrezime);
            if (x == NULL)
            {
                printf("Element ne postoji!\n");
            }
            else
            {
                printf("%s %s %d\n", x->ime, x->prezime, x->godina_rodenja);
            }
            break;

        case 'E':
            printf("Unesite prezime koje zelite obrisati: ");
            scanf(" %s", &trazenoPrezime);
            BrisanjeElementa(&head, trazenoPrezime);
            break;

        case 'F':
            return 0;
            break;

        default:
            printf("Krivi unos!\n");
            break;
        }
    }

    return 0;
}

Pozicija StvaranjeNoveOsobe(char *ime, char *prezime, int godina_rodenja)
{
    Pozicija novaOsoba = NULL;

    novaOsoba = (Pozicija)malloc(sizeof(Osoba));
    if (novaOsoba == NULL)
    {
        perror("Ne moze alocirati memoriju!");
        return NULL;
    }

    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodenja = godina_rodenja;
    novaOsoba->next = NULL;

    return novaOsoba;
}

void DodavanjeNakon(Pozicija a, Pozicija novaOsoba)
{
    novaOsoba->next = a->next;
    a->next = novaOsoba;
}

void IspisListe(Pozicija prvi)
{
    printf("Osobe u listi:\n");
    Pozicija temp = prvi;
    while (temp != NULL)
    {
        printf("\t%s %s %d\n", temp->ime, temp->prezime, temp->godina_rodenja);
        temp = temp->next;
    }
}

void DodavanjeNaKraj(Pozicija a, Pozicija novaOsoba)
{
    while (a->next != NULL)
        a = a->next;
    a->next = novaOsoba;
}

Pozicija PronalaziElementPoPrezimenu(Pozicija a, char *prezime)
{
    while (a != NULL)
    {
        if (strcmp(a->prezime, prezime) == 0)
        {
            return a;
        }
        a = a->next;
    }

    return NULL;
}

void BrisanjeElementa(Pozicija a, char *prezime)
{
    Pozicija element;
    a = PronalaziPrethodni(a, prezime);
    if (a != NULL)
    {
        element = a->next;
        a->next = a->next->next;
        free(element);
    }
    else
    {
        printf("Element ne postoji!\n");
    }
}

Pozicija PronalaziPrethodni(Pozicija a, char *prezime)
{
    while (a->next != NULL && (strcmp(a->next->prezime, prezime)) != 0)
    {
        a = a->next;
    }
    if (a->next == NULL)
        return NULL;
    else
        return a;
}