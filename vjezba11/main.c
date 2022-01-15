#include "drzave.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char odabir;
    long int brojST = 0;
    char traziVece[MAX_NAZIV];
    int i = 0;

    positionLista tablica[HASH_VELICINA];
    positionLista pom = NULL;

    for (i = 0; i < HASH_VELICINA; i++)
    {

        pom = stvoriNovuDrzavu(" ", NULL);
        tablica[i] = pom;
    }

    while (1)
    {

        printf("Odaberite:\n\tA - citanje drzava i gradova\n\tB - ispis drzava pod odredenim kljucem\n\tC - ispis svih drzava\n\t"
               "D - trazi gradove u odredenoj drzavi vece od zadanog broja\n\tK - kraj\n");
        printf("Vas odabir: ");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'A':
            citanjeDrzava("drzave.txt", tablica);

            break;

        case 'B':
            printf("____________________________________________\n");
            printf("Unesite kljuc(mjesto tablice {0,1,...,10}): ");
            scanf(" %d", &i);

            printDrzave(tablica[i]);
            printf("____________________________________________\n");
            break;

        case 'C':
            for (i = 0; i < HASH_VELICINA; i++)
            {
                printf("____________________________________________\n");
                printf("Drzava pod kljucem tablica[%d]:\n", i);
                printDrzave(tablica[i]);
                printf("____________________________________________\n");
            }

            break;

        case 'D':
            printf("Upisite drzavu i broj:\n");
            printf("\tDrzava: ");
            scanf(" %s", &traziVece);
            printf("\tBroj: ");
            scanf(" %ld", &brojST);

            printf("_______________________\n");

            for (i = 0; i < HASH_VELICINA; i++)
            {
                traziDrzavu(traziVece, brojST, tablica[i]);
            }

            printf("_______________________\n");

            break;

        case 'K':
            for (i = 0; i < HASH_VELICINA; i++)
            {
                izbrisiListu(tablica[i]);
            }

            return 0;
            break;

        default:
            printf("Krivi unos!\n");
            break;
        }
    }

    return 0;
}