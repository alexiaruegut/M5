#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m" 

Juego::Juego() : heroe("Nova", 110, 15, 0, 0) { //se le asigna al héroe 110 de vida, 15 de ataque y la posición inicial 0 0
    srand(time(0));
    inicializarTablero();
    colocarPersonajes();
}

void Juego::inicializarTablero() {
    for (int i = 0; i < SIZE; ++i) { //un bucle que incializa el tablero, con 10 de alto y ancho
        for (int j = 0; j < SIZE; ++j) {
            tablero[i][j] = ' ';
        }
    }

    //la salida estará en una posición random del tablero
    salidaX = rand() % SIZE;
    salidaY = rand() % SIZE;
    tablero[salidaX][salidaY] = 'S';
}

void Juego::mostrarHistoria() { //lore
    std::cout << CYAN << "En un rincón remoto del vasto universo, Nora, una valiente astronauta ha quedado varada en su nave tras un desafortunado accidente.\nPerdida en el espacio profundo, rodeada por la inmensidad y el misterio de las estrellas, su único objetivo es regresar a su planeta natal, un lugar de paz y esperanza al que anhela volver.\nSin embargo, su viaje estará plagado de peligros y desafíos que pondrán a prueba su valentía y determinación.\n";
    std::cout << "\nEl jugador deberá guiar a Nova a través de este enigmático mapa estelar. A simple vista, el mapa parece un cielo tranquilo y pacífico, con estrellas brillantes en todas direcciones.\nSin embargo, detrás de esta aparente calma se ocultan los enemigos y el camino a la salvación. Los enemigos y el portal de salida están ocultos, lo que obliga al jugador a explorar cada rincón del mapa. Cada movimiento podría llevar a Nova más cerca de su hogar o a un enfrentamiento mortal con los alienígenas.\n" << RESET;
}

void Juego::colocarPersonajes() {
    //posición 0 0 para que el héroe aparezca en la esquina superior izquierda
    heroe.setPosicionX(0);
    heroe.setPosicionY(0);
    tablero[0][0] = 'H';

    //5 enemigos en posiciones random del tablero
    for (int i = 0; i < 5; ++i) {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (tablero[x][y] != ' ');
        enemigos[i] = Personaje("Alien", 55, 9, x, y); //se le asigna a los enemigos normales 55 de vida, 9 de ataque y la posición se pilla del random
        tablero[x][y] = 'E';
    }

    //un enemigo final en posición random
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (tablero[x][y] != ' ');
    enemigoFinal = EnemigoFinal("Alien Supremo", 140, 10, x, y, 17, 20); //se le asigna al boss 140 de vida, 10 de ataque normal, 17 y 20 para los dos super ataques y la posición se pilla del random
    tablero[x][y] = 'B';
}

void Juego::moverHeroe(int pX, int pY) {
    int nuevaX = heroe.getPosicionX() + pX;
    int nuevaY = heroe.getPosicionY() + pY;

    if (nuevaX < 0 || nuevaX >= SIZE || nuevaY < 0 || nuevaY >= SIZE) { //el héroe solo podrá moverse si está dentro del tamaño 10x10 del tablero, si quiere ir fuera le saldrá un mensaje de error
        std::cout << "Ese movimiento es inválido, muévete dentro del tablero.\n";
        return;
    }

    char celda = tablero[nuevaX][nuevaY]; //la nueva posicion X e Y del héroe

    if (celda == 'E') { //'E' equivale a enemigo, cuando el héroe acaba en una casilla con una 'E', se inicia un combate
        for (int i = 0; i < 5; ++i) {
            if (enemigos[i].getPosicionX() == nuevaX && enemigos[i].getPosicionY() == nuevaY) { //se busca al enemigo que está en la misma posición que el héroe
                batalla(enemigos[i]);
            }
        }
    }
    else if (celda == 'B') { //'B' equivale a boss, cuando el héroe acaba en una casilla con una 'B', se inicia un combate
        batalla(enemigoFinal);
    }
    else if (celda == 'S') { //si se encuentra la salida, se gana el juego
        std::cout << GREEN << u8"\n🌍 ¡Felicidades, Capitán! Gracias a tu astucia y valentía, Nova ha logrado regresar sana y salva a su amado planeta natal. La gente de su hogar la recibe con alegría y gratitud, celebrando su regreso triunfante después de una larga y ardua odisea por el espacio. \nLa aventura de Nova puede haber llegado a su fin, pero su legado vivirá en las estrellas para siempre. ¡Has completado tu misión con éxito y demostrado ser un verdadero héroe del cosmos! ¡Bien hecho! 🌍" << RESET;
        exit(0);
    }

    tablero[heroe.getPosicionX()][heroe.getPosicionY()] = ' '; //para borrar el emoji del heroe en su posición anterior
    heroe.setPosicionX(nuevaX);
    heroe.setPosicionY(nuevaY); //su nueva posición
    tablero[nuevaX][nuevaY] = 'H'; //lo marco como 'H' y luego en mostrarTablero() lo cambio al emoji
}

