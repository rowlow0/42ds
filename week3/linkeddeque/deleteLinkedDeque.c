#include "linkeddeque.h"

void deleteLinkedDeque(LinkedDeque** pDeque)
{
    if (pDeque)
    {
        while ((*pDeque)->currentElementCount)
            deleteFrontLD(*pDeque);
        free(*pDeque);
        *pDeque = 0;
    }
}