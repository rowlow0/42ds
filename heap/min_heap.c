#include	"min_heap.h"

MinHeap* makeMinHeap(int max_size)
{
	MinHeap *newHeap = calloc(1, sizeof(MinHeap));
	newHeap->pElement = calloc(max_size, sizeof(MinHeapNode));
	return (newHeap);
}

void insertMinHeap(MinHeap *heap, MinHeapNode data)
{
	int	i;

	if (heap->currentElementCount == heap->maxElementCount)
	{
		printf("Min_Heap is full\n");
		return (0);
	}
	heap->currentElementCount++;
	i = heap->currentElementCount;
	while((i != 1) && (data.key < heap->pElement[i/2].key)) // data가 부모노드 보다 작을 때
	{
		heap->pElement[i] = heap->pElement[i/2]; // 현재 자리에 부모 노드 저장
		i = i / 2; // 부모노드로 이동
	}
	heap->pElement[i] = data;
}



MinHeapNode deleteRootNodeHeap(MinHeap *heap)
{
	MinHeapNode	result = heap->pElement[1]; // 삭제할 루트 노드
	int i = heap->currentElementCount;
	MinHeapNode tmp = heap->pElement[i]; //맨마지막 값
	heap->currentElementCount--;
	int parent = 1;
	int	child = 2;
	while (child <= heap->currentElementCount)
	{
		if ((child < heap->currentElementCount)
			&& heap->pElement[child].key > heap->pElement[child + 1].key) //왼쪽 자식노드가 오른쪽 자식노드보다 클 때
			child++; // 더 작은 노드를 가리키도록
		if (tmp.key <= heap->pElement[child].key) // 노드가 child 노드보다 크다면 break;
			break;
		heap->pElement[parent] = heap->pElement[child];
		parent = child;
		child *= 2;
	}
	heap->pElement[parent] = tmp;
//	heap->pElement[heap->currentElementCount + 1];
	return (result);
}

/*
MinHeap *deleteNodeHeap(MinHeap *heap, int key)
{

}
*/

void deleteMinHeap(MinHeap** heap)
{
	if (heap && *heap)
	{
		if((*heap)->pElement)
			free((*heap)->pElement);
		free(*heap);
		*heap = 0;
	}
}


int	main(void)
{
	MinHeap *heap;
	MinHeapNode	node;

	node.data = 'a';
	node.visited = 0;
	node.key = 3;
	heap = makeMinHeap(10);
	insertMinHeap(heap, node);
	node.key = 2;
	insertMinHeap(heap, node);
	node.key = 6;
	insertMinHeap(heap, node);
	node.key = 1;
	insertMinHeap(heap, node);
	node.key = 0;
	insertMinHeap(heap, node);
	for (int i = 1; i <= heap->currentElementCount; i++)
	{
		printf("i[%d] heap %d\n", i, (heap->pElement[i]).key);
	}
	for (int i = 1; heap->currentElementCount; i++)
	{
		printf("i[%d] delete node %d\n", i, (deleteNodeHeap(heap[i]->key));
	}
	return (0);
}