
/*
 * Visualizador interactivo de Algoritmos (EDD) con trazado de codigo y memoria.
 */

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELAY_MS	1100
#define ARR_SZ		6

static const int orig_arr[ARR_SZ] = { 9, 2, 3, 1, 20, 17 };

static void	 draw_code(WINDOW *w, const char *title, const char **lines,
		    int nlines, int active_line);
static void	 draw_arr(WINDOW *w, const int *arr, int n, int p1, int p2,
		    int p3, const char *l1, const char *l2, const char *l3);
static void	 draw_trace(WINDOW *w, const char *vars, const char *action);
static void	 sync_view(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l,
		    const char *title, const char **code, int nlines,
		    int act_line, const int *arr, int p1, int p2, int p3,
		    const char *l1, const char *l2, const char *l3,
		    const char *vars, const char *act);
static void	 bsort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l);
static void	 isort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l);
static void	 ssort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l);
static void	 bsearch_vis(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l, int target);
static void	 show_menu(WINDOW *w);

static void
draw_code(WINDOW *w, const char *title, const char **lines, int nlines,
    int active_line)
{
	int	 i;

	werase(w);
	box(w, 0, 0);
	wattron(w, A_BOLD);
	mvwprintw(w, 1, 2, "[ %s ]", title);
	wattroff(w, A_BOLD);
	mvwprintw(w, 2, 1, "--------------------------------------");

	for (i = 0; i < nlines; i++) {
		if (i == active_line) {
			wattron(w, COLOR_PAIR(1) | A_REVERSE | A_BOLD);
			mvwprintw(w, 4 + i, 2, "-> %-32s", lines[i]);
			wattroff(w, COLOR_PAIR(1) | A_REVERSE | A_BOLD);
		} else {
			mvwprintw(w, 4 + i, 2, "   %-32s", lines[i]);
		}
	}
	wrefresh(w);
}

