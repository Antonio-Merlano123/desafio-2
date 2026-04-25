#ifndef TORNEO_H
#define TORNEO_H

#include <string>

#include "grupo.h"
#include "jugador.h"
#include "partido.h"
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
    bool cargarequipobase(int indice, string nombreequipo, string confederacion, int ranking);
    bool cargarjugadorbase(jugador nuevojugador);
    bool armargruposporranking();
    bool generarcalendariogrupos();
    void mostrargrupos() const;
    void mostrarcalendariogrupos() const;
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
    string* equiposbase;
    string* confederacionesbase;
    int* rankingsbase;
    int cantidadequiposbase;
    partido* partidosgrupos;
    int* diapartidosgrupos;
    int cantidadpartidosgrupos;
    int capacidadpartidosgrupos;

    void ordenarporelranking(int indices[], int total) const;
    int buscarhost(int indices[], int total) const;
    int buscarindiceequipo(string nombreequipo) const;
    void barajarbombo(int bombo[], int inicio) const;
    bool intentarsorteo(int bombos[4][12]);
    bool generarcalendarioconlimite(int maxpartidospordia, int descansominimo);
};

#endif // TORNEO_H
