#include "DogRace.h"
#include "Dog.h" // Incluir el encabezado de Dog.h

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// instrucciones iniciales
void mostrarInstrucciones() {
    cout << "Bienvenido a GoodBoy Race, la carrera definitiva de tus perritos favoritos!\n";
    cout << "En este juego competiras contra Rocky para ver quien recorre mas distancia en 5 turnos.\n";
    cout << "Cada turno, lanzaras un dado para aumentar tu velocidad y podras usar una chuche para acelerar.\n";
    cout << "Pero cuidado, puede que la chuche no te siente bien!\n";
    cout << "Buena suerte y disfruta de la carrera!\n\n";
}

// uso el thread sleep para hacer una cuenta atrás
void cuentaRegresiva() {
    cout << "La carrera comenzara en 3 segundos!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Anima a tu corredor, necesita mucha energia!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "2!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "1!\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Comienza la carrera!\n\n";
}

// turno del jugador
void turnoJugador(Dog& pDog) {
    cout << "\n\nEs tu turno, " << pDog.getNombre() << "!\n";
    cout << "Presiona Enter para lanzar el dado...\n";

    char input; // para lanzar al dado se debe presionar enter
    cin.get();
    cin.get(); 

    pDog.lanzarDado();

    string respuesta;
    if (pDog.getChuches() > 0) {
        cout << "Quieres usar una chuche? (s/n): ";
        cin >> respuesta;

        while (respuesta != "s" && respuesta != "n") { // el usuario solo puede contestar s o n
            cout << "\nError, respuesta no valida. Responde con 's' o 'n': ";
            cin >> respuesta;
        }
        if (respuesta == "s") {
            pDog.usarChuche();
        }
    }
    else {
        cout << "\nNo tienes chuches disponibles para usar!" << endl;
        this_thread::sleep_for(chrono::seconds(2)); // para que se espere 2 segundos antes de iniciar el turno del pc
    }
    cout << "";
}



// turno del pc
void turnoAutomatico(Dog& pDog) {
    cout << "\n\nTurno de " << pDog.getNombre() << "!\n" << endl;
    this_thread::sleep_for(chrono::seconds(2)); // se espera dos segundos antes de llamar a la función del dado

    pDog.lanzarDado();
    this_thread::sleep_for(chrono::seconds(1));

    if (pDog.getChuches() > 0 && rand() % 2 == 0) { // se usará la chuche una sola vez por partida
        pDog.usarChuche();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "";
}

// juego
void iniciarJuego() {

    mostrarInstrucciones();

    this_thread::sleep_for(chrono::seconds(7)); // espera de 7 segundos para q de tiempo a leer las instrucciones

    cuentaRegresiva(); // la cuenta atrás de 3 segundos

    string nombrepDogUsuario;
    cout << "\nCual es el nombre de tu perro? "; // para saber el nombre del perro del usuario
    cin >> nombrepDogUsuario; 

    cout << "";

    // usuario y pc con sus respectivos nombres
    Dog jugador(nombrepDogUsuario);
    Dog pc("Rocky");

    // bucle para que haya 5 rondas
    for (int turno = 1; turno <= 5; turno++) {
        cout << "\n\nTurno " << turno;

        cout << "";

        turnoJugador(jugador);
        turnoAutomatico(pc);

        // se calcula la distancia de los dos perros en cada ronda
        jugador.calcularDistancia();
        pc.calcularDistancia();

        // y aquí para mostrar la distancia calculada
        this_thread::sleep_for(chrono::seconds(2));
        cout << "\n\nDistancia recorrida por " << jugador.getNombre() << ": " << jugador.getDistanciaRecorrida() << " metros.\n";
        cout << "\nDistancia recorrida por " << pc.getNombre() << ": " << pc.getDistanciaRecorrida() << " metros.\n";
    }

    // ganar, perder o empate
    if (jugador.getDistanciaRecorrida() > pc.getDistanciaRecorrida()) {
        cout << "\nFelicidades! " << jugador.getNombre() << " ha ganado la carrera!\n";
    }
    else if (jugador.getDistanciaRecorrida() < pc.getDistanciaRecorrida()) {
        cout << "\nLo siento! " << pc.getNombre() << " ha ganado la carrera!\n";
    }
    else {
        cout << "\nHa habido un empate!\n";
    }

    // menú para saber si el usuario desea jugar de nuevo o no
    int opcion;
    bool opcionValida = false;
    char input;

    while (!opcionValida) {
        cout << "\nQue quieres hacer?\n";
        cout << "1 - Jugar de nuevo\n";
        cout << "2 - Salir\n";
        cout << "Elige una opcion (1 o 2): ";

        cin >> input;

        if (input == '1' || input == '2') {
            opcionValida = true;
        }
        else {
            cout << "\nRespuesta no valida. Elige 1 para jugar de nuevo o 2 para salir.\n";
            cin.clear(); // para resetear cualquier error que haya salido en el input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // se usa para que el programa no pete si, por ejemplo, el usuario introduce una letra en vez de un números. numeric_limits<streamsize>::max() -> esto se encarga de poner un número de carácteres máximo a ignorar, al poner max, estás diciéndole al cin que no hay límite. '\n' -> actúa de delimitador
        }
    }

    switch (input) {
    case '1':
        cout << "\nBuena suerte!\n\n";
        iniciarJuego(); // se inicia el juego nuevamente
        break;
    case '2':
        cout << "\nGracias por jugar. Hasta luego!\n"; // salir
        break;
    default:
        break;
    }
}
