/*
============================ Ejercicio 3 ==============================
Crear un programa (con el esqueleto que se deja a continuacion) donde
se tomen los arreglos de frutas y cantidades ya definidos, y se
escriban en un archivo CSV llamado "frutas.csv".

Ya se deja armada la parte que imprime los arreglos por pantalla; lo
que falta es construir la escritura del archivo CSV.

--------------------------- Tips -------------------------------------
1. Un archivo CSV ("Comma-Separated Values") es simplemente un archivo
de texto plano donde cada linea representa una fila de una tabla, y
las columnas de esa fila se separan con comas. Por ejemplo:

-------------ejemplo.csv-------------
fruta,cantidad
Manzana,12
Platano,7
------------------------------------

Se puede abrir con cualquier editor de texto, pero tambien con Excel
o Google Sheets, que lo interpretan automaticamente como una tabla.

2. Para escribir un archivo en C se usa fopen() con el modo "w" (write),
luego fprintf() para escribir cada linea, y finalmente fclose() para
cerrarlo y asegurar que todo se guarde en disco.

3. Siempre verifica que el archivo se haya abierto correctamente (que
el puntero que retorna fopen() no sea NULL) antes de escribir en el.

4. La primera linea del CSV se suele usar para los encabezados de las
columnas (en este caso, algo como "fruta,cantidad").
=======================================================================
*/

#include <stdio.h>  /* <-- Para usar printf, fopen, fprintf y fclose */

int main(void)
{
	char *frutas[] = {"Yuca", "Pera", "Mango", "Palta", "Tomate"};
	int cantidades[] = {12, 7, 20, 15, 9};
	int n = 5;

	FILE *archivo = fopen("./frutas.csv", "w");

	if (archivo == NULL)
	{
		printf("No se pudo abrir archivo frutas.csv Error!\n");
		return 1;
	} 
	else
	{
		// encabezado !
		fprintf(archivo, "FRUTA,CANTIDAD\n");
	}

	printf("Frutas y cantidades:\n");
	for (int i = 0; i < n; i++)
	{
		fprintf(archivo, "%s,%d\n", frutas[i], cantidades[i]);
		printf("%s: %d\n", frutas[i], cantidades[i]);
	}

	fclose(archivo); // es sagrado!!!

	return 0;
}


/*
========================== Salida Esperada ==========================
> gcc csv.c -o csv.out
>
> ./csv.out
> Frutas y cantidades:
> Manzana: 12
> Platano: 7
> Pera: 20
> Uva: 15
> Naranja: 9
>
> cat ./frutas.csv
> fruta,cantidad
> Manzana,12
> Platano,7
> Pera,20
> Uva,15
> Naranja,9
=====================================================================
*/