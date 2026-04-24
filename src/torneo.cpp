#include "torneo.h"

#include <iostream>

using namespace std;

Torneo::Torneo() {
    nombretorneo = "UdeAWorldCup";
    grupos = 0;
    cantidadgrupos = 0;
    tabla = 0;
    cantidadfilastabla = 0;
    equiposcargados = 0;
}

Torneo::~Torneo() {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }
}

void Torneo::preparar() {
    iniciargrupos(12);

    // Esto deja una primera estructura para ir llenando grupos despues.
    for (int i = 0; i < cantidadgrupos; i = i + 1) {
        string nombregrupo = "grupo ";
        char letra = char('a' + i);
        nombregrupo = nombregrupo + letra;
        registrargrupobase(i, nombregrupo);
    }

    cout << "torneo base listo: " << nombretorneo << endl;
}

void Torneo::iniciargrupos(int cantidad) {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }

    int cantidadfinal = cantidad;
    if (cantidadfinal < 0) {
        cantidadfinal = 0;
    }

    cantidadgrupos = cantidadfinal;
    grupos = new grupo[cantidadgrupos];

    cantidadfilastabla = cantidadgrupos * 4;
    tabla = new tablaposiciones[cantidadfilastabla];
    equiposcargados = 0;
}

bool Torneo::registrargrupobase(int indice, string nombregrupo) {
    if (indice < 0) {
        return false;
    } else {
        if (indice >= cantidadgrupos) {
            return false;
        }
    }

    grupos[indice].setnombre(nombregrupo);
    return true;
}

bool Torneo::cargarequipotabla(int fila, string nombreequipo) {
    if (fila < 0) {
        return false;
    }

    if (fila >= cantidadfilastabla) {
        return false;
    }

    tabla[fila].cargarequipo(nombreequipo);
    return true;
}

bool Torneo::cargarequipobase(int indice, string nombreequipo) {
    if (indice < 0) {
        return false;
    }

    if (indice >= cantidadfilastabla) {
        return false;
    }

    bool okfila = cargarequipotabla(indice, nombreequipo);
    if (okfila == false) {
        return false;
    }

    int grupodestino = indice / 4;
    if (grupodestino < 0) {
        return false;
    }

    if (grupodestino >= cantidadgrupos) {
        return false;
    }

    bool okgrupo = grupos[grupodestino].agregarequipo(nombreequipo);
    if (okgrupo == false) {
        return false;
    }

    if (equiposcargados < indice + 1) {
        equiposcargados = indice + 1;
    }

    return true;
}

int Torneo::getequiposcargados() const {
    return equiposcargados;
}

int Torneo::getcantidadgrupos() const {
    return cantidadgrupos;
}
