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

    cout << "equipos base cargados: " << cargados << endl;
    sim.probar();
    med.mostrar();
}

