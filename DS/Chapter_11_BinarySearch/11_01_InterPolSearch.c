#include <stdio.h>

//보간 탐색입니다.
// 이진 탐색과는 달리, 대상에 비례하여 탐색의 위치를 결정합니다.

int ISearch(int ar[], int first, int last, int target)
{
	int mid;

//	if(first > last)
//		return -1;    // 이진 탐색이라면 이 정도 탈출조건을 만족할 수 있었을 테지만
	
	//보간 탐색이기 때문에 새로운 탈출조건을 더해주어야 합니다.
	

	if(ar[first]>target || ar[last]<target) //보간 탐색은 target값의 예상위치를 기반으로 mid값을 잡기 때문인 이유도 있고
		return -1; // 무한루프에 빠지게 됨
 
	// 비례식을 통해 잡는 mid값
	mid = ((double)(target-ar[first]) / (ar[last]-ar[first]) *
			(last-first)) + first;

	if(ar[mid] == target)
		return mid;    // 중간값을 잡았는데 그게 target이랑 일치하면 바로 mid값 반환하면 되죠.
	else if(target < ar[mid]) //만약 그렇지 않고, target값보다 중간값이 더 크다면
		return ISearch(ar, first, mid-1, target); // 중간값 왼쪽 파트에서 다시 보간탐색을 진행합니다.
	else
		return ISearch(ar, mid+1, last, target); //아니면(target값보다 중간값이 더 작다면) 중간값 오른쪽 파트에서 다시 보간탐색을 진행합니다.
}


int main(void)
{
	int arr[] = {1, 3, 5, 7, 9};
	int idx;
	
	idx = ISearch(arr, 0, sizeof(arr)/sizeof(int)-1, 7);
	if(idx == -1)
		printf("Åœ»ö œÇÆÐ \n");
	else
		printf("Åž°Ù ÀúÀå ÀÎµŠœº: %d \n", idx);

	idx = ISearch(arr, 0, sizeof(arr)/sizeof(int)-1, 2);
	if(idx == -1)
		printf("Åœ»ö œÇÆÐ \n");
	else
		printf("Åž°Ù ÀúÀå ÀÎµŠœº: %d \n", idx);

	return 0;
}


/*
int main(void)
{
	int arr[] = {1, 3, 5, 7, 9};
	int idx;
	
	idx = ISearch(arr, 0, sizeof(arr)/sizeof(int)-1, 2);
	if(idx == -1)
		printf("Åœ»ö œÇÆÐ \n");
	else
		printf("Åž°Ù ÀúÀå ÀÎµŠœº: %d \n", idx);

	return 0;
}

*/