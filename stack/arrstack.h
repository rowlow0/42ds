#ifndef _ARRSTACK_H_
#define _ARRSTACK_H_
#define MAX_STACK 65532
#include <stdio.h>
#include <stdlib.h>

typedef struct ArrNodeType
{
	char data;
} ArrNode;

typedef struct ArrType
{
	int count;
	int size;
    ArrNode *array;
} Arr;

Arr* createArrStack();
int pushAR(Arr* arr, ArrNode element);
ArrNode* popAR(Arr* arr);
ArrNode* peekAR(Arr* arr);
void deleteArrStack(Arr** arr);
int isArrStackFull(Arr* arr);
int isArrStackEmpty(Arr* arr);
void displayArrayList(Arr *arr);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif