#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
	List list; //리스트 생성
	int data; 
	ListInit(&list); //리스트 초기화 &연산자를 통해 생성한 리스트의 주소값을 넘겨줍니다.
	//그래야 초기화함수에서 실제로 리스트의 값을 변경할 수 있음.
	
	//리스트에 11, 11, 22, 22, 33 추가.
	LInsert(&list, 11); LInsert(&list, 11);
	LInsert(&list, 22); LInsert(&list, 22);
	LInsert(&list, 33);
	
	
	printf("현재 데이터의 수: %d \n", LCount(&list));
	
	//리스트 조회기능 테스트 부분
	if(LFirst(&list, &data)) //LFirst가 정상작동한다면 1을 반환할테니 if문이 실행됩니다.
	{
		printf("%d ", data);
		
		while(LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	
	
	// 리스트 삭제기능 테스트 부분
	if(LFirst(&list, &data))
	{
		if(data == 22)
			LRemove(&list);
		
		while(LNext(&list, &data))
		{
			if(data == 22)
				LRemove(&list);
		}
	}
	
	//삭제 이후 배열기반리스트 확인
	printf("현재 데이터의 수: %d \n", LCount(&list));
	
	if(LFirst(&list, &data))
	{
		printf("%d ", data);
		
		while(LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}