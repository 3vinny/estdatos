#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* salio mal : version mia ---------------------------------- */
typedef int Producto;
typedef struct Nodo* PtrNodo;
typedef PtrNodo _stack;

struct Nodo {
    Producto producto;
    PtrNodo siguiente;
};

_stack *push(Producto producto, PtrNodo siguiente)
{
    _stack *s = malloc(sizeof(_stack));
    s->producto = producto;
    s->siguiente = siguiente;
    return s;
}

void make_empty(PtrNodo s)
{
    s->producto = NULL;
    s->siguiente = NULL;
}

void pop(PtrNodo s)
{
    s = s->siguiente;
    free(s); // liberamos la memoria
}

int main(void)
{
    printf("Ejercicio de pila, push, pop\n");

    // creamos la pila
    malloc(sizeof(struct _stack), struct _stack);
    struct _stack *s;
    // make empty
    make_empty *m;
    // push
    push(1, m);
    // pop
    pop(s);
    return 0;
}

_stack *push()
{
    
}