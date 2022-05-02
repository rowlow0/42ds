#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <stdlib.h>
#include <stdio.h>
typedef struct LinkedQueueNodeType
{
	char data;
	struct LinkedQueueNodeType *pLink;
} LinkedQueueNode;

typedef struct LinkedQueueType
{
	int currentElementCount;
	LinkedQueueNode *front;
	LinkedQueueNode *rear;
} LinkedQueue;

LinkedQueue* createLinkedQueue();
int enqueueLQ(LinkedQueue* pQueue, LinkedQueueNode element);
int dequeueLQ(LinkedQueue* pQueue);
LinkedQueueNode *peekLQ(LinkedQueue* pQueue);
void deleteLinkedQueue(LinkedQueue** pQueue);
int isLinkedQueueEmpty(LinkedQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0
#define	ERROR		-1

#endif