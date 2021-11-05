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

void DodavanjeIspredElementa(Pozicija a, Pozicija noviElement, Pozicija element);
void DodavanjeNakonElementa(Pozicija noviElement, Pozicija element);
void SortiranoDodajeUListu(Pozicija a, Pozicija element);
void SortiraListu(Pozicija a);
int CitaIzDatoteke(Pozicija a);
int UpisujeNapravljenuListuUDatoteku(Pozicija a);

int main(void)
{
    Osoba head;
    head.next = NULL;
    Pozicija p = &head;
    char ime[MAX], prezime[MAX];
    int godina = 0;
    char odabir;
    char trazenoPrezime[MAX];
    Pozicija x, y;
    char datoteka[1024];

    while (1)
    {
        printf("Odaberite:\n(Prvi zadatak:)\n\tA - Unos novog elementa na pocetak liste\n\tB - Ispis liste\n\tC - Dodavanje elementa na kraj liste\n\t"
               "D - Pronaci element u listi(po prezimenu)\n\tE - Obrisi element iz liste\n(Drugi zadatak:)\n\tF - Dodavanje novog elementa ispred odredenog elementa\n\t"
               "G - Dodavanje novog elementa nakon odredenog elementa\n\tH - Sortirano dodavanje po prezimenu\n"
               "\tS - Sortira listu\n\tI - Upisuje listu u datoteku\n"
               "\tJ - Cita listu iz datoteke\n  \n\tK - Kraj\n");
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
            printf("Unesite ime, prezime i godinu rodenja:\n");
            scanf(" %s %s %d", &ime, &prezime, &godina);
            x = StvaranjeNoveOsobe(ime, prezime, godina);
            printf("Unesite prezime ispred kojeg zelite dodati novi element: ");
            scanf(" %s", &trazenoPrezime);
            y = PronalaziElementPoPrezimenu(&head, trazenoPrezime);
            DodavanjeIspredElementa(&head, x, y);
            break;

        case 'G':
            printf("Unesite ime, prezime i godinu rodenja:\n");
            scanf(" %s %s %d", &ime, &prezime, &godina);
            x = StvaranjeNoveOsobe(ime, prezime, godina);
            printf("Unesite prezime nakon kojeg zelite dodati novi element: ");
            scanf(" %s", &trazenoPrezime);
            y = PronalaziElementPoPrezimenu(&head, trazenoPrezime);
            DodavanjeNakonElementa(x, y);
            break;

        case 'H':
            printf("Unesite ime, prezime i godinu rodenja:\n");
            scanf(" %s %s %d", &ime, &prezime, &godina);
            x = StvaranjeNoveOsobe(ime, prezime, godina);
            SortiranoDodajeUListu(&head, x);
            break;

        case 'S':
            SortiraListu(&head);
            break;

        case 'I':
            UpisujeNapravljenuListuUDatoteku(head.next);
            break;

        case 'J':
            CitaIzDatoteke(&head);
            break;

        case 'K':
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
        perror("Ne može alocirati memoriju!");
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

void DodavanjeIspredElementa(Pozicija a, Pozicija noviElement, Pozicija element)
{
    a = PronalaziPrethodni(a, element->prezime);
    noviElement->next = element;
    a->next = noviElement;
}

void DodavanjeNakonElementa(Pozicija noviElement, Pozicija element)
{
    noviElement->next = element->next;
    element->next = noviElement;
}

void SortiranoDodajeUListu(Pozicija a, Pozicija element)
{
    while (a->next != NULL && strcasecmp(element->prezime, a->next->prezime) > 0)
    {
        a = a->next;
    }
    element->next = a->next;
    a->next = element;
}

void SortiraListu(Pozicija a)
{
    Pozicija j, prev_j, temp, end;
    end = NULL;

    while (a->next != end)
    {
        prev_j = a;
        j = a->next;
        while (j->next != end)
        {
            if (strcasecmp(j->prezime, j->next->prezime) > 0)
            {
                temp = j->next;
                prev_j->next = j->next;
                j->next = j->next->next;
                temp->next = j;
                j = temp;
            }
            prev_j = j;
            j = j->next;
        }
        end = j;
    }
}

int UpisujeNapravljenuListuUDatoteku(Pozicija a)
{
    FILE *datoteka = NULL;
    char nazivDatoteke[64];
    Pozicija temp = NULL;
    char buffer[100];

    printf("Unesite naziv datoteke: ");
    scanf(" %s", &nazivDatoteke);

    datoteka = fopen(nazivDatoteke, "w");
    if (!datoteka)
    {
        printf("Greska kod otvaranja datoteke!");
        return -1;
    }
    while (a != NULL)
    {
        fprintf(datoteka, "%s %s %d\n", a->ime, a->prezime, a->godina_rodenja);
        a = a->next;
    }

    fclose(datoteka);
    return 0;
}

int CitaIzDatoteke(Pozicija a)
{
    FILE *datoteka = NULL;
    char nazivDatoteke[64];
    Pozicija temp = NULL;
    char buffer[100];
    Pozicija b = a;

    printf("Unesite naziv datoteke: ");
    scanf(" %s", &nazivDatoteke);

    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka)
    {
        printf("Greska kod otvaranja datoteke!");
        return -1;
    }

    while (!feof(datoteka))
    {
        temp = (Pozicija)malloc(sizeof(Osoba));
        if (temp == NULL)
        {
            printf("Greska alociranja.");
            return -1;
        }
        fgets(buffer, 100, datoteka);

        if (sscanf(buffer, " %s %s %d", temp->ime, temp->prezime, &temp->godina_rodenja) == 3)
        {
            SortiranoDodajeUListu(b, temp);
        }
    }

    fclose(datoteka);
    return 0;
}