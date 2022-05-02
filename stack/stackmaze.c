#include "stackmaze.h"
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
		m->visited_2[t.x][t.y] = FALSE;
		if (t.x == FX -1 && t.y == FY - 1)
		{
			return m;
		}
		else if (t.dir == 1 && t.x -1 >=0 && maze[t.x - 1][t.y] && !m->visited[t.x][t.y][t.dir - 1] && !m->visited_2[t.x-1][t.y])
		{
				q.x = t.x -1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				m->visited[t.x][t.y][t.dir - 1] = TRUE;
				m->visited[t.x - 1][t.y][2] = TRUE;
				m->visited_2[t.x][t.y] = TRUE;
				pushLS(m, q);
		}
		else if (t.dir == 2 && t.y + 1 < FY && maze[t.x][t.y+1] && !m->visited[t.x][t.y][t.dir - 1] && !m->visited_2[t.x][t.y+1])
		{
				q.x = t.x;
				q.y = t.y+1;
				q.tail = 0;
				q.pLink = 0;
				q.dir = 1;
				m->visited[t.x][t.y][t.dir - 1] = TRUE;
				m->visited[t.x][t.y+1][3] = TRUE;
				m->visited_2[t.x][t.y] = TRUE;
				pushLS(m, q);
		}
		else if (t.dir == 3 && t.x + 1 < FX && maze[t.x +1][t.y] && !m->visited[t.x][t.y][t.dir - 1] && !m->visited_2[t.x+1][t.y])
		{
				q.x = t.x+1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				m->visited[t.x][t.y][t.dir - 1] = TRUE;
				m->visited[t.x+1][t.y][0] = TRUE;
				m->visited_2[t.x][t.y] = TRUE;
				pushLS(m, q);
		}
		else if (t.dir == 4 && t.y -1 >=0 && maze[t.x][t.y-1] && !m->visited[t.x][t.y][t.dir - 1] && !m->visited_2[t.x][t.y-1])
		{
				q.x = t.x;
				q.y = t.y -1;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				m->visited[t.x][t.y][t.dir - 1] = TRUE;
				m->visited[t.x][t.y-1][1] = TRUE;
				m->visited_2[t.x][t.y] = TRUE;
				pushLS(m, q);
		}
		else if (t.dir >= 5)
		{
			m->visited_2[t.x][t.y] = FALSE;
			m->visited[t.x][t.y][0] = FALSE;
			m->visited[t.x][t.y][1] = FALSE;
			m->visited[t.x][t.y][2] = FALSE;
			m->visited[t.x][t.y][3] = FALSE;
			popLS(&m);
		}
		else
		{
			m->pTopElement->tail->dir++;
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
		(*m)->visited_2[t.x][t.y] = FALSE;
		if (count < (*m)->currentElementCount)
		{
			(*m)->visited_2[t.x][t.y] = FALSE;
			(*m)->visited[t.x][t.y][0] = FALSE;
			(*m)->visited[t.x][t.y][1] = FALSE;
			(*m)->visited[t.x][t.y][2] = FALSE;
			(*m)->visited[t.x][t.y][3] = FALSE;
			popLS(m);
		}
		else if (t.x == FX -1 && t.y == FY - 1 && count > (*m)->currentElementCount)
		{
			delete_save(&r);
			r = save(*m);
			count = (*m)->currentElementCount;
		}
		else if (t.dir == 1 && t.x -1 >=0 && maze[t.x - 1][t.y] && !(*m)->visited[t.x][t.y][t.dir-1] && !(*m)->visited_2[t.x-1][t.y])
		{
				q.x = t.x -1;
				q.y = t.y;
				q.tail=0;
				q.pLink=0;
				q.dir=1;
				(*m)->visited[t.x][t.y][t.dir - 1] = TRUE;
				(*m)->visited[t.x - 1][t.y][2] = TRUE;
				(*m)->visited_2[t.x][t.y] = TRUE;
				pushLS(*m, q);
		}
		else if (t.dir == 2 && t.y + 1 < FY && maze[t.x][t.y+1] && !(*m)->visited[t.x][t.y][t.dir-1] && !(*m)->visited_2[t.x][t.y+1])
		{
			q.x = t.x;
			q.y = t.y+1;
			q.tail = 0;
			q.pLink = 0;
			q.dir = 1;
			(*m)->visited[t.x][t.y][t.dir - 1] = TRUE;
			(*m)->visited[t.x][t.y+1][3] = TRUE;
			(*m)->visited_2[t.x][t.y] = TRUE;
			pushLS(*m, q);
		}
		else if (t.dir == 3 && t.x + 1 < FX && maze[t.x +1][t.y] && !(*m)->visited[t.x][t.y][t.dir-1] && !(*m)->visited_2[t.x+1][t.y])
		{
			q.x = t.x+1;
			q.y = t.y;
			q.tail=0;
			q.pLink=0;
			q.dir=1;
			(*m)->visited[t.x][t.y][t.dir - 1] = TRUE;
			(*m)->visited[t.x+1][t.y][0] = TRUE;
			(*m)->visited_2[t.x][t.y] = TRUE;
			pushLS(*m, q);
		}
		else if (t.dir == 4 && t.y -1 >=0 && maze[t.x][t.y-1] && !(*m)->visited[t.x][t.y][t.dir-1] && !(*m)->visited_2[t.x][t.y-1])
		{
			q.x = t.x;
			q.y = t.y -1;
			q.tail=0;
			q.pLink=0;
			q.dir=1;
			(*m)->visited[t.x][t.y][t.dir - 1] = TRUE;
			(*m)->visited[t.x][t.y-1][1] = TRUE;
			(*m)->visited_2[t.x][t.y] = TRUE;
			pushLS(*m, q);
		}
		else if (t.dir >= 5)
		{
			(*m)->visited_2[t.x][t.y] = FALSE;
			(*m)->visited[t.x][t.y][0] = FALSE;
			(*m)->visited[t.x][t.y][1] = FALSE;
			(*m)->visited[t.x][t.y][2] = FALSE;
			(*m)->visited[t.x][t.y][3] = FALSE;
			popLS(m);
		}
		else
		{
			(*m)->pTopElement->tail->dir++;
		}
		//printf("%d %d %d\n",t.x,t.y,t.dir);
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
/*
	 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
*/
/*
		{1, 1, 1, 1, 1},
        {1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1}
*/
int main()
{
	 int maze[FX][FY] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
		{1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
	MageStack	*t = found(maze);
	if (t)
	{
		int	canvas2[FX][FY] = {0 ,};
		StackNode *tt = t->pTopElement;
		printf("there are path ..\n");
		for (int i = 0; i < t->currentElementCount; i++)
			{
				canvas2[tt->x][tt->y] = 1;
				tt = tt->pLink;
			}
		for(int i = 0; i < FX; i++)
		{
			for(int j = 0; j < FY; j++)
			{
				printf("%d ",canvas2[i][j]);
			}
			printf("\n");
		}

		saver	*m = min_found(maze, &t);
		int	canvas[FX][FY] = {0 ,};
		if (m)
		{
			printf("min path ..\n");
			for (int i = 0; i < m->count; i++)
			{
				canvas[m->arr[i].x][m->arr[i].y] = 1;
			}
			for(int i = 0; i < FX; i++)
			{
				for(int j = 0; j < FY; j++)
				{
					printf("%d ",canvas[i][j]);
				}
				printf("\n");
			}
			delete_save(&m);
		}
	}
	else
		printf("path not found!\n");
	return 0;
}