#ifndef _DOUBLYLIST_
#define _DOUBLYLIST_

typedef struct DoublyListNodeType
{
	int data;
	struct DoublyListNodeType* prev;
	struct DoublyListNodeType* next;
} DoublyListNode;

typedef struct DoublyListType
{
	int	count;
	DoublyListNode *head;
} DoublyList;

DoublyList* createDoublyList();
void deleteDoublyList(DoublyList** ls);
int addDLElement(DoublyList* ls, int index, DoublyListNode element);
int removeDLElement(DoublyList* ls, int index);
void clearDoublyList(DoublyList* ls);
int getDoublyListLength(DoublyList* ls);
DoublyListNode* getDLElement(DoublyList* ls, int index);
void displayDoublyList(DoublyList* ls);
//int	setDLElement(DoublyListNode element, int index);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif