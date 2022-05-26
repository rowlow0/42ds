#include "graphlinkedlist.h"
/*
while..
doubly linked list x
edge
graph type
dfs bfs
*/

//create
LinkedList* createLinkedList()
{
    LinkedList *new = malloc(sizeof(LinkedList));
    new->currentElementCount = 0;
    return new;
}

//add; overflow of pList->currentElementCount are not checking
int addLLElement(LinkedList* pList, int index, ListNode element)
{
    if(pList && index >= 0)
    {
        if(index == 0 || !pList->currentElementCount)
        {
            if(pList->currentElementCount)
            {
                ListNode *prev = malloc(sizeof(ListNode));
                prev->data = element.data;
                prev->pLink = pList->headerNode.pLink;
                pList->headerNode.pLink = prev;
            }
            else
            {
                pList->headerNode.pLink = malloc(sizeof(ListNode));
                pList->headerNode.pLink->data = element.data;
                pList->headerNode.pLink->pLink = NULL;
            }
        }
        else
        {
            ListNode *prev = pList->headerNode.pLink;
            if (index >= pList->currentElementCount)
            {
                while(prev->pLink)
                    prev = prev->pLink;
                prev->pLink = malloc(sizeof(ListNode));
                prev->pLink->data = element.data;
                prev->pLink->pLink = NULL;
            }
            else
            {
                while(--index)
                    prev = prev->pLink;
                ListNode *new = malloc(sizeof(ListNode));
                new->data = element.data;
                new->pLink = prev->pLink;
                prev ->pLink = new;
            }
        }
        pList->currentElementCount++;
        return 1;
    }
    return 0;
}

//remove
int removeLLElement(LinkedList* pList, int index)
{
    if (pList && index >= 0)
    {
        index = pList->currentElementCount < index ? pList->currentElementCount -1 : index;
        ListNode *tmp;
        if(index == 0)
        {
            tmp = pList->headerNode.pLink;
            pList->headerNode.pLink = pList->headerNode.pLink->pLink;
        }
        else
        {
            ListNode *prev = pList->headerNode.pLink;
            while(--index)
                prev = prev->pLink;
            tmp = prev->pLink;
            prev->pLink = tmp->pLink;
        }
        free(tmp);
        pList->currentElementCount--;
        return 1;
    }
    return 0;
}

/*
//get element
ListNode* getLLElement(LinkedList* pList, int index)
{
    if (pList && index >= 0 && pList->currentElementCount > index)
    {
        ListNode* pointer = pList->headerNode.pLink;
        while(--index)
            pointer = pointer->pLink;
        return pointer;
    }
    return 0;
}
*/


//clear
void clearLinkedList(LinkedList* pList)
{
    if (pList && pList->headerNode.pLink)
    {
        while (pList->currentElementCount)
        {
            ListNode *prev = pList->headerNode.pLink;
            pList->headerNode.pLink = pList->headerNode.pLink->pLink;
            free(prev);
            pList->currentElementCount--;
        }
    }
}

/*
//length
int getLinkedListLength(LinkedList* pList)
{
        return pList ? pList->currentElementCount : 0;
}
*/

//delete
void deleteLinkedList(LinkedList** pList)
{
    if (pList && *pList)
    {
        while ((*pList)->currentElementCount--)
        {
            ListNode *prev = (*pList)->headerNode.pLink;
            (*pList)->headerNode.pLink = (*pList)->headerNode.pLink->pLink;
            free(prev);
        }
        free(*pList);
        *pList = 0;
    }
}

void    print_list(LinkedList* pList)
{
    if (pList)
    {
        ListNode *pointer = pList->headerNode.pLink; // . x
        for (int i = 0; i < pList->currentElementCount; i++)
        {
            printf("%d ",pointer->data.vertexID);
            pointer = pointer->pLink;
        }
        printf("\n");
    }
}

int main()
{
    LinkedList *list = createLinkedList();
    ListNode element;
    GraphVertex g;
    element.pLink = 0;
    g.weight = 0;
    g.vertexID = 1; // add
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 2;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 3;
    element.data = g;
    addLLElement(list,2,element);
    g.vertexID = 4;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 5;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 0;
    element.data = g;
    addLLElement(list,0,element);
    g.vertexID = 6;
    element.data = g;
    addLLElement(list,4,element);
    print_list(list); // print
    clearLinkedList(list); // clear
    g.vertexID = 1; // re-add
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 2;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 3;
    element.data = g;
    addLLElement(list,2,element);
    g.vertexID = 4;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 5;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 0;
    element.data = g;
    addLLElement(list,0,element);
    g.vertexID = 6;
    element.data = g;
    addLLElement(list,4,element);
    print_list(list); // print
    removeLLElement(list,0);
    print_list(list);
    removeLLElement(list,100);
    print_list(list);
    removeLLElement(list,3);
    print_list(list); // remove & print
    deleteLinkedList(&list);
    print_list(list); //delete
    system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror graphlinkedlist.c
    return (0);
}