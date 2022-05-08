#include "functions.h"

void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
    if (pArrivalQueue && pArrivalQueue->front && pWaitQueue)
    {
        if (currentTime == pArrivalQueue->front->data.arrivalTime)
        {
            enqueueLQ(pWaitQueue, *pArrivalQueue->front);
            dequeueLQ(pArrivalQueue);
        }
    }
}