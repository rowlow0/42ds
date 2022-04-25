#ifndef _LINKEDSTACK_
#define _LINKEDSTACK_
#define MAX_STACK 65532
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StackNodeType
{
	char data;
	struct StackNodeType* pLink;
	struct StackNodeType *tail;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;
	StackNode* pTopElement;
} LinkedStack;

LinkedStack* createLinkedStack();
void reverseLinkedStack(LinkedStack*);
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack** pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack** pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
int	checkBracketMatching(LinkedStack*);


#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif