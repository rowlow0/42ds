#include "linkeddeque.h"

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
    DequeNode   *newNode;

    if (pDeque)
    {
        newNode = malloc(sizeof(DequeNode));
        if (!newNode)
            return (0);
        newNode->data = element.data;
        if (pDeque->currentElementCount == 0)
        {
            pDeque->pRearNode = newNode;
            pDeque->pFrontNode = newNode;
        }
        else
        {
            pDeque->pFrontNode->pLLink = newNode;
            newNode->pRLink = pDeque->pFrontNode;
            pDeque->pFrontNode = newNode;
        }
        pDeque->currentElementCount++;
        return (TRUE);
    }
    return (FALSE);
}