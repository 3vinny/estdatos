void jugarPartida(Pila* mazo, Pila* tesoroMilton, Pila* tesoroLuis, Cola* descarte) {
    int turno = 1; // 1: Milton, 2: Luis

    while (!estaVaciaPila(mazo)) {
        int carta = pop(mazo);
        int turnoExtra = 0;

        Pila* miTesoro = (turno == 1) ? tesoroMilton : tesoroLuis;
        Pila* rivalTesoro = (turno == 1) ? tesoroLuis : tesoroMilton;

        // Regla 1: Multiplo de 15
        if (carta % 15 == 0) {
            push(miTesoro, carta);
            turno = (turno == 1) ? 2 : 1; 
        }
        // Regla 2: Multiplo de 3
        else if (carta % 3 == 0) {
            push(miTesoro, carta);
        }
        // Regla 3: Multiplo de 5
        else if (carta % 5 == 0) {
            if (!estaVaciaPila(rivalTesoro)) {
                int cartaRobada = pop(miTesoro);
                push(rivalTesoro, cartaRobada);
            }
            enqueue(descarte, carta);
        }
        // Regla 4: Multiplo de 7
        else if (carta % 7 == 0) {
            if (!estaVaciaCola(descarte)) {
                int cartaFondo = dequeue(descarte);
                push(miTesoro, cartaFondo);
            }
        }
        // Regla 5: Cualquier otro caso
        else {
            push(descarte, carta);
        }

        // Cambio regular de turno
        if (turnoExtra == 0) {
            turno = (turno == 1) ? 2 : 1;
        }
    }

    int sumaMilton = sumarElementos(tesoroMilton);
    int sumaLuis = sumarElementos(tesoroLuis);

    if (sumaMilton >= sumaLuis) {
        printf("Gana Milton\n");
    } else {
        printf("Gana Luis\n");
    }
}