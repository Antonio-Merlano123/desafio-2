#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <string>

#include "jugador.h"

using namespace std;

class Repositorio {
public:
    // lee csv y deja datos base listos
    Repositorio();
    void cargarBase();

    bool leercsvequipos(string ruta);
    int getfilascsv() const;
    int getcolumnascsv() const;
    int getcantidadequipos() const;
    int getcantidadjugadores() const;
    string getequipo(int indice) const;
    string getconfederacion(int indice) const;
    int getranking(int indice) const;
    double getgolesfavorhistorico(int indice) const;
    double getgolescontrahistorico(int indice) const;
    jugador getjugador(int indice) const;

private:
    // limites del almacenamiento estatico
    static const int maxequipos = 64;
    static const int maxjugadoresporequipo = 15;
    static const int maxjugadores = maxequipos * maxjugadoresporequipo;

    void armarplantillasbase();
    bool agregarjugadorbase(int indiceequipo, string nombrejugador, string posicion);
    void repartirgolesbase(int indiceequipo, int golesbase);
    int calculargolesbase(int ranking) const;

    int filascsv;
    int columnascsv;
    int cantidadequipos;
    int cantidadjugadores;

    string rutacsv;
    string equiposcsv[maxequipos];
    string confederacionescsv[maxequipos];
    int rankingscsv[maxequipos];
    double golesfavorhistorico[maxequipos];
    double golescontrahistorico[maxequipos];
    int inicioplantillas[maxequipos];
    int cantidadplantillas[maxequipos];
    jugador jugadorescsv[maxjugadores];
};

#endif // REPOSITORIO_H
