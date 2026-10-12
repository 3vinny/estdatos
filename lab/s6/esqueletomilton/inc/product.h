/**
 * @file product.h
 * @brief Cabecera para las funciones relacionadas con productos
*/

#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estructura que representa un producto
 *
 * El producto contiene los datos de un producto: su nombre, precio, stock y
 * proveedor. El nombre y el proveedor son strings, mientras que el stock y el
 * precio son enteros.
 *
 * @param name Nombre del producto
 * @param price Precio del producto
 * @param stock Stock del producto
 * @param provider Proveedor del producto
 * @return Product
*/
typedef struct _Product {
	char* name; /**< Nombre del producto */
	float price; /**< Precio del producto */
	int stock; /**< Stock del producto */
	char* provider; /**< Proveedor del producto */
} Product;

Product prod_create(char* name, float price, int stock, char* provider);
void prod_print(Product product);
void prod_delete(Product product);

#endif
