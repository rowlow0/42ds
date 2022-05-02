#include "arrayqueue.h"

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
    if (pQueue && pQueue->currentElementCount)
        return (&pQueue->pElement[pQueue->front]);
    return (FALSE);
}