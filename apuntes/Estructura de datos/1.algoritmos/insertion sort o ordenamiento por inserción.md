- Divide el arreglo en una parte ordenada y otra que no
- Inserta cada elemento en su posición correspondiente desplazando los mayores

5 2 9 1 7

```c
void insertionSort(int arr[], int n) {
	for (int i=1; i<n; i++) {
		int key = arr[i];
		int j = i-1;
		while (j>=0 && arr[j] > key) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}
```

algoritmo de ordenamiento que construye una lista de forma **incremental**