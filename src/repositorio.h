#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <string>
#include <fstream>

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
    int getgolesfavorhistoricototal(int indice) const {
        if (indice < 0 || indice >= cantidadequipos) {
            return 0;
        }
        return golesfavorhistoricototalcsv[indice];
    }

    int getgolescontrahistoricototal(int indice) const {
        if (indice < 0 || indice >= cantidadequipos) {
            return 0;
        }
        return golescontrahistoricototalcsv[indice];
    }
    double getgolesfavorhistorico(int indice) const;
    double getgolescontrahistorico(int indice) const;
    jugador getjugador(int indice) const;
    bool guardarequiposhistoricoactualizado(const int golesfavoractualizados[], const int golescontraactualizados[], int cantidad, string ruta) const {
        if (golesfavoractualizados == 0 || golescontraactualizados == 0) {
            return false;
        }

        ofstream salida(ruta.c_str());
        if (salida.is_open() == false) {
            return false;
        }

        salida << "equipo;confederacion;ranking;goles_favor_historico_actualizado;goles_contra_historico_actualizado" << endl;

        int limite = cantidad;
        if (limite > cantidadequipos) {
            limite = cantidadequipos;
        }

        for (int i = 0; i < limite; i = i + 1) {
            salida << equiposcsv[i] << ";"
                   << confederacionescsv[i] << ";"
                   << rankingscsv[i] << ";"
                   << golesfavoractualizados[i] << ";"
                   << golescontraactualizados[i] << endl;
        }

        salida.close();
        return true;
    }

    bool guardarjugadoreshistoricoactualizado(const jugador jugadores[], int cantidad, string ruta) const {
        if (jugadores == 0 || cantidad <= 0) {
            return false;
        }

        ofstream salida(ruta.c_str());
        if (salida.is_open() == false) {
            return false;
        }

        salida << "equipo;camiseta;nombre;posicion;goles;asistencias;amarillas;rojas;faltas;minutos;partidos" << endl;

        for (int i = 0; i < cantidad; i = i + 1) {
            salida << jugadores[i].getequipo() << ";"
                   << jugadores[i].getcamiseta() << ";"
                   << jugadores[i].getnombre() << ";"
                   << jugadores[i].getposicion() << ";"
                   << jugadores[i].getgoles() << ";"
                   << jugadores[i].getasistencias() << ";"
                   << jugadores[i].getamarillas() << ";"
                   << jugadores[i].getrojas() << ";"
                   << jugadores[i].getfaltas() << ";"
                   << jugadores[i].getminutosjugados() << ";"
                   << jugadores[i].getpartidos() << endl;
        }

        salida.close();
        return true;
    }

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
    int golesfavorhistoricototalcsv[maxequipos];
    int golescontrahistoricototalcsv[maxequipos];
    double golesfavorhistorico[maxequipos];
    double golescontrahistorico[maxequipos];
    int inicioplantillas[maxequipos];
    int cantidadplantillas[maxequipos];
    jugador jugadorescsv[maxjugadores];
};

#endif // REPOSITORIO_H
