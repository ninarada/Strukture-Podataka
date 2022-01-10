#include "drzaveB.h"

// gradovi - lista:
positionListaGradova BstvaranjeNovogGrada(char *naziv, long int brStanovnika)
{
    positionListaGradova new = NULL;

    new = (positionListaGradova)malloc(sizeof(ListaGradova));

    if (new == NULL)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    new->brojStanovnika = brStanovnika;
    strcpy(new->nazivGrada, naziv);
    new->next = NULL;

    return new;
}

int BdodavanjeGrada(positionListaGradova head, positionListaGradova novi)
{
    while (head->next != NULL && novi->brojStanovnika > head->next->brojStanovnika)
    {
        head = head->next;
    }

    novi->next = head->next;
    head->next = novi;

    return 0;
}

int BprintGradovi(positionListaGradova head)
{
    while (head->next != NULL)
    {
        printf("\t%s %ld\n", head->next->nazivGrada, head->next->brojStanovnika);
        head = head->next;
    }

    return 0;
}

int BizbrisiGradove(positionListaGradova head)
{
    positionListaGradova temp;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }

    return 0;
}

// drzave:

positionDrzave BstvaranjeNoveDrzave(char *naziv, positionListaGradova gradovi)
{
    positionDrzave new = NULL;

    new = (positionDrzave)malloc(sizeof(StabloDr));

    if (new == NULL)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    strcpy(new->nazivDrzave, naziv);
    new->left = NULL;
    new->right = NULL;
    new->gradovi = gradovi;

    return new;
}

positionDrzave BdodavanjeDrzave(positionDrzave current, positionDrzave nova)
{
    if (current == NULL)
    {
        return nova;
    }
    else if (strcasecmp(nova->nazivDrzave, current->nazivDrzave) < 0)
    {
        current->left = BdodavanjeDrzave(current->left, nova);
    }
    else if (strcasecmp(nova->nazivDrzave, current->nazivDrzave) > 0)
    {
        current->right = BdodavanjeDrzave(current->right, nova);
    }

    return current;
}

int BprintDrzave(positionDrzave current)
{
    if (current == NULL)
    {
        return 0;
    }

    BprintDrzave(current->left);
    printf("%s:\n", current->nazivDrzave);
    BprintGradovi(current->gradovi);
    BprintDrzave(current->right);

    return 0;
}

int BizbrisiDrzave(positionDrzave current)
{
    if (current == NULL)
    {
        return 0;
    }

    BizbrisiDrzave(current->left);
    BizbrisiDrzave(current->right);
    BizbrisiGradove(current->gradovi);
    free(current);

    return 0;
}

int BtraziGradove(positionListaGradova head, long int broj)
{
    while (head->next != NULL && broj >= head->next->brojStanovnika)
    {
        head = head->next;
    }
    printf("Trazeni gradovi:\n");
    while (head->next != NULL)
    {
        printf("\t%s %ld\n", head->next->nazivGrada, head->next->brojStanovnika);
        head = head->next;
    }

    return 0;
}

positionDrzave BtraziDrzavu(positionDrzave current, char *naziv, long int broj)
{
    if (current == NULL)
    {
        printf("Drzava ne postoji!\n");
        return NULL;
    }
    else if (strcasecmp(naziv, current->nazivDrzave) > 0)
    {
        current = BtraziDrzavu(current->right, naziv, broj);
    }
    else if (strcasecmp(naziv, current->nazivDrzave) < 0)
    {
        current = BtraziDrzavu(current->left, naziv, broj);
    }
    else if (strcasecmp(naziv, current->nazivDrzave) == 0)
    {
        BtraziGradove(current->gradovi, broj);
    }
    return current;
}

int BcitanjeGradova(char *nazDat, positionListaGradova head)
{
    FILE *datoteka = NULL;

    char nazivGr[MAX_NAZIV];
    long int brST;
    positionListaGradova novi = NULL;

    datoteka = fopen(nazDat, "r");

    if (datoteka == NULL)
    {
        printf("GRESKA KOD OTVARANJA DATOTEKE GRADOVI!\n");
        return -1;
    }

    while (!feof(datoteka))
    {
        if (fscanf(datoteka, " %s %ld", &nazivGr, &brST) == 2)
        {
            novi = BstvaranjeNovogGrada(nazivGr, brST);
            BdodavanjeGrada(head, novi);
        }
    }

    fclose(datoteka);
    return 0;
}

positionDrzave BcitanjeDrzava(char *nazDat, positionDrzave current)
{
    FILE *datoteka = NULL;

    char nazivDrzave[MAX_NAZIV];
    char nazivDrzaveTXT[MAX_NAZIV];
    positionDrzave nova = NULL;

    ListaGradova head;
    head.next = NULL;
    positionListaGradova headPok = NULL;

    datoteka = fopen(nazDat, "r");

    if (datoteka == NULL)
    {
        printf("GRESKA KOD OTVARANJA DATOTEKE GRADOVI!\n");
        return NULL;
    }

    while (!feof(datoteka))
    {
        if (fscanf(datoteka, " %s %s", &nazivDrzave, &nazivDrzaveTXT) == 2)
        {

            headPok = BstvaranjeNovogGrada(" ", 0);
            nova = BstvaranjeNoveDrzave(nazivDrzave, headPok);
            BcitanjeGradova(nazivDrzaveTXT, headPok);
            current = BdodavanjeDrzave(current, nova);
        }
    }

    fclose(datoteka);
    return current;
}
