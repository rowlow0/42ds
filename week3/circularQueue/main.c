#include "circularArrayQueue.h"

int main()
{
    int				size;
	CircularArrayQueue		*pQueue;
	CircularArrayQueueNode	node1;
	CircularArrayQueueNode	node2;
	CircularArrayQueueNode	node3;
	CircularArrayQueueNode	node4;
    CircularArrayQueueNode  *peek;

	size = 3;
	pQueue = createCircularArrayQueue(size);
	node1.data = 'a';
	node2.data = 'b';
	node3.data = 'c';
	node4.data = 'd';
	enqueueCAQ(pQueue, node1);       // a
	enqueueCAQ(pQueue, node2);       // a  b
    dequeueCAQ(pQueue);              // () b
	enqueueCAQ(pQueue, node3);       // () b c
	enqueueCAQ(pQueue, node4);       // d b c
    peek = peekCAQ(pQueue);

    deleteCircularArrayQueue(&pQueue);
    return (0);
}