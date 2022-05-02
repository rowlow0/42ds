#ifndef CIRCULAR_ARRAY_QUEUE_
#define CIRCULAR_ARRAY_QUEUE_

#include <stdlib.h>

typedef struct CircularArrayQueueNodeType
{
	char data;
} CircularArrayQueueNode;

typedef struct CircularArrayQueueType
{
	int maxElementCount;		// �ִ� ���� ����
	int currentElementCount;	// ���� ������ ����
	int front;					// front ��ġ
	int rear;					// rear ��ġ
	CircularArrayQueueNode *pElement;	// ��� ������ ���� 1���� �迭 ������
} CircularArrayQueue;

CircularArrayQueue* createCircularArrayQueue(int maxElementCount);
int enqueueCAQ(CircularArrayQueue* pQueue, CircularArrayQueueNode element);
CircularArrayQueueNode *dequeueCAQ(CircularArrayQueue* pQueue);
CircularArrayQueueNode *peekCAQ(CircularArrayQueue* pQueue);
void deleteCircularArrayQueue(CircularArrayQueue** pQueue);
int isCircularArrayQueueFull(CircularArrayQueue* pQueue);
int isCircularArrayQueueEmpty(CircularArrayQueue* pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif