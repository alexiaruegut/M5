#pragma once

#include <string>

using namespace std;

class Dog {
private:
    string nombreCorredor;
    int velocidad;
    int distanciaRecorrida;
    int chuches;

public:
    // constructor
    Dog();
    Dog(string pNombreCorredor, int pVelocidad = 0, int pDistanciaRecorrida = 0, int pChuches = 1);

    // getters
    std::string getNombre();
    int getVelocidad();
    int getDistanciaRecorrida();
    int getChuches();

    // getters
    void setNombre(string pNombreCorredor);
    void setVelocidad(int pVelocidad);
    void setChuches(int pChuches);

    // otros
    void lanzarDado();
    void usarChuche();
    void calcularDistancia();
};
