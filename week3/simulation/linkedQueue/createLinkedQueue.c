#include "linkedQueue.h"

LinkedQueue* createLinkedQueue()
{
        LinkedQueue *pQueue;
        
        pQueue = malloc(sizeof(LinkedQueue));
        if (!pQueue)
            return (FALSE);
        pQueue->currentElementCount = 0;
        pQueue->front = 0;
        pQueue->rear = 0;
        return (pQueue);
}