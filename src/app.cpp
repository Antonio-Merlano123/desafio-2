#include "app.h"

#include <iostream>

// los cuatro modulos que arme para el proyecto
#include "repositorio.h"  // lee el csv
#include "torneo.h"        // hace todo el torneo
#include "medidor.h"       // metricas de iteraciones y memoria
#include "simulador.h"     // prueba del calculo de lambda

using namespace std;

App::App() {
    // nada que inicializar aqui
}

// desde aqui corre todo el programa
void App::iniciar() {
    cout << "UdeAWorldCup" << endl;

    Repositorio repo;   // lee los 48 equipos del csv
    Torneo torneo;      // motor del torneo: sorteo, partidos, informe
    Simulador sim;      // prueba aislada del lambda
    Medidor med;        // imprime las metricas al final

    repo.cargarBase();  // primero el csv, si esto falla no hay nada que simular

    torneo.preparar();  // crea los 12 grupos vacios

    // paso los equipos del repositorio al torneo uno por uno
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

    // sorteo de grupos: bombos por ranking, sede siempre en bombo 1
    bool gruposok = torneo.armargruposporranking();
    bool calendariook = false;
    bool simgruposok = false;

    if (gruposok) {
        calendariook = torneo.generarcalendariogrupos();
    }

    // cargo los jugadores: el repo arma plantillas de 15 por equipo automaticamente
    int totaljugadores = repo.getcantidadjugadores();
    int jugadorescargados = 0;

    for (int i = 0; i < totaljugadores; i = i + 1) {
        jugador actual = repo.getjugador(i);
        bool ok = torneo.cargarjugadorbase(actual);
        if (ok) {
            jugadorescargados = jugadorescargados + 1;
        }
    }

    // muestro resumen de lo que se cargo
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

    // si todo esta listo, ejecuto el torneo completo
    if (calendariook && jugadorescargados > 0) {

        torneo.mostraronceprueba();  // muestra los titulares del primer partido como prueba

        // 72 partidos de grupos, con lambda + Poisson por partido
        simgruposok = torneo.simularfasegrupos(repo);
        cout << "simulacion grupos: " << (simgruposok ? "ok" : "fallo") << endl;

        if (simgruposok) {
            torneo.mostrarresultadosfasegrupos();
            torneo.mostrartablagrupos();

            // 12 primeros + 12 segundos + 8 mejores terceros = 32 clasificados
            torneo.clasificargrupos();
            torneo.mostrarclasificados();

            // armo el bracket, sin cruzar equipos del mismo grupo
            torneo.armardieciseisavos();
            torneo.mostrardieciseisavos();

            // metricas de funcionalidad II
            size_t memoriafunc2 = sizeof(repo) + torneo.estimarmemoriaactual();
            med.mostrarfuncionalidad("II - conformacion grupos y transicion",
                                     torneo.estimariteracionesfuncionalidadII(),
                                     memoriafunc2);

            // ahora las rondas eliminatorias hasta el campeon
            bool finalok = torneo.simularfasesfinales(repo);
            cout << "simulacion eliminatorias: " << (finalok ? "ok" : "fallo") << endl;

            if (finalok) {
                torneo.mostrarfasesfinales();

                // metricas de funcionalidad III
                size_t memoriafunc3 = sizeof(repo) + torneo.estimarmemoriaactual();
                med.mostrarfuncionalidad("III - simulacion eliminatorias",
                                         torneo.estimariteracionesfuncionalidadIII(),
                                         memoriafunc3);

                // informe final: top4, goleadores, confederaciones dominantes
                torneo.mostrarinformeestadisticas(repo);

                bool okguardado = torneo.guardarhistoricoactualizado(repo);
                cout << "actualizacion historica persistente: " << (okguardado ? "ok" : "fallo") << endl;

                // metricas de funcionalidad IV
                size_t memoriafunc4 = sizeof(repo) + torneo.estimarmemoriaactual();
                med.mostrarfuncionalidad("IV - informe estadistico final",
                                         torneo.estimariteracionesfuncionalidadIV(),
                                         memoriafunc4);
            }
        }
    }

    sim.probar(repo);  // prueba del simulador con los 2 primeros equipos del csv

    med.mostrar();
}

