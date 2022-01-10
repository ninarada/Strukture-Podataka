#include "drzave.h"
#include "drzaveB.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    Lista headDrzava;
    headDrzava.next = NULL;
    positionLista headP = &headDrzava;

    positionDrzave root = NULL;

    char odabir;
    long int brojST = 0;
    char traziVece[MAX_NAZIV];

    while (1)
    {

        printf("Odaberite:\n\tA - a.) zadatak\n\tB - b.) zadatak\n\t"
               "K - kraj\n");
        printf("Vas odabir: ");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'A':
            citanjeDrzava("drzave.txt", headP);
            printDrzave(headP);

            printf("Upisite drzavu i broj od kojeg gradovi te drzave imaju veci broj stanovnika:\n");
            printf("\tDrzava: ");
            scanf(" %s", &traziVece);
            printf("\tBroj: ");
            scanf(" %ld", &brojST);

            traziDrzavu(traziVece, brojST, headP);

            break;

        case 'B':

            root = BcitanjeDrzava("drzave.txt", root);
            BprintDrzave(root);
            printf("Upisite drzavu i broj od kojeg gradovi te drzave imaju veci broj stanovnika:\n");
            printf("\tDrzava: ");
            scanf(" %s", &traziVece);
            printf("\tBroj: ");
            scanf(" %ld", &brojST);

            root = BtraziDrzavu(root, traziVece, brojST);

            break;

        case 'K':
            izbrisiListu(headP);
            BizbrisiDrzave(root);
            return 0;
            break;

        default:
            printf("Krivi unos!\n");
            break;
        }
    }

    return 0;
}