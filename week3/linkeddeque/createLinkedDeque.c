#include "linkeddeque.h"

LinkedDeque* createLinkedDeque()
{
    LinkedDeque *deque;

    deque = (LinkedDeque *)malloc(sizeof(LinkedDeque));
    if (!deque)
        return (0);
    deque->currentElementCount = 0;
    deque->pFrontNode = 0;
    deque->pRearNode = 0;
    return (deque);
}