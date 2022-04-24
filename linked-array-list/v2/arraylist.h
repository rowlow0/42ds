#ifndef _ARRAYLIST_
#define _ARRAYLIST_

typedef struct ArrayListNodeType
{
	int data;
} ArrayListNode;

typedef struct ArrayListType
{
	int maxElementCount;
	int currentElementCount;
	ArrayListNode *array;
} ArrayList;

ArrayList* createArrayList(int mount);
void deleteArrayList(ArrayList** list);
int isArrayListFull(ArrayList* list);
int addALElement(ArrayList* list, int index, ArrayListNode element);
int replaceALElement(ArrayList* list, int index, ArrayListNode element);
int removeALElement(ArrayList* list, int index);
ArrayListNode* getALElement(ArrayList* list, int index);
void displayArrayList(ArrayList* list);
void clearArrayList(ArrayList* list);
int getArrayListLength(ArrayList* list);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif