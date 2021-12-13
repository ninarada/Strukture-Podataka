#include "direktorij.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char odabir;
    char naziv[MAX];
    Position x;

    Stog stogg;
    stogg.next = NULL;
    PozicijaS stogPok = &stogg;

    Position s = stvaranje("c:"); // root

    while (1)
    {
        printf("Odaberite:\n\tA - md     (unos novog direktorija)\n\tB - dir    (ispis sadrzaja direktorija)\n\tC - cd dir "
               "(pozicioniranje u direktorij)\n\tD - cd..   (povratak u prethodni direktorij)\n\tK - kraj\nVas unos: ");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'A': // md
            printf("Naziv novog direktorija: ");
            scanf(" %s", &naziv);
            x = stvaranje(naziv);
            s->child = unos(s->child, x);
            break;

        case 'B': // dir
            if (s->child == NULL)
            {
                printf("Direktorij %s je prazan!\n", s->naziv);
            }
            else
            {
                printf("Direktorij %s sadrzi:\n", s->naziv);
                ispis(s->child);
            }

            break;

        case 'C': // cd
            printf("Naziv direktorija: ");
            scanf(" %s", &naziv);
            s = cd(stogPok, naziv, s);

            break;

        case 'D': // cd..
            if (stogPok->next != NULL)
            {
                s = pop(stogPok);
            }

            break;

        case 'K':
            return 0;
            break;

        default:
            printf("krivi unos!\n");
            break;
        }
    }
    return 0;
}