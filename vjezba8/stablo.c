#include "stablo.h"

Position create(int broj)
{
    Position q = NULL;

    q = (Position)malloc(sizeof(Stablo));

    if (NULL == q)
    {
        perror("Greska alociranja memorije!\n");
        return NULL;
    }

    q->el = broj;
    q->left = NULL;
    q->right = NULL;

    return q;
}

Position add(Position current, Position new)
{
    if (current == NULL)
    {
        return new;
    }
    else if (current->el > new->el)
    {
        current->left = add(current->left, new);
    }
    else if (current->el < new->el)
    {
        current->right = add(current->right, new);
    }
    else
    {
        printf("Broj vec postoji!\n");
        free(new);
    }

    return current;
}

int printInorder(Position current)
{
    if (current == NULL)
    {
        return 0;
    }
    printInorder(current->left);
    printf(" %d ", current->el);
    printInorder(current->right);

    return 0;
}

int printPreorder(Position current)
{
    if (current == NULL)
    {
        return 0;
    }

    printf(" %d ", current->el);
    printPreorder(current->left);
    printPreorder(current->right);

    return 0;
}

int printPostorder(Position current)
{
    if (current == NULL)
    {
        return 0;
    }
    printPostorder(current->left);
    printPostorder(current->right);
    printf(" %d ", current->el);

    return 0;
}

int printLevelOrder(Position current, RedP a)
{
    if (current == NULL)
    {
        return 0;
    }
    printf(" %d ", current->el);
    if (current->left != NULL)
    {
        dodavanjeNaKraj(a, current->left);
    }
    if (current->right != NULL)
    {
        dodavanjeNaKraj(a, current->right);
    }
    current = skidanjeSaPocetka(a);
    printLevelOrder(current, a);

    return 0;
}

Position find(Position current, int broj)
{
    if (current == NULL)
    {
        printf("Element ne postoji!\n");
        return NULL;
    }
    else if (current->el > broj)
    {
        current = find(current->left, broj);
    }
    else if (current->el < broj)
    {
        current = find(current->right, broj);
    }

    return current;
}

Position findMin(Position current)
{
    if (current->left != NULL)
    {
        current = findMin(current->left);
    }

    return current;
}

Position delete (Position current, int broj)
{
    Position temp;
    if (current == NULL)
    {
        printf("Element ne postoji!\n");
        return NULL;
    }
    else if (current->el > broj)
    {
        current->left = delete (current->left, broj);
    }
    else if (current->el < broj)
    {
        current->right = delete (current->right, broj);
    }
    else // pronasli smo element koji treba obrisati
    {
        if (current->right != NULL && current->left != NULL) // ako ima oba djeteta
        {
            temp = findMin(current->right);
            current->el = temp->el;
            current->right = delete (current->right, current->el);
        }
        else if (current->left == NULL)
        {
            temp = current;
            current = current->right;
            free(temp);
        }
        else if (current->left != NULL)
        {
            temp = current;
            current = current->left;
            free(temp);
        }
    }

    return current;
}

// red:

RedP stvaranjeElementaReda(Position a)
{
    RedP new = NULL;
    new = (RedP)malloc(sizeof(red));
    if (new == NULL)
    {
        perror("greska alociranja memorije!\n");
        return NULL;
    }
    new->x = a;
    new->next = NULL;
    return new;
}

int dodavanjeNaKraj(RedP head, Position a)
{
    RedP new = stvaranjeElementaReda(a);

    while (head->next != NULL)
    {
        head = head->next;
    }

    head->next = new;

    return 0;
}

Position skidanjeSaPocetka(RedP head)
{
    RedP temp = head->next;
    Position y = NULL;
    if (temp != NULL)
    {
        y = head->next->x;
        head->next = head->next->next;
    }

    return y;
}

int printRed(RedP head)
{

    printf("RED: ");
    while (head->next != NULL)
    {
        printf(" %d ", head->next->x->el);
        head = head->next;
    }
    return 0;
}