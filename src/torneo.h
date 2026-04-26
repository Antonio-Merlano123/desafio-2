#ifndef TORNEO_H
#define TORNEO_H

#include <string>

#include "grupo.h"
#include "jugador.h"
#include "partido.h"
#include "tablaposiciones.h"

using namespace std;

class Repositorio;

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
    bool elegironceinicial(string nombreequipo, jugador once[11]) const;
    bool simularfasegrupos(const Repositorio& repo);
    void clasificargrupos();
    void armardieciseisavos();
    bool simularfasesfinales(const Repositorio& repo);
    void mostrargrupos() const;
    void mostrarcalendariogrupos() const;
    void mostraronceprueba() const;
    void mostrartablagrupos() const;
    void mostrarclasificados() const;
    void mostrardieciseisavos() const;
    void mostrarfasesfinales() const;
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

    string clasificados1[12];
    string clasificados2[12];
    string clasificados3[8];
    int grupoindterceros[8];
    int cantclasificados1;
    int cantclasificados2;
    int cantclasificados3;

    partido* partidosdieciseisavos;
    int cantdieciseisavos;
    partido* partidosoctavos;
    int cantoctavos;
    partido* partidoscuartos;
    int cantcuartos;
    partido* partidossemis;
    int cantsemis;
    partido partidofinal;
    partido partidotercero;
    string equipocampeon;
    string equiposubcampeon;
    string equipotercero;
    string equipocuarto;
    bool finalessimuladas;

    void ordenarporelranking(int indices[], int total) const;
    int buscarhost(int indices[], int total) const;
    int buscarindiceequipo(string nombreequipo) const;
    int buscarfilatabla(string nombreequipo) const;
    int buscarindiceequiporepo(const Repositorio& repo, string nombreequipo) const;
    int buscarjugadoresdelequipo(string nombreequipo, int indices[], int maxindices) const;
    double calcularlambdapartido(double golesfavora, double golescontrab) const;
    int redondeargolespartido(double lambda) const;
    void ordenarfilasgrupo(int filas[4]) const;
    void barajarbombo(int bombo[], int inicio) const;
    bool intentarsorteo(int bombos[4][12]);
    bool generarcalendarioconlimite(int maxpartidospordia, int descansominimo);
};

#endif // TORNEO_H
