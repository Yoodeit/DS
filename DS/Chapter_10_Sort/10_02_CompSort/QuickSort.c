#include <stdio.h>

void Swap(int arr[], int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}	


int Partition(int arr[], int left, int right)
{
	int pivot = arr[left];    // pivot은 배열의 최좌측
	int low = left+1; //low는 그로부터 하나 오른쪽
	int high = right; //high는 배열의 최우측

	while(low <= high)    // 즉, low가 high보다 오른쪽으로 넘어가게 되면, 다시 말해 역전하는 것이 탈출조건
	{	
		/*
		// 피벗보다 큰 값을 찾는 과정
		while(pivot > arr[low]) // 오름차순이니까 pivot보다 작은 것들은 다 왼쪽으로 보내야 함. 그래서 low를 자꾸 키우는 거.
			low++; //high를 오른쪽으로 이동
		
		// 피벗보다 작은 값을 찾는 과정
		while(pivot < arr[high]) //마찬가지로 pivot보다 작은 값이 나올 때까지 high를 낮춰준다.
			high--; //high를 왼쪽으로 이동
		*/
		
		
		while(pivot >= arr[low] && low <= right) //위의 주석에서 수정사항이 있다. 피봇과 데이터가 같은 경우에 무한루프를 돌기 때문에 같더라도 ++이 되도록.
			low++;

		while(pivot <= arr[high] && high >= (left+1)) //또한 정렬 범위를 넘지 않도록 && 문을 추가해준다.
			high--;
		

		if(low <= high) //low랑 high가 역전이 된 게 아니라면   
			Swap(arr, low, high); // low랑 high에 해당하는 데이터를 swap해줍니다.   
	}
	
	// 탈출했다면 low와 high가 교차되었을 테니
	Swap(arr, left, high);  // 피벗과 high가 가리키는 대상 swap
	return high; //옮겨진 피벗의 위치정보 반환  
}

void QuickSort(int arr[], int left, int right)
{
	if(left <= right)
	{
		int pivot = Partition(arr, left, right);    // Partition의 결과로 반환된 인덱스값을 기준으로 왼쪽은 다 작고 오른쪽은 다 큼.
		QuickSort(arr, left, pivot-1);    // 왼쪽에서 또 퀵소트
		QuickSort(arr, pivot+1, right);    // 오른쪽에서 또 퀵소트
	}
}

int main(void)
{
	int arr[7] = {3, 2, 4, 1, 7, 6, 5};
//	int arr[3] = {3, 3, 3};

	int len = sizeof(arr) / sizeof(int);
	int i;

	QuickSort(arr, 0, sizeof(arr)/sizeof(int)-1);

	for(i=0; i<len; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}