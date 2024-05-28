#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);

    Juego juego;
    juego.jugar();
    return 0;
}