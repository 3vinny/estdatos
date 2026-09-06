#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Datos 5

typedef struct {
    char *nombre;
    int cantidad;
    char proveedor[6];
    int precio;
}Producto;

void crea_producto(Producto *producto);
void escribe_csv(Producto *producto);