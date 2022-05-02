#include "arrayqueue.h"

int main()
{
    int				size;
	ArrayQueue		*pQueue;
	ArrayQueueNode	node1;
	ArrayQueueNode	node2;
	ArrayQueueNode	node3;
	ArrayQueueNode	node4;
    ArrayQueueNode  *peek;

	size = 3;
	pQueue = createArrayQueue(size);
	node1.data = 'a';
	node2.data = 'b';
	node3.data = 'c';
	node4.data = 'd';
	enqueueAQ(pQueue, node1);       // a
	enqueueAQ(pQueue, node2);       // a  b
    dequeueAQ(pQueue);              // () b
	enqueueAQ(pQueue, node3);       // () b c
	enqueueAQ(pQueue, node4);       // d b c
    peek = peekAQ(pQueue);

    deleteArrayQueue(&pQueue);
    return (0);
}