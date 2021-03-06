#ifndef _GRAPH_LINKEDLIST_
#define _GRAPH_LINKEDLIST_

#include "stdio.h"
#include "stdlib.h"

typedef struct GraphVertexType
{
	int vertexID;	//
	int weight;
	int parent_ID;
	int count;
} GraphVertex;

typedef struct ListNodeType
{
	GraphVertex data;
	struct ListNodeType* pLink; // vertex
	struct ListNodeType* head; // edege
	struct ListNodeType* que; // for supporting queue
} ListNode;

typedef struct LinkedListType
{
	int currentElementCount;	//
	ListNode headerNode;		//
} LinkedList;

LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int index, ListNode element);
void addLLEEdge(LinkedList* pList, int from, int to, int weight);
int removeLLElement(LinkedList* pList, int index);
ListNode* getLLElement(LinkedList* pList, int index);

void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList** pList);

void deleteLLEEdge(LinkedList *pList, int from, int to);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif