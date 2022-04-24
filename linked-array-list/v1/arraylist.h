#ifndef _ARRAYLIST_
#define _ARRAYLIST_
typedef struct ArrayListNodeType
{
    int data;
} ArrayListNode;
typedef struct ArrayListType
{
    int count;
    int size;
    ArrayListNode *array;
} ArrayList;
ArrayList* createArrayList(int count);
void deleteArrayList(ArrayList **ls);
void isArrayListFull(ArrayList *ls);
void addALElement(ArrayList *ls, int index, ArrayListNode element);
void removeALElement(ArrayList *ls, int index);
ArrayListNode* getALElement(ArrayList *ls, int index);
void clearArrayList(ArrayList *ls);
int getArrayListLength(ArrayList *ls);
void displayArrayList(ArrayList *ls);
void replaceALElement(ArrayList *ls, int index, ArrayListNode element);
#endif
#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_
#define TRUE        1
#define FALSE       0
#endif