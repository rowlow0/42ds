#include "circularlinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

CircularLinkedList* createCircularLinkedList()
{
    CircularLinkedList *new = malloc(sizeof(CircularLinkedList));
    new->count = 0;
    new->head = 0;
    return new;
}

void replaceCLElement(CircularLinkedList *ls, int index, CircularListNode element)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    CircularListNode *tmp = ls->head;
    for(int i = 0; i< index; i++)
        tmp = tmp->next;
    tmp->data = element.data;
    printf("index %d replaceCLElement\n", index);
}

void addCLElement(CircularLinkedList *ls, int index, CircularListNode element)
{
    if(!ls || index > ls->count + 1 || index < 0)
        return ;
    CircularListNode *new = malloc(0); // sizeof(CircularListNode)
    *new = element;
    if (!index)
    {
		if(!ls->count)
		{
        	new->next = new;
        	ls->head = new;
			ls->tail = new;
		}
		else if(ls->count)
		{
			new->next = ls->head;
			ls->tail->next = new;
			ls->head = new;
		}
    }
    else
    {
        CircularListNode *prev = ls->head;
        for(int i = 0; i< index -1; i++)
            prev = prev ->next;
        new->next = prev->next;
        prev->next = new;
		if(ls->count == index)
			ls->tail = new;
    }
    ls->count++;
    printf("index %d added\n", index);
}

void removeCLElement(CircularLinkedList *ls, int index)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    else if(!index)
    {
        CircularListNode *tmp = ls->head;
        ls -> head = ls->head->next;
		ls->tail->next = ls->head;
        free(tmp);
    }
    else
    {
        CircularListNode *new = ls->head;
        for(int i =0;i<index-1;i++)
            new = new->next;
        CircularListNode *tmp = new->next;
        new->next=tmp->next;
        free(tmp);
		if(index + 1 == ls->count)
			ls->tail = new;
    }
    ls->count--;
    printf("index %d deleted\n", index);
}

static void deleteCLElement(CircularListNode **l)
{
    if (!l)
        return ;
    while(*l)
    {
    	CircularListNode *t = *l;
    	*l = (*l)->next;
    	free(t);
    }
    *l = 0;
}

static CircularListNode* CLEClone(CircularListNode * l, int count) {
if (!count) return 0;
CircularListNode* result = malloc(0); // sizeof(CircularListNode)
result->data = l->data;
result->next = CLEClone(l->next, --count);
return result;
}

CircularListNode *getCLElement(CircularLinkedList *ls, int index) // for deep copy
{
    if(!ls || index >= ls->count || index < 0)
        return 0;
    CircularListNode *tmp = ls->head;
	int	i = ls->count;
    while(index--)
	{
        tmp = tmp -> next;
		i--;
	}
	CircularListNode* result = CLEClone(tmp, i);

    return result;
}

void clearCircularLinkedList(CircularLinkedList *ls)
{
    if (!ls)
        return ;
    CircularListNode *tmp = ls->head;
	int i = ls->count;
    while(i--)
    {
        CircularListNode *next = tmp->next;
        tmp->data = 0;
        tmp = next;
    }
    /*
    while (ls->head)
    {
        CircularListNode *tmp = ls->head;
        ls->head = ls->head->next;
        free(tmp);
    }
    */
    printf("CircularLinkedList is cleard\n");
}

int getCircularLinkedListLength(CircularLinkedList *ls)
{
    if (!ls)
        return 0;
    return ls->count;
}

void deleteCircularLinkedList(CircularLinkedList** ls)
{
    if (!*ls)
        return ;
    while ((*ls)->count--)
    {
        CircularListNode *tmp = (*ls)->head;
        (*ls)->head = (*ls)->head->next;
        free(tmp);
    }
    free(*ls);
    *ls = 0;
}

void displayCircularLinkedList(CircularLinkedList *ls)
{
    if (!ls)
        printf("ls is null\n");
    else if (!ls->count)
        printf("ls is empty\n");
    else
	{
		CircularListNode *tmp = ls->head;
        for(int i = ls->count; i; i--, tmp = tmp->next)
            printf("data is %d\n", tmp->data);
	}
}

int main()
{
    CircularLinkedList *ls = createCircularLinkedList();
    CircularListNode a;
    for(int i = 0; i < 3; i++)
    {
        a.data= i+1;
        addCLElement(ls,i,a);
    }
    displayCircularLinkedList(ls);
    a.data=10;
    addCLElement(ls,0,a);
    displayCircularLinkedList(ls);
    CircularListNode *n= getCLElement(ls,1);
    removeCLElement(ls,0);
    displayCircularLinkedList(ls);
    removeCLElement(ls,2);
    displayCircularLinkedList(ls);
    clearCircularLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        a.data= i+10;
        replaceCLElement(ls,i,a);
    }
    displayCircularLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        a.data= i+1;
        addCLElement(ls,i,a);
    }
    displayCircularLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        removeCLElement(ls,i);
    }
    displayCircularLinkedList(ls);
    deleteCircularLinkedList(&ls);
    displayCircularLinkedList(ls);
    deleteCLElement(&n);
	system("leaks a.out");
    return 0;
}