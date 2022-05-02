#include "linkeddeque.h"

int main(void)
{
    LinkedDeque *deque = createLinkedDeque();
    DequeNode   node1;
    DequeNode   node2;
    DequeNode   node3;

    node1.data = 'A';
    node2.data = 'B';
    node3.data = 'C';
    
    insertFrontLD(deque, node1);    // A
    insertRearLD(deque, node2);     // A B
    insertRearLD(deque, node3);     // A B C
    
    deleteRearLD(deque);            // A B
    deleteFrontLD(deque);           // B

    deleteLinkedDeque(&deque);

    system("leaks a.out");
    return (0);

}