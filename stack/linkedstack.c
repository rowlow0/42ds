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
    if(ls && el.data != ' ')
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

int is_alphabet(int c)
{
    return (c <= 'Z' && c>= 'A');
}

int is_arithmetic(int c)
{
    char    cc = c;
    return (cc == '-' || cc == '/' || cc == '*' || cc == '+');
}

int is_infix(LinkedStack *p)
{
    StackNode *t = p->pTopElement;
    int i = 0;
    int f = 0;
    while (i < p->currentElementCount)
    {
        if (is_alphabet(t->data))
            f++;
        if (is_arithmetic(t->data))
            f--;
        if (f > 1 || f < 0)
            return 0;
        t = t->pLink;
        i++;
    }
    return 1;
}

void display(LinkedStack *p)
{
    int  i= 0;
    StackNode *t = p->pTopElement;
    while (i < p->currentElementCount)
    {
        printf("%c",t->data);
        t = t->pLink;
        i++;
    }
}

void    infix_to_postfix(LinkedStack *p)
{
    LinkedStack *main = createLinkedStack();
    LinkedStack *arith = createLinkedStack();
    int i = 0;
    StackNode *t= p->pTopElement;
    while (i <p->currentElementCount)
    {
        if (is_alphabet(t->data))
            pushLS(main, *t);
        else if (is_arithmetic(t->data))
            pushLS(arith, *t);
        else if (t->data == '(')
        {
            i++;
            t = t->pLink;
            int count = arith->currentElementCount;
            while (t->data != ')')
            {
                if(is_alphabet(t->data))
                    pushLS(main, *t);
                else if(is_arithmetic(t->data))
                    pushLS(arith, *t);
                i++;
                t = t->pLink;
            }
            while(arith->currentElementCount > count)
            {
                pushLS(main, *peekLS(arith));
                popLS(&arith);
            }
        }
        t = t->pLink;
        i++;
    }
    display(main);
    display(arith);
    printf("\n");
    deleteLinkedStack(&main);
    deleteLinkedStack(&arith);
}

void    doing_job(char *s)
{
    StackNode el;
    LinkedStack* p = createLinkedStack();
    for (int i = 0; i < strlen(s); i++)
    {
        el.data = *(s + i);
        pushLS(p,el);
    }
    if(checkBracketMatching(p))
    {
        printf("checkBracketMatching : ok\n");
        if(is_infix(p))
        {
            printf("is_infix\n");
            infix_to_postfix(p);
        }
    }
    else
        printf("checkBracketMatching : noo..\n");
    reverseLinkedStack(p);
    if(checkBracketMatching(p))
        printf("checkBracketMatching : ok\n");
    else
        printf("checkBracketMatching : noo..\n");
    deleteLinkedStack(&p);

}

int main()
{
    LinkedStack* p = createLinkedStack();
    StackNode el;
    char *s[] = {"A*B","A*B+C","A +B * C", "A * (B + C )", 0}; //"(5+4)*2","( ( 4 * 2 ) / 2 ) - { ( 3 + 3 ) && ( 3 – 4 ) }","( ( 4 * 7 ) / 4 - { ( 6 + 7 ) && ( 5 – 1 ) ) }"
    for(int i = 0; i< 1; i++)
    {
        el.data= i+48;
        pushLS(p,el);
    }
    reverseLinkedStack(p);
    deleteLinkedStack(&p);
    int i = 0;
    while (s[i])
    {
        doing_job(s[i]);
        i++;
    }
    //system("leaks a.out");
    return 0;
}
