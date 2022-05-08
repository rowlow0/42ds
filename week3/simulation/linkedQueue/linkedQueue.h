#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include "../simdef.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct LinkedQueueNodeType
{
	SimCustomer data;
	struct LinkedQueueNodeType *pLink;
} QueueNode;

typedef struct LinkedQueueType
{
	int currentElementCount;
	QueueNode *front;
	QueueNode *rear;
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int enqueueLQ(LinkedQueue* pQueue, QueueNode element);
int dequeueLQ(LinkedQueue* pQueue);
QueueNode *peekLQ(LinkedQueue* pQueue);
void deleteLinkedQueue(LinkedQueue** pQueue);
int isLinkedQueueEmpty(LinkedQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0
#define	ERROR		-1

#endif