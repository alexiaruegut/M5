#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int NUM_PALOS = 4;
const int NUM_CARTAS = 13;

// para inicializar la disponibilidad de las cartas
void inicializarDisponibilidad(int palos[NUM_PALOS][NUM_CARTAS]) {
    for (int palo = 0; palo < NUM_PALOS; ++palo) {
        for (int carta = 0; carta < NUM_CARTAS; ++carta) {
            palos[palo][carta] = 1; // si tienen un valor de 1, es que están disponibles
        }
    }
}

// para obtener el nombre de la carta
string obtenerNombreCarta(int repCartas) {
    return (repCartas == 0) ? "AS" : (repCartas >= 10) ? (repCartas == 10) ? "J" : (repCartas == 11) ? "Q" : "K" : to_string(repCartas + 1);
}


// para obtener el nombre del palo
string obtenerNombrePalo(int repPalo) {
    return (repPalo == 0) ? "Picas" : (repPalo == 1) ? "Diamantes" : (repPalo == 2) ? "Corazones" : (repPalo == 3) ? "Treboles" : "";
}

// para marcar la carta como no disponible
void marcarCartaNoDisponible(int palos[NUM_PALOS][NUM_CARTAS], int repPalo, int repCartas) {
    palos[repPalo][repCartas] = 0; // después de repartir cada carta se pasa su valor de 1 a 0 para que no pueda salir repetida
}

// para repartir carta al croupier
void repartirCartaCroupier(int palos[NUM_PALOS][NUM_CARTAS], int& totalCartasCroupier) {
    int repPalo, repCartas;

    // para obtener la carta
    do {
        repPalo = rand() % 4;
        repCartas = rand() % 13;
    } while (palos[repPalo][repCartas] != 1);

    // si sale As para el croupier
    if (repCartas == 0) {
        int valorAsCroupier = (totalCartasCroupier + 11 <= 21) ? 11 : 1;
        totalCartasCroupier += valorAsCroupier;
        cout << "El croupier ha obtenido un AS con valor " << valorAsCroupier << " de " << obtenerNombrePalo(repPalo) << "\n";
    }
    else {
        // si sale J, Q y K valen 10
        int valorCarta = (repCartas >= 10) ? 10 : repCartas + 1;
        totalCartasCroupier += valorCarta;
        cout << "El croupier ha obtenido una carta: " << obtenerNombreCarta(repCartas) << " de " << obtenerNombrePalo(repPalo) << "\n";
    }

    // para marcar la carta como no disponible
    marcarCartaNoDisponible(palos, repPalo, repCartas);

    cout << "Puntuacion del croupier: " << totalCartasCroupier << "\n\n";
}

// para repartir carta al jugador
void repartirCartaJugador(int palos[NUM_PALOS][NUM_CARTAS], int& totalCartasJugador) {
    int repPalo, repCartas;

    // para obtener la carta
    do {
        repPalo = rand() % 4;
        repCartas = rand() % 13;
    } while (palos[repPalo][repCartas] != 1);

    // si sale As para el jugador
    if (repCartas == 0) {
        cout << "Has obtenido un AS de " << obtenerNombrePalo(repPalo) << ". Quieres darle valor 1 u 11?: ";
        int valorAsJugador;
        do {
            cout << "Por favor, elige 1 u 11: ";
            cin >> valorAsJugador;
        } while (valorAsJugador != 1 && valorAsJugador != 11);

        totalCartasJugador += valorAsJugador;
    }
    else {
        // si sale J, Q y K valen 10
        int valorCarta = (repCartas >= 10) ? 10 : repCartas + 1;
        totalCartasJugador += valorCarta;
    }

    // para marcar la carta como no disponible
    marcarCartaNoDisponible(palos, repPalo, repCartas);

    cout << "Has obtenido una carta: " << obtenerNombreCarta(repCartas) << " de " << obtenerNombrePalo(repPalo) << "\n";
    cout << "Tu puntuacion actual es: " << totalCartasJugador << "\n\n";
}

