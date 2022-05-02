#include "circularArrayQueue.h"

CircularArrayQueueNode *dequeueCAQ(CircularArrayQueue* pQueue)
{
    CircularArrayQueueNode *node;

    if (!pQueue || pQueue->currentElementCount == 0)
        return (0);
    pQueue->currentElementCount -= 1;
    node = &pQueue->pElement[pQueue->front];
    pQueue->front = ++pQueue->front % pQueue->maxElementCount;
    return (node);
}