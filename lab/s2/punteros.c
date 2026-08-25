// tarea de punteros edd semana 2 lab
#include <stdio.h>
#include <stdlib.h>
#define MAX 3

int main()
{
    int x = 7 , y = 20 , *m , *n , * k ;
    int * arr ;
    arr = ( int *) malloc ( MAX * sizeof ( int ) );

    m = & x ;
    n = m ;
    k = & y ;

    * m = 3;
    * n = * k ;
    *( arr ) = * m ;
    *( arr +1) = * k ;
    *( arr +2) = x + y ;
    n = &y;
    *n += 5;
    
    printf(" %d, %d, %d, %d, %d, %d", x, y, *arr, *( arr +1), *( arr +2), *m);
    return 0;
}