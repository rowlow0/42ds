#include "arrayqueue.h"

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
    ArrayQueueNode *node;

    if (!pQueue || pQueue->currentElementCount == 0)
        return (0);
    pQueue->currentElementCount -= 1;
    node = &pQueue->pElement[pQueue->front];
    pQueue->front += 1;
    return (node);
}