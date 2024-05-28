#pragma once

#include <string>

class Personaje {
private:
    std::string nombre;
    int vida;
    int ataque;
    int posicionX;
    int posicionY;

public:
    //constructor
    Personaje();
    Personaje(std::string nombre, int vida, int ataque, int x, int y);

    //getters
    std::string getNombre();
    int getVida();
    int getAtaque();
    int getPosicionX();
    int getPosicionY();

    //setters
    void setVida(int pVida);
    void setAtaque(int pAtaque);
    void setPosicionX(int pX);
    void setPosicionY(int pY);

    //métodos propios
    void atacar(Personaje& pObjetivo);
};

