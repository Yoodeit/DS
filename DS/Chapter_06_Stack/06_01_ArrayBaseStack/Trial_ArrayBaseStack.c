#include <stdio.h>
#include <stdlib.h>
#include "Trial_ArrayBaseStack.h"

void StackInit(Stack * pstack)
{
	(pstack->numOfData) = 0; //데이터 수 0으로 초기화
	(pstack->curPosition) = -1; //현재 위치 -1로 초기화
}

int SIsEmpty(Stack * pstack)
{
	if(pstack->numOfData == 0) 
	{
		puts("스택이 비어 있습니다."); 
		return TRUE;
	}
	
	return FALSE;
}

void SPush(Stack * pstack, Data data)
{
	if(pstack->numOfData >= STACK_LEN) //지정해둔 스택 길이보다 데이터값이 같거나 더 크면 다 찬거니까
	{
		puts("저장이 불가능합니다."); // 저장이 불가능합니다를 출력한다. puts()는 printf()와 비슷하나 자동줄바꿈이 있고 포매팅은 없음.
		return;
	}
	
	(pstack->curPosition)++; //현위치를 조정.
	pstack->arr[pstack->curPosition] = data ; //현위치에 데이터를 집어넣고
	(pstack->numOfData)++; //데이터 수 1 증가
	
}

Data SPop(Stack * pstack)
{
	if(!SIsEmpty){
		Data rdata = pstack->arr[pstack->curPosition];
		(pstack->curPosition)--;
		(pstack->numOfData)--;
		return rdata;
	}
}

Data SPeek(Stack * pstack)
{
	if(!SIsEmpty){
		Data rdata = pstack->arr[pstack->curPosition];
		return rdata;
	}
}