/**
 * @file inventory.c
 * @brief Funciones relacionadas con inventarios de productos
*/
#include "inventory.h"


//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================
// Inserta un producto en el inventario, justo después de una posición
Inventory inv_insert(Product P, Inventory I, InventoryElement Position)
{
    /* Comprobacion previa */
    if (I == NULL || Position == NULL || P.name == NULL || P.provider == NULL)
    {
        printf("Error: Producto inválido\n");
        return I;
    }
    else
    {
        /* nodo auxiliar */
        InventoryElement aux = malloc(sizeof(struct Node));

        if (aux == NULL)
        {
            printf("Error: Sin memoria!\n");
            return I;
        }

        aux->product = P;
        aux->next = Position->next;
        aux->prev = Position;

        /* actualizamos el next del nodo Position */
        Position->next = aux;

        /* actualizamos el prev del nodo siguiente al nuevo */
        aux->next->prev = aux;

        /* actualizamos el tamanho de la lista */
        I->product.stock++;

        return I;
    }
}

// Inserta un producto al principio del inventario
Inventory inv_insert_first(Product P, Inventory I)
{
    if (I == NULL)
    {
        printf("Error: Inventario no inicializado\n");
        return NULL;
    }

    /* Retorna la insercion al principio de la lista */
    return inv_insert(P, I, inv_header(I));
}

// Inserta un producto al final del inventario
Inventory inv_insert_last(Product P, Inventory I)
{
    if (I == NULL)
    {
        printf("Error: Inventario no inicializado\n");
        return NULL;
    }

    /* Retorna la insercion al final de la lista */
    return inv_insert(P, I, inv_last(I));
}

// Elimina del inventario el producto que se encuentra en una posición
Inventory inv_delete(InventoryElement Position, Inventory I)
{
    /* Comprobacion previa */
    if (I == NULL || Position == NULL || Position == inv_header(I))
    {
        printf("Error: Producto inválido\n");
        return I;
    }
    else
    {
        /* Cambiamos los nodos: el prev del next debe apuntar a next
        * y el next del prev debe apuntar a prev (ciclicamente) */
        Position->prev->next = Position->next;
        Position->next->prev = Position->prev;

        /* Antes de liberar con free la memoria 
        * borramos el producto de tal posicion */
        prod_delete(Position->product);
        free(Position);

        /* Actualizamos el tamaño de la lista */
        I->product.stock--;

        return I;
    }
}

// Retorna el producto que se encuentra en la posición indicada
Product* inv_retrieve(InventoryElement Position, Inventory I)
{
    /* Comprobacion previa */
    if (I == NULL || Position == NULL || Position == inv_header(I))
    {
        printf("Error: Producto inválido\n");
        return NULL;
    }
    else
    {
        return &(Position->product);
    }
}

//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS ÍNDICES DEL INVENTARIO
//==============================================================================
// Devuelve la cabecera inventario
InventoryElement inv_header(Inventory I)
{
    return I;
}

// Devuelve el primer elemento del inventario
// Si el inventario está vacío se retorna la cabecera.
InventoryElement inv_first(Inventory I)
{
    return inv_forward(I);
}

// Devuelve el último elemento del inventario
// Si el inventario está vacío se retorna la cabecera.
// Al ser circular hay que retroceder desde el header/centinela
InventoryElement inv_last(Inventory I)
{
    return inv_backward(I);
}

// Devuelve el elemento siguiente del inventario
// Accede al nodo de position, y luego el siguiente.
// Comprobacion previa de NULL.
InventoryElement inv_forward(InventoryElement Position)
{
    /* Comprobacion previa */
    if (Position == NULL) return NULL;
    return Position->next;
}

// Devuelve el elemento anterior del inventario
// Comprobacion previa de NULL.
InventoryElement inv_backward(InventoryElement Position)
{
    /* Comprobacion previa */
    if (Position == NULL) return NULL;
    return Position->prev;
}

