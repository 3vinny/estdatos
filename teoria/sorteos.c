#include <stdio.h>

void selectionSort(int arr[], int n) 
{
	for (int i=0; i<n-1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = temp;
	}
}

void insertionSort(int arr[], int n) 
{
	for (int i=1; i<n; i++)
    {
		int key = arr[i];
		int j = i-1;
		while (j>=0 && arr[j] > key)
        {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void imprime(int arr[], int n)
{
    for (int i=0; i<n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main(void)
{
    int arr[5] = {5, 2, 9, 1, 7};
    int n = 5;
    
    printf("el arreglo es\n");
    imprime(arr, n);

    printf("\nordenado por selection\n");
    selectionSort(arr, n);
    imprime(arr, n);

    printf("\nordenado por insertion\n");
    insertionSort(arr, n);
    imprime(arr, n);

    return 0;
}