static void
draw_arr(WINDOW *w, const int *arr, int n, int p1, int p2, int p3,
    const char *l1, const char *l2, const char *l3)
{
	int	 i, x;

	werase(w);
	box(w, 0, 0);
	wattron(w, A_BOLD);
	mvwprintw(w, 1, 2, "[ ESTADO DEL ARREGLO ]");
	wattroff(w, A_BOLD);
	mvwprintw(w, 2, 1, "---------------------------------------");

	for (i = 0; i < n; i++) {
		x = 3 + (i * 6);
		if (i == p1 || i == p2 || i == p3) {
			wattron(w, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(w, 4, x, "[%2d]", arr[i]);
			wattroff(w, COLOR_PAIR(1) | A_BOLD);
		} else {
			mvwprintw(w, 4, x, " %2d ", arr[i]);
		}
		mvwprintw(w, 5, x, " i=%d", i);

		/* Punteros o etiquetas de indice */
		if (i == p1 && l1 != NULL)
			mvwprintw(w, 7, x, "%s", l1);
		if (i == p2 && l2 != NULL)
			mvwprintw(w, 7, x, "%s", l2);
		if (i == p3 && l3 != NULL)
			mvwprintw(w, 8, x, "%s", l3);
	}
	wrefresh(w);
}

static void
draw_trace(WINDOW *w, const char *vars, const char *action)
{
	werase(w);
	box(w, 0, 0);
	wattron(w, A_BOLD);
	mvwprintw(w, 1, 2, "[ TRAZA DE EJECUCION ]");
	wattroff(w, A_BOLD);
	mvwprintw(w, 2, 1, "---------------------------------------");

	mvwprintw(w, 4, 2, "Variables:");
	wattron(w, A_BOLD);
	mvwprintw(w, 5, 4, "%-33s", vars ? vars : "-");
	wattroff(w, A_BOLD);

	mvwprintw(w, 7, 2, "Paso actual:");
	wattron(w, COLOR_PAIR(2));
	mvwprintw(w, 8, 4, "%-33s", action ? action : "-");
	wattroff(w, COLOR_PAIR(2));

	wrefresh(w);
}

static void
sync_view(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l, const char *title,
    const char **code, int nlines, int act_line, const int *arr, int p1,
    int p2, int p3, const char *l1, const char *l2, const char *l3,
    const char *vars, const char *act)
{
	draw_code(w_c, title, code, nlines, act_line);
	draw_arr(w_a, arr, ARR_SZ, p1, p2, p3, l1, l2, l3);
	draw_trace(w_l, vars, act);
	napms(DELAY_MS);
}

static void
bsort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l)
{
	static const char *src[] = {
		"for (i = 0; i < n - 1; i++)",
		"    swapped = 0;",
		"    for (j = 0; j < n-i-1; j++)",
		"        if (a[j] > a[j + 1])",
		"            swap(&a[j], &a[j+1]);",
		"            swapped = 1;",
		"    if (swapped == 0) break;"
	};
	char	 v[64];
	int	 a[ARR_SZ];
	int	 i, j, temp, swapped;

	memcpy(a, orig_arr, sizeof(a));

	for (i = 0; i < ARR_SZ - 1; i++) {
		(void)snprintf(v, sizeof(v), "i = %d", i);
		sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 0, a,
		    -1, -1, -1, NULL, NULL, NULL, v, "Inicio de pasada exterior");

		swapped = 0;
		(void)snprintf(v, sizeof(v), "i = %d | swapped = 0", i);
		sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 1, a,
		    -1, -1, -1, NULL, NULL, NULL, v, "Flag reiniciado");

		for (j = 0; j < ARR_SZ - i - 1; j++) {
			(void)snprintf(v, sizeof(v), "i=%d, j=%d, n-i-1=%d",
			    i, j, ARR_SZ - i - 1);
			sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 2, a,
			    j, j + 1, -1, "^j", "^j+1", NULL, v,
			    "Avanza indice adyacente");

			(void)snprintf(v, sizeof(v), "a[%d]=%d > a[%d]=%d ?",
			    j, a[j], j + 1, a[j + 1]);
			sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 3, a,
			    j, j + 1, -1, "^j", "^j+1", NULL, v,
			    "Comparando adyacentes");

			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				swapped = 1;

				(void)snprintf(v, sizeof(v), "swap: %d <-> %d",
				    a[j + 1], a[j]);
				sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 4,
				    a, j, j + 1, -1, "^j", "^j+1", NULL, v,
				    "Intercambio efectuado");

				(void)snprintf(v, sizeof(v), "swapped = 1");
				sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 5,
				    a, j, j + 1, -1, "^j", "^j+1", NULL, v,
				    "Marca flag activa");
			}
		}

		(void)snprintf(v, sizeof(v), "swapped = %d", swapped);
		sync_view(w_c, w_a, w_l, "Bubble Sort", src, 7, 6, a,
		    -1, -1, -1, NULL, NULL, NULL, v, "Verificando corte");
		if (swapped == 0)
			break;
	}

	draw_trace(w_l, "Completado", "Presione una tecla para volver");
	wgetch(w_l);
}

static void
isort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l)
{
	static const char *src[] = {
		"for (i = 1; i < n; i++)",
		"    key = a[i];",
		"    j = i - 1;",
		"    while (j >= 0 && a[j] > key)",
		"        a[j + 1] = a[j];",
		"        j--;",
		"    a[j + 1] = key;"
	};
	char	 v[64];
	int	 a[ARR_SZ];
	int	 i, j, key;

	memcpy(a, orig_arr, sizeof(a));

	for (i = 1; i < ARR_SZ; i++) {
		(void)snprintf(v, sizeof(v), "i = %d", i);
		sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 0, a,
		    i, -1, -1, "^i", NULL, NULL, v, "Siguiente elemento no ordenado");

		key = a[i];
		(void)snprintf(v, sizeof(v), "key = %d (a[%d])", key, i);
		sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 1, a,
		    i, -1, -1, "key", NULL, NULL, v, "Guardando elemento clave");

		j = i - 1;
		(void)snprintf(v, sizeof(v), "j = %d, key = %d", j, key);
		sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 2, a,
		    j, i, -1, "^j", "key", NULL, v, "Inicializando j = i - 1");

		while (j >= 0 && a[j] > key) {
			(void)snprintf(v, sizeof(v), "a[%d]=%d > key=%d", j, a[j], key);
			sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 3, a,
			    j, -1, -1, "^j", NULL, NULL, v, "Condicion while verdadera");

			a[j + 1] = a[j];
			(void)snprintf(v, sizeof(v), "a[%d] = a[%d] (%d)", j + 1, j, a[j]);
			sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 4, a,
			    j + 1, j, -1, "dest", "orig", NULL, v, "Desplazando mayor a derecha");

			j--;
			(void)snprintf(v, sizeof(v), "j = %d", j);
			sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 5, a,
			    j >= 0 ? j : -1, -1, -1, "^j", NULL, NULL, v, "Decrementando j");
		}

		a[j + 1] = key;
		(void)snprintf(v, sizeof(v), "a[%d] = key (%d)", j + 1, key);
		sync_view(w_c, w_a, w_l, "Insertion Sort", src, 7, 6, a,
		    j + 1, -1, -1, "^ins", NULL, NULL, v, "Insercion en posicion final");
	}

	draw_trace(w_l, "Completado", "Presione una tecla para volver");
	wgetch(w_l);
}

