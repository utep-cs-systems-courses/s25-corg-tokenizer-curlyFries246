#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

List *init_history()
{
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->root = NULL;
    return list;
}

void add_history(List *list, char *str)
{
    if (!list) return;

    Item *newItem = malloc(sizeof(Item));
    if (!newItem) return;

    newItem->str = strdup(str);
    newItem->next = NULL;

    if (!list->root) {
        newItem->id = 1;
        list->root = newItem;
        return;
    }

    Item *temp = list->root;
    while (temp->next) temp = temp->next;

    newItem->id = temp->id + 1;
    temp->next = newItem;
}

char *get_history(List *list, int id)
{
    if (!list || !list->root) return NULL;

    Item *temp = list->root;
    while (temp){
        if (temp->id == id) return temp->str;
        temp = temp->next;
    }

    return NULL;
}

void print_history(List *list)
{
    if (!list || !list->root) {
        printf("No history found.\n");
        return;
    }

    Item *temp = list->root;
    while (temp){
        printf("%d. %s\n", temp->id, temp->str);
        temp = temp->next;
    }
}

void free_history(List *list)
{
    if (!list) return;

    Item *temp = list->root;
    while (temp){
        Item *next = temp->next;
        free(temp->str);
        free(temp);
        temp = next;
    }

    free(list);
}
