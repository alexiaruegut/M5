#include "Dog.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// se incializa el constructor con unos valores predeterminados
Dog::Dog() : velocidad(0), distanciaRecorrida(0), chuches(1) {

}

// permite inicializar la clase
Dog::Dog(string pNombreCorredor, int pVelocidad, int pDistanciaRecorrida, int pChuches) {
    nombreCorredor = pNombreCorredor;
    velocidad = pVelocidad;
    distanciaRecorrida = pDistanciaRecorrida;
    chuches = pChuches;
}



// GETTERS

// nombre del perro
string Dog::getNombre() {
    return nombreCorredor;
}

// velocidad del perro
int Dog::getVelocidad() {
    return velocidad;
}

// distancia recorrida por el perro
int Dog::getDistanciaRecorrida() {
    return distanciaRecorrida;
}

// cantidad de chuches que tiene el perro
int Dog::getChuches() {
    return chuches;
}



// SETTERS

// nombre del perro
void Dog::setNombre(string pNombreCorredor) {
    nombreCorredor = pNombreCorredor;
}

// velocidad del perro
void Dog::setVelocidad(int pVelocidad) {
    velocidad = pVelocidad;
}

// cantidad de chuches que tiene el perro
void Dog::setChuches(int pChuches) {
    chuches = pChuches;
}





// otros

// lanzamiento del dado para obtener un num del 1 al 6
void Dog::lanzarDado() {
    int puntos = rand() % 6 + 1; // num aleatorio entre el 1 y el 6
    velocidad += puntos; // velocidad = velocidad + puntos
    cout << nombreCorredor << " ha obtenido " << puntos << " en el dado.\n";
}

// nitro
void Dog::usarChuche() {
    if (chuches > 0) { // solo se tiene una chuche en toda la partida
        int resultado = rand() % 2; // 50/50 posibilidades, num aleatorio entre el 0 y el 1

        if (resultado == 0) {
            velocidad /= 2; // se reduce la velocidad a la mitad
            cout << "\nLa chuche no le ha sentado bien a " << nombreCorredor << "! Su velocidad se ha reducido a la mitad.\n";
        }
        else {
            velocidad *= 2; // se duplica la velocidad
            cout << "\n" << nombreCorredor << " se ha vuelto loco con la chuche! Su velocidad se ha duplicado.\n";
        }
        chuches--; // si se usa la chuche, se resta una para q la cantidad sea 0y no se pueda volver a usar
    }
}

// distancia recorridad
void Dog::calcularDistancia() {
    distanciaRecorrida += velocidad * 100; // distancia = distancia + velocidad * 100
}
