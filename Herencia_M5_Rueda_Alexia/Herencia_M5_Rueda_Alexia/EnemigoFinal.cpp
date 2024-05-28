#include "EnemigoFinal.h"
#include <cstdlib>

//constructores
EnemigoFinal::EnemigoFinal() : Personaje() {

}

EnemigoFinal::EnemigoFinal(std::string nombre,
    int vida,
    int ataque,
    int x,
    int y,
    int pSuperAtaque1,
    int pSuperAtaque2) : Personaje(nombre, vida, ataque, x, y) {
    superAtaque1 = pSuperAtaque1;
    superAtaque2 = pSuperAtaque2;
}

//getters
int EnemigoFinal::getSuperAtaque1() {
    return superAtaque1;
}

int EnemigoFinal::getSuperAtaque2() {
    return superAtaque2;
}

//setters
void EnemigoFinal::setSuperAtaque1(int pSuperAtaque1) {
    superAtaque1 = pSuperAtaque1;
}

void EnemigoFinal::setSuperAtaque2(int pSuperAtaque2) {
    superAtaque2 = pSuperAtaque2;
}

//métodos propios
void EnemigoFinal::atacar(Personaje& objetivo) {
    Personaje::atacar(objetivo); //ataque normal
}

void EnemigoFinal::atacarSuper(Personaje& objetivo) {
    int ataqueSeleccionado = rand() % 2 == 0 ? superAtaque1 : superAtaque2; //se elgirá de forma aleatoria cual de los dos super ataques usará el boss
    int nuevaVida = objetivo.getVida() - ataqueSeleccionado; //se le resta al héroe el daño causado a su vida
    objetivo.setVida(nuevaVida); //se establece su nueva vida
}