void Juego::batalla(Personaje& enemigo) { //enemigo normal
    std::cout << u8"\n👽 Te has encontrado con un alien, lucha por sobrevivir! 👽\n";
    std::cout << "\nEstado inicial:\n";
    std::cout << heroe.getNombre() << " - Vida: " << heroe.getVida() << "\n";
    std::cout << enemigo.getNombre() << " - Vida: " << enemigo.getVida() << "\n";

    while (heroe.getVida() > 0 && enemigo.getVida() > 0) {
        heroe.atacar(enemigo);
        if (enemigo.getVida() > 0) {
            enemigo.atacar(heroe);
        }
    }

    if (enemigo.getVida() <= 0 && heroe.getVida() > 0) { //ganas
        std::cout << CYAN << "\nHas derrotado al alien!\n" << RESET;
        std::cout << "\nEstado final:\n";
        std::cout << heroe.getNombre() << " - Vida: " << heroe.getVida() << "\n";
    }

    if (heroe.getVida() <= 0 && enemigo.getVida() > 0) { //pierdes
        std::cout << RED << "\nLa valiente Nova luchó con coraje, pero la fuerza del enemigo demostró ser demasiado grande. \nSu nave yace destrozada en la oscuridad del espacio, mientras que su espíritu persiste como una chispa de esperanza en el vasto universo. Aunque esta batalla haya sido perdida, la guerra aún no ha terminado. ¡Reanuda tu viaje y guía a Nova hacia la victoria!\n" << RESET;
        exit(0);
    }
}

void Juego::batalla(EnemigoFinal& enemigoFinal) { //boss
    std::cout << u8"\n👾 Te has encontrado con el Alien Supremo, prepárate para luchar! 👾\n";
    std::cout << "\nEstado inicial:\n";
    std::cout << heroe.getNombre() << " - Vida: " << heroe.getVida() << "\n";
    std::cout << enemigoFinal.getNombre() << " - Vida: " << enemigoFinal.getVida() << "\n";

    while (heroe.getVida() > 0 && enemigoFinal.getVida() > 0) {
        //ataque héroe -> alien
        heroe.atacar(enemigoFinal);

        //ataque alien -> héroe
        int opcionAtaque = rand() % 3; //si sale 0, usa ataque normal, si sale 1 usa alguno de los dos super ataques y si sale 2 el alien falla su ataque
        if (opcionAtaque == 0) {
            enemigoFinal.atacar(heroe); //normal
        }
        else if (opcionAtaque == 1) {
            enemigoFinal.atacarSuper(heroe); //super ataque
        }
        else {
            std::cout << ""; //el alien falla su ataque
        }
    }

    if (heroe.getVida() > 0 && enemigoFinal.getVida() <= 0) { //ganas
        std::cout << CYAN << "\nHas derrotado al Alien Supremo!\n" << RESET;
        heroe.setVida(110); //se restaura la vida del usuario como recompensa por ganar
        std::cout << "\nTu vida ha sido restaurada. Buena suerte encontrando la salida!\n";
    }
    else if (heroe.getVida() <= 0 && enemigoFinal.getVida() > 0) { //pierdes
        std::cout << RED << "\nLa batalla fue épica, pero lamentablemente, Nova ha sido superada por el increíble poder del Alien Supremo.\nSu valentía y determinación quedarán grabadas en la historia, pero su viaje llega a un trágico final en el frío abismo del espacio.Aunque su misión haya fracasado, su espíritu perseverará en las estrellas para siempre.¡Inténtalo de nuevo y lleva a Nova hacia la victoria!\n" << RESET;
        exit(0);
    }
}

void Juego::mostrarTablero() {
    std::cout << "\n";

    int espaciosCentrados = (100 - SIZE) / 2; //supongo un ancho de consola de 100 caracteres

    //bucle para imprimir los espacios de la izquierda
    for (int i = 0; i < espaciosCentrados; ++i) {
        std::cout << " ";
    }

    //bucle para dibujar el tablero
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (tablero[i][j] == 'H') {
                std::cout << u8"🚀 "; //héroe
            }
            else if (tablero[i][j] == 'E') {
                std::cout << YELLOW << u8"⭐ " << RESET; //enemigo
            }
            else if (tablero[i][j] == 'B') {
                std::cout << YELLOW << u8"⭐ " << RESET; //enemigo final
            }
            else if (tablero[i][j] == 'S') {
                std::cout << YELLOW << u8"⭐ " << RESET; //salida
            }
            else {
                std::cout << YELLOW << u8"⭐ " << RESET; //casillas vacías
            }
        }
        std::cout << '\n';

        //bucle para imprimir los espacios de la derecha
        for (int k = 0; k < espaciosCentrados; ++k) {
            std::cout << " ";
        }
    }
}

void Juego::jugar() {
    mostrarHistoria();

    char movimiento;
    do {
        mostrarTablero();
        std::cout << "Movimiento (WASD): ";
        std::cin >> movimiento;

        movimiento = std::toupper(movimiento); //para pasar todo a mayúsuculas

        switch (movimiento) {
        case 'W': moverHeroe(-1, 0); break; //al ser un array, para ir hacía arriba es necesario moverse una posición hacía atrás (x = -1)
        case 'A': moverHeroe(0, -1); break; //mover a la izq es una columna anterior y = -1
        case 'S': moverHeroe(1, 0); break; //mover a la der es una columna posterior y = 1
        case 'D': moverHeroe(0, 1); break; //mover hacía abajo es una fila posterior del array x = 1
        default: std::cout << "\nMovimiento inválido, usa WASD.\n"; break;
        }
    } while (heroe.getVida() > 0 && !(heroe.getPosicionX() == salidaX && heroe.getPosicionY() == salidaY));
}
