#include "torneo.h"

#include <iostream>

using namespace std;

Torneo::Torneo() {
    nombretorneo = "UdeAWorldCup";
    grupos = 0;
    cantidadgrupos = 0;
    tabla = 0;
    cantidadfilastabla = 0;
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
}

bool Torneo::registrargrupobase(int indice, string nombregrupo) {
    bool indicevalido = true;

    if (indice < 0) {
        indicevalido = false;
    }

    if (indice >= cantidadgrupos) {
        indicevalido = false;
    }

    if (indicevalido == false) {
        return false;
    }

    grupos[indice].setnombre(nombregrupo);
    return true;
}

bool Torneo::cargarequipotabla(int fila, string nombreequipo) {
    bool filavalida = true;

    if (fila < 0) {
        filavalida = false;
    }

    if (fila >= cantidadfilastabla) {
        filavalida = false;
    }

    if (filavalida == false) {
        return false;
    }

    tabla[fila].cargarequipo(nombreequipo);
    return true;
}

int Torneo::getcantidadgrupos() const {
    return cantidadgrupos;
}
