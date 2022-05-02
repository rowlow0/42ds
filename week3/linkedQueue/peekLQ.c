#include "linkedQueue.h"

LinkedQueueNode *peekLQ(LinkedQueue* pQueue)
{
    if (!pQueue || pQueue->currentElementCount <= 0)
        return (0);
    return (pQueue->front);
}