#include "drzave.h"

// stablo(gradovi):

positionGradovi stvaranjeNovogGrada(char *grad, long int stanovnici)
{
    positionGradovi new = NULL;

    new = (positionGradovi)malloc(sizeof(Stablo));

    if (new == NULL)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    new->stanovnici = stanovnici;
    strcpy(new->grad, grad);
    new->left = NULL;
    new->right = NULL;

    return new;
}

positionGradovi dodavanjeGrada(positionGradovi current, positionGradovi novi)
{
    if (current == NULL)
    {
        return novi;
    }
    else if (novi->stanovnici < current->stanovnici)
    {
        current->left = dodavanjeGrada(current->left, novi);
    }
    else if (novi->stanovnici > current->stanovnici)
    {
        current->right = dodavanjeGrada(current->right, novi);
    }
    else if (novi->stanovnici == current->stanovnici)
    {
        if (strcmp(novi->grad, current->grad) < 0)
        {
            current->left = dodavanjeGrada(current->left, novi);
        }
        else if (strcmp(novi->grad, current->grad) > 0)
        {
            current->right = dodavanjeGrada(current->right, novi);
        }
    }

    return current;
}

int printGradovi(positionGradovi current) // inorder
{
    if (current == NULL)
    {
        return 0;
    }

    printGradovi(current->left);
    printf("\t%s %ld\n", current->grad, current->stanovnici);
    printGradovi(current->right);

    return 0;
}

positionGradovi izbrisiStablo(positionGradovi current)
{
    if (current == NULL)
    {
        return NULL;
    }
    izbrisiStablo(current->left);
    izbrisiStablo(current->right);
    free(current);

    return NULL;
}

// lista(drzave):

positionLista stvoriNovuDrzavu(char *drzava, positionGradovi root)
{
    positionLista new = NULL;

    new = (positionLista)malloc(sizeof(Lista));

    if (new == NULL)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    strcpy(new->drzava, drzava);
    new->rootGradovi = root;
    new->next = NULL;

    return new;
}

int dodavanjeDrzave(positionLista head, positionLista new)
{
    while (head->next != NULL && strcmp(new->drzava, head->next->drzava) > 0)
    {
        head = head->next;
    }
    if (head->next != NULL && strcmp(new->drzava, head->next->drzava) == 0)
    {
        return 0;
    }

    new->next = head->next;
    head->next = new;

    return 0;
}

int printDrzave(positionLista head)
{
    head = head->next; // prvi element

    while (head != NULL)
    {
        printf("%s:\n", head->drzava);
        printGradovi(head->rootGradovi);
        head = head->next;
    }

    return 0;
}

int izbrisiListu(positionLista head)
{
    positionLista temp = NULL;

    while (head->next != NULL)
    {
        temp = head->next;
        izbrisiStablo(temp->rootGradovi);
        head->next = head->next->next;
        free(temp);
    }

    return 0;
}

positionGradovi citanjeGradova(char *nazivDatoteke, positionGradovi root)
{
    FILE *datoteka = NULL;
    int duzinaDatoteke = 0;
    char nazivGrada[MAX_NAZIV];
    int stanovnici = 0;
    positionGradovi new = NULL;

    datoteka = fopen(nazivDatoteke, "r");

    if (datoteka == NULL)
    {
        printf("GRESKA KOD OTVARANJA DATOTEKE GRADA!\n");
        return NULL;
    }

    while (!feof(datoteka))
    {
        if (fscanf(datoteka, " %s %ld", &nazivGrada, &stanovnici) == 2)
        {
            new = stvaranjeNovogGrada(nazivGrada, stanovnici);
            root = dodavanjeGrada(root, new);
        }
    }

    fclose(datoteka);

    return root;
}

int citanjeDrzava(char *nazivDatoteke, positionLista headP)
{
    FILE *datoteka = NULL;
    int duzinaDatoteke = 0;
    char nazivDrzave[MAX_NAZIV];
    char nazivDrzaveTXT[MAX_NAZIV + 4];

    positionGradovi rootTEMP = NULL;
    positionLista listaTEMP = NULL;

    datoteka = fopen(nazivDatoteke, "r");

    if (datoteka == NULL)
    {
        printf("GRESKA KOD OTVARANJA DATOTEKE DRZAVA!\n");
        return -1;
    }

    while (!feof(datoteka))
    {
        if (fscanf(datoteka, " %s %s", &nazivDrzave, &nazivDrzaveTXT) == 2)
        {
            listaTEMP = stvoriNovuDrzavu(nazivDrzave, rootTEMP);
            listaTEMP->rootGradovi = citanjeGradova(nazivDrzaveTXT, listaTEMP->rootGradovi);

            dodavanjeDrzave(headP, listaTEMP);
        }
    }

    fclose(datoteka);

    return 0;
}

int traziDrzavu(char *drzava, long int broj, positionLista headP)
{
    headP = headP->next;
    while (headP != NULL && strcmp(drzava, headP->drzava) != 0)
    {
        headP = headP->next;
    }
    if (headP == NULL)
    {
        printf("Drzava ne postoji!\n");
        return 0;
    }

    traziGradove(broj, headP->rootGradovi);

    return 0;
}

positionGradovi traziGradove(long int broj, positionGradovi root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->stanovnici < broj)
    {
        root = traziGradove(broj, root->right);
    }
    else if (root->stanovnici > broj)
    {

        root->left = traziGradove(broj, root->left);
        printf("%s %ld\n", root->grad, root->stanovnici);
        root->right = traziGradove(broj, root->right);
    }
    return root;
}