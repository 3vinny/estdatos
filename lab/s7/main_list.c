#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"
#define MAX 10

/* version de milton ---------------------------------- */

/* Para listas:
* Requerimos un centinela.
* Requerimos un puntero a la cabecera de la lista.
* falta ver videos :vvvvv
*/
typedef int TipoElemento;
typedef struct Nodo* PtrNodo;
typedef PtrNodo Lista;
typedef PtrNodo Posicion;

struct Nodo {
    TipoElemento Elemento;
    Posicion next; 
};

Lista lista_iniciar(Lista L)
{
    L = malloc(sizeof(struct Nodo));
    if (L == NULL)
    {
        printf("Error: Sin memoria!\n");
    }
    L->next = NULL;
    return L;
}

Lista insertar_nodo(Lista L, Product P);
Lista borrar_nodo(Lista L);
void lista_recorre(Lista L);
int busca_elementos(Lista L);

int main(void)
{
    List L;
    L = lista_iniciar(L);
    return 0;
}