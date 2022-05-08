#include "functions.h"

void insertCustomer(int arrivalTime, int processTime, char name, LinkedQueue *pQueue)
{
    QueueNode *customer;
    
    if (!pQueue || arrivalTime < 0 || processTime <= 0)
        error(pQueue);
    customer = malloc(sizeof(SimCustomer));
    if (!customer)
        error(pQueue);
    customer->data.status = arrival;
    customer->data.arrivalTime = arrivalTime;
    customer->data.processTime = processTime;
    customer->data.endTime = processTime;
    customer->data.startTime = 0;
    customer->data.name = name;
    customer->data.getService = 0;
    enqueueLQ(pQueue, *customer);
}