#include <stdio.h>

void SelSort(int arr[], int n)
{
	int i, j;
	int maxIdx;
	int temp;

	for(i=0; i<n-1; i++)
	{
		maxIdx = i;    // Á€·Ä ŒøŒ­»ó °¡Àå ŸÕŒ­ŽÂ µ¥ÀÌÅÍÀÇ index

		for(j=i+1; j<n; j++)   // ÃÖŒÒ°ª Åœ»ö
		{
			if(arr[j] < arr[maxIdx])
				maxIdx = j;
		}

		/* ±³È¯ */
		temp = arr[i];
		arr[i] = arr[maxIdx];
		arr[maxIdx] = temp;
	}
}


int main(void)
{
	int arr[4] = {3, 4, 2, 1};
	int i;

	SelSort(arr, sizeof(arr)/sizeof(int));

	for(i=0; i<4; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}