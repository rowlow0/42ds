#include "arrayqueue.h"

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
    if(pQueue && pQueue->currentElementCount < pQueue->maxElementCount)
    {
        pQueue->pElement[++pQueue->rear] = element;
        pQueue->currentElementCount++;
        return (TRUE);
    }
    return (FALSE);
}