#include "app.h"

#include <iostream>

#include "repositorio.h"
#include "torneo.h"
#include "medidor.h"
#include "simulador.h"

using namespace std;

App::App() {
}

void App::iniciar() {
    cout << "UdeAWorldCup" << endl;

    Repositorio repo;
    Torneo torneo;
    Simulador sim;
    Medidor med;

    repo.cargarBase();
    torneo.preparar();

    int totalbase = repo.getcantidadequipos();
    int cargados = 0;

    for (int i = 0; i < totalbase; i = i + 1) {
        string nombre = repo.getequipo(i);
        bool ok = torneo.cargarequipobase(i, nombre);
        if (ok) {
            cargados = cargados + 1;
        }
    }

    int totaljugadores = repo.getcantidadjugadores();
    int jugadorescargados = 0;

    for (int i = 0; i < totaljugadores; i = i + 1) {
        jugador actual = repo.getjugador(i);
        bool ok = torneo.cargarjugadorbase(actual);
        if (ok) {
            jugadorescargados = jugadorescargados + 1;
        }
    }

    cout << "equipos base cargados: " << cargados << endl;
    cout << "jugadores base cargados: " << jugadorescargados << endl;
    sim.probar();
    med.mostrar();
}

