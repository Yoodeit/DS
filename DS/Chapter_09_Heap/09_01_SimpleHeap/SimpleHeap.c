#include "SimpleHeap.h"

void HeapInit(Heap * ph) //힙 초기화
{
	ph->numOfData = 0; //데이터수를 0으로 초기화
}

int HIsEmpty(Heap * ph) // 힙이 비어있는지 확인
{
	if(ph->numOfData == 0) //데이터 개수가 0이면 빈 거고
		return TRUE;
	else
		return FALSE; //아님 아닌거지
}

int GetParentIDX(int idx) //배열 기반에서의 식을 이용해 부모노드의 index를 반환하는 함수
{ 
	return idx/2; 
}

int GetLChildIDX(int idx) //배열 기반에서의 식을 이용해 왼쪽 자식노드의 index를 반환하는 함수
{ 
	return idx*2; 
}

int GetRChildIDX(int idx)  //배열 기반에서의 식을 이용해 오른쪽 자식노드 index를 반환하는 함수
{ 
	return GetLChildIDX(idx)+1; 
}

int GetHiPriChildIDX(Heap * ph, int idx) //Get High Priority Child Index 
	//우선도가 더 높은(그러니까 수가 더 낮은) 자식노드의 인덱스를 뱉는 함수.
	//INSERT나 DELETE 둘 다 우선도 중심으로 SWAP하면서 이루어지므로 중요한 Helper
{
	if(GetLChildIDX(idx) > ph->numOfData)    // 왼쪽 자식노드의 인덱스값이 데이터개수보다 큰 건 말이 안됨. 없다고 봐야죠.
		return 0;

	else if(GetLChildIDX(idx) == ph->numOfData)    // 왼쪽 자식노드의 인덱스값과 데이터개수가 같다면(그니까 왼쪽 자식노드가 마지막 노드라면)
		return GetLChildIDX(idx); // 애초에 왼쪽노드밖에 없다는거니까 왼쪽노드를 반환하면 될 일이겠죠.

	else   // 
	{
		if(ph->heapArr[GetLChildIDX(idx)].pr 
						> ph->heapArr[GetRChildIDX(idx)].pr)
			return GetRChildIDX(idx); //왼쪽 자식노드보다 오른쪽 자식노드의 우선도가 더 높다면 오른쪽 자식노드의 인덱스값을 반환.
		else
			return GetLChildIDX(idx); //오른쪽 자식노드보다 왼쪽 자식노드의 우선도가 더 높다면 왼쪽 자식노드의 인덱스값을 반환.
	}
}

void HInsert(Heap * ph, HData data, Priority pr)
{
	int idx = ph->numOfData+1; // 원래 있던 데이터 개수에서 노드 하나가 추가되는 셈이니 +1을 해줍니다.
	HeapElem nelem = {pr, data}; //새 노드를 임시로 저장합니다. 값복사붙여넣기를 통한 재정렬이 끝난 후에 마지막에 넣으려고 ㅇ

	while(idx != 1) // 루트노드가 아닌 이상에야 반복됩니다.
	{
		if(pr < (ph->heapArr[GetParentIDX(idx)].pr)) //부모노드의 우선도보다 더 높다면
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)]; // 그 인덱스에 부모노드 값을 복사해넣고
			idx = GetParentIDX(idx); //부모노드의 인덱스값을 가집니다. 한 층 올라가서 다시 부모노드와 우선도를 비교해야 하기 때문에.
		}
		else //부모노드의 우선도보다 높지 않으면
			break; //거기까지인거겠죠
	}
	
	ph->heapArr[idx] = nelem; //멈춰있는 그 인덱스, 그러니까 노드에 정보를 넣어 주고요.
	ph->numOfData += 1; // 데이터개수는 추가되었으니 하나 추가해줍니다.
}

HData HDelete(Heap * ph)
{
	HData retData = (ph->heapArr[1]).data;    // 우선도가 높은 순서대로 삭제되는 것이 우선순위 큐. 그러니 삭제될 예정인 루트노드의 데이터를 임시로 복붙해둡니다. 삭제될 때 반환해야하니까.
	HeapElem lastElem = ph->heapArr[ph->numOfData]; // 마지막 노드도 임시로 저장해줍니다.

	int parentIdx = 1;    // 부모인덱스 1
	int childIdx; //자식인덱스

	while(childIdx = GetHiPriChildIDX(ph, parentIdx)) // childIdx에 주어진 parentIdx노드에서 좌우 중 더 높은 우선도를 가진 노드의 인덱스를 저장.
		//GetHiPriChildIDX 함수에서 0을 반환하는 경우, 그러니까 더 이상 자식노드가 없지 않고서야 반복.
	{
		if(lastElem.pr <= ph->heapArr[childIdx].pr) // 마지막노드의 우선도가 자식노드의 우선도보다 높으면 멈춥니다. 맞게 정렬되었으니 탈출하면 됨.
			break;

		ph->heapArr[parentIdx] = ph->heapArr[childIdx]; // 부모노드의 위치에 자식노드를 위치시킵니다.
		parentIdx = childIdx; //1레벨 내려서 반복합니다.
	}

	ph->heapArr[parentIdx] = lastElem; //확정된 위치에 lastElem을 넣고
	ph->numOfData -= 1; //데이터가 삭제되었으니 data num 하나 뺴고
	return retData; //삭제된 데이터 반환.
}
