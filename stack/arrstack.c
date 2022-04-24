#include "arrstack.h"

Arr* createArrStack()
{
    Arr *ls = malloc(sizeof(Arr));
    ls->count = 0;
    ls->array = malloc(0);
    return ls;
}

int pushAR(Arr* arr, ArrNode element)
{
    if(arr)
    {
        arr->array[arr->count++]=element;
        return TRUE;
    }
    else
        return FALSE;
}

ArrNode *popAR(Arr* arr)
{
    if(arr)
    {
        arr->count--;
        return TRUE;
    }
    else
        return FALSE;
}

ArrNode *peekAR(Arr* arr)
{
    if(arr)
        return &arr->array[arr->count];
    else
        return FALSE;
}

void deleteArrStack(Arr** arr)
{
    if(arr)
    {
        free((*arr)->array);
        free(*arr);
        *arr = 0;
    }
}

int isArrStackFull(Arr* arr)
{
    if(arr)
        return arr->count >= MAX_STACK;
    else
        return FALSE;
}

int isArrStackEmpty(Arr* arr)
{
    if(arr)
        return arr->count == 0;
    else
        return FALSE;
}

void displayArrayList(Arr *arr)
{
    if(arr)
        for(int i = 0; i < arr->count;i++)
            printf("%d\n",arr->array[i].data);
}

int main()
{
    Arr * s = createArrStack();
    ArrNode t;
    for (int i = 0;i < 10;i++)
    {
        t.data = i+48;
        pushAR(s,t);
    }
    displayArrayList(s);
    deleteArrStack(&s);
    system("leaks out");
    return FALSE;
}
