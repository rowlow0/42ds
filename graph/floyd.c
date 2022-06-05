#include "graphlinkedlist.c"

int main()
{

    LinkedList *list = createLinkedList();
    ListNode element;
    GraphVertex g;
    element.pLink = 0;
    g.vertexID = 1; // add
	g.weight = 0;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 2;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 3;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 4;
    element.data = g;
    addLLElement(list,100,element);
    addLLEEdge(list, 1, 2, 5);
    addLLEEdge(list, 1, 4, 10);
    addLLEEdge(list, 2, 3, 3);
    addLLEEdge(list, 3, 4, 1);
    print_list(list);
    deleteLinkedList(&list);
    //system("leaks a.out");
    //gcc -g -fsanitize=address -Wall -Wextra -Werror linkedstack.c
    return 0;
}