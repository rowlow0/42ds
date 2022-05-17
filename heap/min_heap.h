#ifndef _BIN_TREE_MIN_HEAP_
#define _BIN_TREE_MIN_HEAP_

#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeapNodeType
{
	char data;
	int visited;
	int	key;
} MinHeapNode;

typedef struct MinHeapType
{
	int	currentElementCount;
	int	maxElementCount;
	struct MinHeapNodeType* pElement;
} MinHeap;

MinHeap* makeMinHeap(int max_size);
void insertMinHeap(MinHeap *heap, MinHeapNode data);
MinHeapNode deleteRootNodeHeap(MinHeap *heap);
void deleteMinHeap(MinHeap** heap);

//void  deleteAllNode(MinHeapNode *root);



#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif