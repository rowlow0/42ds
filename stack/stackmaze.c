#include "stackmaze.h"
#define FX 10
#define FY 10
MageStack* createMageStack()
{
    MageStack *new = malloc(sizeof(MageStack));
    new->pTopElement = 0;
    new->currentElementCount = 0;
    return new;
}

int pushLS(MageStack* ls, StackNode el)
{
    if(ls)
    {
        StackNode *tmp = ls->pTopElement;
        if(tmp)
        {
            tmp->tail->pLink = malloc(sizeof(StackNode));
            *(tmp->tail->pLink) = el;
            tmp->tail = tmp->tail->pLink;
            ls->pTopElement->tail->pLink = 0;
        }
        else if(!tmp)
        {
            ls->pTopElement = malloc(sizeof(StackNode));
            *(ls->pTopElement) = el;
            ls->pTopElement->tail = ls->pTopElement;
            ls->pTopElement->tail->pLink = 0;
        }
        ls->currentElementCount++;
        return TRUE;
    }
    else
        return FALSE;
}

StackNode* popLS(MageStack** pStack)
{
    if(pStack)
    {
        if((*pStack)->currentElementCount == 1)
        {
            free((*pStack)->pTopElement);
            (*pStack)->pTopElement = 0;
            (*pStack)->currentElementCount--;
        }
        else
        {
            StackNode * t = (*pStack)->pTopElement;
            free((*pStack)->pTopElement->tail);
            (*pStack)->currentElementCount--;
            for(int i = 1; i < (*pStack)->currentElementCount; i++)
                t = t->pLink;
            t -> pLink = 0;
            (*pStack)->pTopElement->tail = t;
        }
    }
    return FALSE;
}

StackNode* peekLS(MageStack* pStack)
{
    if(pStack && pStack->pTopElement)
        return pStack->pTopElement->tail;
    else
        return FALSE;
}

void deleteMageStack(MageStack** pStack)
{
    if(pStack)
    {
        StackNode* p = (*pStack)->pTopElement;
        StackNode* t;
        while((*pStack)->currentElementCount--)
        {
            t = p;
            p = p->pLink;
            free(t);
        }
        free(*pStack);
        *pStack = 0;
    }
}

//ulimit -Hs
int isMageStackFull(MageStack* pStack)
{
    if(pStack)
        return pStack->currentElementCount >= MAX_STACK;
    else
        return FALSE;
}

int isMageStackEmpty(MageStack* pStack)
{
    if(pStack)
        return pStack->currentElementCount == 0;
    else
        return FALSE;
}

MageStack	*found(int maze[FX][FY])
{
	int visited[FX][FY] = { 0,};
	MageStack *m = createMageStack();
	StackNode t;
	StackNode q;
	t.x=0;
	t.y=0;
	t.tail=0;
	t.pLink=0;
	t.dir=1;
	pushLS(m, t);
	while(!isMageStackEmpty(m))
	{
		t = *peekLS(m);
		visited[t.x][t.y] = TRUE;
		if (t.x == FX -1 && t.y == FY - 1)
		{
			return m;
		}
		if (t.dir == 1)
		{
			m->pTopElement->tail->dir++;
			if(t.x -1 >=0 && maze[t.x - 1][t.y] && !visited[t.x-1][t.y])
			{
				q.x = t.x -1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 2)
		{
			m->pTopElement->tail->dir++;
			if(t.y + 1 < FY && maze[t.x][t.y+1] && !visited[t.x][t.y+1])
			{
				q.x = t.x;
				q.y = t.y+1;
				q.tail = 0;
				q.pLink = 0;
				q.dir = 1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 3)
		{
			m->pTopElement->tail->dir++;
			if(t.x + 1 < FY && maze[t.x +1][t.y] && !visited[t.x + 1][t.y])
			{
				q.x = t.x+1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 4)
		{
			m->pTopElement->tail->dir++;
			if(t.y -1 >=0 && maze[t.x][t.y-1] && !visited[t.x][t.y-1])
			{
				q.x = t.x;
				q.y = t.y -1;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else
		{
			popLS(&m);
		}
	}
	return FALSE;
}

MageStack *getLLElement(MageStack *ls) // for deep copy
{
    if(!ls)
        return 0;
    MageStack *tmp = createMageStack();
	tmp->pTopElement = malloc(sizeof(StackNode));
	tmp->pTopElement = ls->pTopElement;
	StackNode *tmp2 = tmp->pTopElement->pLink;
	StackNode *ls2= ls->pTopElement->pLink;
	int i = 0;
	tmp->currentElementCount = ls->currentElementCount;
	while(++i < ls->currentElementCount)
	{
		tmp2 = malloc(sizeof(StackNode));
		tmp2->dir = ls2->dir;
		tmp2->x = ls2->x;
		tmp2->y = ls2->y;
		tmp2->tail = ls2->tail;
		tmp2 = tmp2->pLink;
		ls2 = ls2->pLink;
	}
	tmp2 = 0;
    return tmp;
}


MageStack	*min_found(int maze[FX][FY], MageStack	*m)
{
	int visited[FX][FY] = { 0,};
	MageStack *r = getLLElement(m);
	int	count = m->currentElementCount;
	StackNode t;
	StackNode q;
	t.x=0;
	t.y=0;
	t.tail=0;
	t.pLink=0;
	t.dir=1;
	while(!isMageStackEmpty(m))
	{
		t = *peekLS(m);
		visited[t.x][t.y] = TRUE;
		if (t.x == FX -1 && t.y == FY - 1 && count > m->currentElementCount)
		{
			deleteMageStack(&r);
			r = getLLElement(m);
			count = m->currentElementCount;
		}
		if (t.dir == 1)
		{
			m->pTopElement->tail->dir++;
			if(t.x -1 >=0 && maze[t.x - 1][t.y] && !visited[t.x-1][t.y])
			{
				q.x = t.x -1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 2)
		{
			m->pTopElement->tail->dir++;
			if(t.y + 1 < FY && maze[t.x][t.y+1] && !visited[t.x][t.y+1])
			{
				q.x = t.x;
				q.y = t.y+1;
				q.tail = 0;
				q.pLink = 0;
				q.dir = 1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 3)
		{
			m->pTopElement->tail->dir++;
			if(t.x + 1 < FY && maze[t.x +1][t.y] && !visited[t.x + 1][t.y])
			{
				q.x = t.x+1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else if (t.dir == 4)
		{
			m->pTopElement->tail->dir++;
			if(t.y -1 >=0 && maze[t.x][t.y-1] && !visited[t.x][t.y-1])
			{
				q.x = t.x;
				q.y = t.y -1;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(m, q);
			}
		}
		else
		{
			popLS(&m);
		}
	}
	return r;
}

int main()
{
	 int maze[FX][FY] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
	MageStack	*t = found(maze);
	if (t)
	{
		MageStack	*m;
		printf("path found!\n");
		m = min_found(maze, t);
		if (m)
		{
			printf("min path found\n");
			for(int x = 0; x <FX; x++)
			{
				StackNode *t = m->pTopElement;
				for(int y = 0; y< FY; y++)
				{
					if (t->x == x && t->y == y)
					{
						printf("1 ");
						t = t->pLink;
					}
					else
						printf("2 ");
				}
				printf("\n");
			}
		}
	}
	else
		printf("no path found!\n");
	return 0;
}