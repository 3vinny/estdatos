-malloc
v = (int *) malloc(4 * sizeof(int));
    //casteo   // reservar memoria
    //cada 4 bytes un nuevo entero
    //crea un arreglo con el espacio de memoria que reserve
     necesario para guardar 4 enteros

-free

// lo contrario a malloc
// libera la memoria que reservé

*(v+1) es lo mismo que v[1]