static void
ssort(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l)
{
	static const char *src[] = {
		"for (i = 0; i < n - 1; i++)",
		"    min_idx = i;",
		"    for (j = i + 1; j < n; j++)",
		"        if (a[j] < a[min_idx])",
		"            min_idx = j;",
		"    if (min_idx != i)",
		"        swap(&a[i], &a[min_idx]);"
	};
	char	 v[64];
	int	 a[ARR_SZ];
	int	 i, j, min_idx, temp;

	memcpy(a, orig_arr, sizeof(a));

	for (i = 0; i < ARR_SZ - 1; i++) {
		(void)snprintf(v, sizeof(v), "i = %d", i);
		sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 0, a,
		    i, -1, -1, "^i", NULL, NULL, v, "Inicio de pasada");

		min_idx = i;
		(void)snprintf(v, sizeof(v), "min_idx = %d (val=%d)", min_idx, a[min_idx]);
		sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 1, a,
		    min_idx, -1, -1, "^min", NULL, NULL, v, "Asume i como minimo");

		for (j = i + 1; j < ARR_SZ; j++) {
			(void)snprintf(v, sizeof(v), "j = %d, min_idx = %d", j, min_idx);
			sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 2, a,
			    j, min_idx, -1, "^j", "^min", NULL, v, "Explorando resto");

			(void)snprintf(v, sizeof(v), "a[%d]=%d < a[%d]=%d ?",
			    j, a[j], min_idx, a[min_idx]);
			sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 3, a,
			    j, min_idx, -1, "^j", "^min", NULL, v, "Comparando con minimo");

			if (a[j] < a[min_idx]) {
				min_idx = j;
				(void)snprintf(v, sizeof(v), "Nuevo min_idx = %d", min_idx);
				sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 4, a,
				    min_idx, -1, -1, "^min", NULL, NULL, v, "Actualizando minimo");
			}
		}

		(void)snprintf(v, sizeof(v), "min_idx(%d) != i(%d)", min_idx, i);
		sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 5, a,
		    i, min_idx, -1, "^i", "^min", NULL, v, "Verifica si requiere swap");

		if (min_idx != i) {
			temp = a[i];
			a[i] = a[min_idx];
			a[min_idx] = temp;
			(void)snprintf(v, sizeof(v), "swap: %d <-> %d", a[i], a[min_idx]);
			sync_view(w_c, w_a, w_l, "Selection Sort", src, 7, 6, a,
			    i, min_idx, -1, "^i", "^min", NULL, v, "Intercambio colocado");
		}
	}

	draw_trace(w_l, "Completado", "Presione una tecla para volver");
	wgetch(w_l);
}

