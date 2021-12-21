#include "stablo.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    int niz[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int i;
    Position p = NULL;
    Position temp;
    char odabir;
    int br = 0;
    srand((unsigned int)time(0));

    while (1)
    {
        printf("Odaberite:\n\tA - insert niz {2, 5, 7, 8, 11, 1, 4, 2, 3, 7}\n\tB - inorder ispis elemenata\n\tC - replace\n\tD - random brojevi\n\t"
               "E - inorder upis u datoteku (stablo iz a) i random)\n\tK - kraj\n");
        printf("Vas odabir: ");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'A':
            p = delete (p); // osigurava da je stablo prazno prije stvaranja novog
            for (i = 0; i < 10; i++)
            {
                temp = create(niz[i]);
                p = insert(p, temp);
            }

            break;

        case 'B':
            printf("Inorder: ");
            printInorder(p);
            printf("\n");
            break;

        case 'C':
            replace(p, br);
            break;

        case 'D':
            p = delete (p); // osigurava da je stablo prazno prije stvaranja novog
            p = random(p);
            break;

        case 'E':
            p = delete (p);
            for (i = 0; i < 10; i++) // upisuje niz {2, 5, 7, 8, 11, 1, 4, 2, 3, 7}
            {
                temp = create(niz[i]);
                p = insert(p, temp);
            }
            inorderFile(p, "file.txt");

            p = delete (p);
            p = random(p);
            inorderFile(p, "file.txt"); // upisuje random niz
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