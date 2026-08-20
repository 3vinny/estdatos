/*
============================ Ejercicio 2 ==============================
Crear un programa (con el esqueleto que se deja a continuacion) donde
se generen cadenas de caracteres aleatorias de 5, 10, 15 y 20 caracteres
de largo, y se muestren por pantalla.

--------------------------- Tips -------------------------------------
1. En C, los caracteres son en el fondo numeros: cada letra tiene un
codigo asociado en la tabla ASCII. Investiga en que rango de numeros
se encuentran las letras mayusculas y en cual las minusculas.

2. Si guardas la cadena en un arreglo de char, no olvides dejar espacio
para el caracter nulo '\0' al final, que es el que le indica a C donde
termina la cadena.
=======================================================================
*/

#include <stdio.h>   /* <-- Para usar printf      */
#include <stdlib.h>  /* <-- Para usar rand y srand */
#include <time.h>    /* <-- Para usar time(NULL)   */

void genera_cadena(int cant);

int main(void)
{
	srand(time(NULL));

	genera_cadena(5);
	genera_cadena(10);
	genera_cadena(15);
	genera_cadena(20);

	return 0;
}

void genera_cadena(int cant)
{
	char cadena[20];
	// limpieza previa
	for (int i=0; i<20; i++)
	{
		cadena[i] = '\0';
	}

	printf("\nCadena %d caracteres:\n", cant);
	for (int i=0; i<cant; i++)
	{
		// char 65 a 90 y 97 a 122 
		// 65-90 mayusculas | 97-122 minusculas
		cadena[i] = (char)(rand()%25 + 65);
		printf("%c", cadena[i]);
	}
}


/*
========================== Salida Esperada ==========================
> gcc string.c -o string.out
> ./string.out
> Cadena de 5 caracteres:  JQXTR
> Cadena de 10 caracteres: MZKPLQARWY
> Cadena de 15 caracteres: BHNOPXQZTYVCLEK
> Cadena de 20 caracteres: DFGHJKLMNPQRSTVWXYZA
=====================================================================
*/
