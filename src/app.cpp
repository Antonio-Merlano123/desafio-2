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
    sim.probar();
    med.mostrar();
}

