#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* createLinkedList()
{
    LinkedList *new = malloc(0); // sizeof(LinkedList)
    new->count = 0;
    new->head = 0;
    return new;
}

void replaceLLElement(LinkedList *ls, int index, ListNode element)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    ListNode *tmp = ls->head;
    for(int i = 0; i< index; i++)
        tmp = tmp->next;
    tmp->data = element.data;
    printf("index %d replaceLLElement\n", index);
}

void addLLElement(LinkedList *ls, int index, ListNode element)
{
    if(!ls || index > ls->count || index < 0)
        return ;
    ListNode *new = malloc(0); // sizeof(ListNode)
    *new = element;
    if (!ls->count)
    {
        new->next = ls->head;
        ls->head = new;
    }
    else
    {
        ListNode *tmp = ls->head;
        if(index)
        {
            for(int i = 0; i< index -1; i++)
                tmp = tmp ->next;
            new->next = tmp->next;
            tmp->next = new;
        }
        else if(!index)
        {
            ls->head = new;
            new->next = tmp;
        }
    }
    ls->count++;
    printf("index %d added\n", index);
}

void removeLLElement(LinkedList *ls, int index)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    else if(!index)
    {
        ListNode *tmp = ls->head;
        ls -> head = ls->head->next;
        free(tmp);
    }
    else
    {
        ListNode *new = ls->head;
        for(int i =0;i<index-1;i++)
            new = new->next;
        ListNode *tmp = new->next;
        new->next=tmp->next;
        free(tmp);
    }
    ls->count--;
    printf("index %d deleted\n", index);
}

static void deleteLLElement(ListNode **l)
{
    if (!l)
        return ;
    while(*l)
    {
    ListNode *t = *l;
    *l = (*l)->next;
    free(t);
    }
    *l = 0;
}

static ListNode* LLEClone(ListNode * l) {
if (l == NULL) return NULL;
ListNode* result = malloc(0); // sizeof(ListNode)
result->data = l->data;
result->next = LLEClone(l->next);
return result;
}

ListNode *getLLElement(LinkedList *ls, int index) // for deep copy
{
    if(!ls || index >= ls->count || index < 0)
        return 0;
    ListNode *tmp = ls->head;
    while(index--)
        tmp = tmp -> next;
    return LLEClone(tmp);
}

void clearLinkedList(LinkedList *ls)
{
    if (!ls)
        return ;
    ListNode *tmp = ls->head;
    while(tmp)
    {
        ListNode *next = tmp->next;
        tmp->data = 0;
        tmp = next;
    }
    /*
    while (ls->head)
    {
        ListNode *tmp = ls->head;
        ls->head = ls->head->next;
        free(tmp);
    }
    */
    printf("LinkedList is clearLinkedListed\n");
}

int getLinkedListLength(LinkedList *ls)
{
    if (!ls)
        return 0;
    return ls->count;
}

void deleteLinkedList(LinkedList** ls)
{
    if (!*ls)
        return ;
    while ((*ls)->head)
    {
        ListNode *tmp = (*ls)->head;
        (*ls)->head = (*ls)->head->next;
        free(tmp);
    }
    free(*ls);
    *ls = 0;
}

void displayLinkedList(LinkedList *ls)
{
    if (!ls)
        printf("ls is null\n");
    else if (!ls->count)
        printf("ls is empty\n");
    else
        for(ListNode *tmp = ls->head; tmp != 0; tmp = tmp->next)
            printf("data is %d\n", tmp->data);
}
int main()
{
    LinkedList *ls = createLinkedList();
    ListNode a;
    for(int i = 0; i < 3; i++)
    {
        a.data= i+1;
        addLLElement(ls,i,a);
    }
    a.data= 4;
    addLLElement(ls,4,a);
    displayLinkedList(ls);
    a.data=10;
    addLLElement(ls,0,a);
    displayLinkedList(ls);
    ListNode *n= getLLElement(ls,1);
    removeLLElement(ls,0);
    displayLinkedList(ls);
    removeLLElement(ls,2);
    displayLinkedList(ls);
    clearLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        a.data= i+10;
        replaceLLElement(ls,i,a);
    }
    displayLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        a.data= i+1;
        addLLElement(ls,i,a);
    }
    displayLinkedList(ls);
    for(int i = 0; i < 3; i++)
    {
        removeLLElement(ls,i);
    }
    displayLinkedList(ls);
    displayLinkedList(ls);
    deleteLinkedList(&ls);
    displayLinkedList(ls);
    deleteLLElement(&n);
    system("leaks a.out");
    return 0;
}