#include <stdio.h>

void InserSort(int arr[], int n)
{
	int i, j;
	int insData;

	for(i=1; i<n; i++)
	{
		insData = arr[i];   // Á€·Ä Žë»óÀ» insData¿¡ ÀúÀå

		for(j=i-1; j>=0 ; j--)
		{
			if(arr[j] > insData) 
				arr[j+1] = arr[j];    // ºñ±³ Žë»ó ÇÑ Ä­ µÚ·Î ¹Ð±â
			else
				break;   // »ðÀÔ À§Ä¡ Ã£ŸÒÀžŽÏ Å»Ãâ!
		}

		arr[j+1] = insData;  // Ã£Àº À§Ä¡¿¡ Á€·Ä Žë»ó »ðÀÔ!
	}
}


int main(void)
{
	int arr[5] = {5, 3, 2, 4, 1};
	int i;

	InserSort(arr, sizeof(arr)/sizeof(int));

	for(i=0; i<5; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}