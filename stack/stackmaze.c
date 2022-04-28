#include "stackmaze.h"
#define FX 4
#define FY 5
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

int found(int maze[FX][FY])
{
	int visited[FX][FY];
	memset(visited, TRUE, sizeof(visited));
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
		if (t.x == FX -1 && t.y == FY - 1)
			return TRUE;
		if (t.dir == 1)
		{
			m->pTopElement->tail->dir++;
			if(t.x -1 >=0 && maze[t.x - 1][t.y] && visited[t.x-1][t.y])
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
			if(t.y + 1 < FY && maze[t.x][t.y+1] && visited[t.x][t.y+1])
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
			if(t.x + 1 < FY && maze[t.x +1][t.y] && visited[t.x + 1][t.y])
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
			if(t.y -1 >=0 && maze[t.x][t.y-1] && visited[t.x][t.y-1])
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
			visited[t.x][t.y] = FALSE;
			popLS(&m);
		}
	}
	return FALSE;
}

int main()
{
	 int maze[FX][FY] = {
        {1, 1, 1, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };
	if (found(maze))
		printf("path found!\n");
	else
		printf("no path found!\n");
	return 0;
}