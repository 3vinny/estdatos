	Divide el arreglo en una parte ordenada y otra desordenada, seleccionando en cada iteración el elemento mínimo de la parte no ordenada y colocandolo en su posicion definitiva.

- Selecciona el mínimo en cada pasada
- Realiza pocos intercambios
- el mejor :v

```c
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
```

``5 2 9 1 7``
 0  1   2  3  4
