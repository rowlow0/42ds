#ifndef _LINKEDLIST_
#define _LINKEDLIST_
typedef struct ListNodeType
{
    int data;
    struct ListNodeType *next;
} ListNode;
typedef struct LinkedListType
{
    int count;
    ListNode *head;
} LinkedList;
LinkedList* createLinkedList();
void addLLElement(LinkedList *ls, int index, ListNode element);
void removeLLElement(LinkedList *ls, int index);
ListNode* getLLElement(LinkedList *ls, int index);
//ListNode* shallow(LinkedList *ls, int index);
void clearLinkedList(LinkedList *ls);
int getLinkedListLength(LinkedList *ls);
void deleteLinkedList(LinkedList** ls);
void displayLinkedList(LinkedList *ls);
void replaceLLElement(LinkedList *ls, int index, ListNode element);
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE        1
#define FALSE       0
#endif