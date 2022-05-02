#include "circularArrayQueue.h"

CircularArrayQueueNode *peekCAQ(CircularArrayQueue* pQueue)
{
    if (pQueue && pQueue->currentElementCount)
        return (&pQueue->pElement[pQueue->front]);
    return (FALSE);
}