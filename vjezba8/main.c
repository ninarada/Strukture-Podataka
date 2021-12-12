#include "stablo.h"

#include <ctype.h>

int main(void)
{
    int niz[8] = {2, 5, 7, 8, 11, 1, 4, 3};
    int i;
    Position p = NULL;
    Position temp;
    char odabir;
    int broj;
    red pomocniRed;
    pomocniRed.next = NULL;
    RedP redPok = &pomocniRed;
    unsigned int bro;

    while (1)
    {
        printf("Odaberite:\n\t(Z - dodaj vec definirani niz)\n\tA - dodaj element\n\tB - inorder ispis elemenata\n\tC - preorder ispis elemenata\n\tD - postorder"
               "ispis elemenata\n\tE - level order ispis elemenata\n\tF - brisanje elementa\n\tT - pronadi element\n\tK - kraj\n");
        printf("Vas odabir: ");
        scanf(" %c", &odabir);
        odabir = toupper(odabir);

        switch (odabir)
        {
        case 'Z':
            for (i = 0; i < 8; i++)
            {
                temp = create(niz[i]);
                p = add(p, temp);
            }

            break;
        case 'A':
            printf("Broj koji zelite upisati u stablo: ");
            scanf(" %d", &broj);

            temp = create(broj);
            p = add(p, temp);

            break;

        case 'B':
            printf("Inorder: ");
            printInorder(p);
            printf("\n");

            break;

        case 'C':
            printf("Preorder: ");
            printPreorder(p);
            printf("\n");

            break;

        case 'D':
            printf("Postorder: ");
            printPostorder(p);
            printf("\n");

            break;

        case 'E':
            printf("Level order: ");
            printLevelOrder(p, redPok);
            printf("\n");
            break;

        case 'F':
            printf("Broj koji zelite obrisati: ");
            scanf(" %d", &broj);
            p = delete (p, broj);

            break;

        case 'T':
            printf("Element koji zelite pronaci: ");
            scanf(" %d", &broj);
            temp = find(p, broj);
            if (temp != NULL)
            {
                printf("%d\n", temp->el);
            }

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