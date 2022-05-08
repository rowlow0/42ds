#include "functions.h"

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
    if (pWaitQueue->front->pLink)
    {
        printf("%currentTime %d, pWaitQueue is \n", currentTime, pWaitQueue->front->pLink->data.name);
    }
    else
    {
        printf("wait status : nothing\n");
    }
}