static void
bsearch_vis(WINDOW *w_c, WINDOW *w_a, WINDOW *w_l, int target)
{
	static const char *src[] = {
		"izq = 0, der = n - 1;",
		"while (izq <= der)",
		"    med = izq + (der - izq)/2;",
		"    if (a[med] == x) return med;",
		"    if (a[med] < x) izq = med + 1;",
		"    else der = med - 1;",
		"return -1;"
	};
	char	 v[64];
	int	 a[ARR_SZ] = { 1, 2, 3, 9, 17, 20 };
	int	 izq, der, med;

	izq = 0;
	der = ARR_SZ - 1;

	(void)snprintf(v, sizeof(v), "izq = %d, der = %d", izq, der);
	sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 0, a,
	    izq, der, -1, "^izq", "^der", NULL, v, "Limites iniciales");

	while (izq <= der) {
		(void)snprintf(v, sizeof(v), "izq(%d) <= der(%d)", izq, der);
		sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 1, a,
		    izq, der, -1, "^izq", "^der", NULL, v, "Rango valido");

		med = izq + (der - izq) / 2;
		(void)snprintf(v, sizeof(v), "med = %d (a[%d] = %d)", med, med, a[med]);
		sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 2, a,
		    izq, der, med, "^izq", "^der", "^med", v, "Calculo punto medio");

		(void)snprintf(v, sizeof(v), "a[%d]=%d == %d ?", med, a[med], target);
		sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 3, a,
		    izq, der, med, "^izq", "^der", "^med", v, "Evaluando coincidencia");

		if (a[med] == target) {
			(void)snprintf(v, sizeof(v), "Encontrado en indice %d", med);
			sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 3, a,
			    med, -1, -1, "^OK", NULL, NULL, v, "Elemento hallado");
			draw_trace(w_l, "Terminado con exito", "Presione tecla para volver");
			wgetch(w_l);
			return;
		}

		if (a[med] < target) {
			(void)snprintf(v, sizeof(v), "%d < %d -> izq = %d",
			    a[med], target, med + 1);
			sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 4, a,
			    izq, der, med, "^izq", "^der", "^med", v, "Descartar mitad izq");
			izq = med + 1;
		} else {
			(void)snprintf(v, sizeof(v), "%d > %d -> der = %d",
			    a[med], target, med - 1);
			sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 5, a,
			    izq, der, med, "^izq", "^der", "^med", v, "Descartar mitad der");
			der = med - 1;
		}
	}

	sync_view(w_c, w_a, w_l, "Busqueda Binaria", src, 7, 6, a,
	    -1, -1, -1, NULL, NULL, NULL, "izq > der", "No encontrado (return -1)");
	draw_trace(w_l, "No encontrado", "Presione tecla para volver");
	wgetch(w_l);
}

static void
show_menu(WINDOW *w)
{
	werase(w);
	box(w, 0, 0);
	wattron(w, A_BOLD);
	mvwprintw(w, 1, 2, "VISUALIZADOR ALGORITMICO EDD");
	wattroff(w, A_BOLD);
	mvwprintw(w, 2, 1, "--------------------------------------------------");

	mvwprintw(w, 4, 3, "1. Bubble Sort (Burbuja optimizada)");
	mvwprintw(w, 5, 3, "2. Insertion Sort (Insercion)");
	mvwprintw(w, 6, 3, "3. Selection Sort (Seleccion)");
	mvwprintw(w, 7, 3, "4. Busqueda Binaria (target = 17)");
	mvwprintw(w, 9, 3, "q. Salir");
	mvwprintw(w, 11, 3, "Opcion: ");
	wrefresh(w);
}

int
main(void)
{
	WINDOW	*w_code, *w_arr, *w_log, *w_menu;
	int	 c, run;

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	if (has_colors()) {
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	}

	if (LINES < 24 || COLS < 80) {
		endwin();
		(void)fprintf(stderr, "Error: Terminal requiere al menos 80x24.\n");
		return (1);
	}

	/* Panel izquierdo: Codigo fuente | Paneles derechos: Arreglo y Traza */
	w_code = newwin(22, 39, 1, 1);
	w_arr  = newwin(10, 39, 1, 40);
	w_log  = newwin(12, 39, 11, 40);
	w_menu = newwin(14, 52, 4, 14);

	run = 1;
	while (run) {
		show_menu(w_menu);
		c = wgetch(w_menu);
		switch (c) {
		case '1':
			bsort(w_code, w_arr, w_log);
			break;
		case '2':
			isort(w_code, w_arr, w_log);
			break;
		case '3':
			ssort(w_code, w_arr, w_log);
			break;
		case '4':
			bsearch_vis(w_code, w_arr, w_log, 17);
			break;
		case 'q':
		case 'Q':
			run = 0;
			break;
		default:
			break;
		}
	}

	delwin(w_code);
	delwin(w_arr);
	delwin(w_log);
	delwin(w_menu);
	endwin();

	return (0);
}
