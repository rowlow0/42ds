#include "linkedQueue.h"

int enqueueLQ(LinkedQueue* pQueue, LinkedQueueNode element)
{
    LinkedQueueNode *newNode;

    if (!pQueue)
        return (FALSE);
    newNode = (LinkedQueueNode *)malloc(sizeof(LinkedQueueNode));
    if (!newNode)
        return (FALSE);
    newNode->data = element.data;
    if (pQueue->currentElementCount == 0)
    {
        pQueue->front = newNode;
        pQueue->rear = newNode;
    }
    else
    {
        pQueue->rear->pLink = newNode;
        pQueue->rear = newNode;
    }
    pQueue->currentElementCount += 1;
    return (TRUE);
}