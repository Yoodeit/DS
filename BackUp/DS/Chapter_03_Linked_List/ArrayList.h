//헤더파일 가드
#ifndef __ARRAY_LIST_H__ // 매크로가 정의되지 않았을 때만 아래의 코드를 컴파일합니다.
#define __ARRAY_LIST_H__ // 매크로를 정의하는 코드.

//매크로 정의
#define TRUE	1
#define FALSE	0

#define LIST_LEN	100

//데이터 타입 정의
typedef int LData;

//구조체 정의
typedef struct __ArrayList //언더바 두 개를 붙인 이유는 충돌방지용이라 하네요.
	//내부적으로 사용되는 것임을 암시하는 역할도 한다고 함.
{
	LData arr[LIST_LEN];
	int numOfData;
	int curPosition;
} ArrayList;

typedef ArrayList List;

// 함수 프로토타입
void ListInit(List * plist); //리스트 초기화
void LInsert(List * plist, LData data); //데이터 저장

int LFirst(List * plist, LData * pdata); //첫 데이터 참조
int LNext(List * plist, LData * pdata); // 두 번째 이후 데이터 참조

LData LRemove(List * plist); // 참조한 데이터 삭제
int LCount(List * plist); // 저장된 데이터 수 반환

#endif