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
SearchTree abb_insert(Product P, SearchTree T)
{
    /* esta comprobacion es siempre falsa, no hace falta imprimir
    si son arreglos dentro de P en vez de char */
    if(P.name == NULL || P.provider == NULL) return T;
    
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
        printf("Error: ya existe un producto con este precio.\n");
        prod_delete(P);
        return T;
    }

    if (P.price > abb_position_get_price(T))
        T->right = abb_insert(P, T->right);
    else
        T->left = abb_insert(P, T->left);
    return T;
}

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================
Position abb_find(float price, SearchTree T)
{
    if (T == NULL)
    {
        printf("Error: El precio no ha sido encontrado.\n");
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

Position abb_find_min(SearchTree T)
{
    if (T == NULL) return NULL;
    if (T->left == NULL) return T;
    return abb_find_min(T->left);
}

Position abb_find_max(SearchTree T)
{
    if (T == NULL) return NULL;
    if (T->right == NULL) return T;
    return abb_find_max(T->right);
}

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================
void abb_print_preorder(SearchTree T)
{
    if (T == NULL) return;

    printf("Nombre %s Precio [%f]\n", T->producto.name, T->producto.price);
    abb_print_preorder(T->left);
    abb_print_preorder(T->right);
}

void abb_print_inorder(SearchTree T)
{
    if (T == NULL) return;
    
    abb_print_inorder(T->left);
    printf("Nombre %s Precio [%f]\n", T->producto.name, T->producto.price);
    abb_print_inorder(T->right);
}

void abb_print_postorder(SearchTree T)
{
    if (T == NULL) return;

    abb_print_postorder(T->left);
    abb_print_postorder(T->right);
    printf("Nombre %s Precio [%f]\n", T->producto.name, T->producto.price);
}

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================
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

SearchTree abb_delete_price(float price, SearchTree T)
{
    if (T == NULL) 
    {
        printf("No existe un producto con ese precio.\n");
        return T;
    }

    /* Si el precio es menor buscamos a la izq, si es mayor derecha. */
    if (price < abb_position_get_price(T))
    {
        T->left = abb_delete_price(price, T->left);
    }   
    else if (price > abb_position_get_price(T))
    {
        T->right = abb_delete_price(price, T->right);
    }
    else
    {
        /* Caso 1) hoja sin hijos */
        if (T->left == NULL && T->right == NULL)
        {
            prod_delete(T->producto);
            free(T);
            return NULL;
        }
        else if (T->left != NULL && T->right != NULL)
        {
            /* Caso 3) Dos hijos */
            /* Intercambiamos con el minimo del arbol der. */
            Position der = abb_find_min(T->right);
            Product temp = T->producto;
            T->producto = der->producto;
            der->producto = temp;
            T->right = abb_delete_price(temp.price, T->right);
        }
        else
        {
            /* Caso 2) Un solo hijo */
            /* Si el izq no es null sube, contrario el derecho sube */
            Position hijo;
            if (T->left != NULL)
                hijo = T->left;
            else
                hijo = T->right;

            prod_delete(T->producto);
            free(T);
            return hijo; /* hijo sube a ocupar el lugar */
        }
    }
    return T;
}

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================
float abb_position_get_price(Position P)
{
    if (P == NULL)
    {
        printf("Error: posicion nula\n");
        return -1;
    }
    return P->producto.price;
}