// fibonacci de la profe
#include <stdio.h>

int fibonacci_rec(int n);
int fibonacci_ite(int n);

int main()
{
    printf("fibonacci de 1 a 5\n");
    for (int i=1; i<=5; i++){
        printf("Fibonacci de %d=%d\n---------\n", i, fibonacci_rec(i));
    }
    
}

// fibonacci recursivo
int fibonacci_rec(int n)
{
	if (n<=1) {
        printf("retorno fib=%d\n", n);
        return n;
    }
    printf("Calculando termino %d\n", n);
    int fib_ant = fibonacci_rec(n-1);
    int fib_antant = fibonacci_rec(n-2);
    printf("Fib %d = %d+%d\n", n, fib_ant, fib_antant);
	return fib_ant + fib_antant;
}

int fibonacci_ite(int n)
{
    int anterior=0;
    int actual=1;
    int siguiente;

    if(n==0) return 0;

    for (int = 1; i<n; i++)
    {
        siguiente = anterior+actual;
        anterior=actual;
        actual=siguiente;
    }
    return actual;
}