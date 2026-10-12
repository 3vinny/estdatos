Resuelve un problema repitiendo un bloque de instrucciones mediante un bucle
En cada paso avanza mientras una variable acumula el resultado
```c
int factorial(int n)
{
	int r = 1;
	for (int i=2; i<=n; i++) r = r*i;
	return r;
}
```

# Ejemplo factorial
```c
	unsigned int factorial(unsigned int n) {
		int fact = 1, i;
		for (i=1; i<=n; i++) {
			fact = fact*i;
		}
		return fact;
	}
```

# fibonacci en iterativo > recursivo
```c
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
```