#include "circularArrayQueue.h"

int enqueueCAQ(CircularArrayQueue* pQueue, CircularArrayQueueNode element)
{
    if(pQueue && pQueue->currentElementCount < pQueue->maxElementCount)
    {
        pQueue->rear = ++pQueue->rear % pQueue->maxElementCount;
        pQueue->pElement[pQueue->rear] = element;
        pQueue->currentElementCount++;
        return (TRUE);
    }
    return (FALSE);
}