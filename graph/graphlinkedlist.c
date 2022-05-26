#include "graphlinkedlist.h"

//create
LinkedList* createLinkedList()
{
    LinkedList *new = malloc(sizeof(LinkedList));
    new->currentElementCount = 0;
    return new;
}

//add
int addLLElement(LinkedList* pList, int position, ListNode element)
{
    return 0;
}

//remove
int removeLLElement(LinkedList* pList, int position)
{
    return 0;
}

//get element
ListNode* getLLElement(LinkedList* pList, int position)
{
    return 0;
}


//clear
void clearLinkedList(LinkedList* pList)
{

}

//length
int getLinkedListLength(LinkedList* pList)
{
        return pList ? pList->currentElementCount : 0;
}

//delete
void deleteLinkedList(LinkedList** pList)
{
    free(*pList);
    *pList = 0;
}

int main()
{
    return (0);
}