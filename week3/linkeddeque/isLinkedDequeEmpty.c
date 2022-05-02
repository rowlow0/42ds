#include "linkeddeque.h"

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
    if (!pDeque)
        return (ERROR);
    if (pDeque->currentElementCount == 0)
        return (TRUE);
    return (FALSE);
}