#include "graphlinkedlist.h"
/*
to do list
graph type & undirected edge
*/

//create
LinkedList* createLinkedList()
{
    LinkedList *new = malloc(sizeof(LinkedList));
    new->currentElementCount = 0;
    return new;
}

//add; pList->currentElementCount overflow is not checked
int addLLElement(LinkedList* pList, int index, ListNode element)
{
    if(pList && index >= 0)
    {
        if(index == 0 || !pList->currentElementCount)
        {
            if(pList->currentElementCount)
            {
                ListNode *prev = malloc(sizeof(ListNode));
                prev->head = NULL;
                prev->data = element.data;
                prev->pLink = pList->headerNode.pLink;
                pList->headerNode.pLink = prev;
            }
            else
            {
                pList->headerNode.pLink = malloc(sizeof(ListNode));
                pList->headerNode.pLink->data = element.data;
                pList->headerNode.pLink->pLink = NULL;
                pList->headerNode.pLink->head = NULL;
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
                prev->pLink->head = NULL;
                prev->pLink->pLink = NULL;
            }
            else
            {
                while(--index)
                    prev = prev->pLink;
                ListNode *new = malloc(sizeof(ListNode));
                new->data = element.data;
                new->head = 0;
                new->pLink = prev->pLink;
                prev ->pLink = new;
            }
        }
        pList->currentElementCount++;
        return 1;
    }
    return 0;
}

//remove //edge ++
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

static int checkVertexValid(LinkedList *pList, int vertex)
{
	ListNode *curr = pList->headerNode.pLink;
	while(curr)
	{
		if(curr->data.vertexID == vertex)
			return (1);
		curr = curr->pLink;
	}
	return (0);
}

void addLLEEdge(LinkedList* pList, int from, int to, int weight)
{
	if(pList && from != to && checkVertexValid(pList, from) && checkVertexValid(pList, to))
	{
        ListNode *prev = pList->headerNode.pLink;
        while(prev->data.vertexID != from)
            prev = prev->pLink;
        while(prev->head)
        {
            prev = prev->head;
            if (prev->data.vertexID == to)
                return ;
        }
        prev->head = malloc(sizeof(ListNode));
        prev->head->data.vertexID = to;
        prev->head->data.weight = weight;
        prev->head->head = NULL;
	}
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
            ListNode *head = prev->head;
            while(head)
            {
                ListNode *prev2 = head;
                head = head->head;
                free(prev2);
            }
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
            ListNode *head = prev->head;
            while(head)
            {
                ListNode *prev2 = head;
                head = head->head;
                free(prev2);
            }
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
        ListNode *pointer = pList->headerNode.pLink;
        for (int i = 0; i < pList->currentElementCount; i++)
        {
            printf("%d",pointer->data.vertexID);
            ListNode *head = pointer->head;
            while(head)
            {
                printf("--%d[%d]", head->data.vertexID,head->data.weight);
                head = head->head;
            }
            pointer = pointer->pLink;
            printf("\n");
        }
        printf("\n");
    }
}

void    print_node(LinkedList* pList)
{
    if (pList)
    {
        ListNode *pointer = pList->headerNode.pLink;
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
    g.vertexID = 1; // add
	g.weight = 0;
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
    print_node(list); // print
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
    print_node(list); // print
    removeLLElement(list,0);
    print_node(list);
    removeLLElement(list,100);
    print_node(list);
    removeLLElement(list,3);
    print_node(list); // remove & print
    deleteLinkedList(&list);
    print_node(list); //delete
    printf("----------\n");
    list = createLinkedList();
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
    addLLElement(list,100,element);
    g.vertexID = 0;
    element.data = g;
    addLLElement(list,0,element);
    g.vertexID = 6;
    element.data = g;
    addLLElement(list,100,element);
    addLLEEdge(list,0,1,1);
    addLLEEdge(list,0,1,3);
    addLLEEdge(list,0,2,2);
    addLLEEdge(list,1,2,3);
    addLLEEdge(list,1,3,4);
    addLLEEdge(list,2,4,5);
    addLLEEdge(list,3,5,6);
    addLLEEdge(list,4,6,7);
    addLLEEdge(list,5,1,8);
    addLLEEdge(list,6,2,9);
    addLLEEdge(list,6,3,10);
    addLLEEdge(list,7,4,11);
    addLLEEdge(list,7,5,12);
    print_list(list);
    deleteLinkedList(&list);
    //system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror graphlinkedlist.c
    return (0);
}