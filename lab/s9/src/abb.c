/**
 * @file abb.c
 * @brief Funciones de árboles binarios de búsqueda (ABB) de productos
 *
 * Cada nodo del árbol guarda un producto y sus dos hijos. El orden lo da el
 * precio: en el subárbol izquierdo de un nodo están los productos más baratos
 * y en el derecho los más caros, por lo que no puede haber dos productos con
 * el mismo precio.
 *
 * Un árbol vacío es un puntero nulo. Por eso las funciones que pueden cambiar
 * la raíz (abb_insert y abb_delete_tree) retornan el árbol resultante y se
 * usan siempre de la forma ABB = abb_insert(P, ABB).
*/

/*
 * EN CLASE:
 *  1. Define los atributos de `struct Node` en inc/abb.h.
 *  2. Implementa cada función de este archivo: reemplaza el `;` del final de
 *     su prototipo por el cuerpo de la función `{ ... }`.
 */
#include "abb.h"

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
 * imprime "Error" y se libera el producto entregado. Lo mismo ocurre si no hay
 * memoria para el nodo. Si el producto es inválido (name o provider en NULL,
 * es decir, un prod_create fallido) se imprime "Error" y el árbol queda
 * intacto.
 *
 * @param P Producto a insertar
 * @param T ABB donde se debe insertar el producto
 * @return SearchTree Referencia al ABB con el producto insertado
 */
SearchTree abb_insert(Product P, SearchTree T)
{
    if(P.name == NULL || P.provider == NULL)
    {
        printf("Error: el producto es invalido...\n");
        return T;
    }
    
    if (T == NULL)
    {
        T = malloc(sizeof(struct Node));
        if (T == NULL)
        {
            printf("Error de memoria\n");
            prod_delete(P);
            return T;
        }
        T->producto = P;
        T->left = NULL;
        T->right = NULL;
        return T;
    }

    /* Lo cortamos antes que compare derecha o izq. */
    if (P.price == abb_position_get_price(T))
    {
        printf("Error\n");
        prod_delete(P);
        return T;
    }

    if (P.price > abb_position_get_price(T))
    {
        abb_insert(P, T->right);
        return T;
    }
    else
    {
        abb_insert(P, T->left);
        return T;
    }
}

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
Position abb_find(float price, SearchTree T)
{
    if (T == NULL)
    {
        printf("Error: T es invalido\n");
        return NULL;
    }
    
    if (!T->left && !T->right && abb_position_get_price(T) != price)
    {
        printf("Error: no se encontro el producto de precio %f\n", price);
        return NULL;
    }

    if (price == abb_position_get_price(T))
        return T;
    else if (price < abb_position_get_price(T))
        return abb_find(price, T->left);
    else
        return abb_find(price, T->right);
}

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
 * @brief Imprime el ABB en inorder (izquierda, raíz, derecha)
 *
 * Los productos salen ordenados de menor a mayor precio. Se imprime una línea
 * por producto, con el formato "nombre [precio]". Si el árbol está vacío no se
 * imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_inorder(SearchTree T)
{
    if (T == NULL) return;
    
    abb_print_inorder(T->left);
    printf("Nombre %s Precio [%f]\n", T->producto.name, T->producto.price);
    abb_print_inorder(T->right);
}

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
SearchTree abb_delete_tree(SearchTree T)
{
    /* atajar el caso pa que no de segmentation fault */
    if (T == NULL) return T;

    abb_delete_tree(T->left);
    abb_delete_tree(T->right);
    prod_delete(T->producto);
    free(T); /* Como antes usamos malloc de T */
    T = NULL;
    return T;
}

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
float abb_position_get_price(Position P)
{
    if (P == NULL)
    {
        printf("Error: posicion nula\n");
        return -1;
    }
    return P->producto.price;
}
