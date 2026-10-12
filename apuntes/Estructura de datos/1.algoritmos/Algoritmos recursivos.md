Es aquel que se define en términos de si mismo
Es decir el algoritmo se llama a si mismo para resolver una versión más pequeña del mismo problema.

Todo algoritmo tiene dos partes fundamentales:
- **Caso base:** Condicion que detiene la recursion (cosas muy obvias)
- **Caso recursivo:** Llamada recursiva al mismo algoritmo que se acerca al caso base

La recursividad permite repetir un bloque de código sin la necesidad de un bucle.

Para resolver P(n), necesito resolver P(n-1), excepto que n ya sea tan chico que la respuesta sea obvia.

Usa "llamada recursiva"

Estructura basica algoritmo recursivo

# ¿Cómo funcionan las llamadas recursivas?
Tienen una particularidad: las llamadas quedarán en espera hasta que la llamada más profunda termine y retorne un resultado.
- Cada llamada es independiente: tiene sus propios parámetros y variables locales
- La llamada recursiva queda en pausa hasta recibir un resultado
- Al llegar el resultado la función se reanuda donde quedó
La llamada de afuera no continúa hasta que la de adentro haya terminado (se anidan)
Cada llamada en espera es apilada en la pila de llamada (call stack)

## EJemplo pila
![[Pasted image 20260821114539.png]]

# Comparacion iterativo-recursivo : factorial

- Algoritmo iterativo:
```c
	unsigned int factorial(unsigned int n) {
		int fact = 1, i;
		for (i=1; i<=n; i++) {
			fact = fact*i;
		}
		return fact;
	}
```
- Algoritmo recursivo:
```c
	unsigned int factorial(unsigned int n) {
		if (n==0) {
			return 1;
		}
		
		return n * factorial(n-1);
	}
```

# ¿Cuando usar algoritmos recursivos?
La recursión es útil cuando el problema:
	- Puede dividirse en problemas chicos
	- Tiene estructura jerárquica
	- Usa la estrategia de divide y vencerás
	
Algunos ejemplos de algoritmos recursivos eficientes:
	- Búsqueda binaria
	- Quicksort
## Ventajas
- Codigo más claro
- Expresa la estructura matemática
- Ideal para problemas de división
## Desventajas
- Puede **consumir mas memoria**
- Si no se diseña bien puede ser exponencial
- A veces puede ser **menos eficiente**
# Fibonacci
``fib(n) = fib(n-1) + fib(n-2)``
``fib(0) = 0; fib(1) = 1``

Es mucho mejor en iterativo  y es ineficiente en recursivo

Fibonacci recursivo (cuesta llegar a ~50 de lo fome que es)
```c
int fibonacci(int n)
{
	int (n<=1) 
	return n;
	return fibonacci(n-1) + fibonacci(n-2);
}
```
![[Pasted image 20260821121307.png|476]]