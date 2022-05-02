#include "arrayqueue.h"

int isArrayQueueEmpty(ArrayQueue *pQueue)
{
    if (pQueue && pQueue->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}