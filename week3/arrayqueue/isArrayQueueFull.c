#include "arrayqueue.h"

int isArrayQueueFull(ArrayQueue *pQueue)
{
    if (pQueue && pQueue->maxElementCount == pQueue->currentElementCount)
        return (TRUE);
    return (FALSE);
}