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
        string confederacion = repo.getconfederacion(i);
        int ranking = repo.getranking(i);
        bool ok = torneo.cargarequipobase(i, nombre, confederacion, ranking);
        if (ok) {
            cargados = cargados + 1;
        }
    }

    bool gruposok = torneo.armargruposporranking();
    bool calendariook = false;
    bool simgruposok = false;
    if (gruposok) {
        calendariook = torneo.generarcalendariogrupos();
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
    cout << "sorteo de grupos: " << (gruposok ? "ok" : "fallo") << endl;
    if (gruposok) {
        torneo.mostrargrupos();
    }
    cout << "calendario grupos: " << (calendariook ? "ok" : "fallo") << endl;
    if (calendariook) {
        torneo.mostrarcalendariogrupos();
    }
    cout << "jugadores base cargados: " << jugadorescargados << endl;
    if (calendariook && jugadorescargados > 0) {
        torneo.mostraronceprueba();

        simgruposok = torneo.simularfasegrupos(repo);
        cout << "simulacion grupos: " << (simgruposok ? "ok" : "fallo") << endl;
        if (simgruposok) {
            torneo.mostrartablagrupos();
            torneo.clasificargrupos();
            torneo.mostrarclasificados();
        }
    }
    sim.probar(repo);
    med.mostrar();
}

