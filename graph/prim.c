#include "graphlinkedlist.c"
#include <limits.h>
//priority queue ElogV
//adjacency matrix v2
//min heap ElogV

typedef struct minHeapNodeType {
    int v;
    int key;
} minHeapNode;

typedef struct MinHeapType {
    int size;
    int capacity;
    int *pos;
    minHeapNode **array;
} minHeap;

minHeapNode *newMinHeapNode(int v, int key)
{
    minHeapNode *new = malloc(sizeof(minHeapNode));
    new->key = key;
    new->v = v;
    return new;
}

minHeap *createMinHeap(int capacity)
{
    minHeap *new = malloc(sizeof(minHeap));
    new->pos = malloc(capacity * sizeof(int));
    new->size = 0;
    new->capacity = capacity;
    new->array = malloc(capacity * sizeof(minHeapNode));
    return new;
}

void swapMinHeapNode(minHeapNode **a, minHeapNode **b)
{
    minHeapNode *q = *a;
    *a = *b;
    *b = q;
}

void minHeapify(minHeap *heap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    if(left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
        smallest = left;
    if(right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
        smallest = right;
    if(smallest != idx)
    {
        minHeapNode *smallestNode = heap->array[smallest];
        minHeapNode *idxNode = heap->array[idx];
        heap->pos[smallestNode->v] = idx;
        heap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isEmpty(minHeap *heap)
{
    return heap->size == 0;
}

minHeapNode *extractMin(minHeap *heap)
{
    if(isEmpty(heap))
        return NULL;
    minHeapNode *root = heap->array[0];
    minHeapNode *lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;
    heap->pos[root->v] = heap->size - 1;
    heap->pos[lastNode->v] = 0;
    --heap->size;
    minHeapify(heap, 0);
    return root;
}

void decreaseKey(minHeap *heap, int v, int key)
{
    int i = heap->pos[v];
    heap->array[i]->key = key;
    while(i && heap->array[i]->key < heap->array[(i - 1) / 2]->key)
    {
        heap->pos[heap->array[i]->v] = (i - 1) / 2;
        heap->pos[heap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&heap->array[i],&heap->array[(i-1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(minHeap *heap, int v)
{
    if(heap->pos[v] < heap->size)
        return 1;
    return 0;
}

void printArr(int *arr, int n, int *arr2, int sum)
{
    for(int i = 1; i < n; i++)
        printf("%d - %d == %d\n", arr[i], i, arr2[i]);
    printf("minimum cost spanning tree: %d", sum);
}

void primMST(LinkedList *list)
{
    int V = list->currentElementCount;
    int parent[V];
    int key[V];
    int sum;

    minHeap *heap = createMinHeap(V);

    for(int v = 1; v< V; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        heap->array[v] = newMinHeapNode(v, key[v]);
        heap->pos[v] = v;
    }
    key[0] = 0;
    sum = 0;
    heap->array[0] = newMinHeapNode(0, key[0]);
    heap->pos[0] = 0;
    heap->size = V;
    while(!isEmpty(heap))
    {
        minHeapNode *node = extractMin(heap);
        int u = node->v;
        ListNode *pCrawl = list->headerNode.pLink;
        while(pCrawl->data.vertexID != u)
            pCrawl = pCrawl->pLink;
        while(pCrawl)
        {
            int v = pCrawl->data.vertexID;
            if(isInMinHeap(heap, v) && pCrawl->data.weight < key[v])
            {
                key[v] = pCrawl->data.weight;
                parent[v] = u;
                decreaseKey(heap, v, key[v]);
            }
            pCrawl = pCrawl->head;
        }
        free(node);
    }
    for(int i = 0; i < V; i++)
        sum +=key[i];
    printArr(parent, V, key, sum);
    free(heap->pos);
    free(heap->array);
    free(heap);
}


int main()
{
    LinkedList *list = createLinkedList();
    ListNode element;
    GraphVertex g;
    element.pLink = 0;
	g.weight = 0;
    g.count = 0;
    g.parent_ID = 0;
    g.vertexID = 1;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 2;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 3;
    element.data = g;
    addLLElement(list,2,element);
    g.vertexID = 4;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 5;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 0;
    element.data = g;
    addLLElement(list,0,element);
    g.vertexID = 6;
    element.data = g;
    addLLElement(list,100,element);
    addLLEEdge(list,0,0,99);
    addLLEEdge(list,0,6,99);
    addLLEEdge(list,0,3,99);
    addLLEEdge(list,0,1,1);
    addLLEEdge(list,0,1,6);
    addLLEEdge(list,0,2,99);
    addLLEEdge(list,1,2,2);
    addLLEEdge(list,1,2,3);
    addLLEEdge(list,1,3,4);
    addLLEEdge(list,1,4,99);
    addLLEEdge(list,2,4,5);
    addLLEEdge(list,3,5,6);
    addLLEEdge(list,4,6,7);
    addLLEEdge(list,5,1,8);
    addLLEEdge(list,6,2,9);
    addLLEEdge(list,6,3,10);
    addLLEEdge(list,7,4,11);
    addLLEEdge(list,7,5,12);
    primMST(list);
    //addLLEEdge(list,0,2,3);
    //addLLEEdge(list,1,2,2);
    //addLLEEdge(list,3,5,5);
    //addLLEEdge(list,4,5,6);
    //addLLEEdge(list,0,1,4);
    //addLLEEdge(list,2,3,1);
    //addLLEEdge(list,4,3,1);
    deleteLinkedList(&list);
    //gcc -g -fsanitize=address -Wall -Wextra -Werror prim.c
    //gcc -Wall -Wextra -Werror prim.c
    //system("leaks a.out");
    return (0);
}