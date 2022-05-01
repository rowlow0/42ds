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

void	delete_save(saver **save)
{
	free((*save)->arr);
	free(*save);
}

saver	*save(MageStack *ls) // save_point
{
	saver	*r= malloc(sizeof(saver));
	r->count = ls->currentElementCount;
	r->arr= malloc(sizeof(saver) * r->count);
	StackNode *t = ls->pTopElement;
	int i = 0;
	while (i < ls->currentElementCount)
	{
		r->arr[i].x = t->x;
		r->arr[i].y = t->y;
		t = t->pLink;
		i++;
	}
	return r;
}


saver	*min_found(int maze[FX][FY], MageStack	**m)
{
	int visited[FX][FY] = { 0,};
	saver *r = save(*m);
	int	count = (*m)->currentElementCount;
	StackNode t;
	StackNode q;
	t.x=0;
	t.y=0;
	t.tail=0;
	t.pLink=0;
	t.dir=1;
	while(!isMageStackEmpty(*m))
	{
		t = *peekLS(*m);
		visited[t.x][t.y] = TRUE;
		if (t.x == FX -1 && t.y == FY - 1 && count > (*m)->currentElementCount)
		{
			delete_save(&r);
			r = save(*m);
			count = (*m)->currentElementCount;
		}
		if (t.dir == 1)
		{
			(*m)->pTopElement->tail->dir++;
			if(t.x -1 >=0 && maze[t.x - 1][t.y] && !visited[t.x-1][t.y])
			{
				q.x = t.x -1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(*m, q);
			}
		}
		else if (t.dir == 2)
		{
			(*m)->pTopElement->tail->dir++;
			if(t.y + 1 < FY && maze[t.x][t.y+1] && !visited[t.x][t.y+1])
			{
				q.x = t.x;
				q.y = t.y+1;
				q.tail = 0;
				q.pLink = 0;
				q.dir = 1;
				pushLS(*m, q);
			}
		}
		else if (t.dir == 3)
		{
			(*m)->pTopElement->tail->dir++;
			if(t.x + 1 < FY && maze[t.x +1][t.y] && !visited[t.x + 1][t.y])
			{
				q.x = t.x+1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(*m, q);
			}
		}
		else if (t.dir == 4)
		{
			(*m)->pTopElement->tail->dir++;
			if(t.y -1 >=0 && maze[t.x][t.y-1] && !visited[t.x][t.y-1])
			{
				q.x = t.x;
				q.y = t.y -1;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				pushLS(*m, q);
			}
		}
		else
		{
			popLS(m);
		}
	}
	deleteMageStack(m);
	return r;
}
/*
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
*/
int main()
{
	 int maze[FX][FY] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
	MageStack	*t = found(maze);
	if (t)
	{
		saver	*m = min_found(maze, &t);
		int b = 0;
		printf("path found!\n");
		if (m)
		{
			for(int i = 0; i < m->count;i++)
			{
			printf("%d",m->arr[i].x);
			printf("%d ",m->arr[i].y);
			}
			printf("\n");
			printf("min path found\n");
			for(int w = 0; w <FX; w++)
			{
				for(int q = 0; q< FY; q++)
				{
					if (m->arr[b].x == w && m->arr[b].y == q)
					{
						printf("1 ");
						b++;
					}
					else
					{
						printf("2 ");
					}
				}
				printf("\n");
			}
			delete_save(&m);
		}
		else
			printf("there only one path\n");
	}
	else
		printf("no path found!\n");
	return 0;
}