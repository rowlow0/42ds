#include "linkeddeque.h"

int deleteFrontLD(LinkedDeque* pDeque)
{
    if (pDeque && pDeque->currentElementCount > 0)
    {
        DequeNode *nextNode = pDeque->pFrontNode->pRLink;
        if (nextNode)
            nextNode->pLLink = 0;
        else
            pDeque->pRearNode = 0;
        pDeque->pFrontNode->pRLink = 0;
        free(pDeque->pFrontNode);
        pDeque->pFrontNode = nextNode;
        pDeque->currentElementCount--;
        return (TRUE);
    }
    return (FALSE);
}