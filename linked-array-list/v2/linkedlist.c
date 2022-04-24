#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 1. 연결 리스트 생성 함수
LinkedList* createLinkedList() {
	LinkedList *result = malloc(sizeof(LinkedList));
	if (!result) {
		printf("[error : createLinkedList] Memory allocation failed.\n");
		return (NULL);
	}
	//초기화 진행
	result->currentElementCount = 0;
	return (result);
}

// 추가: 원소 대체 함수
int replaceLLElement(LinkedList* list, int index, ListNode element)
{
	if (list == NULL) {
		printf("[error : replaceLLElement] LinkedList is Null.\n");
		return (FALSE);
	}
	if (index < 0 || index > list->currentElementCount) {
		printf("[error : replaceLLElement] Invalid index.\n");
		return (FALSE);
	}
	ListNode* tmp = &(list->head);
	for (int i = 0; i <= index; i++) {
		 tmp = tmp->next;
	}
	tmp->data = element.data;
	return (TRUE);
}

// 2. 원소 추가 함수
// 이전노드와 해당 인덱스 사이의 연결을 끊고 새로운 노드를 사이에 끼워야함!
int addLLElement(LinkedList* list, int index, ListNode element) {

	if (list == NULL) {
		printf("[error : addLLElement] LinkedList is Null.\n");
		return (FALSE);
	}
	if (index < 0 || index > list->currentElementCount) {
		printf("[error : addLLElement] Invalid index.\n");
		return (FALSE);
	}
	ListNode *new_Node = malloc(0); //sizeof(ListNode)
	if (!new_Node) {
		printf("[error : addLLElement] Memory allocation failed.\n");
		return (FALSE);
	}
	*new_Node = element;
	if (!index)
	{
		list->head.next = new_Node;
		list->head.next->next = 0;
	}
	else
	{
		ListNode* prev_Node = &(list->head);
		for (int i = 0; i < index; i++) {
			prev_Node = prev_Node->next;
		}
		new_Node->next = prev_Node->next;
		prev_Node->next = new_Node;
	}
	list->currentElementCount += 1;
	return (TRUE);
}

// 3. 원소 삭제 함수
int removeLLElement(LinkedList* list, int index) {
	ListNode* prev_Node; // 이전 노드 (index - 1)
	ListNode* del_Node; // 삭제할 노드

	if (list == NULL) {
		printf("[error : removeLLElement] LinkedList is Null.\n");
		return (FALSE);
	}
	if (index < 0 || index >= list->currentElementCount) {
		printf("[error : removeLLElement] Invalid index.\n");
		return (FALSE);
	}

    if(index == 1)
    {
        free(list->head.next);
		if (list->currentElementCount >= 2)
		list->head.next = list->head.next->next;
    }
    else
    {
        prev_Node = list->head.next;
        for(int i =0;i<index-1;i++)
            prev_Node = prev_Node->next;
        del_Node = prev_Node->next;
        prev_Node->next=del_Node->next;
        free(del_Node);
    }
    list->currentElementCount--;
	return (TRUE);
}

// 4. 연결 리스트에서 특정 인덱스의 원소를 가져오는 함수
ListNode* getLLElement(LinkedList* list, int index) {
	ListNode* result = NULL;

	if (list == NULL) {
		printf("[error : getLLElement] LinkedList is Null.\n");
		return (FALSE);
	}
	if (index < 0 || index >= list->currentElementCount) {
		printf("[error : getLLElement] Invalid index.\n");
		return (FALSE);
	}
	
	result = list->head.next;
	for (int i = 0; i < index; i++) {
		result = result->next;
	}

	return (result);
}

// 5. 연결 리스트의 정보 출력 함수
void displayLinkedList(LinkedList* list) {
	ListNode* tmp = NULL;

	if (list == NULL) {
		printf("[error : displayLinkedList] LinkedList is Null.\n");
		return ;
	}

	printf("Current Element Count : %d\n", list->currentElementCount);
	printf("----[element display]----\n");
	tmp = &(list->head);
	for (int i = 0; i < list->currentElementCount; i++) {
		tmp = tmp->next;
		printf("[%d]'s element : %d\n", i, tmp->data);
	}
}

// 6. 연결 리스트 초기화 함수
void clearLinkedList(LinkedList* list) {
	if (list == NULL) {
		printf("[error : clearLinkedList] LinkedList is Null.\n");
		return ;
	}
	ListNode *t = list->head.next;
	ListNode *next;
	while(t)
	{
		next = t->next;
		free(t);
		t = next;
	}
	list->currentElementCount = 0;
}

