#include "linkedQueue.h"

int dequeueLQ(LinkedQueue* pQueue)
{
    LinkedQueueNode *nextNode;

    if (!pQueue || pQueue->currentElementCount <= 0)
        return (FALSE);
    nextNode = pQueue->front->pLink;
    pQueue->front->pLink = 0;
    free(pQueue->front);
    if (pQueue->currentElementCount == 1)
    {
        pQueue->front = 0;
        pQueue->rear = 0;
    }
    else
        pQueue->front = nextNode;
    pQueue->currentElementCount -= 1;
    return (TRUE);
}