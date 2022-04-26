#ifndef _CIRCULARDOUBLYLIST_H_
#define _CIRCULARDOUBLYLIST_H_

typedef struct CircularDoublyListNodeType
{
	int data;
	struct CircularDoublyListNodeType* prev;
	struct CircularDoublyListNodeType* next;
} CircularDoublyListNode;

typedef struct CircularDoublyListType
{
	int	count;
	CircularDoublyListNode *head;
} CircularDoublyList;

CircularDoublyList* createCircularDoublyList();
void deleteCircularDoublyList(CircularDoublyList** ls);
int addCLElement(CircularDoublyList* ls, int index, CircularDoublyListNode element);
int removeCLElement(CircularDoublyList* ls, int index);
void clearCircularDoublyList(CircularDoublyList* ls);
int getCircularDoublyListLength(CircularDoublyList* ls);
CircularDoublyListNode* getCLElement(CircularDoublyList* ls, int index);
void displayCircularDoublyList(CircularDoublyList* ls);
//int	setCLElement(CircularDoublyListNode element);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif