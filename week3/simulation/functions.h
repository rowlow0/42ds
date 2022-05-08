#include "linkedQueue/linkedQueue.h"

void insertCustomer(int arrivalTime, int processTime, char name, LinkedQueue *pQueue);
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue); 
QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);
QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime); 
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);
void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime);
int getRandomProcessTime();
void error(LinkedQueue *pQueue);
