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
        for(int i = 0; i < pStack->currentElementCount; i++)
        {
            k = character->data;
            c = peekLS(tStack) ? peekLS(tStack)->data : -1;
            if(strchr("([{", k))
            {
                if(c == '(' && strchr("[{", k) || c == '[' && strchr("{", k))
                {
                    result = FALSE;
                    break;
                }
                else
                    pushLS(tStack, *character);
            }
            else if (strchr(")]}", k))
            {
                if((k == ')' && c != '(') || (k == ']' && c != '[') || (k == '}' && c != '{'))
                {
                    result = FALSE;
                    break;
                }
                else
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
    LinkedStack* saver = createLinkedStack();
    while(s->currentElementCount)
    {
        StackNode t = *peekLS(s);
        pushLS(saver, t);
        popLS(&s);
    }
    StackNode t = *(saver->pTopElement); 
    for(int i = 0; i < saver->currentElementCount; i++)
    {
        pushLS(s, t);
        if(t.pLink)
        t = *(t.pLink);
    }
    deleteLinkedStack(&saver);
}

int main()
{
    LinkedStack* p = createLinkedStack();
    StackNode el;
    char s[] = "(5+4)*2";
    char s2[] = "( ( 4 * 2 ) / 2 ) - { ( 3 + 3 ) && ( 3 – 4 ) }";
    char s3[] = "( ( 4 * 7 ) / 4 - { ( 6 + 7 ) && ( 5 – 1 ) ) }";
    for(int i = 0; i< 1; i++)
    {
        el.data= i+48;
        pushLS(p,el);
    }
    reverseLinkedStack(p);
    deleteLinkedStack(&p);
    p = createLinkedStack();
    char *ch = s3;
    for (int i = 0; i < strlen(ch); i++)
    {
        el.data = ch[i];
        pushLS(p,el);
    }
    if(checkBracketMatching(p))
        printf("ok!\n");
    else
        printf("noo..\n");
    reverseLinkedStack(p);
    if(checkBracketMatching(p))
        printf("ok!\n");
    else
        printf("noo..\n");
    deleteLinkedStack(&p);
    system("leaks linkedstack");
    return 0;
}
