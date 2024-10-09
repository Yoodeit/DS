#include <stdio.h>
#include <stdlib.h>

void MergeTwoArea(int arr[], int left, int mid, int right)
{
	int fIdx = left; //front index는 left
	int rIdx = mid+1; //rear index는 mid보다 한 칸 오른쪽
	int i;

	int * sortArr = (int*)malloc(sizeof(int)*(right+1)); //병합 결과를 담을 공간 동적 메모리 할당
	int sIdx = left; //sort index는 left

	while(fIdx<=mid && rIdx<=right) //front index가 mid보다 크지는 않으면서, rear index가 right보다 크지는 않는 동안
	{
		if(arr[fIdx] <= arr[rIdx]) //front index가 가리키는 값이 더 작다면
			sortArr[sIdx] = arr[fIdx++]; //병합 결과를 담을 배열에 front index가 가리키는 값을 넣어주고 front index 값을 1 증가시킴.
		else //rear index가 가리키는 값이 더 작다면
			sortArr[sIdx] = arr[rIdx++]; //rear index가 가리키는 값을 배열에 담아주고 rear index값을 하나 증가시키면 됨.(front던 rear던 한 번 정렬되어 있으니까)

		sIdx++; //뭘 하나 넣었으면 병합 결과를 담을 배열의 index도 +1 해줘야겠죠.
	}

	if(fIdx > mid) //front index가 mid보다 큰 경우가 생기면(front파트가 병합완료 배열에 먼저 모두 들어갔다면)
	{
		for(i=rIdx; i<=right; i++, sIdx++) //남은 rear파트를 차례로 모두 넣어줍니다.
			sortArr[sIdx] = arr[i];
	}
	else
	{
		for(i=fIdx; i<=mid; i++, sIdx++) // 그 반대라면 front part가 남았을 테니 모두 배열에 넣어줍니다.
			sortArr[sIdx] = arr[i];
	}

	for(i=left; i<=right; i++) //병합결과를 원래 배열에 담아주고
		arr[i] = sortArr[i];
	
	free(sortArr); //병합결과를 임시로 담던 배열은 free 해줍니다.
}

void MergeSort(int arr[], int left, int right)
{
	int mid;

	if(left < right) //좌가 우보다 작으면
	{
		// mid 계산
		mid = (left+right) / 2;

		// 재귀적으로 left 부터 mid까지, 그리고 mid+1부터 right까지를 MergeSort함.
		MergeSort(arr, left, mid);
		MergeSort(arr, mid+1, right);

		// 좌우로 끝까지 쪼개지고 나면 가장 작은 단위부터 병합이 시작됨.
		MergeTwoArea(arr, left, mid, right);
	}
}

int main(void)
{
	int arr[7] = {3, 2, 4, 1, 7, 6, 5};
	int i;

	// ¹è¿­ arrÀÇ ÀüÃŒ ¿µ¿ª Á€·Ä 
	MergeSort(arr, 0, sizeof(arr)/sizeof(int)-1);

	for(i=0; i<7; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}