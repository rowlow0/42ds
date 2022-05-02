#include "linkedQueue.h"

int main()
{
    LinkedQueue *queue = createLinkedQueue();
    LinkedQueueNode node;
    LinkedQueueNode *peek;
    int result;
    
    result = isLinkedQueueEmpty(queue);
    for (int i = 65; i < 70; i++)
    {
        node.data = i;
        enqueueLQ(queue, node);
    }
    for (int i = 0; i < 2; i++)
        dequeueLQ(queue);
    peek = peekLQ(queue);
    deleteLinkedQueue(&queue);
    return (0);
}