#include "linkedQueue.h"

void deleteLinkedQueue(LinkedQueue** pQueue)
{
    QueueNode *currNode;
    QueueNode *nextNode;

    if (pQueue)
    {
        if((*pQueue)->currentElementCount > 0)
        {
            currNode = (*pQueue)->front;
            for (int i =0; i < (*pQueue)->currentElementCount; i++)
            {
                nextNode = currNode->pLink;
                currNode->pLink = 0;
                free(currNode);
                currNode = nextNode;
            }
            (*pQueue)->currentElementCount = 0;
        }
        free(*pQueue);
        *pQueue = 0;
    }
}