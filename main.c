#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct List
{
    int value;
    struct List *px;
} List;

typedef struct Pilha
{
    List *adress;
    struct Pilha *px;
    struct Pilha *ant;
} Pilha;

List *addList()
{
    List *list = NULL, *first = NULL;
    for (int i = 0; i < rand() % 100; i++)
    {
        List *node = malloc(sizeof(List));
        node->value = rand() % 100;
        node->px = NULL;
        if (list == NULL)
        {
            list = node;
            first = list;
        }
        else
        {
            list->px = node;
            list = list->px;
        }
    }
    return first;
}

Pilha *addPilha(List *list, List *list_end)
{
    Pilha *pilha = NULL, *first = NULL;
    while (list->px != NULL)
    {
        Pilha *node = malloc(sizeof(Pilha));
        node->adress = list;
        node->ant = NULL;
        node->px = NULL;
        if (pilha == NULL)
        {
            pilha = node;
            first = pilha;
            list = list->px;
        }
        else
        {
            pilha->px = node;
            pilha->px->ant = pilha;
            pilha = pilha->px;
            list = list->px;
        }
    }
    while (list_end->px != NULL)
    {
        Pilha *node = malloc(sizeof(Pilha));
        node->adress = list_end;
        node->ant = NULL;
        node->px = NULL;
        pilha->px = node;
        pilha->px->ant = pilha;
        pilha = pilha->px;
        list_end = list_end->px;
    }
    return first;
}

int main()
{
    srand(time(NULL));
    List *list_1, *list_2, *list_3;
    list_1 = addList();
    list_2 = addList();
    list_3 = addList();
    Pilha *pilha_1, *pilha_2;

    pilha_1 = addPilha(list_1, list_3);
    pilha_2 = addPilha(list_2, list_3);

    printf("\nPilha 1: ");
    while (pilha_1->px != NULL)
    {
        printf(" %d ", pilha_1->adress->value);
        pilha_1 = pilha_1->px;
    }
    printf("\nPilha 2: ");
    while (pilha_2->px != NULL)
    {
        printf(" %d ", pilha_2->adress->value);
        pilha_2 = pilha_2->px;
    }

    Pilha *temp;

    while (pilha_1->adress == pilha_2->adress)
    {
        temp = pilha_1; // poderia ser a pilha_2 também
        pilha_1 = pilha_1->ant;
        pilha_2 = pilha_2->ant;
    }

    printf("\nEndereço: %d, Valor: %d", temp->adress, temp->adress->value);

    free(list_1);
    free(list_2);
    free(list_3);
    free(pilha_1);
    free(pilha_2);

    return 0;
}