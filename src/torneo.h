#ifndef TORNEO_H
#define TORNEO_H

#include <string>

#include "grupo.h"
#include "jugador.h"
#include "tablaposiciones.h"

using namespace std;

class Torneo {
public:
    Torneo();
    ~Torneo();

    void preparar();
    void iniciargrupos(int cantidad);
    bool registrargrupobase(int indice, string nombregrupo);
    bool cargarequipotabla(int fila, string nombreequipo);
    bool cargarequipobase(int indice, string nombreequipo);
    bool cargarjugadorbase(jugador nuevojugador);
    int getequiposcargados() const;
    int getcantidadjugadores() const;
    int getcantidadgrupos() const;

private:
    string nombretorneo;
    grupo* grupos;
    int cantidadgrupos;
    tablaposiciones* tabla;
    int cantidadfilastabla;
    int equiposcargados;
    jugador* jugadoresbase;
    int cantidadjugadores;
    int capacidadjugadores;
};

#endif // TORNEO_H
