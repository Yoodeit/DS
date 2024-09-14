#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

// 이전 3, 4, 5강에서 배운 것을 바탕으로 혼자 구현해본 헤더파일.

#define TRUE	1
#define FALSE	0

#define STACK_LEN	100
typedef int Data;

typedef struct __Stack
{
	Data arr[STACK_LEN];
	int numOfData;  // 생각해보니 굳이 필요 없다. curposition이 곧 데이터개수
	int curPosition; 
} ArrayBaseStack;


typedef ArrayBaseStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);

Data SPeek(Stack * pstack);

#endif