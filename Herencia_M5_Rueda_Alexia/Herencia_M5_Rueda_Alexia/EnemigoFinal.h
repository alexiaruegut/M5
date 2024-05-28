#pragma once

#include "Personaje.h"

class EnemigoFinal : public Personaje {
private:
    int superAtaque1;
    int superAtaque2;

public:
    //constructores
    EnemigoFinal();
    EnemigoFinal(std::string nombre, int vida, int ataque, int x, int y, int superAtaque1, int superAtaque2);

    //getters
    int getSuperAtaque1();
    int getSuperAtaque2();

    //setters
    void setSuperAtaque1(int pSuperAtaque1);
    void setSuperAtaque2(int pSuperAtaque2);

    //métodos propios
    void atacar(Personaje& objetivo);
    void atacarSuper(Personaje& objetivo);
};