// 7. 연결 리스트의 길이를 리턴하는 함수
int getLinkedListLength(LinkedList* list) {
	if (list == NULL) {
		printf("[error : getLinkedListLength] LinkedList is Null.\n");
		return (FALSE);
	}
	return (list->currentElementCount);
}

// 8. 연결 리스트 삭제 함수
void deleteLinkedList(LinkedList** list) {
	if (list == NULL) {
		printf("[error : deleteLinkedList] LinkedList is Null.\n");
		return ;
	}
	ListNode *t = (*list)->head.next;
	ListNode *next;
	while(t)
	{
		next = t->next;
		free(t);
		t = next;
	}
	free(*list);
	*list = NULL;
}

int main(void) {
	LinkedList *list = NULL;

	// 총 8개의 함수 TEST 진행

	// 1. 연결 리스트 생성
	list = createLinkedList();

	if (list) {
		printf("----------------\n");
		printf("연결 리스트 생성완료!\n");
		printf("----------------\n");
		printf("\n\n");


		ListNode node;

		//ListNode* a= getLLElement(list,0);
		//printf("!!@@%d@@!!\n",a->data);

		// 2. 원소 추가 진행
		node.data = 10000;
		addLLElement(list, 0, node);
		node.data = 23451234;
		addLLElement(list, 1, node);
		node.data = -232;
		addLLElement(list, 2, node);
		node.data = 234;
		addLLElement(list, 3, node);
		node.data = 425933;
		addLLElement(list, 4, node);
		node.data = 121;
		addLLElement(list, 5, node);
		printf("----------------\n");
		printf("원소 6개 추가\n");
		printf("----------------\n");
		printf("\n\n");

		// 5. 정보 출력
		displayLinkedList(list);
		printf("\n\n");

		// 3. 원소 삭제 진행
		printf("----------------\n");
		printf("1 INDEX 원소 삭제!\n");
		printf("----------------\n");
		removeLLElement(list, 1);
		printf("\n\n");

		// 5. 정보 출력
		displayLinkedList(list);
		printf("\n\n");

		printf("----------------\n");
		printf("2 INDEX 원소 삭제!\n");
		printf("----------------\n");
		removeLLElement(list, 2);
		// 5. 정보 출력
		displayLinkedList(list);
		printf("\n\n");

		// 4. 특정 인덱스 원소 가져와서 출력해보기
		printf("----------------\n");
		printf("%d번째 원소 확인: %d\n", 1, getLLElement(list, 1)->data);
		printf("----------------\n");
		printf("\n\n");

		printf("----------------\n");
		printf("%d번째 원소 확인: %d\n", 0, getLLElement(list, 0)->data);
		printf("----------------\n");
		printf("\n\n");

		ListNode* a= getLLElement(list,0);
		printf("!!@@%d@@!!\n",a->data);

		// 원소 하나 더 삭제
		printf("----------------\n");
		printf("0번째 원소 삭제!\n");
		printf("----------------\n");
		removeLLElement(list, 0);
		displayLinkedList(list);
		printf("\n\n");

		printf("!!@@%d@@!!\n",a->data);

		// 원소 대체
		printf("----------------\n");
		printf("0번째 원소 대체!\n");
		printf("----------------\n");
		node.data=22;
		replaceLLElement(list, 0, node);
		displayLinkedList(list);
		printf("\n\n");

		// 8. 현재 연결 리스트의 길이 확인
		printf("----------------\n");
		printf("현재 연결리스트의 길이? : %d\n", getLinkedListLength(list));
		printf("----------------\n");
		printf("\n\n");

		// 7. 연결 리스트 초기화 진행
		printf("----------------\n");
		printf("연결 리스트 초기화 진행\n");
		printf("----------------\n");
		clearLinkedList(list);
		displayLinkedList(list);
		addLLElement(list, 0, node);
		printf("\n\n");

		// 9. 연결 리스트 삭제 진행
		printf("----------------\n");
		printf("연결 리스트 삭제 진행\n");
		printf("----------------\n");
		deleteLinkedList(&list);
		if (list) {
			printf("연결 리스트 삭제 안됐음!\n");
		} else {
			printf("연결 리스트 삭제 완료!\n");
		}
	}
	system("leaks linkedlist");
	return (0);
}