#include "Personaje.h"

//constructores
Personaje::Personaje() {

}

Personaje::Personaje(std::string pNombre, int pVida, int pAtaque, int pX, int pY) {
    nombre = pNombre;
    vida = pVida;
    ataque = pAtaque;
    posicionX = pX;
    posicionY = pY;
}

//getters
std::string Personaje::getNombre() {
    return nombre;
}

int Personaje::getVida() {
    return vida;
}

int Personaje::getAtaque() {
    return ataque;
}

int Personaje::getPosicionX() {
    return posicionX;
}

int Personaje::getPosicionY() {
    return posicionY;
}

//setters
void Personaje::setVida(int nuevaVida) {
    vida = nuevaVida;
}

void Personaje::setAtaque(int nuevoAtaque) {
    ataque = nuevoAtaque;
}

void Personaje::setPosicionX(int x) {
    posicionX = x;
}

void Personaje::setPosicionY(int y) {
    posicionY = y;
}

//métodos propios
void Personaje::atacar(Personaje& objetivo) {
    int nuevaVida = objetivo.getVida() - ataque; //se le resta al enemigo el daño causado a su vida
    objetivo.setVida(nuevaVida); //se establece su nueva vida
}
