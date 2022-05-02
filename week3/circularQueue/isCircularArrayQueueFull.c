#include "circularArrayQueue.h"

int isCircularArrayQueueFull(CircularArrayQueue *pQueue)
{
    if (pQueue && pQueue->maxElementCount == pQueue->currentElementCount)
        return (TRUE);
    return (FALSE);
}