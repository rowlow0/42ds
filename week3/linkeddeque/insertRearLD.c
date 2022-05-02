#include "linkeddeque.h"

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
    DequeNode   *newNode;

    if (!pDeque)
        return (FALSE);
    newNode = (DequeNode *)malloc(sizeof(DequeNode));
    if (!newNode)
        return (FALSE);
    newNode->data = element.data;
    if (pDeque->currentElementCount == 0)
    {
        pDeque->pFrontNode = newNode;
        pDeque->pRearNode = newNode;
    }
    else
    {
        pDeque->pRearNode->pRLink = newNode;
        newNode->pLLink = pDeque->pRearNode;
        pDeque->pRearNode = newNode;
    }
    pDeque->currentElementCount += 1;
    return (TRUE);
}