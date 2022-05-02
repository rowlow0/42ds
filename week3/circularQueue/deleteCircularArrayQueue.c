#include "circularArrayQueue.h"

void deleteCircularArrayQueue(CircularArrayQueue **pQueue)
{
    CircularArrayQueueNode  *pArray;

    if (!pQueue)
        return ;
    pArray = (*pQueue)->pElement;
    (*pQueue)->pElement = 0;
    free(pArray);
    free(*pQueue);
    *pQueue = 0;
}