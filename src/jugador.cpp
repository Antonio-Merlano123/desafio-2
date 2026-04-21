#include "jugador.h"

jugador::jugador() {
    nombre = "sin nombre";
    equipo = "sin equipo";
    posicion = "delantero";
    goles = 0;
    asistencias = 0;
    partidos = 0;
}

jugador::jugador(string nombreinicial, string equipoinicial, string posicioninicial) {
    nombre = nombreinicial;
    equipo = equipoinicial;
    posicion = posicioninicial;
    goles = 0;
    asistencias = 0;
    partidos = 0;
}

string jugador::getnombre() const {
    return nombre;
}

string jugador::getequipo() const {
    return equipo;
}

string jugador::getposicion() const {
    return posicion;
}

int jugador::getgoles() const {
    return goles;
}

int jugador::getasistencias() const {
    return asistencias;
}

int jugador::getpartidos() const {
    return partidos;
}

void jugador::setnombre(string nuevonombre) {
    nombre = nuevonombre;
}

void jugador::setequipo(string nuevoequipo) {
    equipo = nuevoequipo;
}

void jugador::setposicion(string nuevaposicion) {
    posicion = nuevaposicion;
}

void jugador::agregargol() {
    goles = goles + 1;
}

void jugador::agregarasistencia() {
    asistencias = asistencias + 1;
}

void jugador::agregarpartido() {
    partidos = partidos + 1;
}
