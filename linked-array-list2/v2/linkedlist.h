#ifndef _LINKEDLIST_
#define _LINKEDLIST_

typedef struct ListNodeType
{
	int data;
	struct ListNodeType* next;
} ListNode;

typedef struct LinkedListType
{
	int currentElementCount;	// ���� ����� ������ ����
	ListNode head;		// ��� ���(Header Node)
} LinkedList;

LinkedList* createLinkedList();
int addLLElement(LinkedList* list, int index, ListNode element);
int removeLLElement(LinkedList* list, int index);
ListNode* getLLElement(LinkedList* list, int index);
void displayLinkedList(LinkedList* list);
void clearLinkedList(LinkedList* list);
int getLinkedListLength(LinkedList* list);
void deleteLinkedList(LinkedList** list);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif