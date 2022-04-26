#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_
typedef struct CircularListNodeType
{
    int data;
    struct CircularListNodeType *next;
} CircularListNode;
typedef struct CircularLinkedListType
{
    int count;
    CircularListNode *head;
	CircularListNode *tail;
} CircularLinkedList;
CircularLinkedList* createCircularLinkedList();
void addCLElement(CircularLinkedList *ls, int index, CircularListNode element);
void removeCLElement(CircularLinkedList *ls, int index);
CircularListNode* getCLElement(CircularLinkedList *ls, int index);
//CircularListNode* shallow(CircularLinkedList *ls, int index);
void clearCircularLinkedList(CircularLinkedList *ls);
int getCircularLinkedListLength(CircularLinkedList *ls);
void deleteCircularLinkedList(CircularLinkedList** ls);
void displayCircularLinkedList(CircularLinkedList *ls);
void replaceCLElement(CircularLinkedList *ls, int index, CircularListNode element);
//int	setDLElement(CircularLinkedList element, int index);
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE        1
#define FALSE       0
#endif