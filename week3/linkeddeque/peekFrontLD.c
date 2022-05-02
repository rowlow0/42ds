#include "linkeddeque.h"

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
    if (pDeque && pDeque->currentElementCount > 0)
        return (pDeque->pFrontNode);
    return (NULL);
}