#include "stablo.h"

Position create(int broj)
{
    Position new = NULL;

    new = (Position)malloc(sizeof(Stablo));
    if (new == NULL)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    new->broj = broj;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Position insert(Position current, Position new)
{
    if (current == NULL)
    {
        return new;
    }
    else if (new->broj >= current->broj)
    {
        current->left = insert(current->left, new);
    }
    else if (new->broj < current->broj)
    {
        current->right = insert(current->right, new);
    }
    return current;
}

Position random(Position root)
{
    int i, randBroj;
    Position temp = NULL;

    for (i = 0; i < 10; i++)
    {
        randBroj = (rand() % (MAX_RAND - MIN_RAND + 1)) + MIN_RAND;
        temp = create(randBroj);
        root = insert(root, temp);
    }
    return root;
}

int replace(Position current, int a)
{
    if (current == NULL)
    {
        return 0;
    }
    a = current->broj;

    current->broj = replace(current->left, a) + replace(current->right, a);

    return a + current->broj;
}

int printInorder(Position current)
{
    if (current == NULL)
    {
        return 0;
    }
    printInorder(current->left);
    printf(" %d ", current->broj);
    printInorder(current->right);

    return 0;
}

Position delete (Position current)
{

    if (current == NULL)
    {
        return NULL;
    }
    delete (current->left);
    delete (current->right);
    free(current);

    return NULL;
}

int inorderFile(Position current, char *nazivDat)
{
    FILE *datoteka = NULL;

    Lista head;
    head.next = NULL;
    ListaPok pokLista = &head;

    datoteka = fopen(nazivDat, "a");
    if (datoteka == NULL)
    {
        perror("Greska kod otvaranja datoteke!\n");
        return -1;
    }

    printInorderFILE(current, pokLista);

    while (pokLista->next != NULL)
    {
        fprintf(datoteka, "%d ", pokLista->next->broj);
        pokLista = pokLista->next;
        if (pokLista->next == NULL)
        {
            fprintf(datoteka, "\n");
        }
    }

    deleteList(pokLista);
    fclose(datoteka);
    return 0;
}

int printInorderFILE(Position current, ListaPok head)
{
    if (current == NULL)
    {
        return 0;
    }
    printInorderFILE(current->right, head);
    unesiL(head, current->broj);
    printInorderFILE(current->left, head);

    return 0;
}

// lista :

ListaPok stvoriL(int broj)
{
    ListaPok new = NULL;

    new = (ListaPok)malloc(sizeof(Lista));
    if (new == NULL)
    {
        perror("greska alociranja memorije!\n");
        return NULL;
    }

    new->broj = broj;
    new->next = NULL;

    return new;
}

int unesiL(ListaPok lista, int broj)
{
    ListaPok novi = stvoriL(broj);

    novi->next = lista->next;
    lista->next = novi;
    return 0;
}

int deleteList(ListaPok head)
{
    ListaPok temp;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = head->next->next;
        free(temp);
    }

    return 0;
}