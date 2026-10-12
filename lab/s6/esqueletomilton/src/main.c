#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "product.h"

/*
Hacer la funcion de busqueda con strcmp
Que sean dos al mismo tiempo
- una que busque con prev
- otra que busque con next
en el mismo while, al mismo tiempo
que indique por consola que puntero encontró el producto
*/
/*
rubrica:::::
- compila con make sin warnings 0.5
- doc con doxygen completa (brief, param, return) en todas las funciones 0.5
- sin fugas ni errores de memoria (valgrind) 1.5
- insercion 1.0
- eliminacion (inv_delete) 1.0
- indices.. 0.5
- vaciado.. 0.5
- busqueda (inv_find_by_name) 1.5 !!!!!!!!
- tiempo de retraso

datos::::::::
- usara un main propio llamando a todas las funciones, debera SU MAIN salir sin fugas
- no operaciones prohibidas en la cabecera
- makeempty
- reutilizando inventario
- findbyname
- destruyendo inventario
*/

int main(){
	printf("Programa de Inventarios\n===========================================\n");

	Inventory I = inv_make_empty(NULL);

	/* Insertamos un producto en inventario */
	inv_insert(prod_create("Producto 1", 100, 1, "Proveedor 1"), I, inv_last(I));
	inv_insert(prod_create("Producto 2", 2, 2, "Proveedor 2"), I, inv_last(I));
	inv_insert(prod_create("Producto 3", 3, 3, "Proveedor 3"), I, inv_last(I));
	inv_insert(prod_create("Producto 4", 4, 4, "Proveedor 4"), I, inv_last(I));
	inv_insert(prod_create("Producto 5", 5, 5, "Proveedor 5"), I, inv_last(I));

	inv_find_by_name("Producto 1", I);
	inv_find_by_name("Producto 3", I);
	inv_find_by_name("Producto 5", I);
	inv_find_by_name("No existo", I);

	inv_print(I);
	/* Destruimos el inventario, evitamos dilemas de memoria */
	inv_destroy(I);
	return 0;
}
