#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>
ArrayList* createArrayList(int size)
{
    if (size <= 0)
        return 0;
    ArrayList *ls = malloc(sizeof(ArrayList));
    ls->count = 0;
    ls->size = size;
    ls->array = malloc(sizeof(ArrayListNode *) * size);
    printf("ls is created (size %d)\n", size);
    return ls;
}

void deleteArrayList(ArrayList** ls)
{
    if (!*ls)
    {
        printf("deleteArrayList : ls not exist\n");
        return;
    }
    free((*ls)->array);
    free(*ls);
    *ls = 0;
    printf("ls is deleted\n");
}

void isArrayListFull_(ArrayList *ls)
{
    if (!ls || !ls->size)
        printf("ls is null");
    else if(ls->count == ls->size)
        printf("there is no room\n");
    else
        printf("not full\n");
}

void replaceALElement(ArrayList *ls, int index, ArrayListNode element)
{
    if(!ls || ls->count <= index || index < 0 || ls->count == ls->size)
    {
        printf("set : out of range\n");
        return;
    }
    ls->array[index] = element;
    printf("index %d replaced\n",index);
}

void addALElement(ArrayList *ls, int index, ArrayListNode element)
{
    if(!ls || ls->count < index || index < 0 || ls->count >= ls->size)
    {
        printf("addALElement : out of range\n");
        return;
    }
    if(index==ls->count)
    {
        ls->array[ls->count++]=element;
    }
    else
    {
        for (int i = index; i < ls->count; i++)
        {
            ArrayListNode temp = ls->array[i];
            ls->array[i] = element;
            element = temp;
        }
        ls->array[ls->count++]=element;
    }
    printf("index %d added\n", index);
}

void removeALElement(ArrayList *ls, int index)
{
    if (!ls || index >= ls->count || index < 0)
    {
        printf("removeALElement : out of range\n");
        return;
    }
    for (int i = index; i < ls->count; i++)
        ls->array[i] = ls->array[i+1];
     ls->count--;
     printf("index %d deleted\n", index);
}

ArrayListNode* getALElement(ArrayList *ls, int index)
{
    if (index >= ls->count || index < 0)
    {
        printf("get : out of range\n");
        return 0;
    }
    ArrayListNode *new = malloc(sizeof(ArrayListNode *));
    *new = ls->array[index];
    return new;
}

/*
ArrayListNode* lookup(list *ls, int index)
{
    if (index >= ls->count || index < 0)
        return 0;
    return &(ls->array[index]);
}
*/

void displayArrayList(ArrayList *ls)
{
    if (!ls)
        return;
    else if (!ls->count)
        printf("displayArrayList : ls is null\n");
    else
        for(int i = 0; i < ls->count; i++)
            printf("%d\n", ls->array[i].data);
}

void clearArrayList(ArrayList *ls)
{
    if(!ls)
    {
        printf("displayArrayList : ls is null\n");
    }
    else
    {
        for(int i = 0; i < ls->count; i++)
                ls->array[i].data = 0;
        ls->count = 0;
    }
}

int getArrayListLength(ArrayList *ls)
{
    if (!ls)
        return 0;
    return ls->count;
}

int main()
{
    ArrayList *ls = createArrayList(3);
    printf("ls data %d\n",ls->array->data);
    ArrayListNode a;
    for(int i =0; i < 3; i++)
    {
        a.data=i+1;
        addALElement(ls,i,a);
    }
    displayArrayList(ls);
    removeALElement(ls,2);
    displayArrayList(ls);
    isArrayListFull_(ls);
    a.data=1;
    addALElement(ls,1,a);
    displayArrayList(ls);
    isArrayListFull_(ls);
    clearArrayList(ls);
    displayArrayList(ls);
    for(int i =0; i < 5; i++)
    {
    a.data=i+1;
    addALElement(ls,i,a);
    }
    displayArrayList(ls);
    removeALElement(ls, 0);
    displayArrayList(ls);
    ArrayListNode *b = getALElement(ls,0);
    printf("ls index 0 equals to %d\n",b->data);
    removeALElement(ls, 0);
    displayArrayList(ls);
    printf("ls index 0 equals to %d\n",b->data);
    int c = getArrayListLength(ls);
    printf("getArrayListLength is %d\n",c);
    a.data=1;
    addALElement(ls,1,a);
    a.data=1;
    addALElement(ls,1,a);
    c = getArrayListLength(ls);
    displayArrayList(ls);
    printf("getArrayListLength is %d\n",c);
    removeALElement(ls,ls->count - 1);
    displayArrayList(ls);
    removeALElement(ls,3);
    displayArrayList(ls);
    a.data=1;
    replaceALElement(ls,0,a);
    displayArrayList(ls);
    deleteArrayList(&ls);
    displayArrayList(ls);
    system("leaks arraylist");
    return (0);
}
