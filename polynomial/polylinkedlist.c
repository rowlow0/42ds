#include "polylinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

PolyLinkedList* createPolyLinkedList()
{
    PolyLinkedList *new = malloc(sizeof(PolyLinkedList));
    new->count = 0;
    new->head = 0;
    return new;
}

void replaceLLElement(PolyLinkedList *ls, int index, PolyListNode element)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    PolyListNode *tmp = ls->head;
    for(int i = 0; i< index; i++)
        tmp = tmp->next;
    tmp->data = element.data;
    tmp->pow = element.pow;
    printf("index %d replaceLLElement\n", index);
}

void addLLElement(PolyLinkedList *ls, int index, PolyListNode element)
{
    if(!ls || index > ls->count || index < 0)
        return ;
    PolyListNode *new = malloc(sizeof(PolyListNode));
    *new = element;
    if (!ls->count)
    {
        new->next = ls->head;
        ls->head = new;
    }
    else
    {
        PolyListNode *tmp = ls->head;
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

void removeLLElement(PolyLinkedList *ls, int index)
{
    if(!ls || index >= ls->count || index < 0)
        return ;
    else if(!index)
    {
        PolyListNode *tmp = ls->head;
        ls -> head = ls->head->next;
        free(tmp);
    }
    else
    {
        PolyListNode *new = ls->head;
        for(int i =0;i<index-1;i++)
            new = new->next;
        PolyListNode *tmp = new->next;
        new->next=tmp->next;
        free(tmp);
    }
    ls->count--;
    printf("index %d deleted\n", index);
}
/*
static void deleteLLElement(PolyListNode **l)
{
    if (!l)
        return ;
    while(*l)
    {
    PolyListNode *t = *l;
    *l = (*l)->next;
    free(t);
    }
    *l = 0;
}
*/
static PolyListNode* LLEClone(PolyListNode * l) {
if (l == NULL) return NULL;
PolyListNode* result = malloc(sizeof(PolyListNode));
result->data = l->data;
result->pow = l->pow;
result->next = LLEClone(l->next);
return result;
}

PolyListNode *getLLElement(PolyLinkedList *ls, int index) // for deep copy
{
    if(!ls || index >= ls->count || index < 0)
        return 0;
    PolyListNode *tmp = ls->head;
    while(index--)
        tmp = tmp -> next;
    return LLEClone(tmp);
}

void clearPolyLinkedList(PolyLinkedList *ls)
{
    if (!ls)
        return ;
    PolyListNode *tmp = ls->head;
    while(tmp)
    {
        PolyListNode *next = tmp->next;
        tmp->data = 0;
        tmp->pow = 0;
        tmp = next;
    }
    /*
    while (ls->head)
    {
        PolyListNode *tmp = ls->head;
        ls->head = ls->head->next;
        free(tmp);
    }
    */
    printf("PolyLinkedList is clearPolyLinkedListed\n");
}

int getPolyLinkedListLength(PolyLinkedList *ls)
{
    if (!ls)
        return 0;
    return ls->count;
}

void deletePolyLinkedList(PolyLinkedList** ls)
{
    if (!*ls)
        return ;
    while ((*ls)->head)
    {
        PolyListNode *tmp = (*ls)->head;
        (*ls)->head = (*ls)->head->next;
        free(tmp);
    }
    free(*ls);
    *ls = 0;
}

void displayPolyLinkedList(PolyLinkedList *ls)
{
    if (!ls)
        printf("ls is null\n");
    else if (!ls->count)
        printf("ls is empty\n");
    else
    {
        PolyListNode *tmp = ls->head;
        for(int i = 0;i< ls->count; i++,tmp = tmp->next)
        {
            printf("%dx", tmp->data);
            if (i > 1)
                printf(" ^ %d + ", tmp->pow);
        }
        printf("\n");
    }
    printf("\n");
}

PolyLinkedList *PolyLinkedListSort(PolyLinkedList *ls)
{
    for (int i = 0; i < ls->count; i++) {
    PolyListNode *prev = ls->head;
    PolyListNode *curr = ls->head->next;

    if (curr)
    {
    do {
        if (curr->pow > prev->pow){
            int temp2 = curr->pow;
            curr->pow = prev->pow;
            prev->pow = temp2;

            int temp3 = curr->data;
            curr->data = prev->data;
            prev->data = temp3;

            prev = ls->head;
            curr = ls->head->next;
        }

            prev = prev->next;
            curr = curr->next;
        } while(curr);
    }
    }
    return ls;
}
//base code https://www.geeksforgeeks.org/adding-two-polynomials-using-linked-list/
PolyLinkedList *PolyLinkedListMerge(PolyLinkedList *ls, PolyLinkedList *ls2, PolyLinkedList *ls3)
{
    PolyListNode * poly1 = ls->head;
    PolyListNode * poly2 = ls2->head;
    PolyListNode * poly = ls3->head;
    while (poly1 && poly2) {
        // If power of 1st polynomial is greater then 2nd,
        // then store 1st as it is and move its pointer
        if (poly1->pow > poly2->pow) {
            poly->pow = poly1->pow;
            poly->data = poly1->data;
            poly1 = poly1->next;
        }
 
        // If power of 2nd polynomial is greater then 1st,
        // then store 2nd as it is and move its pointer
        else if (poly1->pow < poly2->pow) {
            poly->pow = poly2->pow;
            poly->data = poly2->data;
            poly2 = poly2->next;
        }
 
        // If power of both polynomial numbers is same then
        // add their coefficients
        else {
            poly->pow = poly1->pow;
            poly->data = poly1->data + poly2->data;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
 
        // Dynamically create new node
        if(poly1 || poly2)
        {
        poly->next = malloc(sizeof(PolyListNode));
        poly = poly->next;
        }
        poly->next = NULL;
        ls3->count++;
    }
    while (poly1 || poly2) {
        if (poly1) {
            poly->pow = poly1->pow;
            poly->data = poly1->data;
            poly1 = poly1->next;
        }
        if (poly2) {
            poly->pow = poly2->pow;
            poly->data = poly2->data;
            poly2 = poly2->next;
        }
        if(poly1 || poly2)
        {
        poly->next = malloc(sizeof(PolyListNode));
        poly = poly->next;
        }
        poly->next = NULL;
        ls3->count++;
    }
    return ls3;
}

void PolyLinkedListSum(PolyLinkedList *ls, PolyLinkedList *ls2, PolyLinkedList **sum)
{
    if(!ls && !ls2)
        return ;
    *sum = malloc(sizeof(PolyLinkedList));
    (*sum)->head = malloc(sizeof(PolyLinkedList));
    PolyLinkedListMerge(PolyLinkedListSort(ls), PolyLinkedListSort(ls2), *sum);
}

int main()
{
    PolyLinkedList *ls = createPolyLinkedList();
    PolyLinkedList *ls2 = createPolyLinkedList();
    PolyListNode a;
    for(int i = 0; i < 3; i++)
    {
        a.data= i+1;
        a.pow= i+1;
        addLLElement(ls,i,a);
    }
    a.data= 7;
    a.pow= 7;
    addLLElement(ls,3,a);
    for(int i = 0; i < 3; i++)
    {
        a.data= i + 1;
        a.pow= i+1; 
        addLLElement(ls2,i,a);
    }
    a.data= -6;
    a.pow= 6;
    addLLElement(ls2,3,a);
    a.data= -5;
    a.pow= 7;
    addLLElement(ls2,3,a);
    PolyLinkedList *sum;
    PolyLinkedListSum(ls,ls2,&sum);
    displayPolyLinkedList(sum);
    deletePolyLinkedList(&sum);
    deletePolyLinkedList(&ls);
    deletePolyLinkedList(&ls2);
    system("leaks polylinkedlist");
    return 0;
}
