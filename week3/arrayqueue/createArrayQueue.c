#include "arrayqueue.h"

ArrayQueue* createArrayQueue(int maxElementCount)
{
    ArrayQueue      *pQueue;
    ArrayQueueNode  *pArray;

    if (maxElementCount <= 0)
        return (0);
    pQueue = (ArrayQueue *)malloc(sizeof(ArrayQueue));
    if (!pQueue)
        return (0);
    pArray = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode) * maxElementCount);
    if (!pArray)
    {
        free(pQueue);
        return (0);
    }
    pQueue->maxElementCount = maxElementCount;
    pQueue->currentElementCount = 0;
    pQueue->front = 0;
    pQueue->rear = -1;
    pQueue->pElement = pArray;
    return (pQueue);
}