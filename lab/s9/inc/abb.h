/**
 * @file abb.h
 * @brief Cabecera para las funciones de árboles binarios de búsqueda (ABB) de
 * productos
*/

#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

/* Nodo arbol de busqueda y posicion */
typedef struct Node* PtrToNode;
typedef PtrToNode SearchTree;
typedef PtrToNode Position;

/**
 * @brief Representa un nodo de un ABB
 *
 * El orden del árbol lo da el precio del producto: los productos más baratos
 * que el del nodo están en el subárbol izquierdo y los más caros en el
 * derecho.
 */
struct Node {
	Product producto; /* Producto guardado en nodo */
	Position left; /* Hijo izquierdo (productos mas baratos)*/
	Position right; /* Hijo derecho (productos mas caros) */
};

//==============================================================================
//        FUNCIONES DE INSERCIÓN
//==============================================================================
/**
 * @brief Inserta un producto en el ABB, según su precio
 *
 * Un producto más barato que el del nodo actual se inserta a la izquierda y
 * uno más caro a la derecha. El árbol pasa a ser el dueño de los strings del
 * producto, por lo que quien llama nunca debe liberarlo después de insertarlo.
 *
 * No se permiten precios repetidos: si ya existe un producto con ese precio se
 * imprime "Error: ya existe producto con este precio" y se libera
 * el producto entregado. Lo mismo ocurre si no hay memoria para el nodo. 
 * Si el producto es inválido (name o provider en NULL, es decir, 
 * un prod_create fallido) se imprime "Error" y el árbol queda intacto.
 *
 * @param P Producto a insertar
 * @param T ABB donde se debe insertar el producto
 * @return SearchTree Referencia al ABB con el producto insertado
 */
SearchTree abb_insert(Product P, SearchTree T);

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================
/**
 * @brief Busca en el ABB el producto que tiene un precio determinado
 *
 * En cada nodo se compara el precio buscado con el del nodo y se sigue por el
 * subárbol izquierdo (si es menor) o por el derecho (si es mayor), descartando
 * el otro. Se retorna el nodo que contiene el producto, no una copia.
 *
 * Si no existe un producto con ese precio, o el árbol está vacío, se imprime
 * un aviso con el precio buscado y se retorna un puntero nulo.
 *
 * @param price Precio del producto a buscar
 * @param T ABB donde se busca
 * @return Position Nodo que contiene el producto, o NULL si no se encuentra
 */
Position abb_find(float price, SearchTree T);

/**
 * @brief Busca el producto más barato del ABB
 *
 * El más barato es siempre el nodo que queda más a la izquierda. Si el árbol
 * está vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más barato, o NULL si el árbol está vacío
 */
Position abb_find_min(SearchTree T);

/**
 * @brief Busca el producto más caro del ABB
 *
 * El más caro es siempre el nodo que queda más a la derecha. Si el árbol está
 * vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más caro, o NULL si el árbol está vacío
 */
Position abb_find_max(SearchTree T);

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================
/**
 * @brief Imprime el ABB en preorder (raíz, izquierda, derecha)
 *
 * Primero se imprime el producto del nodo y luego sus subárboles izquierdo y
 * derecho, por lo que la primera línea siempre es la raíz. Se imprime una
 * línea por producto, con el mismo formato que abb_print_inorder. Si el árbol
 * está vacío no se imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_preorder(SearchTree T);

/**
 * @brief Imprime el ABB en inorder (izquierda, raíz, derecha)
 *
 * Los productos salen ordenados de menor a mayor precio. Se imprime una línea
 * por producto, con el formato "nombre [precio]". Si el árbol está vacío no se
 * imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_inorder(SearchTree T);

/**
 * @brief Imprime el ABB en postorder (izquierda, derecha, raíz)
 *
 * Se imprimen primero los subárboles izquierdo y derecho y al final el
 * producto del nodo, por lo que la última línea siempre es la raíz. Se imprime
 * una línea por producto, con el mismo formato que abb_print_inorder. Si el
 * árbol está vacío no se imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_postorder(SearchTree T);

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================
/**
 * @brief Elimina todos los nodos del ABB
 *
 * Se libera la memoria de todos los productos y nodos. Los nodos se liberan
 * en postorder (primero los dos subárboles y al final la raíz), porque si se
 * liberara la raíz primero se perdería el acceso a sus hijos. Después de
 * llamarla, T deja de ser válido, por lo que se debe asignar el valor
 * retornado: ABB = abb_delete_tree(ABB).
 *
 * @param T ABB a eliminar
 * @return SearchTree Siempre NULL (el árbol vacío)
 */
SearchTree abb_delete_tree(SearchTree T);

/**
 * @brief Elimina del árbol el producto que tiene el precio indicado.
 * 
 * abb_delete_price elimina del árbol el producto que tiene el precio indicado. 
 * Libera la memoria del producto y la del nodo, y retorna el árbol resultante, 
 * que puede tener una raíz distinta (o quedar vacío). 
 * Si no existe un producto con ese precio, avisa por
 * pantalla y deja el árbol intacto.
 *
 * Casos:
 * 1. El nodo a eliminar no tiene hijos (es una hoja): se libera el nodo y el padre queda con NULL.
 * 2. El nodo a eliminar tiene un solo hijo: se libera el nodo y el hijo ocupa su lugar.
 * 3. El nodo a eliminar tiene dos hijos: se intercambia el producto con el del nodo más
 * barato del subárbol derecho (el sucesor inorder) y se elimina ese nodo, que ya
 * tiene a lo más un hijo.
 *
 * @param price Precio del producto a eliminar
 * @param T ABB donde eliminar el precio
 * @return SearchTree ABB resultante
 */
SearchTree abb_delete_price(float price, SearchTree T);

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================
/**
 * @brief Devuelve el precio del producto que está en una posición del ABB
 *
 * Si la posición es nula se imprime "Error" y se retorna -1.
 *
 * @param P Posición (nodo) del ABB
 * @return float Precio del producto, o -1 si la posición es nula
 */
float abb_position_get_price(Position P);

#endif
