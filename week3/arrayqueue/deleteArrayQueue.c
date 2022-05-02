#include "arrayqueue.h"

void deleteArrayQueue(ArrayQueue **pQueue)
{
    ArrayQueueNode  *pArray;

    if (!pQueue)
        return ;
    pArray = (*pQueue)->pElement;
    (*pQueue)->pElement = 0;
    free(pArray);
    free(*pQueue);
    *pQueue = 0;
}