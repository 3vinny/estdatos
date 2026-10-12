#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product.h"
#define MAX 10

/* version de milton ---------------------------------- */

typedef struct _stack {
    Product *elements;
    int k;
    int p;
} Stack;

Stack stack_make_empty(int k);
Stack stack_push(Stack S, Product P);
Product stack_pop(Stack S);
void stack_print(Stack S);

/* Crea el centinela (make empty) */
Stack stack_make_empty(int k)
{
    Stack S;
    S.elements = malloc(sizeof(Product) * k);
    if (S.elements == NULL)
    {
        printf("Error: Sin memoria\n");
    }
    S.k = k;
    S.p = 0;
    return S;
}

/* push() */
Stack stack_push(Stack S, Product P)
{
    if (S.p == S.k)
    {
        printf("Error: Pila llena (stack overflow)\n");
        return S;
    }

    // Guardamos el producto en la posición y aumentamos el contador de posicion de S.p
    S.elements[S.p] = P;
    S.p++;
    printf("valor de p en push %d\n", S.p);
    return S;
}

/* pop() */
Product stack_pop(Stack S)
{
    if (S.p == 0)
    {
        printf("Error: Stack underflow (pila vacía)\n");
    }
    // Retrocedemos el contador de posicion de S, luego retornamos el producto en la posición
    S.p--;
    return S.elements[S.p];;
}

void stack_print(Stack S)
{
    printf("Stack:\n");
    // p: posicion, k: tamaño
    for (int i = S.p - 1; i >= 0; i--)
    {
        printf("Stack:\n");
        prod_print(S.elements[i]);
        printf("\n");
    }
}

int main(void)
{
    Stack S = stack_make_empty(MAX);
    S = stack_push(S, prod_create("Computadora", 100, 10, "Tecnologia papu"));
    return 0;
}