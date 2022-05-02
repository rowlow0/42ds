#include "linkeddeque.h"

int deleteRearLD(LinkedDeque* pDeque)
{
    DequeNode   *prevNode;

    if (!pDeque || pDeque->currentElementCount == 0)
        return (FALSE);
    prevNode = pDeque->pRearNode->pLLink;
    if (!prevNode)
        pDeque->pFrontNode = 0; // prevNode 가 NULL 인 경우
    else
        prevNode->pRLink = 0; // prevNode 가 NULL 이 아닌 경우
    pDeque->pRearNode->pLLink = 0;
    free(pDeque->pRearNode);
    pDeque->pRearNode = prevNode;
    pDeque->currentElementCount -= 1;
    return (TRUE);
}