#include "functions.h"

int main(void)
{
    int i = 0, t = 0, processTime = 0, serviceCount = 0, totalWaitTime = 0, amount = 0, working = 0;
    char    name = 0;

    LinkedQueue *pArrivalQueue = malloc(sizeof(LinkedQueue));
    LinkedQueue *pWaitQueue = malloc(sizeof(LinkedQueue));

    /*
    printf("Input the queue length : ");
    scanf("%d", &amount);
    */
   amount = 3;

    for(i = 0; i < amount * 2; i += 2)
    {
        processTime = getRandomProcessTime();
        printf("i: %d, processTime: %d\n", i, processTime);
        name =  65 + i / 2;
        insertCustomer(i, processTime, name, pArrivalQueue);
    }

    while (!isLinkedQueueEmpty(pArrivalQueue) || !isLinkedQueueEmpty(pWaitQueue))
    {
        processArrival(t, pArrivalQueue, pWaitQueue);
        QueueNode   *currCustomer = peekLQ(pWaitQueue);
        
        if (currCustomer->data.status == arrival)
        {
            currCustomer->data.status = start;
            currCustomer->data.endTime += t;
            currCustomer->data.startTime = t;
            working = 0;
        }
        else if (currCustomer->data.status == end)
        {
            dequeueLQ(pWaitQueue);
            serviceCount++;
            continue;
        }
        if(currCustomer->pLink)
        {
            totalWaitTime++;
        }
        if (currCustomer->data.startTime + working == currCustomer->data.endTime)
        {
            currCustomer->data.status = end;
            continue;
        }
        else
            working++;
        t += 1;
        printSimCustomer(t, currCustomer->data);
    }
    printReport(0, serviceCount, totalWaitTime);
    return (0);
}