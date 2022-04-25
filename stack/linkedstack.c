#include "linkedstack.h"

LinkedStack* createLinkedStack()
{
    LinkedStack *new = malloc(sizeof(LinkedStack));
    new->pTopElement = 0;
    new->currentElementCount = 0;
    return new;
}

int pushLS(LinkedStack* ls, StackNode el)
{
    if(ls)
    {
        StackNode *tmp = ls->pTopElement;
        if(tmp)
        {
            tmp->tail->pLink = malloc(sizeof(StackNode));
            *(tmp->tail->pLink) = el;
            tmp->tail = tmp->tail->pLink;
        }
        else if(!tmp)
        {
            ls->pTopElement = malloc(sizeof(StackNode));
            *(ls->pTopElement) = el;
            ls->pTopElement->tail = ls->pTopElement;
        }
        ls->currentElementCount++;
        return TRUE;
    }
    else
        return FALSE;
}

StackNode* popLS(LinkedStack** pStack)
{
    if(pStack)
    {
        StackNode * t = (*pStack)->pTopElement;
        free((*pStack)->pTopElement->tail);
        (*pStack)->pTopElement->tail = 0;
        (*pStack)->currentElementCount--;
        for(int i = 1; i < (*pStack)->currentElementCount; i++)
            t = t->pLink;
        t -> pLink = 0;
        if((*pStack)->currentElementCount == 0)
            (*pStack)->pTopElement = 0;
        else
            (*pStack)->pTopElement->tail = t;
    }
    return FALSE;
}

StackNode* peekLS(LinkedStack* pStack)
{
    if(pStack && pStack->pTopElement)
        return pStack->pTopElement->tail;
    else
        return FALSE;
}

void deleteLinkedStack(LinkedStack** pStack)
{
    if(pStack)
    {
        StackNode* p = (*pStack)->pTopElement;
        StackNode* t;
        while(p)
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
int isLinkedStackFull(LinkedStack* pStack)
{
    if(pStack)
        return pStack->currentElementCount >= MAX_STACK;
    else
        return FALSE;
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
    if(pStack)
        return pStack->currentElementCount == 0;
    else
        return FALSE;
}

//checking bracket
int	checkBracketMatching(LinkedStack* pStack)
{
    int result = TRUE;
    char c, k;
    if(pStack)
    {
        LinkedStack* tStack = createLinkedStack();
        StackNode *character = pStack->pTopElement;
        while(character)
        {
            k = character->data; 
            if(strchr("([{", k))
                pushLS(tStack, *character);
            else if (strchr(")]}", k))
            {
                c = peekLS(tStack) ? peekLS(tStack)->data : -1;
                if((k == ')' && c != '(') || (k == ']' && c != '[') || (k == '}' && c != '{'))
                {
                    result = FALSE;
                    break;
                }
                popLS(&tStack);
            }
                character = character->pLink;
        }
        if(!isLinkedStackEmpty(tStack))
            result = FALSE;
        deleteLinkedStack(&tStack);
        return result;
    }
    else
        return FALSE;
}

/*reverse*/
void reverseLinkedStack(LinkedStack* s)
{
    LinkedStack* saver = malloc(sizeof(LinkedStack));
    while(s->currentElementCount)
    {
        StackNode t = *peekLS(s);
        pushLS(saver, t);
        popLS(&s);
    }
    while(saver->currentElementCount)
    {
        StackNode t = *(saver->pTopElement);
        pushLS(s, t);
        StackNode *st = saver->pTopElement;
        saver->pTopElement = saver->pTopElement->pLink;
        saver->currentElementCount--;
        free(st);

    }
    free(saver);
}

int main()
{
    LinkedStack* p = createLinkedStack();
    StackNode el;
    for(int i = 0; i< 3; i++)
    {
        el.data= i+48;
        pushLS(p,el);
    }
    reverseLinkedStack(p);
    deleteLinkedStack(&p);
    p = createLinkedStack();
    el.data = '(';
    pushLS(p, el);
    el.data = '5';
    pushLS(p, el);
    el.data = '+';
    pushLS(p, el);
    el.data = '4';
    pushLS(p, el);
    el.data = ')';
    pushLS(p, el);
    //pushLS(p, el);
    el.data = '*';
    pushLS(p, el);
    el.data = '2';
    pushLS(p, el);
    if(checkBracketMatching(p))
    {
        printf("ok!\n");
    }
    else
    {
        printf("noo..\n");
    }
    deleteLinkedStack(&p);
    system("leaks a.out");
    return 0;
}