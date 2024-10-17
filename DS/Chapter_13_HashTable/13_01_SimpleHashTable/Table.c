#include <stdio.h>
#include <stdlib.h>
#include "Table.h"

//초기화 기능
void TBLInit(Table * pt, HashFunc * f)
{
	int i;
	
	// 모든 슬롯 초기화
	for(i=0; i<MAX_TBL; i++)
		(pt->tbl[i]).status = EMPTY;

	pt->hf = f; //해쉬 함수 등록(해시함수 코드가 직접 박혀있더라도 최적의 해시함수는 아니다. Default값으로 제공할 뿐. 등록가능해서 나쁠 것 없다.)
}

// 삽입 기능
void TBLInsert(Table * pt, Key k, Value v)
{
	int hv = pt->hf(k); //해쉬 값 겟
	pt->tbl[hv].val = v;
	pt->tbl[hv].key = k;
	pt->tbl[hv].status = INUSE;
}

//삭제 기능
Value TBLDelete(Table * pt, Key k)
{
	int hv = pt->hf(k);

	if((pt->tbl[hv]).status != INUSE)
	{
		return NULL;
	}
	else
	{
		(pt->tbl[hv]).status = DELETED;
		return (pt->tbl[hv]).val;
	}
}

// 탐색 기능
Value TBLSearch(Table * pt, Key k)
{
	int hv = pt->hf(k);

	if((pt->tbl[hv]).status != INUSE)
		return NULL;
	else
		return (pt->tbl[hv]).val;
}