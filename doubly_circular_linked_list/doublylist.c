#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>
DoublyList* createDoublyList()
{
	DoublyList *new = malloc(sizeof(DoublyList));
	new->count = 0;
	new->head = 0;
	printf("create complete\n");	
	return new;
}

void deleteDoublyList(DoublyList** ls)
{
	if(ls)
	{
    	while ((*ls)->head)
    	{
    	    DoublyListNode *tmp = (*ls)->head;
    	    (*ls)->head = (*ls)->head->next;
    	    free(tmp);
    	}
    	free(*ls);
    	*ls = 0;
		printf("== delete complete ==\n");
	}
	else
		printf("delete not complete\n");
	return ;
}

int addDLElement(DoublyList* ls, int index, DoublyListNode element)
{
	if(ls && index >= 0 && index <= ls->count)
	{
		DoublyListNode *new = malloc(sizeof(DoublyListNode));
		if(!new)
			return (FALSE);
		*new = element;
		if (!index)
		{
			new->next = ls->head;
			new->prev = 0;
			if(ls->count)
				ls->head->prev = new;
			ls->head = new;
		}
		else if (ls->count)
		{
			DoublyListNode *prev = ls->head;
			for(int i = 0; i< index -1; i++)
				prev = prev->next;
			new->next = prev->next;
			new->prev = prev;
			prev->next = new;
			if(new->next)
				new->next->prev = new;
		}
		else
		{
			printf("add not complete\n");
			return (FALSE);
		}
		ls->count++;
		printf("add complete\n");
		return (TRUE);
	}
	else
		printf("add not complete\n");
	return FALSE;
}

int removeDLElement(DoublyList* ls, int index)
{
	if(ls && index >= 0 && index < ls->count)
	{
		if (!index)
		{
			DoublyListNode *tmp = ls->head;
			ls->head = ls->head->next;
			ls->head->prev = 0;
			free(tmp);
		}
		else if (index)
		{
			DoublyListNode *prev = ls->head;
			for(int i = 0; i< index -1; i++)
				prev = prev->next;
			DoublyListNode *tmp = prev->next;
			prev->next = prev->next->next;
			if (prev->next)
					prev->next->prev = prev;
			free(tmp);
		}
		else
		{
			printf("remove not complete\n");
			return (FALSE);
		}
		ls->count--;
		printf("remove complete\n");
		return (TRUE);
	}
	else
		printf("can't remove\n");
	return FALSE;
}

void clearDoublyList(DoublyList* ls)
{
	if (ls)
	{
		DoublyListNode *t = ls->head;
		while(t)
		{
			DoublyListNode *n = t->next;
			t->data = 0;
			t = n;
		}
		printf("clear complete\n");
	}
	else
		printf("can't clear\n");
	return ;
}

int getDoublyListLength(DoublyList* ls)
{
	if (ls)
	{
		printf("get length [%d]\n", ls->count);
		return ls->count;
	}
	else
		printf("can't find doubly list length\n");
	return (FALSE);
}

DoublyListNode* getDLElement(DoublyList* ls, int index) //ub shalow
{
	if (ls)
	{
		DoublyListNode *t = ls->head;
		while(index--)
			t = t->next;
		printf("get doubly list\n");
		return (t);
	}
	else
		printf("can't get doubly list\n");
	return FALSE;
}

void displayDoublyList(DoublyList* ls)
{
	if (ls)
	{
		DoublyListNode *t=ls->head;
		for(int i = 0; t; i++)
		{
			DoublyListNode *n = t->next;
			printf("display [index %d] = %d\n",i, t->data);
			t = n;
		}
	}
	else
		printf("can't display doubly list\n");
	return ;
}

int main()
{
	DoublyList* ls= createDoublyList();
	DoublyListNode n;
	n.data = 0;
	for(int i = 0; i < 3; i++)
	{
		n.data = i + 1;
		addDLElement(ls,i, n);
	}
	n.data = 10;
	addDLElement(ls,0, n);
	n.data = 15;
	addDLElement(ls,2, n);
	n.data = 20;
	addDLElement(ls,6, n);
	addDLElement(ls,5, n);
	displayDoublyList(ls);
	removeDLElement(ls,0);
	displayDoublyList(ls);
	removeDLElement(ls,1);
	displayDoublyList(ls);
	removeDLElement(ls,3);
	displayDoublyList(ls);
	printf("%d\n",getDoublyListLength(ls));
	//clearDoublyList(ls);
	//displayDoublyList(ls);
	//for()
	//n.data = i + 1;
	//setDLElement(n, 0);
	//displayDoublyList(ls);
	deleteDoublyList(&ls);
	displayDoublyList(ls);
	system("leaks doublylist");
	return 0;
}