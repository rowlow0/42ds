#include "linkedQueue.h"

int isLinkedQueueEmpty(LinkedQueue* pQueue)
{
    if (!pQueue)
        return (ERROR);
    if (pQueue->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}