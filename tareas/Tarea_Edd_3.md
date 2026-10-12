# Tarea 3 - Estructuras de datos
En carpeta lab/s6 se encuentra el esqueleto modificado y documentado !

**[Clic acá!](https://github.com/3vinny/estdatos/tree/main/lab/s6)**

## inv_find_by_name
```c
/**
 * @brief Busca un producto por su nombre en el inventario
 *
 * La búsqueda revisa ambos extremos del inventario al mismo tiempo: un
 * puntero avanza desde el primer elemento y otro retrocede desde el último,
 * hasta que se encuentra el producto o los punteros se encuentran o se cruzan.
 * Cada vuelta en la que se compara el elemento de cada extremo cuenta como una
 * iteración. Si en una misma iteración coinciden ambos extremos, se prefiere
 * el puntero de avance.
 *
 * Con una cantidad impar de elementos los punteros terminan sobre el elemento
 * central, que también se debe comparar (contando una iteración más). Un
 * inventario vacío no contiene ningún producto.
 *
 * Retorna un puntero al producto encontrado (no una copia) o un puntero nulo
 * si no se encuentra. Cuando se encuentra, se imprime en cuántas iteraciones
 * se encontró y qué puntero lo encontró (el de avance, el de retroceso, o
 * ambos si estaban sobre el elemento central). Cuando no se encuentra, se
 * imprime un aviso indicando el nombre buscado.
 *
 * @param name Nombre del producto a buscar
 * @param I Referencia al inventario
 * @return Puntero al Producto encontrado o Puntero NULL si no se encuentra
 */
Product* inv_find_by_name(char* name, Inventory I);
```