/**
 * @file queue.c
 * @brief Funciones de colas de productos implementadas con arreglos circulares
*/
#include "queue.h"

/* Static: solo se usa en cierto archivo .c, no esta def en .h 
* succ: sucesor, busca el sig. y es circular [no se sale de los limites de la cola]
*/
static int succ(int value, Queue Q)
{
    if (value >= Q->capacity || value < 0)
    {
        printf("Error:");
        return -1;
    }

    value++;

    if (value == (Q->capacity))
        return 0;

    return value;
}

Queue queue_create(int n)
{
    /* Crear la cola Q de tamaño de la estructura QueueRecord */
    Queue Q = malloc(sizeof(struct QueueRecord));

    /* La cola esta almacenando Productos, tiene capacidad n */
    /* Ademas de tamanho 0, el Rear en 0, Front en 1*/
    Q->array = malloc(n * sizeof(Product));
    Q->capacity = n;
    Q->size = 0;
    Q->rear = 0;
    Q->front = 1;
    return Q;
}

Queue queue_make_empty(Queue Q)
{

}

int queue_is_empty(Queue Q)
{
    /* 1) Version compacta */
    return (Q->size == 0) ? 1 : 0;

    /* //2) Version tradicional
    if (Q->size == 0)
        return 1; //verdadero=1,falso=0
    return 0;
    */
}

int queue_is_full(Queue Q)
{
    return (Q->size == Q->capacity) ? 1 : 0;
}

Queue queue_enqueue(Product P, Queue Q)
{
    /* Faltan las comprobaciones */
    if (P.name == NULL || P.provider == NULL)
    {
        printf("Error:\n");
        return -1;
    }

    if (queue_isfull(Q))
    {
        printf("La cola esta llena!\n");
        return Q;
    }

    /* Rear apunta a su sucesor, El arreglo en tal posicion es igual al producto. */
    Q->rear = succ(Q->rear, Q);
    Q->array[Q->rear] = P;
    Q->size++;
    return Q;

}

Product queue_dequeue(Queue Q)
{
    if (queue_isempty(Q))
    {
        printf("Error, cola vacia!\n");
    }
    /* Front apuntara a otra funcion, su sucesor, el arreglo en tal posicion */
    Q->size--; 
    Q->front = succ(Q->front, Q);
    return Q;
}

Product queue_front(Queue Q)
{

}

int queue_size(Queue Q)
{
    return Q->size;
}

void queue_print(Queue Q)
{

}
void queue_delete(Queue Q)
{
    // Free()
}
