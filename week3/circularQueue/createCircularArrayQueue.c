#include "circularArrayQueue.h"

CircularArrayQueue* createCircularArrayQueue(int maxElementCount)
{
    CircularArrayQueue      *pQueue;
    CircularArrayQueueNode  *pArray;

    if (maxElementCount <= 0)
        return (0);
    pQueue = (CircularArrayQueue *)malloc(sizeof(CircularArrayQueue));
    if (!pQueue)
        return (0);
    pArray = (CircularArrayQueueNode *)malloc(sizeof(CircularArrayQueueNode) * maxElementCount);
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