//==============================================================================
//        FUNCIONES RELACIONADAS CON LA TOTALIDAD DEL INVENTARIO
//==============================================================================

// Elimina todos los elementos del inventario, incluida su cabecera
// Usamos free en ambos casos que este vacio o no.
void inv_destroy(Inventory I)
{
    if (I == NULL)
    {
        printf("Error: Inventario no inicializado\n");
        return;
    }

    if (inv_is_empty(I))
    {
        printf("Inventario vacío!!\n");
    }

    while (inv_is_empty(I) == false)
    {
        inv_delete(inv_first(I), I);
    }
    /* tenga productos o no, se libera */
    free(I);
}

// Crea un inventario vacío o vacía uno ya existente
Inventory inv_make_empty(Inventory I)
{
    if (I != NULL)
    {
        inv_destroy(I);
    }
        
    I = malloc(sizeof(struct Node));
    if (I == NULL)
    {
        printf("Error: Sin memoria!\n");
        return NULL;
    }

    /* Inicializa el nodo */
    I->next = I;
    I->prev = I;
    I->product.stock = 0;
    return I;
}

void inv_print(Inventory I)
{
    if (I == NULL)
        return;

    if (I->product.stock == 0)
    {
        printf("Inventario vacio\n");
        return;
    }

    InventoryElement actual = inv_first(I);
    int cont = 0;

    printf("\n=====================================\n");
    printf("Cantidad de productos: %d\n", I->product.stock);
    while(actual != inv_header(I))
    {
        printf("[%d] ", cont);
        prod_print(actual->product);
        cont++;
        actual = inv_forward(actual);
    }
}

//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================
// Devuelve el estado del inventario
// Retorna 1 si el inventario está vacío y 0 en caso contrario.
int inv_is_empty(Inventory I)
{
    if (I == NULL || I->product.stock == 0)
    {
        return 1;
    }
    /* Caso contrario */
    return 0;
}

// Devuelve si el elemento indicado es el último del inventario
int inv_is_last(InventoryElement Position, Inventory I)
{
    if (I != NULL && Position != NULL && Position != inv_header(I) && Position->next == inv_header(I))
    {
        return 1;
    }
    return 0;
}

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================
// Busca un producto por su nombre en el inventario
Product* inv_find_by_name(char* name, Inventory I)
{
    if (name == NULL || inv_is_empty(I))
    {
        /* Por seguridad pasarlo a string */
        if (name == NULL) name = "NULO";
        printf("Error: No se encontró en inventario %s\n", name);
        return NULL;
    }
    else
    {
        InventoryElement avance = inv_first(I);
        InventoryElement retroceso = inv_last(I);
        int i = 0;

        while (avance != inv_header(I) && retroceso != inv_header(I))
        {
            i++;
            if (avance == retroceso)
            {
                /* Compara el nombre del producto en la posicion con lo buscado */
                if (strcmp(avance->product.name, name) == 0)
                {
                    printf("Producto %s encontrado en %d iteraciones por los punteros\n", name, i);
                    return &(avance->product);
                }
                break;
            }
            else
            {
                /* Si no coinciden, avance tiene la prioridad */
                if (strcmp(avance->product.name, name) == 0)
                {
                    printf("Producto %s encontrado en %d iteraciones por el puntero de avance\n", name, i);
                    return &(avance->product);
                }

                /* Se revisa el retroceso */
                if (strcmp(retroceso->product.name, name) == 0)
                {
                    printf("Producto %s encontrado en %d iteraciones por el puntero de retroceso\n", name, i);
                    return &(retroceso->product);
                }

                /* Revisar si se cruzan los punteors, pues
                * Si estan al lado al moverlos se cruzarian
                * Por ende cortamos el ciclo while
                */
                if (inv_forward(avance) == retroceso)
                {
                    break;
                }

                /* Y los Movemos al centro */
                avance = inv_forward(avance);
                retroceso = inv_backward(retroceso);
            }
        }
        printf("Error: No se encontró en el inventario: %s\n", name);
        return NULL;
    }
}