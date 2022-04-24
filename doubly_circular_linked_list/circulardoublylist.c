#include "circulardoublylist.h"
#include <stdio.h>
#include <stdlib.h>

CircularDoublyList* createCircularDoublyList()
{
	CircularDoublyList *new = malloc(0); // sizeof(CircularDoublyList)
	new->count = 0;
	new->head = 0;
	printf("create complete\n");
	return new;
}

void deleteCircularDoublyList(CircularDoublyList** ls)
{
	if(ls)
	{
    	while ((*ls)->count--)
    	{
    	    CircularDoublyListNode *tmp = (*ls)->head;
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

int addDLElement(CircularDoublyList* ls, int index, CircularDoublyListNode element)
{
	if(ls && index >= 0 && index <= ls->count)
	{
		CircularDoublyListNode *new = malloc(17); // sizeof(CircularDoublyListNode)
		if(!new)
			return (FALSE);
		*new = element;
		if (!index)
		{
			if(ls->count)
			{
				new->prev = ls->head->prev;
				new->next = ls->head;
				ls->head = new;
			}
			else if (!ls->count)
			{
				new->next = new;
				new->prev = new;
				ls->head = new;
			}
		}
		else if (ls->count)
		{
			CircularDoublyListNode *prev = ls->head;
			for(int i = 0; i< index -1; i++)
				prev = prev->next;
			new->next = prev->next;
			new->prev = prev;
			prev->next = new;
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

int removeDLElement(CircularDoublyList* ls, int index)
{
	if(ls && index >= 0 && index < ls->count)
	{
		if (!index)
		{
			CircularDoublyListNode *tmp = ls->head;
			ls->head = ls->head->next;
			ls->head->prev = ls->head->prev;
			free(tmp);
		}
		else if (index)
		{
			CircularDoublyListNode *prev = ls->head;
			for(int i = 0; i< index -1; i++)
				prev = prev->next;
			CircularDoublyListNode *tmp = prev->next;
			prev->next = prev->next->next;
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

void clearCircularDoublyList(CircularDoublyList* ls)
{
	if (ls)
	{
		CircularDoublyListNode *t = ls->head;
		for(int i = ls->count; i; i--)
		{
			CircularDoublyListNode *n = t->next;
			t->data = 0;
			t = n;
		}
		printf("clear complete\n");
	}
	else
		printf("can't clear\n");
	return ;
}

int getCircularDoublyListLength(CircularDoublyList* ls)
{
	if (ls)
	{
		printf("get length [%d]\n", ls->count);
		return ls->count;
	}
	else
		printf("can't find CircularDoubly list length\n");
	return (FALSE);
}

CircularDoublyListNode* getDLElement(CircularDoublyList* ls, int index) //ub shalow
{
	if (ls)
	{
		CircularDoublyListNode *t = ls->head;
		while(index--)
			t = t->next;
		printf("get CircularDoubly list\n");
		return (t);
	}
	else
		printf("can't get CircularDoubly list\n");
	return FALSE;
}

void displayCircularDoublyList(CircularDoublyList* ls)
{
	if (ls)
	{
		CircularDoublyListNode *t=ls->head;
		for(int i = 0; i < ls->count; i++)
		{
			CircularDoublyListNode *n = t->next;
			printf("display [index %d] = %d\n",i, t->data);
			t = n;
		}
	}
	else
		printf("can't display CircularDoubly list\n");
	return ;
}

int main()
{
	CircularDoublyList* ls= createCircularDoublyList();
	CircularDoublyListNode n;
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
	displayCircularDoublyList(ls);
	removeDLElement(ls,0);
	displayCircularDoublyList(ls);
	removeDLElement(ls,1);
	displayCircularDoublyList(ls);
	removeDLElement(ls,3);
	displayCircularDoublyList(ls);
	printf("%d\n",getCircularDoublyListLength(ls));
	CircularDoublyListNode* tmp =getDLElement(ls,0);
	//clearCircularDoublyList(ls);
	//displayCircularDoublyList(ls);
	//for()
	//n.data = i + 1;
	//setDLElement(n);
	//displayCircularDoublyList(ls);
	deleteCircularDoublyList(&ls);
	displayCircularDoublyList(ls);
	system("leaks a.out");
	return 0;
}