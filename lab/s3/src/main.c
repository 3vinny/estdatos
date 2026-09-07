#include "headers.h"

void print_producto(Producto *producto);

int main(void)
{
    Producto producto[Datos];
    srand(time(NULL));
    crea_producto(producto);   
    escribe_csv(producto);
    print_producto(producto);
    return 0;
}

void crea_producto(Producto *producto)
{
    char *nombres[] = {"PlayStation", "iPhone", "Laptop", "Impresora", "XBOX"};

    for (int i=0; i<Datos; i++)
    {
        producto[i].nombre = nombres[i];
        producto[i].cantidad = rand()%100; // cantidad

        for (int j=0; j<Datos; j++)
        {
            producto[i].proveedor[j] = (char)(rand()%26 + 65);
        }
        producto[i].proveedor[5] = '\0'; // vacio
        printf("Precio para %s: ", producto[i].nombre);
        while (producto[i].precio <= 0){
            scanf("%d", &producto[i].precio);
            if (producto[i].precio <= 0) printf("Invalido! Intente de nuevo: ");
        }
        
        
    }
}

void escribe_csv(Producto *producto)
{
    FILE *archivo = fopen("datos.csv", "w");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo!!\n");
        exit(1);
    }

    fprintf(archivo, "Nombre,Cantidad,Proveedor,Precio\n");
    for (int i=0; i<Datos; i++)
    {
        fprintf(archivo, "%s,%d,%s,%d\n", producto[i].nombre, producto[i].cantidad, producto[i].proveedor, producto[i].precio);
    }
    fclose(archivo);
}

void print_producto(Producto *producto)
{
    printf("\n===============================\n");
    printf("Nombres | Cantidad | Proveedor | Precio\n");
    for (int i=0; i<Datos; i++)
    {
        printf("%s %d %s %d\n", producto[i].nombre, producto[i].cantidad, producto[i].proveedor, producto[i].precio);
    }
}