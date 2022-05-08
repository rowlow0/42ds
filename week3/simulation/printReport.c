#include "functions.h"

void printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime)
{
    (void)pWaitQueue;
    printf("totil user count : %d total wait time : %d\n", serviceUserCount, totalWaitTime);
    
}