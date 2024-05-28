#pragma once

#include "Personaje.h"
#include "EnemigoFinal.h"

class Juego {
private:
    int SIZE = 10;
    char tablero[10][10];
    Personaje heroe;
    Personaje enemigos[5];
    EnemigoFinal enemigoFinal;
    int salidaX, salidaY;

public:
    //constructores
    Juego();

    //métodos propios
    void inicializarTablero();
    void colocarPersonajes();
    void moverHeroe(int dx, int dy);
    void batalla(Personaje& enemigo);
    void batalla(EnemigoFinal& enemigoFinal);
    void jugar();
    void mostrarTablero();
    void mostrarHistoria();
};

