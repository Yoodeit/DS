#include <stdio.h>
#include "ArrayList.h"

void ListInit(List * plist) //연결리스트 초기화 함수
{
	(plist->numOfData) = 0; //데이터 수 0으로 초기화
	(plist->curPosition) = -1; //현재 위치 -1로 초기화
}

void LInsert(List * plist, LData data) //연결리스트 값삽입 함수
{
	if(plist->numOfData >= LIST_LEN) //지정해둔 리스트 길이보다 데이터값이 같거나 더 크면 다 찬거니까
	{
		puts("저장이 불가능합니다."); // 저장이 불가능합니다를 출력한다. puts()는 printf()와 비슷하나 자동줄바꿈이 있고 포매팅은 없음.
		return;
	}
	
	plist->arr[plist->numOfData] = data;
	(plist->numOfData)++;
}

int LFirst(List * plist, LData * pdata)
{
	if(plist->numOfData == 0) //데이터가 하나도 없는 상항은 거르고
		return FALSE;
	
	(plist->curPosition) = 0; //하나라도 있으면 현위치를 인덱스0으로 재조준
	*pdata = plist->arr[0]; //역참조연산자 *를 사용해서 포인터변수가 가리키는 주소값이 아니라 실제 그 주소에 들어있는 값에 접근.
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	if(plist->curPosition >= (plist->numOfData)-1) //갖고 있는 데이터 수 만큼 다 참조했다면
		return FALSE;
	
	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List * plist)
{
	int rpos = plist->curPosition;
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos]; //삭제할 값을 백업해둡니다.
	
	for(i=rpos; i<num-1; i++) //삭제하고자 하는 위치 이후의 것들을 하나씩 앞으로 당겨옵니다.
		plist->arr[i] = plist->arr[i+1];
	
	(plist->numOfData)--; //삭제했으니 데이터 개수 하나 줄이고
	(plist->curPosition)--; //하나 뛰어넘지 않게 현위치도 하나 이전으로 돌려놓고
	return rdata; //삭제한 데이터는 반환합니다.
}

int LCount(List * plist)
{
	return plist->numOfData; //데이터 개수 세어줍니다.
}

