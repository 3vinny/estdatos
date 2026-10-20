/**
 * @file queue.h
 * @brief Cabecera para las funciones de colas de productos implementadas con
 * arreglos circulares
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

/**
 * @brief Capacidad mínima de una cola
 *
 * Como queue_make_empty deja front en 1, el arreglo necesita al menos dos
 * posiciones para que ese índice exista. Se usa 5, igual que en el apunte.
*/
#define QUEUE_MIN_SIZE (5)

typedef struct QueueRecord* Queue;

/**
 * @brief Cola de productos sobre un arreglo circular de tamaño fijo
 *
 * Los productos se insertan por rear y se sacan por front (FIFO). En vez de
 * mover los productos dentro del arreglo, lo que se mueve son los índices
 * front y rear, y cuando uno de ellos pasa la última posición (capacity - 1)
 * vuelve a la primera (0). Para eso se usa la función auxiliar succ.
 *  - front es la posición del primer producto (el próximo en salir)
 *  - rear es la posición del último producto (el último que entró)
 *  - size es la cantidad de productos en la cola
 *
 * Al vaciar la cola se deja rear = 0 y front = 1, es decir, rear queda justo
 * "detrás" de front. Así, el primer enqueue avanza rear a la posición 1 y deja
 * ahí el producto, que es justo donde está front.
*/
struct QueueRecord {
	Product* array; /**< Arreglo de productos */
	int capacity; /**< Cantidad máxima de productos que caben en la cola */
	int front; /**< Posición del primer producto de la cola */
	int rear; /**< Posición del último producto de la cola */
	int size; /**< Cantidad de productos en la cola */
};

//==============================================================================
//        FUNCIONES DE LA COLA
//==============================================================================
Queue queue_create(int n);
Queue queue_make_empty(Queue Q);
int queue_is_empty(Queue Q);
int queue_is_full(Queue Q);
Queue queue_enqueue(Product P, Queue Q);
Product queue_dequeue(Queue Q);
Product queue_front(Queue Q);
int queue_size(Queue Q);
void queue_print(Queue Q);
void queue_delete(Queue Q);

#endif