int main() {
    srand(time(NULL));

    int palos[NUM_PALOS][NUM_CARTAS];
    inicializarDisponibilidad(palos);

    cout << "Bienvenido al Blackjack!\n\n";
    cout << "Reglas del Juego:\n";
    cout << "1. Gana quien tenga mas puntos sin pasar de 21.\n";
    cout << "2. La J, Q y K valen 10 puntos. El As vale 1 u 11.\n";
    cout << "3. Puedes decidir si quieres mas cartas ('s') o te plantas ('n').\n\n";
    cout << "Diviertete y buena suerte!\n\n";

    char respuestaIniciar;
    cout << "Quieres iniciar una partida? (s/n): ";
    cin >> respuestaIniciar;
    cout << "\n";

    while (respuestaIniciar != 's' && respuestaIniciar != 'n') {
        cout << "Por favor, introduce una respuesta valida ('s' para si, 'n' para no): ";
        cin >> respuestaIniciar;
        cout << "\n";
    }

    while (respuestaIniciar == 's') {

        int totalCartasJugador = 0;
        int totalCartasCroupier = 0;

        // se reparten dos cartas al jugador
        repartirCartaJugador(palos, totalCartasJugador);
        repartirCartaJugador(palos, totalCartasJugador);

        // la primera carta del croupier
        repartirCartaCroupier(palos, totalCartasCroupier);

        // para saber si el jugador quiere más cartas
        cout << "Tu puntuacion actual es: " << totalCartasJugador << "\n\n";
        char respuestaJugador;
        cout << "Quieres otra carta? (s/n): ";
        cin >> respuestaJugador;

        while (respuestaJugador != 's' && respuestaJugador != 'n') {
            cout << "Por favor, introduce una respuesta valida ('s' para si, 'n' para no): ";
            cin >> respuestaJugador;
            cout << "\n";
        }

        while (respuestaJugador == 's' && totalCartasJugador < 21) {
            repartirCartaJugador(palos, totalCartasJugador);

            if (totalCartasJugador < 21) {
                cout << "Quieres otra carta? (s/n): ";
                cin >> respuestaJugador;

                while (respuestaJugador != 's' && respuestaJugador != 'n') {
                    cout << "Por favor, introduce una respuesta valida ('s' para si, 'n' para no): ";
                    cin >> respuestaJugador;
                    cout << "\n";
                }
            }
        }

        // el resto de carttas el croupier
        cout << "\nTurno del croupier:\n";
        while (totalCartasCroupier < 17) {
            repartirCartaCroupier(palos, totalCartasCroupier);
        }

        // resultados
        cout << "\nResultados:\n";
        cout << "Tu puntuacion: " << totalCartasJugador << "\n";
        cout << "Puntuacion del croupier: " << totalCartasCroupier << "\n";

        // para enseñar si el jugador gana o pierde del juego, también existe empate
        if (totalCartasJugador > 21 || (totalCartasCroupier <= 21 && totalCartasCroupier > totalCartasJugador)) {
            cout << "Has perdido!\n\n";
        }
        else if (totalCartasCroupier > 21 || (totalCartasJugador <= 21 && totalCartasJugador > totalCartasCroupier)) {
            cout << "Has ganado!\n\n";
        }
        else {
            cout << "Empate. Gana el croupier.\n\n";
        }

        // para saber si el jugador quiere iniciar otra partida
        cout << "Quieres jugar de nuevo? (s/n): ";
        cin >> respuestaIniciar;
        cout << "\n";

        while (respuestaIniciar != 's' && respuestaIniciar != 'n') {
            cout << "Por favor, introduce una respuesta valida ('s' para si, 'n' para no): ";
            cin >> respuestaIniciar;
            cout << "\n";
        }

        cout << "_________________________________";
        cout << "\n\n";

    }

    cout << "Hasta luego! Gracias por jugar.\n";

    return 0;
}
