#include "linkedQueue.h"

int enqueueLQ(LinkedQueue* pQueue, QueueNode element)
{
    QueueNode *newNode;

    if (!pQueue)
        return (FALSE);
    newNode = (QueueNode *)malloc(sizeof(QueueNode));
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