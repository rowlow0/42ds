#ifndef _POLYLINKEDLIST_H_
#define _POLYLINKEDLIST_H_

typedef struct PolyListNodeType
{
    int data;
    int pow;
    struct PolyListNodeType *next;
} PolyListNode;

typedef struct PolyLinkedListType
{
    int count;
    PolyListNode *head;
} PolyLinkedList;

PolyLinkedList* createPolyLinkedList();
void addPLLElement(PolyLinkedList *ls, int index, PolyListNode element);
void removePLLElement(PolyLinkedList *ls, int index);
PolyListNode* getPLLElement(PolyLinkedList *ls, int index);
//ListNode* shallow(LinkedList *ls, int index);
void clearPolyLinkedList(PolyLinkedList *ls);
int getPolyLinkedListLength(PolyLinkedList *ls);
void deletePolyLinkedList(PolyLinkedList** ls);
void displayPolyLinkedList(PolyLinkedList *ls);
void replacePLLElement(PolyLinkedList *ls, int index, PolyListNode element);
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE        1
#define FALSE       0
#endif