#include "linkeddeque.h"

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
    if (pDeque && pDeque->currentElementCount > 0)
        return (pDeque->pRearNode);
    return (NULL);
}