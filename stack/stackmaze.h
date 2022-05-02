#ifndef _STACKMAGE_H_
#define _STACKMAGE_H_
#define MAX_STACK 65532
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FX 10
#define FY 10
#define FF 4
typedef struct StackNodeType
{
	int x;
	int y;
	int	dir;
	struct StackNodeType *pLink;
	struct StackNodeType *tail;
} StackNode;

typedef struct MageStackType
{
	int visited[FX][FY][FF];
	int currentElementCount;
	StackNode* pTopElement;
} MageStack;

typedef struct SaverNode
{
	int	x;
	int	y;
}	saverNode;

typedef struct Saver
{
	int	count;
	saverNode *arr;
}	saver;

MageStack* createMageStack();
void reverseMageStack(MageStack*);
int pushLS(MageStack* pStack, StackNode element);
StackNode* popLS(MageStack** pStack);
StackNode* peekLS(MageStack* pStack);
void deleteMageStack(MageStack** pStack);
int isMageStackFull(MageStack* pStack);
int isMageStackEmpty(MageStack* pStack);
int	checkBracketMatching(MageStack*);




#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif