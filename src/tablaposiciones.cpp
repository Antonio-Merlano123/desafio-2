#include "tablaposiciones.h"

tablaposiciones::tablaposiciones() {
    nombre = "";
    puntos = 0;
    golesfavor = 0;
    golescontra = 0;
    partidos = 0;
}

void tablaposiciones::cargarequipo(string nombreequipo) {
    nombre = nombreequipo;
    puntos = 0;
    golesfavor = 0;
    golescontra = 0;
    partidos = 0;
}

string tablaposiciones::getnombre() const {
    return nombre;
}

void tablaposiciones::sumarganado() {
    int puntosactuales = puntos;
    int partidosactuales = partidos;

    puntos = puntosactuales + 3;
    partidos = partidosactuales + 1;
}

void tablaposiciones::sumarempate() {
    int puntosactuales = puntos;
    int partidosactuales = partidos;

    puntos = puntosactuales + 1;
    partidos = partidosactuales + 1;
}

void tablaposiciones::sumargoles(int afavor, int encontra) {
    int favoractual = golesfavor;
    int contraactual = golescontra;

    golesfavor = favoractual + afavor;
    golescontra = contraactual + encontra;
}

int tablaposiciones::getpuntos() const {
    return puntos;
}

int tablaposiciones::getgolesfavor() const {
    return golesfavor;
}

int tablaposiciones::getgolescontra() const {
    return golescontra;
}

int tablaposiciones::getpartidos() const {
    return partidos;
}

int tablaposiciones::getdiferencia() const {
    int diferencia = golesfavor - golescontra;
    return diferencia;
}
