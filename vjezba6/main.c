#include "racun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    Racuni rh;
    rh.next = NULL;
    RacuniP yp = &rh;
    char buffer[20];
    char art[20];
    DatumP x = NULL, y = NULL;
    ArtikliP trart;
    char odabir;

    Citanje(yp, "racuni.txt");

    while (1)
    {
        printf("Odaberite:\n\tA - Ispis svih racuna\n\tB - Koliko je novaca sveukupno potroseno na specificni "
               "artikl u odredenom\n\t    vremenskom razdoblju i u kojoj je kolicini isti kupljen\n\tK - Kraj\n");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);
        switch (odabir)
        {
        case 'A':
            IspisRacuna(rh.next);
            printf("------------------\n");
            break;

        case 'B':
            printf("Upisite artikl za koji vas zanima koliko je ukupno potroseno: ");
            scanf(" %s", &art);

            printf("Upisite u kojem vremenskom razdoblju trazite (format: YYYY-MM-DD)\nOd: ");

            scanf(" %s", &buffer);
            x = CitanjeDatuma(buffer);
            if (x == NULL)
            {
                break;
            }

            printf("Do: ");
            scanf(" %s", &buffer);
            y = CitanjeDatuma(buffer);

            if (y == NULL)
            {
                break;
            }

            trart = UkupnoPotrosenoNaArtikl(rh.next, art, x, y);
            printf("------------------\n");
            IspisArtikla(trart);

            break;

        case 'K':
            IzbrisiSveRacune(yp);
            return 0;
            break;

        default:
            printf("Krivi unos!\n");
            break;
        }
    }

    IzbrisiSveRacune(yp);
    return 0;
}