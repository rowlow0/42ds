#include "graphlinkedlist.h"
/*
to do list
graph type & undirected edge
dfs -> stack
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
    if (pList && index >= 0 && pList->currentElementCount)
    {
        index = pList->currentElementCount <= index ? pList->currentElementCount -1 : index;
        ListNode *tmp;
        if(index == 0)
        {
            tmp = pList->headerNode.pLink;
            ListNode *pointer = pList->headerNode.pLink;
            while(pointer)
            {
                deleteLLEEdge(pList, pointer->data.vertexID, tmp->data.vertexID);
                deleteLLEEdge(pList, tmp->data.vertexID, pointer->data.vertexID);
                pointer = pointer->pLink;
            }
            pList->headerNode.pLink = pList->headerNode.pLink->pLink;
        }
        else
        {
            ListNode *prev = pList->headerNode.pLink;
            while(--index)
                prev = prev->pLink;
            tmp = prev->pLink;
            ListNode *pointer = pList->headerNode.pLink;
            while(pointer)
            {
                deleteLLEEdge(pList, pointer->data.vertexID, tmp->data.vertexID);
                deleteLLEEdge(pList, tmp->data.vertexID, pointer->data.vertexID);
                pointer = pointer->pLink;
            }
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

void deleteLLEEdge(LinkedList *pList, int from, int to)
{
    if(pList && from != to && checkVertexValid(pList, from) && checkVertexValid(pList, to))
    {
        ListNode *prev = pList->headerNode.pLink;
        while(prev->data.vertexID != from)
            prev = prev->pLink;
        if(!prev->head)
                return ;
        while(prev->head->data.vertexID != to)
        {
            prev = prev->head;
            if(!prev->head)
                return ;
        }
        ListNode *get = prev->head;
        prev->head = prev ->head->head;
        free(get);
    }
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

typedef struct Queue
{
    int         i;
	ListNode *front;
    ListNode *rear;
} queue;

queue *create(ListNode * node)
{
    queue *q = malloc(sizeof(queue));
    q->rear = node;
    q->front = node;
    q->i = 1;
    return q;
}

void enqueue(queue *q, ListNode *node)
{
    q->rear->que = node;
    q->rear = node;
    q->rear->que = NULL;
    q->i++;
}

void dequeue(queue *q)
{
    q->front = q->front->que;
    q->i--;
}

int empty(queue *q)
{
    return q->i == 0;
}

void bfs(LinkedList* pList,int vertex, int *visited)
{
    visited[vertex] = 1;
    ListNode *pointer = pList->headerNode.pLink;
    while(vertex != pointer->data.vertexID)
        pointer = pointer->pLink;
    queue *q = create(pointer);
    while(!empty(q))
    {
        //push
        ListNode *pointer2 = q->front->head;
        while(pointer2)
        {
            if(!visited[pointer2->data.vertexID])
            {
                visited[pointer2->data.vertexID] = 1;
                ListNode *pointer3 = pList->headerNode.pLink;
                while(pointer3->data.vertexID != pointer2->data.vertexID)
                    pointer3 = pointer3->pLink;
                enqueue(q, pointer3);
            }
            pointer2 = pointer2->head;
        }
        printf("%d ", q->front->data.vertexID);
        dequeue(q);
    }
    printf("\n");
    free(q);
}

void dfs(LinkedList* pList,int vertex, int *visited)
{
    visited[vertex] = 1;
    printf("%d ",vertex);
    ListNode *i = pList->headerNode.pLink;
    while (i->data.vertexID != vertex)
        i = i->pLink;
    for(i = i->head; i;i = i->head)
        if(!visited[i->data.vertexID])
            dfs(pList, i->data.vertexID, visited);
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
    addLLEEdge(list,0,0,99);
    addLLEEdge(list,0,6,99);
    addLLEEdge(list,0,1,1);
    addLLEEdge(list,0,1,6);
    addLLEEdge(list,0,2,99);
    addLLEEdge(list,1,2,2);
    addLLEEdge(list,1,2,3);
    addLLEEdge(list,1,3,4);
    addLLEEdge(list,1,4,99);
    addLLEEdge(list,2,4,5);
    addLLEEdge(list,3,5,6);
    addLLEEdge(list,4,6,7);
    addLLEEdge(list,5,1,8);
    addLLEEdge(list,6,2,9);
    addLLEEdge(list,6,3,10);
    addLLEEdge(list,7,4,11);
    addLLEEdge(list,7,5,12);
    print_list(list);

    int *visited =calloc(sizeof(int),sizeof(int) *list->currentElementCount);
    printf("dfs\n");
    //int tt = 0;
    //if tt && list && visited 
    dfs(list, 0, visited);
    //else
    // printf("null\n");
    free(visited);
    printf("\n\n");
    printf("bfs\n"); //queue
    visited =calloc(sizeof(int),sizeof(int) *list->currentElementCount);
    //if tt && list && visited 
    bfs(list, 0, visited);
    //else
    // printf("null\n");
    free(visited);
    
    printf("=================\n");
    /*
    deleteLLEEdge(list, 0, 6);
    deleteLLEEdge(list, 0, 2);
    deleteLLEEdge(list, 1, 3);
    print_list(list);
    addLLEEdge(list,0,6,99);
    addLLEEdge(list,0,2,99);
    print_list(list);
    deleteLLEEdge(list, 6, 0);
    deleteLLEEdge(list, 2, 0);
    deleteLLEEdge(list,2, 4);
    removeLLElement(list, 7);
    print_list(list);
    addLLEEdge(list, 3, 2, 15);
    addLLEEdge(list, 3, 4, 16);
    addLLEEdge(list, 3, 5, 17);
    addLLEEdge(list, 3, 6, 18);
    addLLEEdge(list, 3, 6, 18);
    print_list(list);
    removeLLElement(list, 4);
    removeLLElement(list, 5);
    print_list(list);
    */
    deleteLinkedList(&list);
    //system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror graphlinkedlist.c
    return (0);
}