#include "circularArrayQueue.h"

int isCircularArrayQueueEmpty(CircularArrayQueue *pQueue)
{
    if (pQueue && pQueue->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}